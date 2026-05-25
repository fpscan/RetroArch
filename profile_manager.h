#ifndef __RARCH_PROFILE_MANAGER_H
#define __RARCH_PROFILE_MANAGER_H

#include <boolean.h>
#include <retro_miscellaneous.h>

#define MAX_PROFILES 32

typedef struct
{
   char name[128];
   char image_path[PATH_MAX_LENGTH];
   char config_name[128]; 
} rarch_profile_t;

typedef struct
{
   rarch_profile_t profiles[MAX_PROFILES];
   int count;
   int active_index;
} rarch_profile_list_t;

/* Initialise the profile manager. Called from config_load() each time
 * a config is loaded so the manager knows the config directory. */
void profile_manager_init(const char *config_dir, const char *main_config_path);

/* Get the name and optional icon of the currently active profile. */
int profile_manager_get_active_index(void);
void profile_manager_get_active(char *name, size_t name_len,
      char *image_path, size_t image_path_len);

/* Startup redirect: call from config_load() after profile_manager_init().
 * Returns true (and fills *out_path) when RARCH_PATH_CONFIG should be
 * redirected from retroarch.cfg to the active profile's cfg file.
 * Returns false when config_replace() has already set the right path. */
bool profile_manager_get_startup_redirect(const char *loaded_path,
      char *out_path, size_t len);

/* Resolve the full filesystem path for a specific profile index.
 * Index 0 (Default) returns the main retroarch.cfg path.
 * Used by action_ok_profile_select to feed config_replace(). */
bool profile_manager_get_config_path_for_index(int index, char *path, size_t len);

/* Create a new profile from the current settings snapshot. */
bool profile_manager_create(const char *name, const char *image_name);

/* Set which profile is active (updates profiles.cfg). */
bool profile_manager_set_active(int index);

/* Save current in-memory settings to the active profile's cfg file. */
bool profile_manager_save_current(void);

/* Delete a profile (cannot delete Default at index 0). */
bool profile_manager_delete(int index);

/* Return the full profile list (read-only). */
const rarch_profile_list_t *profile_manager_get_list(void);

/* Return the path to the system icons directory. */
void profile_manager_get_sysicons_dir(char *dir, size_t len);

#endif
