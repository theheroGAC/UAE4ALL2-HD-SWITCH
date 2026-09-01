#ifndef UAE_WHDLOAD_MANAGER_SWITCH_H
#define UAE_WHDLOAD_MANAGER_SWITCH_H

#ifdef __SWITCH__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SWITCH_WHDLOAD_ROOT "./data/whdload"

int switch_whdload_install_lha(const char *archive_path, char *installed_path, size_t installed_path_size);
int switch_whdload_list(char names[][128], int max_names);
int switch_whdload_prepare_launch(const char *game_name);
const char *switch_whdload_root(void);
const char *switch_whdload_get_last_error(void);

#ifdef __cplusplus
}
#endif

#endif
#endif