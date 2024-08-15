#include "Rte_Type.h"

#include "Os.h"
#include "Com.h"
#include "Rte_Internal.h"

TASK (TASK_MIRROR_RIGHT) {
    VAR(EventMaskType, AUTOMATIC) Event;

    while(1)
    {
        (VAR(void, AUTOMATIC))WaitEvent(Rte_DRE_ChangeRight);
        Event = 0U;
        (VAR(void, AUTOMATIC))GetEvent(TASK_MIRROR_RIGHT, &Event);

        if( (Event & Rte_DRE_ChangeRight) > 0U ) {
            (VAR(void, AUTOMATIC))ClearEvent(Rte_DRE_ChangeRight);
            Rte_ChangeRight();
        } 
    }
}