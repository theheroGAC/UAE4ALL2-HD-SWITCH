#ifdef __SWITCH__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "sysconfig.h"
#include "sysdeps.h"
#include "config.h"
#include "options.h"
#include "uae.h"
#include "sound.h"
#include "disk.h"
#include "memory-uae.h"
#include "custom.h"
#include "xwin.h"
#include "drawing.h"
#include "menu.h"
#include "menu_config.h"
#include "savestate.h"
#include "gui.h"
#include "cdrom.h"

#include "uae_gui_switch.h"
#include "switch_kbd.h"
#include <switch.h>



static void ttf_shutdown_cleanup(void);

extern int screenWidth;
extern int mainMenu_case;
extern int bReloadKickstart;
extern int oldkickstart;
extern int kickstart;
extern int emulating;
extern int inside_menu;
extern bool resetOnStartingApp;
extern char launchDir[300];
extern char currentDir[300];
extern char uae4all_image_file0[256];
extern char uae4all_image_file1[256];
extern char uae4all_image_file2[256];
extern char uae4all_image_file3[256];
extern char uae4all_hard_file0[256];
extern char uae4all_hard_file1[256];
extern char uae4all_hard_file2[256];
extern char uae4all_hard_file3[256];
extern char uae4all_hard_dir[256];
extern void setCpuSpeed(void);
extern int displaying_menu;
extern int kickstart_warning;

extern SDL_Surface *prSDLScreen;


static void switch_gui_free_screen(void)
{
    if (prSDLScreen == NULL)
        return;

    write_log("[SWITCH] switch_gui_free_screen: freeing %dx%d\n", prSDLScreen->w, prSDLScreen->h);
    
    SDL_FreeSurface(prSDLScreen);
    prSDLScreen = NULL;
    write_log("[SWITCH] switch_gui_free_screen: done\n");
}

static bool s_gui_initialized = false;
static float s_boing_angle = 0.0f;
static SwitchGuiTab s_active_tab = SWITCH_TAB_FLOPPY;
static int s_tab_selected_item[SWITCH_TAB_COUNT] = {0};
static int s_save_as_ime_active = 0;
static int s_save_as_ime_result = 0;
static char s_save_as_ime_name[100];
void switch_gui_save_as_started(void) { s_save_as_ime_active = 1; }
extern char *config_filename;
extern const char *config_save_as_name;
extern int buttonSelect[4];

static const unsigned char s_font_8x8[96][8] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    {0x18,0x3C,0x3C,0x18,0x18,0x00,0x18,0x00},
    {0x66,0x66,0x24,0x00,0x00,0x00,0x00,0x00},
    {0x6C,0x6C,0xFE,0x6C,0xFE,0x6C,0x6C,0x00},
    {0x18,0x7E,0x18,0x3C,0x66,0x3C,0x18,0x7E},
    {0x00,0xC6,0xCC,0x18,0x30,0x66,0xC6,0x00},
    {0x38,0x6C,0x38,0x76,0xDC,0xCC,0x76,0x00},
    {0x18,0x18,0x30,0x00,0x00,0x00,0x00,0x00},
    {0x0C,0x18,0x30,0x30,0x30,0x18,0x0C,0x00},
    {0x30,0x18,0x0C,0x0C,0x0C,0x18,0x30,0x00},
    {0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00},
    {0x00,0x18,0x18,0x7E,0x18,0x18,0x00,0x00},
    {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x30},
    {0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00},
    {0x06,0x0C,0x18,0x30,0x60,0xC0,0x80,0x00},
    {0x3C,0x66,0x6E,0x76,0x66,0x66,0x3C,0x00},
    {0x18,0x38,0x18,0x18,0x18,0x18,0x7E,0x00},
    {0x3C,0x66,0x06,0x0C,0x18,0x30,0x7E,0x00},
    {0x3C,0x66,0x06,0x1C,0x06,0x66,0x3C,0x00},
    {0x0C,0x1C,0x34,0x64,0x7E,0x0C,0x0C,0x00},
    {0x7E,0x60,0x7C,0x06,0x06,0x66,0x3C,0x00},
    {0x1C,0x30,0x60,0x7C,0x66,0x66,0x3C,0x00},
    {0x7E,0x06,0x0C,0x18,0x30,0x30,0x30,0x00},
    {0x3C,0x66,0x66,0x3C,0x66,0x66,0x3C,0x00},
    {0x3C,0x66,0x66,0x3E,0x06,0x0C,0x38,0x00},
    {0x00,0x18,0x18,0x00,0x18,0x18,0x00,0x00},
    {0x00,0x18,0x18,0x00,0x18,0x18,0x30,0x00},
    {0x0C,0x18,0x30,0x60,0x30,0x18,0x0C,0x00},
    {0x00,0x00,0x7E,0x00,0x7E,0x00,0x00,0x00},
    {0x30,0x18,0x0C,0x06,0x0C,0x18,0x30,0x00},
    {0x3C,0x66,0x06,0x0C,0x18,0x00,0x18,0x00},
    {0x3C,0x66,0x6E,0x6E,0x60,0x62,0x3C,0x00},
    {0x18,0x3C,0x66,0x66,0x7E,0x66,0x66,0x00},
    {0x7C,0x66,0x66,0x7C,0x66,0x66,0x7C,0x00},
    {0x3C,0x66,0x60,0x60,0x60,0x66,0x3C,0x00},
    {0x78,0x6C,0x66,0x66,0x66,0x6C,0x78,0x00},
    {0x7E,0x60,0x60,0x7C,0x60,0x60,0x7E,0x00},
    {0x7E,0x60,0x60,0x7C,0x60,0x60,0x60,0x00},
    {0x3C,0x66,0x60,0x6E,0x66,0x66,0x3C,0x00},
    {0x66,0x66,0x66,0x7E,0x66,0x66,0x66,0x00},
    {0x7E,0x18,0x18,0x18,0x18,0x18,0x7E,0x00},
    {0x06,0x06,0x06,0x06,0x06,0x66,0x3C,0x00},
    {0x66,0x6C,0x78,0x70,0x78,0x6C,0x66,0x00},
    {0x60,0x60,0x60,0x60,0x60,0x60,0x7E,0x00},
    {0x63,0x77,0x7F,0x6B,0x63,0x63,0x63,0x00},
    {0x66,0x76,0x7E,0x7E,0x6E,0x66,0x66,0x00},
    {0x3C,0x66,0x66,0x66,0x66,0x66,0x3C,0x00},
    {0x7C,0x66,0x66,0x7C,0x60,0x60,0x60,0x00},
    {0x3C,0x66,0x66,0x66,0x6E,0x3C,0x0E,0x00},
    {0x7C,0x66,0x66,0x7C,0x78,0x6C,0x66,0x00},
    {0x3C,0x66,0x60,0x3C,0x06,0x66,0x3C,0x00},
    {0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x00},
    {0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x00},
    {0x66,0x66,0x66,0x66,0x66,0x3C,0x18,0x00},
    {0x63,0x63,0x63,0x6B,0x7F,0x77,0x63,0x00},
    {0x66,0x66,0x3C,0x18,0x3C,0x66,0x66,0x00},
    {0x66,0x66,0x66,0x3C,0x18,0x18,0x18,0x00},
    {0x7E,0x06,0x0C,0x18,0x30,0x60,0x7E,0x00},
    {0x3C,0x30,0x30,0x30,0x30,0x30,0x3C,0x00},
    {0xC0,0x60,0x30,0x18,0x0C,0x06,0x02,0x00},
    {0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0x00},
    {0x18,0x3C,0x66,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00},
    {0x30,0x18,0x0C,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x3C,0x06,0x3E,0x66,0x3E,0x00},
    {0x60,0x60,0x7C,0x66,0x66,0x66,0x7C,0x00},
    {0x00,0x00,0x3C,0x66,0x60,0x66,0x3C,0x00},
    {0x06,0x06,0x3E,0x66,0x66,0x66,0x3E,0x00},
    {0x00,0x00,0x3C,0x66,0x7E,0x60,0x3C,0x00},
    {0x1C,0x30,0x7C,0x30,0x30,0x30,0x30,0x00},
    {0x00,0x00,0x3E,0x66,0x66,0x3E,0x06,0x3C},
    {0x60,0x60,0x7C,0x66,0x66,0x66,0x66,0x00},
    {0x18,0x00,0x38,0x18,0x18,0x18,0x3C,0x00},
    {0x0C,0x00,0x1C,0x0C,0x0C,0x0C,0x6C,0x38},
    {0x60,0x60,0x66,0x6C,0x78,0x6C,0x66,0x00},
    {0x38,0x18,0x18,0x18,0x18,0x18,0x3C,0x00},
    {0x00,0x00,0x66,0x7F,0x7B,0x63,0x63,0x00},
    {0x00,0x00,0x7C,0x66,0x66,0x66,0x66,0x00},
    {0x00,0x00,0x3C,0x66,0x66,0x66,0x3C,0x00},
    {0x00,0x00,0x7C,0x66,0x66,0x7C,0x60,0x60},
    {0x00,0x00,0x3E,0x66,0x66,0x3E,0x06,0x06},
    {0x00,0x00,0x7C,0x66,0x60,0x60,0x60,0x00},
    {0x00,0x00,0x3E,0x60,0x3C,0x06,0x7C,0x00},
    {0x18,0x18,0x7E,0x18,0x18,0x18,0x0C,0x00},
    {0x00,0x00,0x66,0x66,0x66,0x66,0x3E,0x00},
    {0x00,0x00,0x66,0x66,0x66,0x3C,0x18,0x00},
    {0x00,0x00,0x63,0x6B,0x7F,0x77,0x36,0x00},
    {0x00,0x00,0x66,0x3C,0x18,0x3C,0x66,0x00},
    {0x00,0x00,0x66,0x66,0x66,0x3E,0x06,0x3C},
    {0x00,0x00,0x7E,0x0C,0x18,0x30,0x7E,0x00},
    {0x0E,0x18,0x18,0x70,0x18,0x18,0x0E,0x00},
    {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00},
    {0x70,0x18,0x18,0x0E,0x18,0x18,0x70,0x00},
    {0x76,0xDC,0x00,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} 
};

static const unsigned char s_char_widths[96] = {
    4, 3, 5, 7, 7, 7, 7, 3, 4, 4, 6, 7, 3, 6, 3, 6,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 5, 7, 5, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 6, 7, 6, 8, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 8, 7, 7, 7, 4, 6, 4, 5, 7,
    3, 6, 6, 6, 6, 6, 5, 6, 3, 4, 6, 3, 8, 6, 6, 6,
    6, 5, 6, 5, 6, 6, 8, 6, 6, 6, 4, 3, 4, 7, 0     
};

static const char *s_tab_names[SWITCH_TAB_COUNT] = {
    "Floppy",
    "Hard Disk",
    "WHDLoad",
    "Presets",
    "Hardware",
    "Display",
    "Controls",
    "Savestate",
    "System"
};

