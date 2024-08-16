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

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Read_RP_Setting_ButtonArray                              */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Receive status of buttons from Setting Port                  */
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
/* Name        : Rte_Call_NV_PreviousNvValue                                  */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Read data from NV block                                      */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/

FUNC(NvM_ReturnType, RTE_CODE) Rte_Call_NV_NvM_ReadBlock( P2VAR(AUTOSAR_Angle, AUTOMATIC, RTE_APPL_DATA) DataBuffer)
{
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    // Call the NvM_ReadBlock function with the specified BlockId, buffer, and length
    ret_val = NvM_ReadBlock(NV_ANGLE_BLOCK_ID, DataBuffer);

    // Handle the return value to check if the operation was successful
    return ret_val;

}

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Call_NV_NvM_WriteBlock                                   */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Write data to NV block                                       */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/

FUNC(NvM_ReturnType, RTE_CODE) Rte_Call_NV_NvM_WriteBlock( P2CONST(AUTOSAR_Angle, AUTOMATIC, RTE_APPL_DATA) DataBuffer)
{
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;
    // Call the NvM_WriteBlock function with the specified BlockId, buffer
    ret_val = NvM_WriteBlock(NV_ANGLE_BLOCK_ID, DataBuffer);
    // Handle the return value to check if the operation was successful
    return ret_val;
}

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Call_Dem_SetEventStatus                                  */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Set status of diagnostic event                               */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/

FUNC(Std_ReturnType , RTE_CODE) Rte_Call_Dem_SetEventStatus(Dem_EventIdType eventId, Dem_EventStatusType eventStatus) 
{
    VAR(Std_ReturnType, AUTOMATIC) ret_val;
    ret_val = Dem_SetEventStatus(eventId, eventStatus);
    return ret_val;
}

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Write_SetAngle_AngleValue_SignalGroup                    */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Send Signal group to PDU buffer                              */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/

#define RTE_START_SEC_CODE_EcucPartition_0
#include "Rte_MemMap.h"
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SetAngle_AngleValue_SignalGroup( VAR(AUTOSAR_Angle, AUTOMATIC) data ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;
    VAR(Std_ReturnType, AUTOMATIC) ret;
    VAR(AUTOSAR_Angle, AUTOMATIC) tmp_data = data;

    Com_SendSignal( ComConf_ComGroupSignal_ComISignal_HS_CAN1_SetAngle_Fold, &tmp_data.fold_angle );
    Com_SendSignal( ComConf_ComGroupSignal_ComISignal_HS_CAN1_SetAngle_LeftYaw, &tmp_data.left_yaw_angle );
    Com_SendSignal( ComConf_ComGroupSignal_ComISignal_HS_CAN1_SetAngle_LeftPitch, &tmp_data.left_pitch_angle );
    Com_SendSignal( ComConf_ComGroupSignal_ComISignal_HS_CAN1_SetAngle_RightYaw, &tmp_data.right_yaw_angle );
    Com_SendSignal( ComConf_ComGroupSignal_ComISignal_HS_CAN1_SetAngle_RightPitch, &tmp_data.right_pitch_angle );
    ret = Com_SendSignalGroup(ComConf_ComSignalGroup_ComISignal_HS_CAN1_SetAngle);

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

FUNC(NvM_ReturnType, RTE_CODE) Rte_Read_Parameter_AngleParamValue( P2VAR(AUTOSAR_Angle, AUTOMATIC, RTE_APPL_DATA) ParamPtr ) {
    // stimulate function to read data from SWC calibration
}

#include "Rte_MemMap.h"
FUNC(void, RTE_CODE) Rte_GetParram( VAR(void, AUTOMATIC) ) {
    GetParram();
}

#include "Rte_MemMap.h"
FUNC(void, RTE_CODE) Rte_UpdatePossition( VAR(void, AUTOMATIC) ) {
    UpdatePossition();
}

/* End of Rte_MirrorControl.c */