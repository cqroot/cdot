#include "dotfile.h"
#include "color.h"
#include <cJSON.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

RetCode read_dotfiles_from_json(Dotfile **dotfiles, int *dotfile_cnt)
{
    FILE *fptr = fopen("./cdot.json", "r");
    if (!fptr) {
        fprintf(stderr,
                COLOR_FG_RED "ERROR: " COLOR_RESET
                             "open file ./cdot.json failed (errno: %d)\n",
                errno);
        return RET_FAILED;
    }

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

    *dotfile_cnt = 0;
    for (int i = 0; i < arr_size; ++i) {
        cJSON *item = NULL;

        item = cJSON_GetObjectItem(arr_item, "name");
        if (!item && !cJSON_IsString(item)) {
            arr_item = arr_item->next;
            continue;
        }
        strcpy((*dotfiles)[*dotfile_cnt].name, item->valuestring);

        item = cJSON_GetObjectItem(arr_item, "exec");
        if (!item && !cJSON_IsString(item)) {
            arr_item = arr_item->next;
            continue;
        }
        strcpy((*dotfiles)[*dotfile_cnt].exec, item->valuestring);

        (*dotfile_cnt)++;
        arr_item = arr_item->next;
    }

    cJSON_Delete(cjson);
    return RET_OK;
}