int switch_gui_init(void)
{
    write_log("[SWITCH] switch_gui_init: entry\n");
    if (s_gui_initialized && prSDLScreen != NULL && prSDLScreen->w == SWITCH_SCREEN_W && prSDLScreen->h == SWITCH_SCREEN_H)
        return 0;

    switch_gui_free_screen();
    write_log("[SWITCH] switch_gui_init: free_screen done\n");

    displaying_menu = 1;

    prSDLScreen = SDL_SetVideoMode(SWITCH_SCREEN_W, SWITCH_SCREEN_H, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (prSDLScreen == NULL) {
        prSDLScreen = SDL_SetVideoMode(SWITCH_SCREEN_W, SWITCH_SCREEN_H, 16, SDL_SWSURFACE | SDL_DOUBLEBUF);
    }
    if (prSDLScreen == NULL) {
        write_log("[SWITCH] switch_gui_init: SDL_SetVideoMode failed\n");
        return -1;
    }
    SDL_SetVideoModeScaling(0, 0, SWITCH_SCREEN_W, SWITCH_SCREEN_H);
    SDL_SetVideoModeBilinear(1);

    
    

    write_log("[SWITCH] switch_gui_init: menu screen ready (%dx%d)\n", prSDLScreen->w, prSDLScreen->h);
    s_gui_initialized = true;
    return 0;
}

void switch_gui_shutdown(void)
{
    if (prSDLScreen) {
        SDL_FillRect(prSDLScreen, NULL, 0);
        SDL_Flip(prSDLScreen);
        SDL_FreeSurface(prSDLScreen);
        prSDLScreen = NULL;
    }
    s_gui_initialized = false;
    displaying_menu = 0;
}

void switch_gui_shutdown_final(void)
{
    
    ttf_shutdown_cleanup();
    s_gui_initialized = false;
    switch_gui_free_screen();
    displaying_menu = 0;
}

void switch_gui_prepare_exit(void)
{
    if (prSDLScreen) {
        
        SDL_FreeSurface(prSDLScreen);
        prSDLScreen = NULL;
    }
    s_gui_initialized = false;
    displaying_menu = 0;
}

void switch_gui_update_input(SwitchInputState *input)
{
    input->prev_pad = input->pad;
    input->pad.buttons = 0;

    PadState pad;
    padInitializeDefault(&pad);
    padUpdate(&pad);

    u64 kHeld = padGetButtons(&pad);

    if (kHeld & HidNpadButton_Up) input->pad.buttons |= SWITCH_BTN_UP;
    if (kHeld & HidNpadButton_Down) input->pad.buttons |= SWITCH_BTN_DOWN;
    if (kHeld & HidNpadButton_Left) input->pad.buttons |= SWITCH_BTN_LEFT;
    if (kHeld & HidNpadButton_Right) input->pad.buttons |= SWITCH_BTN_RIGHT;

    HidAnalogStickState stick = padGetStickPos(&pad, 0);
    if (stick.y > 16000) input->pad.buttons |= SWITCH_BTN_UP;
    if (stick.y < -16000) input->pad.buttons |= SWITCH_BTN_DOWN;
    if (stick.x < -16000) input->pad.buttons |= SWITCH_BTN_LEFT;
    if (stick.x > 16000) input->pad.buttons |= SWITCH_BTN_RIGHT;

    if (kHeld & HidNpadButton_A) input->pad.buttons |= SWITCH_BTN_A;
    if (kHeld & HidNpadButton_B) input->pad.buttons |= SWITCH_BTN_B;
    if (kHeld & HidNpadButton_X) input->pad.buttons |= SWITCH_BTN_X;
    if (kHeld & HidNpadButton_Y) input->pad.buttons |= SWITCH_BTN_Y;

    if (kHeld & HidNpadButton_L) input->pad.buttons |= SWITCH_BTN_L;
    if (kHeld & HidNpadButton_R) input->pad.buttons |= SWITCH_BTN_R;
    if (kHeld & HidNpadButton_ZL) input->pad.buttons |= SWITCH_BTN_ZL;
    if (kHeld & HidNpadButton_ZR) input->pad.buttons |= SWITCH_BTN_ZR;
    if (kHeld & HidNpadButton_Plus) input->pad.buttons |= SWITCH_BTN_PLUS;
    if (kHeld & HidNpadButton_Minus) input->pad.buttons |= SWITCH_BTN_MINUS;

    input->pressed  = input->pad.buttons & ~input->prev_pad.buttons;
    input->released = ~input->pad.buttons & input->prev_pad.buttons;
    input->held     = input->pad.buttons;

    HidTouchScreenState touchState;
    if (hidGetTouchScreenStates(&touchState, 1) > 0 && touchState.count > 0) {
        input->touch_x = (touchState.touches[0].x * SWITCH_SCREEN_W) / 1280;
        input->touch_y = (touchState.touches[0].y * SWITCH_SCREEN_H) / 720;
        input->touch_active = 1;
        input->touch_hold_frames++;
        input->touch_tap = (input->touch_hold_frames == 1) ? 1 : 0;
    } else {
        input->touch_active = 0;
        input->touch_hold_frames = 0;
        input->touch_tap = 0;
    }
}

void switch_gui_update_system_info(SwitchSystemInfo *sysinfo)
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    if (tm_info) {
        snprintf(sysinfo->time_str, sizeof(sysinfo->time_str), "%02d:%02d", tm_info->tm_hour, tm_info->tm_min);
        snprintf(sysinfo->date_str, sizeof(sysinfo->date_str), "%02d/%02d/%04d", tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900);
    }

    u32 battery_pct = 100;
    if (R_SUCCEEDED(psmInitialize())) {
        psmGetBatteryChargePercentage(&battery_pct);
        PsmChargerType ctype;
        psmGetChargerType(&ctype);
        sysinfo->is_charging = (ctype != PsmChargerType_Unconnected);
        psmExit();
    }
    sysinfo->battery_percent = (int)battery_pct;
}

static inline Uint32 to_sdl_color(unsigned int col)
{
    Uint8 r = (col >> 0) & 0xFF;
    Uint8 g = (col >> 8) & 0xFF;
    Uint8 b = (col >> 16) & 0xFF;
    return SDL_MapRGB(prSDLScreen->format, r, g, b);
}

#define TTF_PX_MIN 10
#define TTF_PX_MAX 36
#define TTF_FONT_SLOTS 12
#define TTF_CACHE_MAX 640

typedef struct {
    char text[192];
    int px;
    Uint32 col;
    SDL_Surface *surface;
} TtfStringCache;

static char s_ttf_path[256] = "";
static TTF_Font *s_ttf_fonts[TTF_FONT_SLOTS] = {0};
static int s_ttf_font_px[TTF_FONT_SLOTS] = {0};
static TtfStringCache s_ttf_cache[TTF_CACHE_MAX] = {{0}};
static int s_ttf_cache_next = 0;
static int s_ttf_ready = 0;
static int s_ttf_checked = 0;
static unsigned short s_ttf_adv[TTF_PX_MAX - TTF_PX_MIN + 1][128];
static unsigned char s_ttf_adv_valid[TTF_PX_MAX - TTF_PX_MIN + 1][128];

static void ttf_string_cache_clear(void)
{
    for (int i = 0; i < TTF_CACHE_MAX; i++) {
        if (s_ttf_cache[i].surface) {
            SDL_FreeSurface(s_ttf_cache[i].surface);
            s_ttf_cache[i].surface = NULL;
        }
    }
    s_ttf_cache_next = 0;
    memset(s_ttf_adv_valid, 0, sizeof(s_ttf_adv_valid));
}

static void ttf_shutdown_cleanup(void)
{
    for (int i = 0; i < TTF_FONT_SLOTS; i++) {
        if (s_ttf_fonts[i]) {
            TTF_CloseFont(s_ttf_fonts[i]);
            s_ttf_fonts[i] = NULL;
            s_ttf_font_px[i] = 0;
        }
    }
    ttf_string_cache_clear();
    s_ttf_checked = 0;
    s_ttf_ready = 0;
}

static int ttf_ensure_loaded(void)
{
    if (s_ttf_checked)
        return s_ttf_ready;
    s_ttf_checked = 1;

    if (TTF_Init() < 0) {
        write_log("[SWITCH] TTF_Init failed: %s\n", TTF_GetError());
        return 0;
    }

    const char *paths[2];
    paths[0] = "./data/font.ttf";
    paths[1] = "./font.ttf";
    for (int i = 0; i < 2; i++) {
        TTF_Font *probe = TTF_OpenFont(paths[i], 16);
        if (probe) {
            TTF_CloseFont(probe);
            strncpy(s_ttf_path, paths[i], sizeof(s_ttf_path) - 1);
            s_ttf_path[sizeof(s_ttf_path) - 1] = '\0';
            s_ttf_ready = 1;
            write_log("[SWITCH] TrueType font: %s\n", s_ttf_path);
            return 1;
        }
    }
    write_log("[SWITCH] No TTF font found; using built-in 8x8 font\n");
    return 0;
}

static TTF_Font *ttf_font_for_px(int px)
{
    for (int i = 0; i < TTF_FONT_SLOTS; i++) {
        if (s_ttf_font_px[i] == px && s_ttf_fonts[i])
            return s_ttf_fonts[i];
    }
    int slot = 0;
    for (int i = 0; i < TTF_FONT_SLOTS; i++) {
        if (!s_ttf_fonts[i]) { slot = i; break; }
    }
    if (s_ttf_fonts[slot]) {
        TTF_CloseFont(s_ttf_fonts[slot]);
        s_ttf_fonts[slot] = NULL;
        s_ttf_font_px[slot] = 0;
        ttf_string_cache_clear();
    }
    s_ttf_fonts[slot] = TTF_OpenFont(s_ttf_path, px);
    if (s_ttf_fonts[slot])
        s_ttf_font_px[slot] = px;
    return s_ttf_fonts[slot];
}

static int ttf_advance_char(TTF_Font *font, int px, unsigned char c)
{
    if (c >= 128)
        return (c >= 32 && c <= 126) ? s_char_widths[c - 32] : 6;
    int ri = px - TTF_PX_MIN;
    if (ri < 0 || ri > TTF_PX_MAX - TTF_PX_MIN)
        return 0;
    if (!s_ttf_adv_valid[ri][c]) {
        int minx, maxx, miny, maxy, adv;
        s_ttf_adv_valid[ri][c] = 1;
        if (TTF_GlyphMetrics(font, (Uint16)c, &minx, &maxx, &miny, &maxy, &adv) == 0 && adv > 0)
            s_ttf_adv[ri][c] = (unsigned short)adv;
    }
    return s_ttf_adv[ri][c];
}

static int ttf_px_for_scale(float scale)
{
    int raw = (int)(scale * 18.0f + 0.5f);
    if (raw <= 13) return 13;
    if (raw <= 16) return 16;
    if (raw <= 19) return 19;
    return 21;
}

