#include "status.h"
#include "color.h"
#include "define.h"
#include "dotfile.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

RetCode show_dotfile_status(const Dotfile *dotfile,
                            const DotfileAlignParams *ap)
{
    CHECK_PARAM_NOT_NULL(dotfile);
    CHECK_PARAM_NOT_NULL(ap);

    printf("  %s%*s  %s%*s  %s%*s  %s\n", dotfile->name,
           (int)(ap->name_len - strlen(dotfile->name)), "", dotfile->exec,
           (int)(ap->exec_len - strlen(dotfile->exec)), "", dotfile->path,
           (int)(ap->path_len - strlen(dotfile->path)), "",
           df_status_string(df_get_status(dotfile)));

    return RET_OK;
}

RetCode run_status_cmd(void)
{
    Dotfile *dotfiles = NULL;
    size_t count = 0;
    DotfileAlignParams align_params = { 0 };
    RetCode ret = df_read_from_json(&dotfiles, &count, &align_params);
    if (ret != RET_OK) {
        return ret;
    }

    printf(" " COLOR_BG_BLUE COLOR_FG_BLACK
           " NAME%*s  EXEC%*s  PATH%*s  STATUS         " COLOR_RESET "\n",
           (int)align_params.name_len - 4, "", (int)align_params.exec_len - 4,
           "", (int)align_params.path_len - 4, "");
    for (size_t i = 0; i < count; ++i) {
        (void)show_dotfile_status(&dotfiles[i], &align_params);
    }

    free(dotfiles);
    return RET_OK;
}
