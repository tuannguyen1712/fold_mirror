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

// write data to PP_Position port
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Write_PP_Position_ButtonArray( VAR(buttonValues, AUTOMATIC) button ) {
    VAR (Std_ReturnType, AUTOMIC) ret_val = RTE_E_OK

    for (VAR(uint8, AUTOMATIC) i = 0; i < NUM_BUTTONS; i++)
    {
        buttonArrayVal[i] = button[i];
    }
    
    return ret_val;
}

// call service IoHwAb_Dio_ReadChannelGroup from IO port
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Call_RP_IO_IoHwAb_Dio_ReadChannelGroup( VAR(uint8, AUTOMATIC) id, P2VAR(buttonValues, AUTOMATIC, RTE_APPL_DATA) value ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;
    if (value == NULL) {
        ret_val = RTE_E_INVALID;
        return ret_val;
    }
    retval = IoHwAb_Dio_ReadChannelGroup( id, value );
    return ret_val;
}

#include "Rte_MemMap.h"
FUNC(void, RTE_CODE_EcucPartition_0) Rte_GetUserOption_10ms(void) {
    GetUserOption_10ms();
}

/* End of Rte_Adjuster.c */