static SDL_Surface *ttf_render_line(int px, Uint32 col, const char *line, int *out_width)
{
    size_t len = strlen(line);
    if (len == 0 || len >= sizeof(s_ttf_cache[0].text))
        return NULL;

    for (int i = 0; i < TTF_CACHE_MAX; i++) {
        TtfStringCache *e = &s_ttf_cache[i];
        if (e->surface && e->px == px && e->col == col && strcmp(e->text, line) == 0) {
            *out_width = e->surface->w;
            return e->surface;
        }
    }

    TTF_Font *font = ttf_font_for_px(px);
    if (!font)
        return NULL;

    SDL_Color c;
    c.r = (Uint8)((col >> 0) & 0xFF);
    c.g = (Uint8)((col >> 8) & 0xFF);
    c.b = (Uint8)((col >> 16) & 0xFF);
    SDL_Surface *s = TTF_RenderUTF8_Blended(font, (char *)line, c);
    if (!s)
        return NULL;

    TtfStringCache *e = &s_ttf_cache[s_ttf_cache_next];
    s_ttf_cache_next = (s_ttf_cache_next + 1) % TTF_CACHE_MAX;
    if (e->surface)
        SDL_FreeSurface(e->surface);
    e->surface = s;
    e->px = px;
    e->col = col;
    strncpy(e->text, line, sizeof(e->text) - 1);
    e->text[sizeof(e->text) - 1] = '\0';

    *out_width = s->w;
    return s;
}

static bool switch_draw_text_ttf(float x, float y, unsigned int color, float scale, const char *text)
{
    if (!prSDLScreen || !text)
        return text && text[0] == 0;
    if (!ttf_ensure_loaded() || text[0] == '\0')
        return false;

    int px = ttf_px_for_scale(scale);
    TTF_Font *font = ttf_font_for_px(px);
    if (!font)
        return false;

    int cur_x = (int)x;
    int cur_y = (int)y;
    const char *p = text;
    while (*p) {
        const char *nl = strchr(p, '\n');
        char line[192];
        if (nl) {
            size_t n = (size_t)(nl - p);
            if (n >= sizeof(line)) n = sizeof(line) - 1;
            memcpy(line, p, n);
            line[n] = '\0';
        } else {
            if (strlen(p) >= sizeof(line))
                return false;
            strcpy(line, p);
        }
        int w = 0;
        SDL_Surface *s = ttf_render_line(px, color, line, &w);
        if (!s)
            return false;
        SDL_Rect r = { (Sint16)cur_x, (Sint16)cur_y, (Uint16)s->w, (Uint16)s->h };
        SDL_BlitSurface(s, NULL, prSDLScreen, &r);
        if (!nl)
            break;
        cur_y += TTF_FontLineSkip(font);
        p = nl + 1;
    }
    return true;
}


void switch_draw_rounded_rect(float x, float y, float w, float h, float r, unsigned int color)
{
    if (!prSDLScreen || w <= 0 || h <= 0) return;
    Uint32 sdl_col = to_sdl_color(color);

    int xi = (int)x;
    int yi = (int)y;
    int wi = (int)w;
    int hi = (int)h;

    float rad = r;
    float min_half = ((wi < hi) ? (float)wi : (float)hi) * 0.5f;
    if (rad <= 0.0f || rad < 1.0f) {
        SDL_Rect full = { (Sint16)xi, (Sint16)yi, (Uint16)wi, (Uint16)hi };
        SDL_FillRect(prSDLScreen, &full, sdl_col);
        return;
    }
    if (rad > min_half) rad = min_half;
    int ri = (int)rad;
    if (ri < 1) ri = 1;

    int mid_y = yi + ri;
    int mid_h = hi - 2 * ri;
    if (mid_h > 0) {
        SDL_Rect mid = { (Sint16)xi, (Sint16)mid_y, (Uint16)wi, (Uint16)mid_h };
        SDL_FillRect(prSDLScreen, &mid, sdl_col);
    }

    float radius_sq = (float)ri * (float)ri;
    for (int row = 0; row < ri; row++) {
        float dist_y = (float)ri - (float)row - 0.5f;
        float chord = sqrtf(radius_sq - dist_y * dist_y);
        int inset = ri - (int)(chord + 0.5f);
        if (inset < 0) inset = 0;
        int row_w = wi - 2 * inset;
        if (row_w <= 0) continue;

        SDL_Rect top = { (Sint16)(xi + inset), (Sint16)(yi + row), (Uint16)row_w, 1 };
        SDL_FillRect(prSDLScreen, &top, sdl_col);

        int bot_y = yi + hi - 1 - row;
        if (bot_y > yi + row) {
            SDL_Rect bot = { (Sint16)(xi + inset), (Sint16)bot_y, (Uint16)row_w, 1 };
            SDL_FillRect(prSDLScreen, &bot, sdl_col);
        }
    }
}

void switch_draw_rounded_rect_outline(float x, float y, float w, float h, float r, float thickness, unsigned int color)
{
    if (!prSDLScreen || w <= 0 || h <= 0) return;
    Uint32 sdl_col = to_sdl_color(color);
    Uint16 th = (Uint16)(thickness > 1.0f ? thickness : 1.0f);

    SDL_Rect top = { (Sint16)x, (Sint16)y, (Uint16)w, th };
    SDL_Rect bot = { (Sint16)x, (Sint16)(y + h - th), (Uint16)w, th };
    SDL_Rect lft = { (Sint16)x, (Sint16)y, th, (Uint16)h };
    SDL_Rect rgt = { (Sint16)(x + w - th), (Sint16)y, th, (Uint16)h };

    SDL_FillRect(prSDLScreen, &top, sdl_col);
    SDL_FillRect(prSDLScreen, &bot, sdl_col);
    SDL_FillRect(prSDLScreen, &lft, sdl_col);
    SDL_FillRect(prSDLScreen, &rgt, sdl_col);
}

void switch_draw_card(float x, float y, float w, float h, bool focused, bool active)
{
    unsigned int bg_col = focused ? SWITCH_COLOR_CARD_FOCUSED : SWITCH_COLOR_CARD;
    unsigned int border_col = focused ? SWITCH_COLOR_FOCUS_BORDER : SWITCH_COLOR_CARD_BORDER;

    switch_draw_rounded_rect(x, y, w, h, 6.0f, bg_col);
    if (focused) {
        switch_draw_rounded_rect_outline(x, y, w, h, 6.0f, 2.0f, border_col);
        switch_draw_rounded_rect(x + 2.0f, y + 3.0f, 4.0f, h - 6.0f, 2.0f, SWITCH_COLOR_AMIGA_RED);
    } else {
        switch_draw_rounded_rect_outline(x, y, w, h, 6.0f, 1.0f, border_col);
    }
}

void switch_draw_card_custom(float x, float y, float w, float h, unsigned int bg_col, unsigned int border_col)
{
    switch_draw_rounded_rect(x, y, w, h, 6.0f, bg_col);
    switch_draw_rounded_rect_outline(x, y, w, h, 6.0f, 1.0f, border_col);
}


int switch_get_text_width(float scale, const char *text)
{
    if (!text || text[0] == '\0') return 0;

    if (ttf_ensure_loaded()) {
        char line[192];
        size_t n = 0;
        while (text[n] && text[n] != '\n' && n + 1 < sizeof(line)) {
            line[n] = text[n];
            n++;
        }
        line[n] = '\0';
        TTF_Font *font = ttf_font_for_px(ttf_px_for_scale(scale));
        if (font) {
            int w = 0, h = 0;
            if (TTF_SizeUTF8(font, line, &w, &h) == 0)
                return w;
        }
    }

    int total_w = 0;
    float factor = scale * 2.0f;
    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char c = (unsigned char)text[i];
        if (c == '\n') break;
        int cw = (c >= 32 && c <= 126) ? s_char_widths[c - 32] : 6;
        total_w += (int)ceilf((float)(cw + 1) * factor);
    }
    return total_w;
}

int switch_get_text_height(float scale)
{
    return (int)ceilf(8.0f * scale * 2.0f);
}

void switch_truncate_text(const char *in_text, float max_w, float scale, char *out_buf, size_t out_size)
{
    if (!in_text || !out_buf || out_size == 0) return;
    int full_w = switch_get_text_width(scale, in_text);
    if (full_w <= (int)max_w) {
        strncpy(out_buf, in_text, out_size - 1);
        out_buf[out_size - 1] = '\0';
        return;
    }

    int dots_w = switch_get_text_width(scale, "...");
    int cur_w = 0;
    size_t out_idx = 0;
    float factor = scale * 2.0f;
    TTF_Font *tfont = NULL;
    int ttf_px = 0;
    if (ttf_ensure_loaded()) {
        ttf_px = ttf_px_for_scale(scale);
        tfont = ttf_font_for_px(ttf_px);
    }

    for (size_t i = 0; in_text[i] != '\0' && out_idx + 4 < out_size; i++) {
        unsigned char c = (unsigned char)in_text[i];
        int next_w;
        if (tfont) {
            next_w = cur_w + ttf_advance_char(tfont, ttf_px, c) + 2;
        } else {
            int cw = (c >= 32 && c <= 126) ? s_char_widths[c - 32] : 6;
            next_w = cur_w + (int)ceilf((float)(cw + 1) * factor);
        }
        if (next_w + dots_w > (int)max_w) {
            break;
        }
        out_buf[out_idx++] = in_text[i];
        cur_w = next_w;
    }

    out_buf[out_idx++] = '.';
    out_buf[out_idx++] = '.';
    out_buf[out_idx++] = '.';
    out_buf[out_idx] = '\0';
}

void switch_draw_text(float x, float y, unsigned int color, float scale, const char *text)
{
    if (!prSDLScreen || !text || text[0] == '\0') return;

    if (switch_draw_text_ttf(x, y, color, scale, text))
        return;

    Uint32 sdl_col = to_sdl_color(color);
    int cur_x = (int)x;
    int cur_y = (int)y;

    float factor = scale * 2.0f;
    int dot_w = (int)ceilf(factor);
    int dot_h = (int)ceilf(factor);
    if (dot_w < 2) dot_w = 2;
    if (dot_h < 2) dot_h = 2;

    for (int idx = 0; text[idx] != '\0'; idx++) {
        unsigned char c = (unsigned char)text[idx];
        if (c == '\n') {
            cur_x = (int)x;
            cur_y += (int)(10.0f * factor) + 4;
            continue;
        }

        if (c >= 32 && c <= 126) {
            const unsigned char *glyph = s_font_8x8[c - 32];
            int char_w = s_char_widths[c - 32];

            for (int r = 0; r < 8; r++) {
                unsigned char row = glyph[r];
                for (int col = 0; col < 8; col++) {
                    if (row & (0x80 >> col)) {
                        SDL_Rect p = {
                            (Sint16)(cur_x + (int)(col * factor)),
                            (Sint16)(cur_y + (int)(r * factor)),
                            (Uint16)dot_w,
                            (Uint16)dot_h
                        };
                        SDL_FillRect(prSDLScreen, &p, sdl_col);
                    }
                }
            }
            cur_x += (int)ceilf((float)(char_w + 1) * factor);
        } else {
            cur_x += (int)ceilf(7.0f * factor);
        }
    }
}

