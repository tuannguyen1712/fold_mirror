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
#include "DataType.h"

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_PP_Position_ButtonArray( VAR(buttonValues, AUTOMATIC) button );
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_RP_IO_IoHwAb_Dio_ReadChannelGroup( VAR(uint8, AUTOMATIC) id, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) value );

#endif

/* End of Rte_Adjuster.h */