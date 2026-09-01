#ifndef UAE_GUI_SWITCH_H
#define UAE_GUI_SWITCH_H

#ifdef __SWITCH__

#include <switch.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SWITCH_SCREEN_W 960
#define SWITCH_SCREEN_H 544
#define SWITCH_FOOTER_H 42.0f
#define SWITCH_LIST_START_Y 90.0f
#define SWITCH_LIST_ITEM_H 48.0f
#define SWITCH_LIST_ITEM_GAP 6.0f
#define SWITCH_LIST_BOTTOM_Y ((float)SWITCH_SCREEN_H - SWITCH_FOOTER_H - 4.0f)

#ifndef RGBA8
#define RGBA8(r,g,b,a) ((((a)&0xFF)<<24) | (((b)&0xFF)<<16) | (((g)&0xFF)<<8) | (((r)&0xFF)<<0))
#endif

#define SWITCH_COLOR_BG            RGBA8(15, 18, 26, 255)
#define SWITCH_COLOR_HEADER        RGBA8(22, 27, 39, 255)
#define SWITCH_COLOR_FOOTER        RGBA8(20, 24, 34, 255)
#define SWITCH_COLOR_CARD          RGBA8(28, 34, 48, 230)
#define SWITCH_COLOR_CARD_FOCUSED  RGBA8(38, 48, 70, 255)
#define SWITCH_COLOR_CARD_BORDER   RGBA8(50, 60, 85, 255)
#define SWITCH_COLOR_FOCUS_BORDER  RGBA8(229, 37, 33, 255)
#define SWITCH_COLOR_ACTIVE_PILL   RGBA8(229, 37, 33, 255)
#define SWITCH_COLOR_AMIGA_RED     RGBA8(229, 37, 33, 255)
#define SWITCH_COLOR_AMIGA_BLUE    RGBA8(0, 136, 204, 255)
#define SWITCH_COLOR_AMIGA_ORANGE  RGBA8(255, 140, 0, 255)
#define SWITCH_COLOR_AMIGA_GREEN   RGBA8(34, 197, 94, 255)
#define SWITCH_COLOR_TEXT_WHITE    RGBA8(255, 255, 255, 255)
#define SWITCH_COLOR_TEXT_MUTED    RGBA8(148, 163, 184, 255)
#define SWITCH_COLOR_TEXT_DIM      RGBA8(90, 105, 125, 255)
#define SWITCH_COLOR_ACCENT_GOLD   RGBA8(245, 158, 11, 255)
#define SWITCH_COLOR_SUCCESS       RGBA8(16, 185, 129, 255)
#define SWITCH_COLOR_DANGER        RGBA8(239, 68, 68, 255)
#define SWITCH_COLOR_OVERLAY_BG    RGBA8(8, 10, 16, 210)

typedef enum {
    SWITCH_TAB_FLOPPY = 0,
    SWITCH_TAB_HARD_DISK,
    SWITCH_TAB_WHDLOAD,
    SWITCH_TAB_PRESETS,
    SWITCH_TAB_HARDWARE,
    SWITCH_TAB_DISPLAY,
    SWITCH_TAB_CONTROLS,
    SWITCH_TAB_SAVESTATES,
    SWITCH_TAB_SYSTEM,
    SWITCH_TAB_COUNT
} SwitchGuiTab;

#define SWITCH_BTN_A        (1 << 0)
#define SWITCH_BTN_B        (1 << 1)
#define SWITCH_BTN_X        (1 << 2)
#define SWITCH_BTN_Y        (1 << 3)
#define SWITCH_BTN_L        (1 << 4)
#define SWITCH_BTN_R        (1 << 5)
#define SWITCH_BTN_ZL       (1 << 6)
#define SWITCH_BTN_ZR       (1 << 7)
#define SWITCH_BTN_PLUS     (1 << 8)
#define SWITCH_BTN_MINUS    (1 << 9)
#define SWITCH_BTN_UP       (1 << 10)
#define SWITCH_BTN_DOWN     (1 << 11)
#define SWITCH_BTN_LEFT     (1 << 12)
#define SWITCH_BTN_RIGHT    (1 << 13)

typedef struct {
    unsigned int buttons;
    int lx;
    int ly;
    int rx;
    int ry;
} SwitchPadData;

typedef struct {
    SwitchPadData pad;
    SwitchPadData prev_pad;
    unsigned int pressed;
    unsigned int released;
    unsigned int held;
    int touch_x;
    int touch_y;
    int touch_active;
    int touch_tap;
    int touch_hold_frames;
} SwitchInputState;

typedef struct {
    int battery_percent;
    bool is_charging;
    char time_str[16];
    char date_str[32];
} SwitchSystemInfo;