void switch_draw_textf(float x, float y, unsigned int color, float scale, const char *fmt, ...)
{
    char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    switch_draw_text(x, y, color, scale, buf);
}

void switch_draw_text_centered(float cx, float y, unsigned int color, float scale, const char *text)
{
    int w = switch_get_text_width(scale, text);
    switch_draw_text(cx - ((float)w * 0.5f), y, color, scale, text);
}

void switch_draw_text_right(float rx, float y, unsigned int color, float scale, const char *text)
{
    int w = switch_get_text_width(scale, text);
    switch_draw_text(rx - (float)w, y, color, scale, text);
}

void switch_draw_text_wrapped(float x, float y, float max_w, unsigned int color, float scale, const char *text)
{
    if (!text || text[0] == '\0') return;

    char line_buf[256];
    line_buf[0] = '\0';
    float cur_y = y;
    float line_h = (8.0f * scale * 2.0f) + 6.0f;

    const char *p = text;
    while (*p != '\0') {
        char word[128];
        int w_idx = 0;
        while (*p == ' ') p++;
        if (*p == '\n') {
            if (line_buf[0] != '\0') {
                switch_draw_text(x, cur_y, color, scale, line_buf);
                cur_y += line_h;
                line_buf[0] = '\0';
            }
            p++;
            continue;
        }

        while (*p != '\0' && *p != ' ' && *p != '\n' && w_idx < 120) {
            word[w_idx++] = *p++;
        }
        word[w_idx] = '\0';

        char test_line[256];
        if (line_buf[0] == '\0') {
            snprintf(test_line, sizeof(test_line), "%s", word);
        } else {
            snprintf(test_line, sizeof(test_line), "%s %s", line_buf, word);
        }

        if (switch_get_text_width(scale, test_line) <= (int)max_w) {
            strncpy(line_buf, test_line, sizeof(line_buf) - 1);
        } else {
            if (line_buf[0] != '\0') {
                switch_draw_text(x, cur_y, color, scale, line_buf);
                cur_y += line_h;
            }
            strncpy(line_buf, word, sizeof(line_buf) - 1);
        }
    }

    if (line_buf[0] != '\0') {
        switch_draw_text(x, cur_y, color, scale, line_buf);
    }
}


void switch_draw_button_glyph(float x, float y, SwitchButtonGlyph glyph)
{
    if (!prSDLScreen) return;

    switch (glyph) {
        case SWITCH_GLYPH_A: {
            switch_draw_rounded_rect(x, y, 22.0f, 22.0f, 11.0f, RGBA8(229, 37, 33, 255));
            switch_draw_text_centered(x + 11.0f, y + 3.0f, SWITCH_COLOR_TEXT_WHITE, 0.90f, "A");
            break;
        }
        case SWITCH_GLYPH_B: {
            switch_draw_rounded_rect(x, y, 22.0f, 22.0f, 11.0f, RGBA8(60, 68, 82, 255));
            switch_draw_text_centered(x + 11.0f, y + 3.0f, SWITCH_COLOR_TEXT_WHITE, 0.90f, "B");
            break;
        }
        case SWITCH_GLYPH_X: {
            switch_draw_rounded_rect(x, y, 22.0f, 22.0f, 11.0f, RGBA8(0, 136, 204, 255));
            switch_draw_text_centered(x + 11.0f, y + 3.0f, SWITCH_COLOR_TEXT_WHITE, 0.90f, "X");
            break;
        }
        case SWITCH_GLYPH_Y: {
            switch_draw_rounded_rect(x, y, 22.0f, 22.0f, 11.0f, RGBA8(245, 158, 11, 255));
            switch_draw_text_centered(x + 11.0f, y + 3.0f, SWITCH_COLOR_TEXT_WHITE, 0.90f, "Y");
            break;
        }
        case SWITCH_GLYPH_L: {
            switch_draw_rounded_rect(x, y, 28.0f, 22.0f, 5.0f, RGBA8(38, 48, 68, 255));
            switch_draw_rounded_rect_outline(x, y, 28.0f, 22.0f, 5.0f, 1.0f, RGBA8(75, 90, 120, 255));
            switch_draw_text_centered(x + 14.0f, y + 3.0f, SWITCH_COLOR_TEXT_WHITE, 0.85f, "L");
            break;
        }
        case SWITCH_GLYPH_R: {
            switch_draw_rounded_rect(x, y, 28.0f, 22.0f, 5.0f, RGBA8(38, 48, 68, 255));
            switch_draw_rounded_rect_outline(x, y, 28.0f, 22.0f, 5.0f, 1.0f, RGBA8(75, 90, 120, 255));
            switch_draw_text_centered(x + 14.0f, y + 3.0f, SWITCH_COLOR_TEXT_WHITE, 0.85f, "R");
            break;
        }
        case SWITCH_GLYPH_ZL: {
            switch_draw_rounded_rect(x, y, 32.0f, 22.0f, 5.0f, RGBA8(38, 48, 68, 255));
            switch_draw_rounded_rect_outline(x, y, 32.0f, 22.0f, 5.0f, 1.0f, RGBA8(75, 90, 120, 255));
            switch_draw_text_centered(x + 16.0f, y + 3.0f, SWITCH_COLOR_TEXT_WHITE, 0.80f, "ZL");
            break;
        }
        case SWITCH_GLYPH_ZR: {
            switch_draw_rounded_rect(x, y, 32.0f, 22.0f, 5.0f, RGBA8(38, 48, 68, 255));
            switch_draw_rounded_rect_outline(x, y, 32.0f, 22.0f, 5.0f, 1.0f, RGBA8(75, 90, 120, 255));
            switch_draw_text_centered(x + 16.0f, y + 3.0f, SWITCH_COLOR_TEXT_WHITE, 0.80f, "ZR");
            break;
        }
        case SWITCH_GLYPH_PLUS: {
            switch_draw_rounded_rect(x, y, 22.0f, 22.0f, 11.0f, RGBA8(45, 55, 75, 255));
            switch_draw_rounded_rect_outline(x, y, 22.0f, 22.0f, 11.0f, 1.0f, RGBA8(80, 95, 125, 255));
            switch_draw_text_centered(x + 11.0f, y + 3.0f, SWITCH_COLOR_TEXT_WHITE, 0.95f, "+");
            break;
        }
        case SWITCH_GLYPH_MINUS: {
            switch_draw_rounded_rect(x, y, 22.0f, 22.0f, 11.0f, RGBA8(45, 55, 75, 255));
            switch_draw_rounded_rect_outline(x, y, 22.0f, 22.0f, 11.0f, 1.0f, RGBA8(80, 95, 125, 255));
            switch_draw_text_centered(x + 11.0f, y + 3.0f, SWITCH_COLOR_TEXT_WHITE, 0.95f, "-");
            break;
        }
        default:
            break;
    }
}

void switch_draw_hint_item(float x, float y, SwitchButtonGlyph glyph, const char *label)
{
    switch_draw_button_glyph(x, y, glyph);
    float offset_x = 28.0f;
    if (glyph == SWITCH_GLYPH_L || glyph == SWITCH_GLYPH_R) offset_x = 34.0f;
    else if (glyph == SWITCH_GLYPH_ZL || glyph == SWITCH_GLYPH_ZR) offset_x = 38.0f;
    if (label && label[0] != '\0') {
        switch_draw_text(x + offset_x, y + 3.0f, RGBA8(220, 230, 245, 255), 0.85f, label);
    }
}

void switch_draw_badge(float x, float y, const char *label, unsigned int bg_col, unsigned int text_col)
{
    if (!label) return;
    int text_w = switch_get_text_width(0.80f, label);
    float badge_w = (float)text_w + 14.0f;
    float badge_h = 22.0f;

    switch_draw_rounded_rect(x, y, badge_w, badge_h, 4.0f, bg_col);
    switch_draw_text_centered(x + (badge_w * 0.5f), y + 4.0f, text_col, 0.80f, label);
}

void switch_draw_led(float x, float y, const char *label, bool state, unsigned int led_col)
{
    unsigned int active_col = state ? led_col : RGBA8(50, 50, 50, 255);
    SDL_Rect led_r = { (Sint16)x, (Sint16)(y + 3.0f), 10, 10 };
    SDL_FillRect(prSDLScreen, &led_r, to_sdl_color(active_col));

    if (label) {
        switch_draw_text(x + 16.0f, y + 1.0f, state ? SWITCH_COLOR_TEXT_WHITE : SWITCH_COLOR_TEXT_MUTED, 0.85f, label);
    }
}

void switch_draw_header(const char *title, SwitchGuiTab current_tab, const SwitchSystemInfo *sysinfo)
{
    SDL_Rect hdr_r = { 0, 0, SWITCH_SCREEN_W, 48 };
    SDL_FillRect(prSDLScreen, &hdr_r, to_sdl_color(SWITCH_COLOR_HEADER));
    switch_draw_rounded_rect_outline(0, 0, SWITCH_SCREEN_W, 48, 0.0f, 1.0f, SWITCH_COLOR_CARD_BORDER);

    float ball_cx = 32.0f;
    float ball_cy = 24.0f;
    s_boing_angle += 2.0f;
    if (s_boing_angle >= 360.0f) s_boing_angle -= 360.0f;
    switch_draw_boing_ball_icon(ball_cx, ball_cy, 15.0f, s_boing_angle);

    float title_scale = 1.0f;
    float title_x = 58.0f;
    switch_draw_text(title_x, 15.0f, SWITCH_COLOR_TEXT_WHITE, title_scale, "UAE4ALL2");
    float hd_x = title_x + (float)switch_get_text_width(title_scale, "UAE4ALL2") + 10.0f;
    switch_draw_badge(hd_x, 13.0f, "HD SWITCH", SWITCH_COLOR_AMIGA_RED, SWITCH_COLOR_TEXT_WHITE);

    if (sysinfo) {
        char time_buf[16];
        if (sysinfo->time_str[0] != '\0') {
            strncpy(time_buf, sysinfo->time_str, sizeof(time_buf) - 1);
            time_buf[sizeof(time_buf) - 1] = '\0';
        } else {
            time_t rawtime;
            time(&rawtime);
            struct tm *ti = localtime(&rawtime);
            if (ti) {
                strftime(time_buf, sizeof(time_buf), "%H:%M", ti);
            } else {
                strcpy(time_buf, "--:--");
            }
        }
        float time_x = SWITCH_SCREEN_W - 90.0f;
        switch_draw_text(time_x, 15.0f, SWITCH_COLOR_TEXT_MUTED, 0.90f, time_buf);

        if (sysinfo->battery_percent >= 0) {
            float bat_x = time_x - 130.0f;
            char bat_str[32];
            snprintf(bat_str, sizeof(bat_str), "%d%%", sysinfo->battery_percent);

            unsigned int bat_col = sysinfo->is_charging ? SWITCH_COLOR_SUCCESS : (sysinfo->battery_percent < 20 ? SWITCH_COLOR_DANGER : SWITCH_COLOR_TEXT_WHITE);
            switch_draw_rounded_rect_outline(bat_x, 14.0f, 32.0f, 18.0f, 3.0f, 1.5f, SWITCH_COLOR_TEXT_MUTED);
            SDL_Rect tip = { (Sint16)(bat_x + 32.0f), 19, 3, 8 };
            SDL_FillRect(prSDLScreen, &tip, to_sdl_color(SWITCH_COLOR_TEXT_MUTED));

            float fill_w = 26.0f * ((float)sysinfo->battery_percent / 100.0f);
            if (fill_w > 0.0f) {
                switch_draw_rounded_rect(bat_x + 3.0f, 17.0f, fill_w, 12.0f, 2.0f, bat_col);
            }
            switch_draw_text(bat_x + 40.0f, 15.0f, bat_col, 0.85f, bat_str);
        }
    }
}

