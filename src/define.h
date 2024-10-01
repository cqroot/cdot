#ifndef __CDOT_DEFINE_H
#define __CDOT_DEFINE_H

#define ARRAY_LEN(arr) sizeof(arr) / sizeof(arr[0])

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

#endif /* ifndef __CDOT_DEFINE_H */
