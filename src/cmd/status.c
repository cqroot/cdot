#include "status.h"
#include "color.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_command_exist(char *command)
{
    char whichCommand[256] = { 0 };
    sprintf(whichCommand, "which %s >/dev/null 2>&1", command);
    return !system(whichCommand);
}

void show_dotfile_status(Dotfile dotfile)
{
    printf("%-12s: ", dotfile.name);
    if (is_command_exist(dotfile.exec)) {
        printf(COLOR_FG_GREEN "OK\n" COLOR_RESET);
    } else {
        printf(COLOR_FG_RED "FAIL\n" COLOR_RESET);
    }
}

RetCode run_status_cmd(Dotfile *dotfiles, size_t len)
{
    for (size_t i = 0; i < len; ++i) {
        show_dotfile_status(dotfiles[i]);
    }

    return RET_OK;
}