void switch_draw_tab_bar(SwitchGuiTab current_tab, float y)
{
    float tab_w = (float)SWITCH_SCREEN_W / (float)SWITCH_TAB_COUNT;
    float tab_h = 36.0f;
    float tab_scale = 0.85f;

    for (int i = 0; i < SWITCH_TAB_COUNT; i++) {
        float tx = (float)i * tab_w;
        if (i == (int)current_tab) {
            switch_draw_rounded_rect(tx + 4.0f, y + 2.0f, tab_w - 8.0f, tab_h - 4.0f, 4.0f, SWITCH_COLOR_CARD_FOCUSED);
            switch_draw_rounded_rect(tx + 8.0f, y + tab_h - 4.0f, tab_w - 16.0f, 3.0f, 1.5f, SWITCH_COLOR_AMIGA_RED);
            switch_draw_text_centered(tx + (tab_w * 0.5f), y + 7.0f, SWITCH_COLOR_TEXT_WHITE, tab_scale, s_tab_names[i]);
        } else {
            switch_draw_text_centered(tx + (tab_w * 0.5f), y + 7.0f, SWITCH_COLOR_TEXT_MUTED, tab_scale, s_tab_names[i]);
        }
    }
}

void switch_draw_footer(const char *left_hint, const char *right_hint)
{
    SDL_Rect ftr_r = { 0, SWITCH_SCREEN_H - 42, SWITCH_SCREEN_W, 42 };
    SDL_FillRect(prSDLScreen, &ftr_r, to_sdl_color(SWITCH_COLOR_FOOTER));
    switch_draw_rounded_rect_outline(0, SWITCH_SCREEN_H - 42, SWITCH_SCREEN_W, 42, 0.0f, 1.0f, SWITCH_COLOR_CARD_BORDER);

    float btn_y = SWITCH_SCREEN_H - 32.0f;

    if (left_hint && right_hint) {
        switch_draw_text(20.0f, btn_y + 3.0f, SWITCH_COLOR_TEXT_WHITE, 0.85f, left_hint);
        switch_draw_text_right(SWITCH_SCREEN_W - 20.0f, btn_y + 3.0f, SWITCH_COLOR_TEXT_MUTED, 0.85f, right_hint);
        return;
    }

    if (s_active_tab == SWITCH_TAB_WHDLOAD) {
        switch_draw_hint_item(20.0f, btn_y, SWITCH_GLYPH_A, "LAUNCH");
        switch_draw_hint_item(140.0f, btn_y, SWITCH_GLYPH_X, "INSTALL LHA");
        switch_draw_hint_item(290.0f, btn_y, SWITCH_GLYPH_Y, "REBOOT");
    } else {
        switch_draw_hint_item(20.0f, btn_y, SWITCH_GLYPH_A, "SELECT");

        if (s_active_tab == SWITCH_TAB_FLOPPY) {
            switch_draw_hint_item(130.0f, btn_y, SWITCH_GLYPH_Y, "EJECT");
            switch_draw_hint_item(230.0f, btn_y, SWITCH_GLYPH_X, "REBOOT");
        } else if (s_active_tab == SWITCH_TAB_HARD_DISK) {
            switch_draw_hint_item(130.0f, btn_y, SWITCH_GLYPH_Y, "EJECT");
            switch_draw_hint_item(230.0f, btn_y, SWITCH_GLYPH_X, "HDF TOOL");
        } else if (s_active_tab == SWITCH_TAB_SAVESTATES) {
            switch_draw_hint_item(130.0f, btn_y, SWITCH_GLYPH_X, "LOAD");
        }
    }

    switch_draw_hint_item(620.0f, btn_y, SWITCH_GLYPH_ZL, "");
    switch_draw_hint_item(665.0f, btn_y, SWITCH_GLYPH_ZR, "TAB");
    switch_draw_hint_item(770.0f, btn_y, SWITCH_GLYPH_PLUS, "START / RESUME");
}

void switch_draw_button_item_custom(float x, float y, float w, float h, const char *title, const char *subtitle, const char *badge, unsigned int badge_col, bool focused, bool active)
{
    switch_draw_card(x, y, w, h, focused, active);

    char title_buf[128];
    float max_title_w = badge ? (w - 180.0f) : (w - 40.0f);
    switch_truncate_text(title, max_title_w, 0.95f, title_buf, sizeof(title_buf));

    bool has_sub = (subtitle != NULL && subtitle[0] != '\0');
    float text_y = has_sub ? (y + (h * 0.5f) - 13.0f) : (y + (h - 14.0f) * 0.5f);
    unsigned int title_col = focused ? SWITCH_COLOR_TEXT_WHITE : RGBA8(220, 230, 245, 255);
    switch_draw_text(x + 16.0f, text_y, title_col, 0.95f, title_buf);

    if (has_sub) {
        char sub_buf[256];
        float sub_max_w = badge ? (w - 40.0f - 140.0f) : (w - 40.0f);
        switch_truncate_text(subtitle, sub_max_w, 0.72f, sub_buf, sizeof(sub_buf));
        float sub_y = y + (h * 0.5f) + 5.0f;
        switch_draw_text(x + 16.0f, sub_y, SWITCH_COLOR_TEXT_MUTED, 0.72f, sub_buf);
    }

    if (badge) {
        int bw = switch_get_text_width(0.80f, badge) + 14;
        float badge_y = y + (h - 22.0f) * 0.5f;
        switch_draw_badge(x + w - (float)bw - 16.0f, badge_y, badge, badge_col, SWITCH_COLOR_TEXT_WHITE);
    }
}

void switch_draw_button_item(float x, float y, float w, float h, const char *title, const char *subtitle, const char *badge, bool focused, bool active)
{
    unsigned int badge_col = focused ? SWITCH_COLOR_AMIGA_BLUE : RGBA8(40, 52, 75, 255);
    switch_draw_button_item_custom(x, y, w, h, title, subtitle, badge, badge_col, focused, active);
}

int switch_list_visible_rows(float start_y, float item_h, float gap)
{
    float available = SWITCH_LIST_BOTTOM_Y - start_y;
    if (available < item_h)
        return 1;
    int rows = (int)((available + gap) / (item_h + gap));
    if (rows < 1)
        rows = 1;
    while (rows > 1) {
        float used = (float)rows * item_h + (float)(rows - 1) * gap;
        if (start_y + used <= SWITCH_LIST_BOTTOM_Y)
            break;
        rows--;
    }
    return rows;
}

void switch_draw_list_page_indicator(int selected_item, int total_items, int visible_items)
{
    if (total_items <= visible_items)
        return;
    char page_buf[24];
    snprintf(page_buf, sizeof(page_buf), "%d / %d", selected_item + 1, total_items);
    switch_draw_text_right(SWITCH_SCREEN_W - 20.0f, SWITCH_LIST_BOTTOM_Y - 18.0f, SWITCH_COLOR_TEXT_MUTED, 0.80f, page_buf);
}

void switch_draw_selector_item(float x, float y, float w, float h, const char *title, const char *current_value, bool focused)
{
    switch_draw_card(x, y, w, h, focused, false);
    float text_y = y + (h - 14.0f) * 0.5f;

    char title_buf[128];
    switch_truncate_text(title, w * 0.50f, 0.95f, title_buf, sizeof(title_buf));
    int title_w = switch_get_text_width(0.95f, title_buf);
    switch_draw_text(x + 16.0f, text_y, focused ? SWITCH_COLOR_TEXT_WHITE : RGBA8(220, 230, 245, 255), 0.95f, title_buf);

    char value_buf[128];
    char val_str[128];
    const char *value = current_value ? current_value : "None";
    float max_val_w = w - (float)title_w - (focused ? 80.0f : 50.0f);
    if (max_val_w < 120.0f) max_val_w = 120.0f;
    switch_truncate_text(value, max_val_w, focused ? 0.95f : 0.90f, value_buf, sizeof(value_buf));

    if (focused) {
        snprintf(val_str, sizeof(val_str), "<  %s  >", value_buf);
        switch_draw_text_right(x + w - 16.0f, text_y, SWITCH_COLOR_FOCUS_BORDER, 0.95f, val_str);
    } else {
        snprintf(val_str, sizeof(val_str), "%s", value_buf);
        switch_draw_text_right(x + w - 16.0f, text_y, SWITCH_COLOR_TEXT_MUTED, 0.90f, val_str);
    }
}

void switch_draw_switch_item(float x, float y, float w, float h, const char *title, bool enabled, bool focused)
{
    switch_draw_card(x, y, w, h, focused, false);
    float text_y = y + (h - 14.0f) * 0.5f;
    switch_draw_text(x + 16.0f, text_y, focused ? SWITCH_COLOR_TEXT_WHITE : RGBA8(220, 230, 245, 255), 0.95f, title);

    float sw_w = 48.0f;
    float sw_h = 24.0f;
    float sw_x = x + w - sw_w - 18.0f;
    float sw_y = y + (h - sw_h) * 0.5f;

    unsigned int track_col = enabled ? SWITCH_COLOR_SUCCESS : RGBA8(45, 55, 75, 255);
    switch_draw_rounded_rect(sw_x, sw_y, sw_w, sw_h, 6.0f, track_col);

    float knob_x = enabled ? (sw_x + sw_w - 20.0f) : (sw_x + 4.0f);
    SDL_Rect knob = { (Sint16)knob_x, (Sint16)(sw_y + 4.0f), 16, 16 };
    SDL_FillRect(prSDLScreen, &knob, to_sdl_color(SWITCH_COLOR_TEXT_WHITE));
}

