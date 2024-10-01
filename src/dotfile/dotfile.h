#ifndef __CDOT_DOTFILES_H
#define __CDOT_DOTFILES_H

#include "define.h"

typedef struct {
    char name[20];
    char exec[20];
} Dotfile;

RetCode read_dotfiles_from_json(Dotfile **dotfiles, int *dotfile_cnt);

#endif /* ifndef __CDOT_DOTFILES_H */
