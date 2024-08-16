/******************************************************************************/
/* Copyright   : Autosar_02_G2                                                */
/* System Name : AUTOSAR BSW                                                  */
/* File Name   : Rte_SwcMirrorControl.h                                       */
/* Version     : v2.2.2                                                       */
/* Contents    : Ecu Configuration(Ecuc)                                      */
/* Author      : QINeS Ecuc Generator 2019.12 (Java)                          */
/* Note        :                                                              */
/******************************************************************************/

#ifndef RTE_SWCMIRRORCONTROL_H
#define RTE_SWCMIRRORCONTROL_H

#include "Rte_Type.h"
#include "Rte_SwcAdjuster.h"
#include "DataType.h"

FUNC(void, RTE_CODE) UpdatePossition(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_RP_Setting_ButtonArray( P2VAR(buttonValues, AUTOMATIC, RTE_APPL_DATA) button );
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SetAngle_AngleValue_SignalGroup( VAR(AUTOSAR_Angle, AUTOMATIC) data );
FUNC(NvM_ReturnType, RTE_CODE) Rte_Call_NV_NvM_ReadBlock( P2VAR(AUTOSAR_Angle, AUTOMATIC, RTE_APPL_DATA) DataBuffer);
FUNC(NvM_ReturnType, RTE_CODE) Rte_Call_NV_NvM_WriteBlock( P2CONST(AUTOSAR_Angle, AUTOMATIC, RTE_APPL_DATA) DataBuffer);
FUNC(NvM_ReturnType, RTE_CODE) Rte_Read_Parameter_AngleParamValue( P2VAR(Angle_Param, AUTOMATIC, RTE_APPL_DATA) ParamPtr );

#include "SwcMirrorControl_MemMap.h"

#endif

/* End of Rte_MirrorControl.h */