#include "Rte_MotorRight.h"

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : TASK_MIRROR_RIGHT                                            */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Program on ECU_03                                            */
/* Author      : Autosar_Group_03                                             */
/* Note        : TASK_MIRROR_RIGHT is extended task. Activating this task is  */
/*               autostart. The event that awakens this task is               */
/*               Rte_DRE_ChangeRight - OSEvent_ChangeRight                    */
/******************************************************************************/
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