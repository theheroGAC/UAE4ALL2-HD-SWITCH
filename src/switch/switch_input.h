#ifndef SWITCH_INPUT_H
#define SWITCH_INPUT_H

#include <SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

int switch_poll_event(SDL_Event *event);
#define PSP2_PollEvent switch_poll_event

void exit_safely(int quit_via_home);

#define PAD_LEFT 12
#define PAD_UP 13
#define PAD_RIGHT 14
#define PAD_DOWN 15
#define PAD_TRIANGLE 2
#define PAD_SQUARE 3
#define PAD_CROSS 1
#define PAD_CIRCLE 0
#define PAD_SELECT 11
#define PAD_START 10
#define PAD_L 6
#define PAD_R 7
#define PAD_L2 8
#define PAD_R2 9
#define PAD_L3 4
#define PAD_R3 5
#define LSTICK_LEFT 16
#define LSTICK_UP 17
#define LSTICK_RIGHT 18
#define LSTICK_DOWN 19
#define RSTICK_LEFT 20
#define RSTICK_UP 21
#define RSTICK_RIGHT 22
#define RSTICK_DOWN 23
#define PAD_SL_LEFT 24
#define PAD_SR_LEFT 25
#define PAD_SL_RIGHT 26
#define PAD_SR_RIGHT 27
#define BUTTON_NONE 254

#ifdef __cplusplus
}
#endif

#endif // SWITCH_INPUT_H
