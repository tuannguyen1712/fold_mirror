/******************************************************************************/
/* Copyright   : Autosar_02_G2                                                */
/* System Name : AUTOSAR BSW                                                  */
/* File Name   : Rte_App.c                                                    */
/* Version     : v2.2.2                                                       */
/* Contents    : Ecu Configuration(Ecuc)                                      */
/* Author      : QINeS Ecuc Generator 2019.12 (Java)                          */
/* Note        :                                                              */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Rte_Type.h"

#include "Os.h"
#include "Com.h"
#include "Rte_Internal.h"

extern FUNC(void, RTE_CODE) Rte_GetParram( VAR(void, AUTOMATIC) );
extern FUNC(void, RTE_CODE) Rte_GetUserOption_10ms( VAR(void, AUTOMATIC) );
extern FUNC(void, RTE_CODE) Rte_UpdatePossition( VAR(void, AUTOMATIC) );

// TASK_INIT have higher priority, TASK_INIT and TASK_CONTROL auto run

TASK (TASK_INIT) {
    Rte_GetParram();
    // ActivateTask(TASK_CONTROL);
    TermiateTask();
}

TASK (TASK_CONTROL) {
    VAR(EventMaskType, AUTOMATIC) Event;

    while( 1 )
    {
        (VAR(void, AUTOMATIC))WaitEvent( Rte_TE_10ms_GetOption | Rte_DRE_UpdatePosition );
        Event = 0U;
        (VAR(void, AUTOMATIC))GetEvent( TASK_CONTROL, &Event );

        if( (Event & Rte_TE_10ms_GetOption) > 0U ) {
            (VAR(void, AUTOMATIC))ClearEvent( Rte_TE_10ms_GetOption );
            Rte_GetUserOption_10ms();
             // scheduled for runnale UpdatePossition
        } 
        if ( (Event & Rte_DRE_UpdatePosition) > 0U ) {
            (VAR(void, AUTOMATIC))ClearEvent( Rte_DRE_UpdatePosition );
            Rte_UpdatePossition();
        }
    }
}


/* End of Rte_App.c */
