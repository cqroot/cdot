#include "define.h"
#include "dotfile.h"
#include "status.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_help_msg(void)
{
    printf("Dotfiles management tool.\n\n");
    printf("Usage:\n");
    printf("    cdot <command>\n\n");
    printf("The commands are:\n");
    printf("    status  Show the dotfiles status\n");
}

int main(int argc, char *argv[])
{
    RetCode ret = RET_OK;

    if (argc == 1) {
        show_help_msg();
        return RET_ERR_PARAM;
    }

    Dotfile *dotfiles = NULL;
    int dotfile_cnt = 0;
    ret = read_dotfiles_from_json(&dotfiles, &dotfile_cnt);
    if (ret != RET_OK) {
        return ret;
    }

    // Command: status
    if (!strcmp(argv[1], "status")) {
        ret = run_status_cmd(dotfiles, dotfile_cnt);
        free(dotfiles);
        return ret;
    }

    free(dotfiles);
    show_help_msg();
    return RET_ERR_PARAM;
}
