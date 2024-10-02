#ifndef __CDOT_DEFINE_H
#define __CDOT_DEFINE_H

#define ARRAY_LEN(arr) sizeof(arr) / sizeof(arr[0])

#define OUT

typedef enum {
    RET_OK,
    RET_FAILED,
    RET_ERR_PARAM,
    RET_ERR_MALLOC,
    RET_ERR_OPEN_FILE,
} RetCode;

#define RETURN_IF_ERR(ret)                                                     \
    if (ret != RET_OK) {                                                       \
        return ret;                                                            \
    }

#define CHECK_PARAM_NOT_NULL(param)                                            \
    if (!param) {                                                              \
        fprintf(stderr, COLOR_FG_RED "ERROR: " COLOR_RESET "param is NULL.");  \
        return RET_ERR_PARAM;                                                  \
    }

#endif /* ifndef __CDOT_DEFINE_H */
