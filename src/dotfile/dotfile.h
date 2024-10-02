#ifndef __CDOT_DOTFILES_H
#define __CDOT_DOTFILES_H

#include "color.h"
#include "define.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    char name[32];
    char exec[32];
    char path[256];
} Dotfile;

typedef struct {
    size_t name_len;
    size_t exec_len;
    size_t path_len;
} DotfileAlignParams;

RetCode df_read_from_json(OUT Dotfile **dotfiles, OUT size_t *count,
                          OUT DotfileAlignParams *align_params);
bool df_is_exec_exist(const Dotfile *dotfile);

typedef enum {
    DOTFILE_STATUS_OK,
    DOTFILE_STATUS_EXEC_NOT_FOUND,
} DotfileStatus;

static inline const char *df_status_string(DotfileStatus status)
{
    static const char *strings[] = {
        COLOR_FG_GREEN "OK" COLOR_RESET,
        COLOR_FG_RED "EXEC NOT FOUND" COLOR_RESET,
    };
    return strings[status];
}
DotfileStatus df_get_status(const Dotfile *dotfile);

#endif /* ifndef __CDOT_DOTFILES_H */
