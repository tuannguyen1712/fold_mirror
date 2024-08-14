/******************************************************************************/
/* Copyright   : Autosar_02_G2                                                */
/* System Name : AUTOSAR BSW                                                  */
/* File Name   : Rte_SwcAdjuster.h                                            */
/* Version     : v2.2.2                                                       */
/* Contents    : Ecu Configuration(Ecuc)                                      */
/* Author      : QINeS Ecuc Generator 2019.12 (Java)                          */
/* Note        :                                                              */
/******************************************************************************/

#ifndef RTE_SWCADJUSTER_H
#define RTE_SWCADJUSTER_H

#include "Rte_Type.h"

#define NUM_BUTTONS 7

typedef uint8 buttonValues[NUM_BUTTONS];

FUNC(void, RTE_CODE_EcucPartition_0) Rte_GetUserOption_10ms(void);
FUNC(Std_ReturnType, AUTOMATIC) Rte_Write_PP_Position_ButtonArray( VAR(buttonValues, AUTOMATIC) button );
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Call_RP_IO_Dio_ReadChannel( VAR(uint8, AUTOMATIC) id, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) value );

#endif