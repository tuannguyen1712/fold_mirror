/******************************************************************************/
/* Copyright   : Autosar_02_G2                                                */
/* System Name : AUTOSAR BSW                                                  */
/* File Name   : Rte_SwcMirrorControl.c                                       */
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
#include "Rte_SwcMirrorControl.h"
#include "DataType.h"


extern VAR(buttonValues, AUTOMATIC) buttonArrayVal;

VAR(uint8, AUTOMATIC) yaw_upper_limit;
VAR(uint8, AUTOMATIC) yaw_lower_limit;
VAR(uint8, AUTOMATIC) yaw_change_value;

VAR(uint8, AUTOMATIC) pitch_upper_limit;
VAR(uint8, AUTOMATIC) pitch_lower_limit;
VAR(uint8, AUTOMATIC) pitch_change_value;

VAR(uint8, AUTOMATIC) fold;                     // fold angle value
VAR(uint8, AUTOMATIC) l_yaw;                    // left mirror yaw angle value
VAR(uint8, AUTOMATIC) l_pitch;                  // left mirror pitch angle value
VAR(uint8, AUTOMATIC) r_yaw;                    // right mirror yaw angle value
VAR(uint8, AUTOMATIC) r_pitch;                  // right mirror pitch angle value

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Read_RP_Setting_ButtonArray                              */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Ecu Configuration(Ecuc)                                      */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/


FUNC(Std_ReturnType, AUTOMATIC) Rte_Read_RP_Setting_ButtonArray( P2VAR(buttonValues, AUTOMATIC, RTE_APPL_DATA) button ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;
    if (button == NULL) {
        ret_val =  RTE_E_INVALID;
        return ret_val;
    }

    for (VAR(uint8, AUTOMATIC) i = 0; i < NUM_BUTTONS; i++)
    {
        button[i] = buttonArrayVal[i];
    }
    return ret_val;
}

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Write_SetAngle_AngleValue_SignalGroup                    */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Ecu Configuration(Ecuc)                                      */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/

#define RTE_START_SEC_CODE_EcucPartition_0
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Write_SetAngle_AngleValue_SignalGroup( VAR(AUTOSAR_Angle, AUTOMATIC) data ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;
    VAR(Std_ReturnType, AUTOMATIC) ret;
    VAR(AUTOSAR_uint8, AUTOMATIC) tmp_data = data;

    ret = Com_SendSignal( ComConf_ComGroupSignal_ComISignal_HS_CAN1_SetAngle_Fold, &data.fold_angle );
    ret = Com_SendSignal( ComConf_ComGroupSignal_ComISignal_HS_CAN1_SetAngle_LeftYaw, &data.left_yaw_angle );
    ret = Com_SendSignal( ComConf_ComGroupSignal_ComISignal_HS_CAN1_SetAngle_LeftPitch, &data.left_pitch_angle );
    ret = Com_SendSignal( ComConf_ComGroupSignal_ComISignal_HS_CAN1_SetAngle_RightYaw, &data.right_yaw_angle );
    ret = Com_SendSignal( ComConf_ComGroupSignal_ComISignal_HS_CAN1_SetAngle_RightPitch, &data.right_pitch_angle );
    ret = Com_SendSignalGroup(ComConf_ComSignalGroup_ComISignal_HS_CAN1_SetAngle_RightPitch)

    switch( ret ) {
    case COM_SERVICE_NOT_AVAILABLE:
        ret_val = RTE_E_COM_STOPPED;
        break;
    case COM_BUSY:
        ret_val = RTE_E_COM_BUSY;
        break;
    default:
        /* nothing */
        break;
    }

    return ret_val;
}

#include "Rte_MemMap.h"
FUNC(void, RTE_CODE_EcucPartition_0) Rte_GetParram( VAR(void, AUTOMATIC) ) {
    GetParram();
}

#include "Rte_MemMap.h"
FUNC(void, RTE_CODE_EcucPartition_0) Rte_UpdatePossition( VAR(void, AUTOMATIC) ) {
    UpdatePossition();
}

/* End of Rte_MirrorControl.c */