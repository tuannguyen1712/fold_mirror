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

/* AUTOSAR Version Check : Com */
#if ( ( COM_AR_RELEASE_MINOR_VERSION != RTE_AR_RELEASE_MINOR_VERSION )\
|| ( COM_AR_RELEASE_MAJOR_VERSION != RTE_AR_RELEASE_MAJOR_VERSION ) )
#error "AUTOSAR Release Version error between Com and RTE." 
#endif

/*----------------------------------------------------------------------------*/
/* variables                                                                  */
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : ModeCtrlTask_10ms                                            */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Ecu Configuration(Ecuc)                                      */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/

extern FUNC(void, RTE_CODE_EcucPartition_0) Rte_GetParram( VAR(void, AUTOMATIC) );
extern FUNC(void, RTE_CODE_EcucPartition_0) Rte_GetUserOption_10ms( VAR(void, AUTOMATIC) );
extern FUNC(void, RTE_CODE_EcucPartition_0) Rte_UpdatePossition( VAR(void, AUTOMATIC) );

TASK (TASK_INIT) {
    Rte_GetParram();
    ActivateTask(TASK_CONTROL);
    TermiateTask();
}

TASK (TASK_CONTROL) {
    VAR(EventMaskType, AUTOMATIC) Event;

    while( 1 )
    {
        (VAR(void, AUTOMATIC))WaitEvent( OSEvent_10ms_GetOption | OSEvent_UpdatePosition );
        Event = 0U;
        (VAR(void, AUTOMATIC))GetEvent( OsTask_ModeCtrlTask_10ms, &Event );

        if( (Event & OSEvent_10ms_GetOption) > 0U ) {
            (VAR(void, AUTOMATIC))ClearEvent( OSEvent_10ms_GetOption );
            Rte_GetUserOption_10ms();
        } 
        else if ( (Event & OSEvent_UpdatePosition) > 0U ) {
            (VAR(void, AUTOMATIC))ClearEvent( OSEvent_UpdatePosition );
            Rte_UpdatePossition();
        }
    }
}


/* End of Rte_Partition_EcucPartition_0.c */
