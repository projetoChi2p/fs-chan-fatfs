#include "ff.h"

#include "FreeRTOS.h"
#include "semphr.h"

int ff_cre_syncobj (BYTE vol, _SYNC_t* sobj) {
    FRESULT result;

    *sobj = xSemaphoreCreateMutex();

    if (*sobj != NULL) {
        result = 1;
    }
    else {
        result = 0;
    }

    return result;
}

int ff_req_grant(_SYNC_t sobj) {
    BaseType_t status;
    int result;

    status = xSemaphoreTake(sobj, (TickType_t)_FS_TIMEOUT);

    if (status == pdTRUE) {
        result = 1;
    }
    else {
        result = 0;
    }

    return result;
}

void ff_rel_grant(_SYNC_t sobj) {
    xSemaphoreGive(sobj);
}

int ff_del_syncobj(_SYNC_t sobj) {
    if (sobj != NULL) {
        vSemaphoreDelete(sobj);
    }

    return 1;
}