/******************************************************************************/
/* Copyright   : SCSK Corporation                                             */
/* System Name : AUTOSAR BSW                                                  */
/* File Name   : Rte_AppComTxRx.h                                             */
/* Version     : v2.2.2                                                       */
/* Contents    : Ecu Configuration(Ecuc)                                      */
/* Author      : QINeS Ecuc Generator 2019.12 (Java)                          */
/* Note        :                                                              */
/******************************************************************************/

#ifndef RTE_APPCOMTXRX_H
#define RTE_APPCOMTXRX_H


/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Rte_AppComTxRx_Type.h"
#include "Rte_DataHandleType.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct Rte_CDS_AppComTxRx {
    VAR(uint8, AUTOMATIC) Rte_Dummy;
};

extern CONSTP2CONST(struct Rte_CDS_AppComTxRx, RTE_CONST, RTE_CONST) Rte_Inst_AppComTxRx;

/*----------------------------------------------------------------------------*/
/* function prototype declarations                                            */
/*----------------------------------------------------------------------------*/
extern FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Write_SetAngle_Fold_Signal( VAR(AUTOSAR_uint8, AUTOMATIC) data );

extern FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Write_SetAngle_LeftYaw_Signal( VAR(AUTOSAR_uint8, AUTOMATIC) data );

extern FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Write_SetAngle_LeftPitch_Signal( VAR(AUTOSAR_uint8, AUTOMATIC) data );

extern FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Write_SetAngle_RightYaw_Signal( VAR(AUTOSAR_uint8, AUTOMATIC) data );

extern FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Write_SetAngle_RightPitch_Signal( VAR(AUTOSAR_uint8, AUTOMATIC) data );

#define AppComTxRx_START_SEC_CODE
#include "AppComTxRx_MemMap.h"
FUNC(void, AppComTxRx_CODE) App_ComTxRx( VAR(void, AUTOMATIC) );
#define AppComTxRx_STOP_SEC_CODE
#include "AppComTxRx_MemMap.h"
#define RTE_RUNNABLE_Run_AppComTxRx App_ComTxRx

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */


#endif /* RTE_APPCOMTXRX_H */

/* End of Rte_AppComTxRx.h */
