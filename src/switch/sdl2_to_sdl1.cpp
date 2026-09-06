#ifdef USE_SDL2
#include <SDL.h>
#include <SDL_ttf.h>
#include <switch.h>
#include <sdl2_to_sdl1.h>

static SDL_Window* window = NULL;
static SDL_Texture* texture = NULL;
static SDL_Texture* prescaled = NULL;
static SDL_Renderer* renderer = NULL;
static int prescaled_width = 320;
static int prescaled_height = 240;
static int surface_width = 320;
static int surface_height = 240;

static int currently_docked = -1;

static int x_offset;
static int y_offset;
static int scaled_height;
static int scaled_width;
static int display_width;
static int display_height;

extern int mainMenu_shader;
extern int mainMenu_displayedLines;
extern int mainMenu_displayHires;
extern int visibleAreaWidth;
extern int displaying_menu;
extern int mainMenu_screenOffsetX;
extern int mainMenu_screenOffsetY;
extern int mainMenu_autoCrop;
extern int presetModeId;

extern void update_joycon_mode(void);

#define MIN(a,b) ((a) < (b) ? (a) : (b))

typedef struct {
    int active_left;
    int active_top;
    int active_right;
    int active_bottom;
    int stable_left;
    int stable_top;
    int stable_right;
    int stable_bottom;
    int shrink_hold_frames;
    int last_surface_w;
    int last_surface_h;
} SwitchCropState;

static SwitchCropState s_crop = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void switch_reset_autocrop(void) {
    s_crop.last_surface_w = 0;
    s_crop.last_surface_h = 0;
    s_crop.shrink_hold_frames = 0;
}

static inline bool is_border_pixel(Uint16 pix, Uint16 border_col) {
    if (pix == border_col || pix == 0) return true;
    Uint32 r = (pix >> 11) & 0x1F;
    Uint32 g = (pix >> 5) & 0x3F;
    Uint32 b = pix & 0x1F;
    return (r <= 1 && g <= 2 && b <= 1);
}

