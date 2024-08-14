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
#define RTE_START_SEC_CODE_EcucPartition_0
#include "Rte_MemMap.h"

extern VAR(buttonValues, AUTOMATIC) yaw_upper_limit;
extern VAR(buttonValues, AUTOMATIC) yaw_lower_limit;
extern VAR(buttonValues, AUTOMATIC) yaw_change_value;

extern VAR(buttonValues, AUTOMATIC) pitch_upper_limit;
extern VAR(buttonValues, AUTOMATIC) pitch_lower_limit;
extern VAR(buttonValues, AUTOMATIC) pitch_change_value;

extern VAR(uint8, AUTOMATIC) fold;                     // fold angle value
extern VAR(uint8, AUTOMATIC) l_yaw;                    // left mirror yaw angle value
extern VAR(uint8, AUTOMATIC) l_pitch;                  // left mirror pitch angle value
extern VAR(uint8, AUTOMATIC) r_yaw;                    // right mirror yaw angle value
extern VAR(uint8, AUTOMATIC) r_pitch;                  // right mirror pitch angle value

TASK (ModeCtrlTask_10ms) {
    VAR(EventMaskType, AUTOMATIC) Event;

    while( 1 )
    {
        (VAR(void, AUTOMATIC))WaitEvent( OSEvent_10ms_GetOption | OSEvent_UpdatePosition );
        Event = 0U;
        (VAR(void, AUTOMATIC))GetEvent( OsTask_ModeCtrlTask_10ms, &Event );

        if( (Event & OSEvent_10ms_GetOption) > 0U ) {
            (VAR(void, AUTOMATIC))ClearEvent( OSEvent_10ms_GetOption );
            GetUserOption_10ms();
        } 
        else if ( (Event & OSEvent_UpdatePosition) > 0U ) {
            (VAR(void, AUTOMATIC))ClearEvent( OSEvent_UpdatePosition );
            UpdatePossition();
        }
    }
}


/* End of Rte_Partition_EcucPartition_0.c */