int  switch_set_kickstart(int index, int load_rom);
int  switch_confirm_eject_for_hard_disk_launch(void);
int  switch_gui_init(void);
void switch_gui_shutdown(void);
void switch_gui_shutdown_final(void);
void switch_gui_prepare_exit(void);
void switch_gui_update_input(SwitchInputState *input);
void switch_gui_update_system_info(SwitchSystemInfo *sysinfo);
void switch_gui_save_as_started(void);

void switch_draw_rounded_rect(float x, float y, float w, float h, float r, unsigned int color);
void switch_draw_rounded_rect_outline(float x, float y, float w, float h, float r, float thickness, unsigned int color);
void switch_draw_card(float x, float y, float w, float h, bool focused, bool active);
void switch_draw_card_custom(float x, float y, float w, float h, unsigned int bg_col, unsigned int border_col);
void switch_draw_header(const char *title, SwitchGuiTab current_tab, const SwitchSystemInfo *sysinfo);
void switch_draw_footer(const char *left_hint, const char *right_hint);
void switch_draw_tab_bar(SwitchGuiTab current_tab, float y);

typedef enum {
    SWITCH_GLYPH_A = 0,
    SWITCH_GLYPH_B,
    SWITCH_GLYPH_X,
    SWITCH_GLYPH_Y,
    SWITCH_GLYPH_L,
    SWITCH_GLYPH_R,
    SWITCH_GLYPH_ZL,
    SWITCH_GLYPH_ZR,
    SWITCH_GLYPH_PLUS,
    SWITCH_GLYPH_MINUS,
    SWITCH_GLYPH_DPAD,
    SWITCH_GLYPH_STICK
} SwitchButtonGlyph;

void switch_draw_text(float x, float y, unsigned int color, float scale, const char *text);
void switch_draw_textf(float x, float y, unsigned int color, float scale, const char *fmt, ...);
void switch_draw_text_centered(float cx, float y, unsigned int color, float scale, const char *text);
void switch_draw_text_right(float rx, float y, unsigned int color, float scale, const char *text);
void switch_draw_text_wrapped(float x, float y, float max_w, unsigned int color, float scale, const char *text);
void switch_truncate_text(const char *in_text, float max_w, float scale, char *out_buf, size_t out_size);
int  switch_get_text_width(float scale, const char *text);
int  switch_get_text_height(float scale);

void switch_draw_button_glyph(float x, float y, SwitchButtonGlyph glyph);
void switch_draw_hint_item(float x, float y, SwitchButtonGlyph glyph, const char *label);
void switch_draw_badge(float x, float y, const char *label, unsigned int bg_col, unsigned int text_col);
void switch_draw_boing_ball_icon(float cx, float cy, float radius, float rot_angle);
void switch_draw_led(float x, float y, const char *label, bool state, unsigned int led_col);
void switch_draw_button_item(float x, float y, float w, float h, const char *title, const char *subtitle, const char *badge, bool focused, bool active);
void switch_draw_button_item_custom(float x, float y, float w, float h, const char *title, const char *subtitle, const char *badge, unsigned int badge_col, bool focused, bool active);
void switch_draw_selector_item(float x, float y, float w, float h, const char *title, const char *current_value, bool focused);
int  switch_list_visible_rows(float start_y, float item_h, float gap);
void switch_draw_list_page_indicator(int selected_item, int total_items, int visible_items);
void switch_draw_switch_item(float x, float y, float w, float h, const char *title, bool enabled, bool focused);
void switch_draw_slider_item(float x, float y, float w, float h, const char *title, int val, int min, int max, const char *suffix, bool focused);

void switch_show_message_box(const char *title, const char *message, const char *btn_label);
void switch_show_about_box(void);
bool switch_show_confirm_box(const char *title, const char *message, const char *yes_label, const char *no_label);
void switch_gui_draw_progress(const char *title, const char *subtitle, float fraction, const char *item_name);

void switch_view_floppy(SwitchInputState *input, int *selected_item);
void switch_view_hard_disk(SwitchInputState *input, int *selected_item);
void switch_view_whdload(SwitchInputState *input, int *selected_item);
void switch_view_presets(SwitchInputState *input, int *selected_item);
void switch_view_hardware(SwitchInputState *input, int *selected_item);
void switch_view_display(SwitchInputState *input, int *selected_item);
void switch_view_controls(SwitchInputState *input, int *selected_item);
void switch_view_savestates(SwitchInputState *input, int *selected_item);
void switch_view_system(SwitchInputState *input, int *selected_item);

int  switch_gui_run_browser(char *out_path, const char *start_dir, int disk_drive_idx);

int  run_mainMenu_switch(void);
int  run_overlay_switch(void);

#ifdef __cplusplus
}
#endif

#endif
#endif