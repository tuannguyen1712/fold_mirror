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

FUNC(void, RTE_CODE_EcucPartition_0) UpdatePossition(void);
FUNC(Std_ReturnType, AUTOMATIC) Rte_Read_RP_Setting_ButtonArray( P2VAR(buttonValues, AUTOMATIC, RTE_APPL_DATA) button );
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Write_SetAngle_AngleValue_SignalGroup( VAR(AUTOSAR_Angle, AUTOMATIC) data );

#include "SwcMirrorControl_MemMap.h"

#endif

/* End of Rte_MirrorControl.h */