void switch_draw_slider_item(float x, float y, float w, float h, const char *title, int val, int min, int max, const char *suffix, bool focused)
{
    switch_draw_card(x, y, w, h, focused, false);

    char label_buf[128];
    snprintf(label_buf, sizeof(label_buf), "%s: %d%s", title, val, suffix ? suffix : "");
    switch_draw_text(x + 16.0f, y + 8.0f, focused ? SWITCH_COLOR_TEXT_WHITE : RGBA8(220, 230, 245, 255), 0.90f, label_buf);

    float bar_x = x + 16.0f;
    float bar_y = y + 28.0f;
    float bar_w = w - 32.0f;
    float bar_h = 8.0f;

    float progress = (float)(val - min) / (float)(max - min);
    if (progress < 0.0f) progress = 0.0f;
    if (progress > 1.0f) progress = 1.0f;

    switch_draw_rounded_rect(bar_x, bar_y, bar_w, bar_h, 4.0f, RGBA8(40, 50, 70, 255));
    unsigned int fill_col = focused ? SWITCH_COLOR_AMIGA_RED : SWITCH_COLOR_AMIGA_BLUE;
    switch_draw_rounded_rect(bar_x, bar_y, bar_w * progress, bar_h, 4.0f, fill_col);
}

static void switch_draw_text_f(float x, float y, unsigned int color, float scale, const char *text)
{
    if (!prSDLScreen || !text || text[0] == '\0') return;

    if (ttf_ensure_loaded()) {
        switch_draw_text_ttf((float)(int)(x + 0.5f), (float)(int)(y + 0.5f), color, scale, text);
        return;
    }

    Uint32 sdl_col = to_sdl_color(color);
    float factor = scale * 2.0f;
    int dot_w = (int)ceilf(factor);
    int dot_h = dot_w;
    if (dot_w < 2) dot_w = 2;
    if (dot_h < 2) dot_h = 2;

    float cur_x = x;
    for (int idx = 0; text[idx] != '\0'; idx++) {
        unsigned char c = (unsigned char)text[idx];
        if (c == '\n') {
            cur_x = x;
            y += 10.0f * factor + 4.0f;
            continue;
        }
        if (c >= 32 && c <= 126) {
            const unsigned char *glyph = s_font_8x8[c - 32];
            int char_w = s_char_widths[c - 32];
            for (int r = 0; r < 8; r++) {
                unsigned char row = glyph[r];
                if (!row) continue;
                int row_y = (int)(y + (float)r * factor);
                for (int col = 0; col < 8; col++) {
                    if (row & (0x80 >> col)) {
                        SDL_Rect p = {
                            (Sint16)(int)(cur_x + (float)col * factor),
                            (Sint16)row_y,
                            (Uint16)dot_w,
                            (Uint16)dot_h
                        };
                        SDL_FillRect(prSDLScreen, &p, sdl_col);
                    }
                }
            }
            cur_x += ceilf((float)(char_w + 1) * factor);
        } else {
            cur_x += ceilf(7.0f * factor);
        }
    }
}

static SDL_Surface *s_boing3d_surf = NULL;

static void switch_draw_boing_ball_3d(float cx, float cy, float radius, float rot_x, float rot_y)
{
    if (!prSDLScreen || radius < 2.0f) return;

    int size = (int)(radius * 2.0f) + 4;
    if (!s_boing3d_surf || s_boing3d_surf->w != size || s_boing3d_surf->h != size) {
        if (s_boing3d_surf)
            SDL_FreeSurface(s_boing3d_surf);
        s_boing3d_surf = SDL_CreateRGBSurface(0, size, size, 32,
            0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
        if (s_boing3d_surf)
            SDL_SetColorKey(s_boing3d_surf, SDL_TRUE, 0xFF000000);
    }
    if (!s_boing3d_surf)
        return;

    SDL_Surface *surf = s_boing3d_surf;
    SDL_LockSurface(surf);
    int pitch = surf->pitch / 4;
    Uint32 *pix = (Uint32 *)surf->pixels;

    float r = radius;
    float r2 = r * r;
    float center = (float)size * 0.5f;
    float cosx = cosf(rot_x), sinx = sinf(rot_x);
    float cosy = cosf(rot_y), siny = sinf(rot_y);

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            float nx = ((float)col - center) / r;
            float ny = ((float)row - center) / r;
            float nz2 = 1.0f - nx * nx - ny * ny;
            if (nz2 < 0.0f) {
                pix[row * pitch + col] = 0xFF000000;
                continue;
            }
            float nz = sqrtf(nz2);

            float x1 = nx * cosy + nz * siny;
            float z1 = -nx * siny + nz * cosy;
            float y1 = ny;
            float y2 = y1 * cosx - z1 * sinx;
            float z2 = y1 * sinx + z1 * cosx;
            float x2 = x1;

            float u = atan2f(z2, x2) / 6.2831853f + 0.5f;
            float v = asinf(y2) / 3.14159265f + 0.5f;
            int cu = (int)(u * 4.0f) & 1;
            int cv = (int)(v * 4.0f) & 1;
            bool is_red = ((cu + cv) & 1) != 0;

            float shade = nx * -0.35f + ny * -0.45f + nz * 0.82f;
            if (shade < 0.15f) shade = 0.15f;
            if (shade > 1.0f) shade = 1.0f;

            if (is_red)
                pix[row * pitch + col] = RGBA8((int)(229 * shade), (int)(37 * shade), (int)(33 * shade), 255);
            else
                pix[row * pitch + col] = RGBA8((int)(238 * shade), (int)(238 * shade), (int)(240 * shade), 255);
        }
    }

    SDL_UnlockSurface(surf);

    SDL_Rect dst = {
        (Sint16)(int)(cx - center),
        (Sint16)(int)(cy - center),
        (Uint16)size,
        (Uint16)size
    };
    SDL_BlitSurface(surf, NULL, prSDLScreen, &dst);
}

typedef enum {
    CR_EMPTY = 0,
    CR_TITLE,  
    CR_SUBTITLE,
    CR_TEXT,   
    CR_DIM,    
    CR_LINK,   
    CR_SECTION,
    CR_RED     
} CreditStyle;

typedef struct {
    const char *text;
    CreditStyle style;
} CreditLine;

void switch_show_about_box(void)
{
    static const CreditLine credits[] = {
        { "UAE4ALL2 HD Switch", CR_TITLE },
        { "Version 1.00 - Amiga Emulator for Nintendo Switch", CR_SUBTITLE },
        { "", CR_EMPTY },
        { "A high-definition port of the classic UAE4ALL Amiga emulator,", CR_TEXT },
        { "now with WHDLoad, HDF, IPF and CD32 support on Switch.", CR_TEXT },
        { "github.com/theheroGAC/UAE4ALL2-HD-SWITCH", CR_LINK },
        { "", CR_EMPTY },
        { "=====  WHDLoad Support  =====", CR_SECTION },
        { "WHDLoad by Bert Jahn (Wepl)", CR_TEXT },
        { "The legendary hard-disk loader system for Amiga games.", CR_DIM },
        { "Official website: www.whdload.de", CR_LINK },
        { "Game packages & patches: aminet.net", CR_LINK },
        { "Thanks to the WHDLoad team and every slave author.", CR_DIM },
        { "", CR_EMPTY },
        { "=====  Hardware Tribute  =====", CR_SECTION },
        { "In memory of the engineers who made the Amiga possible:", CR_TEXT },
        { "Jay Miner - father of the Amiga chipset", CR_RED },
        { "Dave Needle - Amiga chipset co-designer", CR_RED },
        { "RJ Mical - system software & creator of the Boing Ball demo", CR_RED },
        { "And to every Amiga user, past and present.", CR_DIM },
        { "", CR_EMPTY },
        { "=====  Original Authors & Credits  =====", CR_SECTION },
        { "This project is a derivative work of UAE4All and would not", CR_DIM },
        { "exist without the original authors and contributors:", CR_DIM },
        { "Chui, john4p, TomB, notaz, Bernd Schneider, Toni Wilen,", CR_TEXT },
        { "Pickle, smoku, AnotherGuest, Anonymous engineer, finkel,", CR_TEXT },
        { "Lubomyr, pelya", CR_TEXT },
        { "", CR_EMPTY },
        { "theheroGAC - HD modern GUI, LHA decompressor and enhancements", CR_TEXT },
        { "Cpasjuste - original Vita port, SDL-Vita, shader support", CR_TEXT },
        { "rsn8887 - Vita/Switch work and UAE4ALL2 improvements", CR_TEXT },
        { "github.com/rsn8887/uae4all2", CR_LINK },
        { "ScHlAuChi - testing, ideas, virtual keyboard", CR_TEXT },
        { "wronghands - menu font, keyboard styles and design", CR_TEXT },
        { "Menu font: Fira Sans (Mozilla/Telefonica, SIL OFL 1.1)", CR_DIM },
        { "CrashMidnick - French virtual keyboard", CR_TEXT },
        { "The devkitPro / libnx Team and all beta testers", CR_TEXT },
        { "", CR_EMPTY },
        { "Thank you for playing!", CR_RED },
    };
    const int total_lines = (int)(sizeof(credits) / sizeof(credits[0]));
    const float line_h = 27.0f;
    const float content_h = (float)total_lines * line_h;

    float scroll = 0.0f;
    float speed = 1.0f;
    int paused = 0;
    int frame_count = 0;
    int hold_counter = 0;
    float rot_x = 0.0f, rot_y = 0.0f;

    SwitchInputState input;
    memset(&input, 0, sizeof(input));
    switch_gui_init();

    while (1) {
        switch_gui_update_input(&input);
        frame_count++;

        if (frame_count > 6 && (input.pressed & (SWITCH_BTN_B | SWITCH_BTN_A | SWITCH_BTN_PLUS)))
            break;

        if (input.pressed & SWITCH_BTN_X)
            paused = !paused;

        bool up_held = (input.held & SWITCH_BTN_UP) != 0;
        bool down_held = (input.held & SWITCH_BTN_DOWN) != 0;
        if (input.pressed & SWITCH_BTN_UP)
            speed -= 0.5f;
        if (input.pressed & SWITCH_BTN_DOWN)
            speed += 0.5f;
        if (up_held || down_held) {
            hold_counter++;
            if ((hold_counter & 3) == 0) {
                if (up_held) speed -= 0.25f;
                if (down_held) speed += 0.25f;
            }
        } else {
            hold_counter = 0;
            if (speed < 1.0f) speed += 0.25f;
            else if (speed > 1.0f) speed -= 0.25f;
        }
        if (speed < -5.0f) speed = -5.0f;
        if (speed > 8.0f) speed = 8.0f;

        if (!paused && speed != 0.0f) {
            scroll += speed;
            if (scroll >= content_h) scroll -= content_h;
            if (scroll < 0.0f) scroll += content_h;
        }

        SDL_FillRect(prSDLScreen, NULL, to_sdl_color(SWITCH_COLOR_OVERLAY_BG));
        float dx = 24.0f;
        float dy = 14.0f;
        float dw = SWITCH_SCREEN_W - 48.0f;
        float dh = SWITCH_SCREEN_H - 28.0f;
        switch_draw_card_custom(dx, dy, dw, dh, SWITCH_COLOR_HEADER, SWITCH_COLOR_FOCUS_BORDER);

        rot_x += 0.045f;
        rot_y += 0.065f;
        switch_draw_boing_ball_3d(dx + 46.0f, dy + 40.0f, 24.0f, rot_x, rot_y);
        switch_draw_text(dx + 92.0f, dy + 20.0f, SWITCH_COLOR_AMIGA_RED, 1.15f, "UAE4ALL2 HD Switch");
        switch_draw_text(dx + 92.0f, dy + 44.0f, SWITCH_COLOR_AMIGA_ORANGE, 0.85f, "About & Credits - WHDLoad Edition");

        switch_draw_rounded_rect_outline(dx + 16.0f, dy + 76.0f, dw - 32.0f, 1.0f, 0.0f, 1.0f, SWITCH_COLOR_CARD_BORDER);

        float area_top = dy + 90.0f;
        float area_bottom = dy + dh - 44.0f;
        for (int i = 0; i < total_lines; i++) {
            float y = area_top + (float)i * line_h - scroll;
            if (y < area_top - line_h || y > area_bottom)
                continue;

            const CreditLine *line = &credits[i];
            if (line->style == CR_EMPTY)
                continue;

            float scale;
            unsigned int color;
            switch (line->style) {
                case CR_TITLE:    scale = 1.00f; color = SWITCH_COLOR_AMIGA_RED; break;
                case CR_SUBTITLE: scale = 0.80f; color = SWITCH_COLOR_AMIGA_ORANGE; break;
                case CR_SECTION:  scale = 0.85f; color = SWITCH_COLOR_AMIGA_ORANGE; break;
                case CR_LINK:     scale = 0.75f; color = SWITCH_COLOR_AMIGA_BLUE; break;
                case CR_DIM:      scale = 0.75f; color = SWITCH_COLOR_TEXT_MUTED; break;
                case CR_RED:      scale = 0.78f; color = SWITCH_COLOR_AMIGA_RED; break;
                default:          scale = 0.78f; color = SWITCH_COLOR_TEXT_WHITE; break;
            }

            float cx = SWITCH_SCREEN_W * 0.5f;
            float x = cx - (float)switch_get_text_width(scale, line->text) * 0.5f;
            switch_draw_text_f(x, y, color, scale, line->text);
        }

        char footer[96];
        if (paused)
            snprintf(footer, sizeof(footer), "X RESUME   %d%%   B / A / + CLOSE", (int)(speed * 100.0f));
        else
            snprintf(footer, sizeof(footer), "UP REWIND  DOWN ACCELERATE  X PAUSE  B / A / + CLOSE");
        switch_draw_text_centered(SWITCH_SCREEN_W * 0.5f, SWITCH_SCREEN_H - 32.0f,
            paused ? SWITCH_COLOR_AMIGA_ORANGE : SWITCH_COLOR_TEXT_MUTED, 0.72f, footer);

        SDL_Flip(prSDLScreen);
        SDL_Delay(16);
    }
}

