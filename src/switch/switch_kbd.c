#include <string.h>
#include <stdbool.h>

#include <switch.h>
#include "switch_kbd.h"

void kbdswitch_get(char *title, const char *initial_text, int maxLen, int multiline, char *buf) {
	Result rc = 0;
	SwkbdConfig kbd;
	rc = swkbdCreate(&kbd, 0);
	if (R_SUCCEEDED(rc)) {
		swkbdConfigMakePresetDefault(&kbd);
		if (title && title[0]) {
			swkbdConfigSetGuideText(&kbd, title);
			swkbdConfigSetHeaderText(&kbd, title);
		}
		if (initial_text && initial_text[0]) {
			swkbdConfigSetInitialText(&kbd, initial_text);
		}
		swkbdConfigSetStringLenMax(&kbd, maxLen > 1 ? (maxLen - 1) : 64);
		rc = swkbdShow(&kbd, buf, maxLen);
		swkbdClose(&kbd);
	}
}