static void auto_crop_detect(SDL_Surface *surface, SDL_Rect *out_src_rect) {
    if (!surface || !surface->pixels) {
        out_src_rect->x = 0;
        out_src_rect->y = 0;
        out_src_rect->w = surface ? surface->w : 320;
        out_src_rect->h = surface ? surface->h : 240;
        return;
    }

    int w = surface->w;
    int h = surface->h;

    if (mainMenu_autoCrop == 0) {
        out_src_rect->x = 0;
        out_src_rect->y = 0;
        out_src_rect->w = w;
        out_src_rect->h = h;
        return;
    }

    if (s_crop.last_surface_w != w || s_crop.last_surface_h != h) {
        s_crop.last_surface_w = w;
        s_crop.last_surface_h = h;
        s_crop.stable_left = 0;
        s_crop.stable_top = 0;
        s_crop.stable_right = w - 1;
        s_crop.stable_bottom = h - 1;
        s_crop.shrink_hold_frames = 0;
    }

    Uint16 *pixels = (Uint16 *)surface->pixels;
    int pitch_words = surface->pitch / (int)sizeof(Uint16);
    Uint16 border_color = pixels[0];

    int top_line = 0;
    int max_top_scan = (h * 2) / 5;
    for (int y = 0; y < max_top_scan; y++) {
        int non_border = 0;
        Uint16 *row = pixels + y * pitch_words;
        for (int x = 4; x < w - 4; x += 2) {
            if (!is_border_pixel(row[x], border_color)) {
                non_border++;
                if (non_border >= 3) break;
            }
        }
        if (non_border >= 3) {
            top_line = y;
            break;
        }
    }

    int bottom_line = h - 1;
    int min_bottom_scan = (h * 3) / 5;
    for (int y = h - 1; y >= min_bottom_scan; y--) {
        int non_border = 0;
        Uint16 *row = pixels + y * pitch_words;
        for (int x = 4; x < w - 4; x += 2) {
            if (!is_border_pixel(row[x], border_color)) {
                non_border++;
                if (non_border >= 3) break;
            }
        }
        if (non_border >= 3) {
            bottom_line = y;
            break;
        }
    }

    int left_col = 0;
    int max_left_scan = (w * 2) / 5;
    for (int x = 0; x < max_left_scan; x++) {
        int non_border = 0;
        for (int y = top_line; y <= bottom_line; y += 4) {
            Uint16 pix = pixels[y * pitch_words + x];
            if (!is_border_pixel(pix, border_color)) {
                non_border++;
                if (non_border >= 2) break;
            }
        }
        if (non_border >= 2) {
            left_col = x;
            break;
        }
    }

    int right_col = w - 1;
    int min_right_scan = (w * 3) / 5;
    for (int x = w - 1; x >= min_right_scan; x--) {
        int non_border = 0;
        for (int y = top_line; y <= bottom_line; y += 4) {
            Uint16 pix = pixels[y * pitch_words + x];
            if (!is_border_pixel(pix, border_color)) {
                non_border++;
                if (non_border >= 2) break;
            }
        }
        if (non_border >= 2) {
            right_col = x;
            break;
        }
    }

    if (top_line < bottom_line && left_col < right_col) {
        int min_w = (w * 7) / 10;
        int min_h = (h * 7) / 10;

        int det_w = right_col - left_col + 1;
        int det_h = bottom_line - top_line + 1;

        if (det_w < min_w) {
            int pad = (min_w - det_w) / 2;
            left_col -= pad;
            right_col += pad;
        }
        if (det_h < min_h) {
            int pad = (min_h - det_h) / 2;
            top_line -= pad;
            bottom_line += pad;
        }

        if (left_col < 0) left_col = 0;
        if (right_col >= w) right_col = w - 1;
        if (top_line < 0) top_line = 0;
        if (bottom_line >= h) bottom_line = h - 1;

        if (left_col < s_crop.stable_left) s_crop.stable_left = left_col;
        if (right_col > s_crop.stable_right) s_crop.stable_right = right_col;
        if (top_line < s_crop.stable_top) s_crop.stable_top = top_line;
        if (bottom_line > s_crop.stable_bottom) s_crop.stable_bottom = bottom_line;

        bool is_smaller = (left_col > s_crop.stable_left ||
                           right_col < s_crop.stable_right ||
                           top_line > s_crop.stable_top ||
                           bottom_line < s_crop.stable_bottom);

        if (is_smaller) {
            s_crop.shrink_hold_frames++;
            if (s_crop.shrink_hold_frames > 60) {
                if (s_crop.stable_left < left_col) s_crop.stable_left++;
                if (s_crop.stable_right > right_col) s_crop.stable_right--;
                if (s_crop.stable_top < top_line) s_crop.stable_top++;
                if (s_crop.stable_bottom > bottom_line) s_crop.stable_bottom--;
            }
        } else {
            s_crop.shrink_hold_frames = 0;
        }
    }

    if (mainMenu_autoCrop == 1) {
        out_src_rect->x = s_crop.stable_left;
        out_src_rect->y = s_crop.stable_top;
        out_src_rect->w = s_crop.stable_right - s_crop.stable_left + 1;
        out_src_rect->h = s_crop.stable_bottom - s_crop.stable_top + 1;
    } else if (mainMenu_autoCrop == 2) {
        out_src_rect->x = 0;
        out_src_rect->y = s_crop.stable_top;
        out_src_rect->w = w;
        out_src_rect->h = s_crop.stable_bottom - s_crop.stable_top + 1;
    } else if (mainMenu_autoCrop == 3) {
        out_src_rect->x = s_crop.stable_left;
        out_src_rect->y = 0;
        out_src_rect->w = s_crop.stable_right - s_crop.stable_left + 1;
        out_src_rect->h = h;
    } else {
        out_src_rect->x = 0;
        out_src_rect->y = 0;
        out_src_rect->w = w;
        out_src_rect->h = h;
    }

    if (out_src_rect->w <= 0) out_src_rect->w = w;
    if (out_src_rect->h <= 0) out_src_rect->h = h;
}

int isDocked() {
	switch (appletGetOperationMode()) {
		case AppletOperationMode_Handheld:
			return 0;
			break;
		case AppletOperationMode_Console:
			return 1;
			break;
		default:
			return 0;
	}
}

void updateResolution() {
	int docked = isDocked();
	if ((docked && !currently_docked) || (!docked && currently_docked)) {
		if (docked) {
			display_width = 1920;
			display_height = 1080;
			currently_docked = 1;
		} else {
			display_width = 1280;
			display_height = 720;
			currently_docked = 0;
		}
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		SDL_SetWindowSize(window, display_width, display_height);
		SDL_SetVideoModeScaling(0, 0, 0, 0);
	}
}

SDL_Surface *SDL_SetVideoMode(int w, int h, int bpp, int flags) {
	if (currently_docked == -1) {
		if (isDocked()) {
			display_width = 1920;
			display_height = 1080;
			currently_docked = 1;
		} else {
			display_width = 1280;
			display_height = 720;
			currently_docked = 0;
		}
	}

	if (!renderer) {
		window = SDL_CreateWindow("uae4all2", 0, 0, display_width, display_height, 0);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
		SDL_RenderClear(renderer);
	}

	SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, w, h, 16, SDL_PIXELFORMAT_RGB565);
	surface_width = w;
	surface_height = h;
	return surface;
}