void switch_show_message_box(const char *title, const char *message, const char *btn_label)
{
    switch_gui_init();
    SwitchInputState input;
    memset(&input, 0, sizeof(input));
    int frame_count = 0;

    while (1) {
        switch_gui_update_input(&input);
        frame_count++;

        if (frame_count > 6 && (input.pressed & (SWITCH_BTN_A | SWITCH_BTN_B | SWITCH_BTN_PLUS))) {
            break;
        }

        SDL_FillRect(prSDLScreen, NULL, to_sdl_color(SWITCH_COLOR_OVERLAY_BG));

        float dw = 640.0f, dh = 270.0f;
        float dx = (SWITCH_SCREEN_W - dw) * 0.5f;
        float dy = (SWITCH_SCREEN_H - dh) * 0.5f;
        switch_draw_card_custom(dx, dy, dw, dh, SWITCH_COLOR_HEADER, SWITCH_COLOR_FOCUS_BORDER);

        switch_draw_text_centered(dx + (dw * 0.5f), dy + 22.0f, SWITCH_COLOR_AMIGA_RED, 1.10f, title ? title : "Message");
        switch_draw_text_wrapped(dx + 30.0f, dy + 70.0f, dw - 60.0f, SWITCH_COLOR_TEXT_WHITE, 0.90f, message ? message : "");

        float bw = 180.0f, bh = 38.0f;
        float bx = dx + (dw - bw) * 0.5f;
        float by = dy + dh - 54.0f;
        switch_draw_rounded_rect(bx, by, bw, bh, 6.0f, SWITCH_COLOR_AMIGA_RED);

        char clean_label[64];
        const char *source_label = btn_label ? btn_label : "OK";
        strncpy(clean_label, source_label, sizeof(clean_label) - 1);
        clean_label[sizeof(clean_label) - 1] = '\0';
        char *paren = strchr(clean_label, '(');
        if (paren) *paren = '\0';
        size_t label_len = strlen(clean_label);
        while (label_len > 0 && clean_label[label_len - 1] == ' ')
            clean_label[--label_len] = '\0';
        switch_draw_button_glyph(bx + 28.0f, by + 8.0f, SWITCH_GLYPH_A);
        switch_draw_text(bx + 62.0f, by + 11.0f, SWITCH_COLOR_TEXT_WHITE, 0.95f, clean_label);

        SDL_Flip(prSDLScreen);
        SDL_Delay(20);
    }
}

void switch_gui_draw_progress(const char *title, const char *subtitle, float fraction, const char *item_name)
{
    switch_gui_init();
    if (fraction < 0.0f) fraction = 0.0f;
    if (fraction > 1.0f) fraction = 1.0f;

    SDL_FillRect(prSDLScreen, NULL, to_sdl_color(SWITCH_COLOR_OVERLAY_BG));

    float dw = 640.0f, dh = 240.0f;
    float dx = (SWITCH_SCREEN_W - dw) * 0.5f;
    float dy = (SWITCH_SCREEN_H - dh) * 0.5f;
    switch_draw_card_custom(dx, dy, dw, dh, SWITCH_COLOR_HEADER, SWITCH_COLOR_FOCUS_BORDER);

    switch_draw_text_centered(dx + (dw * 0.5f), dy + 22.0f, SWITCH_COLOR_AMIGA_RED, 1.10f, title ? title : "Processing...");
    switch_draw_text(dx + 30.0f, dy + 66.0f, SWITCH_COLOR_TEXT_WHITE, 0.95f, subtitle ? subtitle : "");

    float bar_x = dx + 30.0f;
    float bar_y = dy + 105.0f;
    float bar_w = dw - 60.0f;
    float bar_h = 24.0f;

    switch_draw_rounded_rect(bar_x, bar_y, bar_w, bar_h, 4.0f, SWITCH_COLOR_CARD_BORDER);
    switch_draw_rounded_rect(bar_x + 1.0f, bar_y + 1.0f, bar_w - 2.0f, bar_h - 2.0f, 3.0f, SWITCH_COLOR_BG);

    float fill_w = (bar_w - 4.0f) * fraction;
    if (fill_w > 0.0f) {
        switch_draw_rounded_rect(bar_x + 2.0f, bar_y + 2.0f, fill_w, bar_h - 4.0f, 2.0f, SWITCH_COLOR_AMIGA_RED);
    }

    if (item_name && item_name[0]) {
        char item_buf[80];
        strncpy(item_buf, item_name, sizeof(item_buf) - 1);
        item_buf[sizeof(item_buf) - 1] = '\0';
        switch_draw_text(dx + 30.0f, dy + 145.0f, SWITCH_COLOR_TEXT_DIM, 0.80f, item_buf);
    }

    SDL_Flip(prSDLScreen);
}

bool switch_show_confirm_box(const char *title, const char *message, const char *yes_label, const char *no_label)
{
    if (title && strcmp(title, "About") == 0) {
        switch_show_about_box();
        return false;
    }
    if (title && strcmp(title, "Exit") == 0)
        return true;

    switch_gui_init();
    SwitchInputState input;
    memset(&input, 0, sizeof(input));
    int choice = 0;
    int frame_count = 0;

    while (1) {
        switch_gui_update_input(&input);
        frame_count++;

        if (frame_count > 6) {
            if (input.pressed & (SWITCH_BTN_LEFT | SWITCH_BTN_RIGHT)) {
                choice = 1 - choice;
            }
            if (input.pressed & SWITCH_BTN_A) {
                return (choice == 0);
            }
            if (input.pressed & SWITCH_BTN_B) {
                return false;
            }
        }

        SDL_FillRect(prSDLScreen, NULL, to_sdl_color(SWITCH_COLOR_OVERLAY_BG));

        float dw = 640.0f, dh = 270.0f;
        float dx = (SWITCH_SCREEN_W - dw) * 0.5f;
        float dy = (SWITCH_SCREEN_H - dh) * 0.5f;
        switch_draw_card_custom(dx, dy, dw, dh, SWITCH_COLOR_HEADER, SWITCH_COLOR_FOCUS_BORDER);

        switch_draw_text_centered(dx + (dw * 0.5f), dy + 22.0f, SWITCH_COLOR_AMIGA_RED, 1.10f, title ? title : "Confirm");
        switch_draw_text_wrapped(dx + 30.0f, dy + 70.0f, dw - 60.0f, SWITCH_COLOR_TEXT_WHITE, 0.90f, message ? message : "");

        float bw = 160.0f, bh = 38.0f;
        float b1_x = dx + 110.0f;
        float b2_x = dx + dw - 110.0f - bw;
        float by = dy + dh - 54.0f;

        switch_draw_rounded_rect(b1_x, by, bw, bh, 6.0f, choice == 0 ? SWITCH_COLOR_AMIGA_RED : SWITCH_COLOR_CARD);
        switch_draw_text_centered(b1_x + (bw * 0.5f), by + 11.0f, SWITCH_COLOR_TEXT_WHITE, 0.95f, yes_label ? yes_label : "Yes (A)");

        switch_draw_rounded_rect(b2_x, by, bw, bh, 6.0f, choice == 1 ? SWITCH_COLOR_AMIGA_RED : SWITCH_COLOR_CARD);
        switch_draw_text_centered(b2_x + (bw * 0.5f), by + 11.0f, SWITCH_COLOR_TEXT_WHITE, 0.95f, no_label ? no_label : "No (B)");

        SDL_Flip(prSDLScreen);
        SDL_Delay(20);
    }
    return false;
}

