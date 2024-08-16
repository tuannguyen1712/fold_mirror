/******************************************************************************/
/* Copyright   : Autosar_02_G2                                                */
/* System Name : AUTOSAR BSW                                                  */
/* File Name   : Rte_SwcAdjuster.c                                            */
/* Version     : v2.2.2                                                       */
/* Contents    : Ecu Configuration(Ecuc)                                      */
/* Author      : QINeS Ecuc Generator 2019.12 (Java)                          */
/* Note        :                                                              */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Os.h"
#include "Rte_Internal.h"
#include "Com.h"
#include "Rte_SwcAdjuster.h"
#include "DataType.h"

VAR(buttonValues, AUTOMATIC) buttonArrayVal;

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Write_SetAngle_AngleValue_SignalGroup                    */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : write data to PP_Position port                               */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_PP_Position_ButtonArray( VAR(buttonValues, AUTOMATIC) button ) {
    VAR (Std_ReturnType, AUTOMIC) ret_val = RTE_E_OK

    for (VAR(uint8, AUTOMATIC) i = 0; i < NUM_BUTTONS; i++)
    {
        buttonArrayVal[i] = button[i];
    }

    // scheduled for runnale UpdatePossition
    SetEvent(TASK_CONTROL, Rte_DRE_UpdatePosition);
    
    return ret_val;
}

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Write_SetAngle_AngleValue_SignalGroup                    */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : call service IoHwAb_Dio_ReadChannelGroup from IO port,       */
/*               return value 8 bit (each bit is 1 pin state)                 */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_RP_IO_IoHwAb_Dio_ReadChannelGroup( VAR(uint8, AUTOMATIC) id, P2VAR(buttonValues, AUTOMATIC, RTE_APPL_DATA) value ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;
    if (value == NULL) {
        ret_val = RTE_E_INVALID;
        return ret_val;
    }
    retval = IoHwAb_Dio_ReadChannelGroup( id, value );
    return ret_val;
}

#include "Rte_MemMap.h"
FUNC(void, RTE_CODE) Rte_GetUserOption_10ms(void) {
    GetUserOption_10ms();
}

/* End of Rte_Adjuster.c */