void SDL_SetVideoModeScaling(int x, int y, float sw, float sh) {
	if (!displaying_menu) {
		int aspect_variant = presetModeId % 10;
		bool is_fullscreen = (aspect_variant == 7);
		bool is_five_four = (aspect_variant == 8);

		if (mainMenu_shader == 0 && mainMenu_autoCrop == 0) {
			int screen_width = visibleAreaWidth;
			int screen_height = mainMenu_displayHires ? (2 * mainMenu_displayedLines) : mainMenu_displayedLines;
			if (screen_height <= 0) screen_height = 240;
			if (screen_width <= 0) screen_width = 320;
			int scale_factor = MIN(display_height / screen_height, display_width / screen_width);
			if (scale_factor < 1) scale_factor = 1;
			scaled_height = scale_factor * screen_height;
			scaled_width = scale_factor * screen_width;
		} else if (is_fullscreen) {
			scaled_width = display_width;
			scaled_height = display_height;
		} else if (is_five_four) {
			scaled_height = display_height;
			scaled_width = (display_height * 5) / 4;
		} else {
			scaled_height = display_height;
			scaled_width = (display_height * 4) / 3;
		}
		x_offset = (display_width - scaled_width) / 2;
		y_offset = (display_height - scaled_height) / 2;
		if (mainMenu_shader == 1) {
			int base_w = surface_width > 0 ? surface_width : 320;
			int base_h = surface_height > 0 ? surface_height : 240;
			int prescale_factor_x = scaled_width / base_w;
			int prescale_factor_y = scaled_height / base_h;
			if (prescale_factor_x < 1) prescale_factor_x = 1;
			if (prescale_factor_y < 1) prescale_factor_y = 1;
			prescaled_width = prescale_factor_x * base_w;
			prescaled_height = prescale_factor_y * base_h;
		}
	} else {
		if (!currently_docked) {
			prescaled_width = 1281;
			prescaled_height = 720;
			scaled_width = 1281;
			scaled_height = 720;
		} else {
			prescaled_width = 1708;
			prescaled_height = 960;
			scaled_width = display_width;
			scaled_height = display_height;
		}
		x_offset = 0;
		y_offset = 0;
	}
	if (prescaled) {
		SDL_DestroyTexture(prescaled);
		prescaled = NULL;
	}
	if (mainMenu_shader == 1 || displaying_menu) {
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		prescaled = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, prescaled_width, prescaled_height);
	}
}

void SDL_SetVideoModeBilinear(int value) {
	if (value && (mainMenu_shader != 3))
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	else
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
}

void SDL_SetVideoModeSync(int value) {
	if (1)
		SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
	else
		SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
}

void switch_get_game_viewport(int *x, int *y, int *w, int *h) {
	int eff_off_x = 0;
	int eff_off_y = 0;
	if (!displaying_menu) {
		eff_off_x = mainMenu_screenOffsetX;
		eff_off_y = mainMenu_screenOffsetY;
		if (isDocked() && display_width > 0 && display_height > 0) {
			eff_off_x = (mainMenu_screenOffsetX * display_width) / 1280;
			eff_off_y = (mainMenu_screenOffsetY * display_height) / 720;
		}
	}
	if (x) *x = x_offset + eff_off_x;
	if (y) *y = y_offset + eff_off_y;
	if (w) *w = scaled_width;
	if (h) *h = scaled_height;
}

static TTF_Font *s_osd_font = NULL;
static char s_osd_text[128] = {0};
static Uint32 s_osd_start_time = 0;
static Uint32 s_osd_duration = 0;
int switch_fast_forward = 0;
int switch_turbo_toggle = 0;

void switch_osd_show(const char *text, int duration_ms)
{
	if (!text || text[0] == '\0') return;
	strncpy(s_osd_text, text, sizeof(s_osd_text) - 1);
	s_osd_text[sizeof(s_osd_text) - 1] = '\0';
	s_osd_start_time = SDL_GetTicks();
	s_osd_duration = (Uint32)duration_ms;
}