void switch_draw_boing_ball_icon(float cx, float cy, float radius, float rot_angle)
{
    (void)rot_angle;
    if (!prSDLScreen || radius < 2.0f) return;

    Uint32 white_col  = to_sdl_color(RGBA8(240, 240, 240, 255));
    Uint32 red_col    = to_sdl_color(SWITCH_COLOR_AMIGA_RED);
    Uint32 border_col = to_sdl_color(RGBA8(16, 20, 30, 255));

    int ri = (int)radius;
    float r2 = (float)ri * (float)ri;

    float r_out = (float)ri + 1.0f;
    float r_out2 = r_out * r_out;
    for (int row = -ri - 1; row <= ri + 1; row++) {
        float chord = sqrtf(r_out2 - (float)(row * row));
        int half = (int)(chord + 0.5f);
        if (half < 0) half = 0;
        SDL_Rect seg = { (Sint16)(cx - half), (Sint16)(cy + row), (Uint16)(half * 2), 1 };
        SDL_FillRect(prSDLScreen, &seg, border_col);
    }

    int grid = 4;
    float cell = (radius * 2.0f) / (float)grid;
    for (int row = -ri; row <= ri; row++) {
        float chord = sqrtf(r2 - (float)(row * row));
        int half = (int)(chord + 0.5f);
        if (half < 0) half = 0;

        int gy = (int)(((float)row + radius) / cell);
        if (gy < 0) gy = 0;
        if (gy >= grid) gy = grid - 1;

        int col = -half;
        while (col < half) {
            int gx = (int)(((float)col + radius) / cell);
            if (gx < 0) gx = 0;
            if (gx >= grid) gx = grid - 1;

            bool is_red = ((gx + gy) & 1) != 0;

            int next_x = (int)((float)(gx + 1) * cell) - ri;
            if (next_x > half) next_x = half;
            if (next_x <= col) next_x = col + 1;

            SDL_Rect seg = { (Sint16)(cx + col), (Sint16)(cy + row), (Uint16)(next_x - col), 1 };
            SDL_FillRect(prSDLScreen, &seg, is_red ? red_col : white_col);
            col = next_x;
        }
    }
}

int run_overlay_switch(void)
{
    if (switch_gui_init() != 0)
        return 1;

    SwitchInputState input;
    SwitchSystemInfo sysinfo;
    const char *items[6] = { "Resume", "Save State", "Load State", "Eject DF0", "Eject CD32", "Screenshot" };
    int selected = 0;
    int frame_count = 0;
    memset(&input, 0, sizeof(input));
    memset(&sysinfo, 0, sizeof(sysinfo));
    buttonSelect[0] = 0;
    inside_menu = 1;

    while (1) {
        switch_gui_update_input(&input);
        switch_gui_update_system_info(&sysinfo);
        frame_count++;

        if (input.pressed & (SWITCH_BTN_B | SWITCH_BTN_PLUS)) {
            mainMenu_case = MAIN_MENU_CASE_RUN;
            break;
        }
        if (input.pressed & SWITCH_BTN_UP) {
            selected--;
            if (selected < 0) selected = 5;
        }
        if (input.pressed & SWITCH_BTN_DOWN) {
            selected++;
            if (selected > 5) selected = 0;
        }
        if (input.pressed & SWITCH_BTN_A) {
            extern char *savestate_filename;
            extern char *screenshot_filename;
            if (selected == 0) {
                mainMenu_case = MAIN_MENU_CASE_RUN;
                break;
            } else if (selected == 1) {
                saveMenu_n_savestate = 1;
                make_savestate_filenames(savestate_filename, screenshot_filename);
                savestate_state = STATE_DOSAVE;
                mainMenu_case = MAIN_MENU_CASE_RUN;
                break;
            } else if (selected == 2) {
                saveMenu_n_savestate = 1;
                make_savestate_filenames(savestate_filename, screenshot_filename);
                FILE *state_file = fopen(savestate_filename, "rb");
                if (state_file) {
                    fclose(state_file);
                    savestate_state = STATE_DORESTORE;
                }
                mainMenu_case = MAIN_MENU_CASE_RUN;
                break;
            } else if (selected == 3) {
                uae4all_image_file0[0] = '\0';
                gui_update();
                mainMenu_case = MAIN_MENU_CASE_RUN;
                break;
            } else if (selected == 4) {
                cdrom_close_image();
                mainMenu_case = MAIN_MENU_CASE_RUN;
                break;
            } else {
                vita_screenshot_request = 1;
                mainMenu_case = MAIN_MENU_CASE_RUN;
                break;
            }
        }

        SDL_FillRect(prSDLScreen, NULL, to_sdl_color(SWITCH_COLOR_OVERLAY_BG));
        switch_draw_header("Quick Menu", SWITCH_TAB_FLOPPY, &sysinfo);
        for (int i = 0; i < 6; i++) {
            float y = 82.0f + (float)i * 58.0f;
            switch_draw_button_item(80.0f, y, SWITCH_SCREEN_W - 160.0f, 48.0f, items[i], NULL, NULL, selected == i, false);
        }
        switch_draw_footer("A SELECT", "B / + RESUME");
        SDL_Flip(prSDLScreen);
        SDL_Delay(16);
    }

    inside_menu = 0;
    switch_gui_shutdown();
    return 1;
}

int run_mainMenu_switch(void)
{
    if (switch_gui_init() != 0) {
        write_log("[SWITCH] run_mainMenu_switch: gui init failed\n");
        return 1;
    }
    write_log("[SWITCH] run_mainMenu_switch: enter menu\n");
    inside_menu = 1;

    SwitchInputState input;
    memset(&input, 0, sizeof(input));
    SwitchSystemInfo sysinfo;
    memset(&sysinfo, 0, sizeof(sysinfo));
    buttonSelect[0] = 0;

    mainMenu_case = -1;
    int menu_frame = 0;

    if (resetOnStartingApp) {
        resetOnStartingApp = false;
        mainMenu_case = MAIN_MENU_CASE_RESET;
    }

    while (mainMenu_case < 0) {
        menu_frame++;
        if (menu_frame <= 3)
            write_log("[SWITCH] menu: frame %d input begin\n", menu_frame);
        switch_gui_update_input(&input);
        if (s_save_as_ime_active) {
            char ime_name[100] = "";
            kbdswitch_get((char*)"Save Config As", config_save_as_name ? config_save_as_name : "", sizeof(ime_name) - 1, 0, ime_name);
            if (ime_name[0]) {
                strncpy(s_save_as_ime_name, ime_name, sizeof(s_save_as_ime_name) - 1);
                s_save_as_ime_name[sizeof(s_save_as_ime_name) - 1] = '\0';
                config_save_as_name = s_save_as_ime_name;
                saveconfig(4);
                config_save_as_name = NULL;
            }
            s_save_as_ime_active = 0;
            input.pressed = 0;
            continue;
        }
        if (menu_frame <= 3)
            write_log("[SWITCH] menu: frame %d input done buttons=0x%08x\n", menu_frame, input.pressed);
        switch_gui_update_system_info(&sysinfo);

        if (input.pressed & SWITCH_BTN_ZL) {
            s_active_tab = (SwitchGuiTab)((s_active_tab + SWITCH_TAB_COUNT - 1) % SWITCH_TAB_COUNT);
        }
        if (input.pressed & SWITCH_BTN_ZR) {
            s_active_tab = (SwitchGuiTab)((s_active_tab + 1) % SWITCH_TAB_COUNT);
        }

        if (input.touch_tap && input.touch_y >= 48 && input.touch_y <= 84) {
            float tab_w = (float)SWITCH_SCREEN_W / (float)SWITCH_TAB_COUNT;
            int touched_tab = (int)(input.touch_x / tab_w);
            if (touched_tab >= 0 && touched_tab < SWITCH_TAB_COUNT) {
                s_active_tab = (SwitchGuiTab)touched_tab;
            }
        }
        if (input.pressed & SWITCH_BTN_PLUS) {
            int automatic_media = -1;
            if (mainMenu_whdload_game[0] != '\0')
                automatic_media = 2;
            else if (current_cd_image[0] != '\0')
                automatic_media = 3;
            else if (uae4all_hard_file0[0] != '\0' || uae4all_hard_file1[0] != '\0' ||
                     uae4all_hard_file2[0] != '\0' || uae4all_hard_file3[0] != '\0')
                automatic_media = 1;
            else if (uae4all_hard_dir[0] != '\0')
                automatic_media = 2;
            else if (uae4all_image_file0[0] != '\0' || uae4all_image_file1[0] != '\0' ||
                     uae4all_image_file2[0] != '\0' || uae4all_image_file3[0] != '\0')
                automatic_media = 0;
            if ((automatic_media == 1 || automatic_media == 2) && !switch_confirm_eject_for_hard_disk_launch())
                continue;
            if (automatic_media >= 0 && !emulating) {
                ApplyAutomaticGamePreset(automatic_media);
                switch_set_kickstart(kickstart, 0);
            }
            write_log("[SWITCH] menu: Start pressed (kickstart_warning=%d)\n", kickstart_warning);
            if (kickstart_warning) {
                write_log("[SWITCH] run_mainMenu_switch: Start blocked, Kickstart missing\n");
                switch_show_message_box("Kickstart Missing", "Copy kick13.rom and kick31.rom for normal Amiga use, or kick40060.CD32 and kick40060.CD32.ext for CD32, to ./kickstarts/ or ./data/.", "OK (A)");
            } else {
                mainMenu_case = MAIN_MENU_CASE_RUN;
                break;
            }
        }

        if (menu_frame <= 3)
            write_log("[SWITCH] menu: frame %d render begin\n", menu_frame);
        SDL_FillRect(prSDLScreen, NULL, to_sdl_color(SWITCH_COLOR_BG));

        switch_draw_header("UAE4ALL2 HD", s_active_tab, &sysinfo);
        switch_draw_tab_bar(s_active_tab, 48.0f);

        int *cur_sel = &s_tab_selected_item[s_active_tab];
        switch (s_active_tab) {
            case SWITCH_TAB_FLOPPY:
                switch_view_floppy(&input, cur_sel);
                break;
            case SWITCH_TAB_HARD_DISK:
                switch_view_hard_disk(&input, cur_sel);
                break;
            case SWITCH_TAB_WHDLOAD:
                switch_view_whdload(&input, cur_sel);
                break;
            case SWITCH_TAB_PRESETS:
                switch_view_presets(&input, cur_sel);
                break;
            case SWITCH_TAB_HARDWARE:
                switch_view_hardware(&input, cur_sel);
                break;
            case SWITCH_TAB_DISPLAY:
                switch_view_display(&input, cur_sel);
                break;
            case SWITCH_TAB_CONTROLS:
                switch_view_controls(&input, cur_sel);
                break;
            case SWITCH_TAB_SAVESTATES:
                switch_view_savestates(&input, cur_sel);
                break;
            case SWITCH_TAB_SYSTEM:
                switch_view_system(&input, cur_sel);
                break;
            default:
                break;
        }

        switch_draw_footer(NULL, NULL);

        SDL_Flip(prSDLScreen);
        if (menu_frame <= 3)
            write_log("[SWITCH] menu: frame %d render done\n", menu_frame);
        SDL_Delay(16);
    }

    inside_menu = 0;
    setCpuSpeed();
    write_log("[SWITCH] run_mainMenu_switch: exit menu (case=%d)\n", mainMenu_case);
    switch_gui_shutdown();

    return (mainMenu_case == MAIN_MENU_CASE_RESET) ? 2 : (mainMenu_case == MAIN_MENU_CASE_QUIT ? 0 : 1);
}

#endif
