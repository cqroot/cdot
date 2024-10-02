#include "dotfile.h"
#include "define.h"
#include <cJSON.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static RetCode __df_set_align_params(const Dotfile *dotfile,
                                     OUT DotfileAlignParams *params)
{
    CHECK_PARAM_NOT_NULL(dotfile);
    CHECK_PARAM_NOT_NULL(params);

    if (strlen(dotfile->name) > params->name_len) {
        params->name_len = strlen(dotfile->name);
    }
    if (strlen(dotfile->exec) > params->exec_len) {
        params->exec_len = strlen(dotfile->exec);
    }
    if (strlen(dotfile->path) > params->path_len) {
        params->path_len = strlen(dotfile->path);
    }

    if (params->name_len < 4) {
        params->name_len = 4;
    }
    if (params->exec_len < 4) {
        params->exec_len = 4;
    }
    if (params->path_len < 4) {
        params->path_len = 4;
    }

    return RET_OK;
}

RetCode df_read_from_json(OUT Dotfile **dotfiles, OUT size_t *count,
                          OUT DotfileAlignParams *align_params)
{
    CHECK_PARAM_NOT_NULL(dotfiles);
    CHECK_PARAM_NOT_NULL(count);
    CHECK_PARAM_NOT_NULL(align_params);

    FILE *fptr = fopen("./cdot.json", "r");
    if (!fptr) {
        fprintf(stderr,
                COLOR_FG_RED "ERROR: " COLOR_RESET
                             "open file ./cdot.json failed (errno: %d)\n",
                errno);
        return RET_FAILED;
    }

    char *home_dir = getenv("HOME");

    fseek(fptr, 0, SEEK_END);
    long length = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    char *json_buf = (char *)malloc(length);
    if (!json_buf) {
        fprintf(stderr, COLOR_FG_RED "ERROR: " COLOR_RESET
                                     "allocate memory for json_buf failed\n");
        return RET_ERR_MALLOC;
    }
    fread(json_buf, 1, length, fptr);
    fclose(fptr);

    cJSON *cjson = cJSON_Parse(json_buf);
    free(json_buf);

    if (cjson == NULL) {
        fprintf(stderr,
                COLOR_FG_RED "ERROR: " COLOR_RESET
                             "cJSON parse failed (pos: %s)\n",
                cJSON_GetErrorPtr());
        return RET_FAILED;
    }

    cJSON *arr_item = cjson->child;
    int arr_size = cJSON_GetArraySize(cjson);

    *dotfiles = (Dotfile *)malloc(arr_size * sizeof(Dotfile));
    if (!*dotfiles) {
        fprintf(stderr, COLOR_FG_RED "ERROR: " COLOR_RESET
                                     "allocate memory for dotfiles failed\n");
        return RET_ERR_MALLOC;
    }

    *count = 0;
    for (int i = 0; i < arr_size; ++i) {
        cJSON *item = NULL;

        item = cJSON_GetObjectItem(arr_item, "name");
        if (!item && !cJSON_IsString(item)) {
            arr_item = arr_item->next;
            continue;
        }
        strcpy((*dotfiles)[*count].name, item->valuestring);

        item = cJSON_GetObjectItem(arr_item, "exec");
        if (!item && !cJSON_IsString(item)) {
            arr_item = arr_item->next;
            continue;
        }
        strcpy((*dotfiles)[*count].exec, item->valuestring);

#if defined(_WIN32) || defined(_WIN64)
        item = cJSON_GetObjectItem(arr_item, "windows");
#else
        item = cJSON_GetObjectItem(arr_item, "linux");
#endif
        if (!item && !cJSON_IsString(item)) {
            arr_item = arr_item->next;
            continue;
        }
        sprintf((*dotfiles)[*count].path, "%s/%s", home_dir, item->valuestring);

        __df_set_align_params(&(*dotfiles)[*count], align_params);

        (*count)++;
        arr_item = arr_item->next;
    }

    cJSON_Delete(cjson);
    return RET_OK;
}

bool df_is_exec_exist(const Dotfile *dotfile)
{
    if (!dotfile) {
        return false;
    }

    char whichCommand[256] = { 0 };
    sprintf(whichCommand, "which %s >/dev/null 2>&1", dotfile->exec);
    return !system(whichCommand);
}

DotfileStatus df_get_status(const Dotfile *dotfile)
{
    if (!df_is_exec_exist(dotfile)) {
        return DOTFILE_STATUS_EXEC_NOT_FOUND;
    }
    return DOTFILE_STATUS_OK;
}
