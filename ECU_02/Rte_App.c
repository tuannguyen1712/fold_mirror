#include "Rte_MotorLeft.h"

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : TASK_MIRROR_LEFT                                             */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Program on ECU_02                                            */
/* Author      : Autosar_Group_02                                             */
/* Note        : TASK_MIRROR_LEFT is extended task. Activating this task is   */
/*               autostart. The event that awakens this task is               */
/*               Rte_DRE_ChangeLeft - OSEvent_ChangeLeft                      */
/******************************************************************************/
TASK (TASK_MIRROR_LEFT) {
    VAR(EventMaskType, AUTOMATIC) Event;

    while(1)
    {
        (VAR(void, AUTOMATIC))WaitEvent(Rte_DRE_ChangeLeft);
        Event = 0U;
        (VAR(void, AUTOMATIC))GetEvent(TASK_MIRROR_LEFT, &Event);

        if( (Event & Rte_DRE_ChangeLeft) > 0U ) {
            (VAR(void, AUTOMATIC))ClearEvent(Rte_DRE_ChangeLeft);
            Rte_ChangeLeft();
        } 
    }
}