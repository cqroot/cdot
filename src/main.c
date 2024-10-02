#include "config.h"
#include "define.h"
#include "dotfile.h"
#include "status.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_help_msg(void)
{
    printf("CDOT - Dotfiles management tool.\n");
    printf("\n");
    printf("Usage:\n");
    printf("    cdot [-v | --version] [-h | --help]\n");
    printf("         <command>\n");
    printf("\n");
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

    if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
        show_help_msg();
        return RET_OK;
    }

    if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) {
        printf("cdot %d.%d.%d\n", CDOT_VERSION_MAJOR, CDOT_VERSION_MINOR,
               CDOT_VERSION_PATCH);
        return RET_OK;
    }

    // Command: status
    if (!strcmp(argv[1], "status")) {
        ret = run_status_cmd();
        return ret;
    }

    show_help_msg();
    return RET_ERR_PARAM;
}