static void switch_render_osd_overlays(SDL_Renderer *rend, int sw, int sh)
{
	if (!rend || displaying_menu) return;

	if (!s_osd_font) {
		TTF_Init();
		s_osd_font = TTF_OpenFont("./data/font.ttf", 20);
		if (!s_osd_font) s_osd_font = TTF_OpenFont("./font.ttf", 20);
	}

	if (switch_fast_forward) {
		SDL_Rect ff_rect = { sw - 160, 20, 140, 34 };
		SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(rend, 229, 37, 33, 230);
		SDL_RenderFillRect(rend, &ff_rect);
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		SDL_RenderDrawRect(rend, &ff_rect);

		if (s_osd_font) {
			SDL_Color col = { 255, 255, 255, 255 };
			SDL_Surface *ts = TTF_RenderUTF8_Blended(s_osd_font, ">> TURBO >>", col);
			if (ts) {
				SDL_Texture *tt = SDL_CreateTextureFromSurface(rend, ts);
				if (tt) {
					SDL_Rect tr = { ff_rect.x + (ff_rect.w - ts->w) / 2, ff_rect.y + (ff_rect.h - ts->h) / 2, ts->w, ts->h };
					SDL_RenderCopy(rend, tt, NULL, &tr);
					SDL_DestroyTexture(tt);
				}
				SDL_FreeSurface(ts);
			}
		}
	}

	if (s_osd_text[0] != '\0') {
		Uint32 now = SDL_GetTicks();
		if (now - s_osd_start_time < s_osd_duration) {
			int tw = 200, th = 24;
			if (s_osd_font) {
				TTF_SizeUTF8(s_osd_font, s_osd_text, &tw, &th);
			}
			int box_w = tw + 36;
			int box_h = th + 14;
			int box_x = (sw - box_w) / 2;
			int box_y = 20;

			SDL_Rect box_rect = { box_x, box_y, box_w, box_h };
			SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(rend, 18, 24, 38, 230);
			SDL_RenderFillRect(rend, &box_rect);
			SDL_SetRenderDrawColor(rend, 0, 136, 204, 255);
			SDL_RenderDrawRect(rend, &box_rect);

			if (s_osd_font) {
				SDL_Color col = { 255, 255, 255, 255 };
				SDL_Surface *ts = TTF_RenderUTF8_Blended(s_osd_font, s_osd_text, col);
				if (ts) {
					SDL_Texture *tt = SDL_CreateTextureFromSurface(rend, ts);
					if (tt) {
						SDL_Rect tr = { box_x + 18, box_y + 7, ts->w, ts->h };
						SDL_RenderCopy(rend, tt, NULL, &tr);
						SDL_DestroyTexture(tt);
					}
					SDL_FreeSurface(ts);
				}
			}
		} else {
			s_osd_text[0] = '\0';
		}
	}
}

void SDL_Flip(SDL_Surface *surface) {
	update_joycon_mode();
	if (surface && renderer && window) {
		updateResolution();
		if (texture) {
			SDL_DestroyTexture(texture);
			texture = NULL;
		}

		SDL_Rect src_rect;
		if (!displaying_menu && mainMenu_autoCrop != 0) {
			auto_crop_detect(surface, &src_rect);
		} else {
			src_rect.x = 0;
			src_rect.y = 0;
			src_rect.w = surface->w;
			src_rect.h = surface->h;
		}

		int eff_off_x = 0;
		int eff_off_y = 0;
		if (!displaying_menu) {
			eff_off_x = mainMenu_screenOffsetX;
			eff_off_y = mainMenu_screenOffsetY;
			if (isDocked() && display_width > 0 && display_height > 0) {
				eff_off_x = (mainMenu_screenOffsetX * display_width) / 1280;
				eff_off_y = (mainMenu_screenOffsetY * display_height) / 720;
			}
		}

		SDL_Rect dst_rect = { x_offset + eff_off_x, y_offset + eff_off_y, scaled_width, scaled_height };

		if (mainMenu_shader == 1 || displaying_menu) {
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
			texture = SDL_CreateTextureFromSurface(renderer, surface);
			
			SDL_SetRenderTarget(renderer, prescaled);
			SDL_Rect dst_rect_prescale = { 0, 0, prescaled_width, prescaled_height };
			SDL_RenderCopy(renderer, texture, displaying_menu ? NULL : &src_rect, &dst_rect_prescale);

			SDL_SetRenderTarget(renderer, NULL);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
			SDL_RenderCopy(renderer, prescaled, NULL, &dst_rect);
			switch_render_osd_overlays(renderer, display_width, display_height);
			SDL_RenderPresent(renderer);
		} else {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_RenderCopy(renderer, texture, displaying_menu ? NULL : &src_rect, &dst_rect);
			switch_render_osd_overlays(renderer, display_width, display_height);
			SDL_RenderPresent(renderer);
		}
	}
}
#endif