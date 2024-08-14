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

extern VAR(buttonValues, AUTOMATIC) buttonArrayVal;

VAR(buttonValues, AUTOMATIC) yaw_upper_limit;
VAR(buttonValues, AUTOMATIC) yaw_lower_limit;
VAR(buttonValues, AUTOMATIC) yaw_change_value;

VAR(buttonValues, AUTOMATIC) pitch_upper_limit;
VAR(buttonValues, AUTOMATIC) pitch_lower_limit;
VAR(buttonValues, AUTOMATIC) pitch_change_value;

VAR(uint8, AUTOMATIC) fold;                     // fold angle value
VAR(uint8, AUTOMATIC) l_yaw;                    // left mirror yaw angle value
VAR(uint8, AUTOMATIC) l_pitch;                  // left mirror pitch angle value
VAR(uint8, AUTOMATIC) r_yaw;                    // right mirror yaw angle value
VAR(uint8, AUTOMATIC) r_pitch;                  // right mirror pitch angle value

FUNC(void, RTE_CODE_EcucPartition_0) GetParram(void) 
{
    
}

FUNC(void, RTE_CODE_EcucPartition_0) UpdatePossition(void) 
{
    VAR(buttonValues, AUTOMATIC) button;

    Rte_Write_PP_Position_ButtonArray(&button);

    if (btn[2] == 1) 
    {                                           // press fold button, chage fold state
        if (fold == 90)         
            fold = 0;
        else if (fold == 0) {
            fold = 90;
        }
    }

    if (button[0] && !button[1])                // Left mirror
    { 
        if (button[4]) 
        {                                       // Increase yaw angle
            if (l_yaw < yaw_upper_limit) 
            {
                l_yaw += yaw_change_value;
            }
            else {
                // do nothing
            }
        }
        if (button[5])
        {                                       // Decrease yaw angle
            if (l_yaw > yaw_lower_limit) 
            {
                l_yaw -= yaw_change_value;
            }
            else {
                // do nothing
            }
        }
        if (button[6]) 
        {                                       // Increase pitch angle
            if (l_pitch < pitch_upper_limit) 
            {
                l_pitch += pitch_change_value;
            }
            else {
                // do nothing
            }
        }
        if (button[5]) 
        {                                       // Decrease pitch angle
            if (l_pitch > pitch_lower_limit) 
            {
                l_pitch -= pitch_change_value;
            }
            else {
                // do nothing
            }
        }
    }

    else if (!button[0] && button[1])           // Right mirror
    { 
        if (button[4]) {                        // Increase yaw angle
            if (l_yaw < yaw_upper_limit) 
            {
                l_yaw += yaw_change_value;
            }
            else {
                // do nothing
            }
        }
        if (button[5]) {                        // Decrease yaw angle
            if (l_yaw > yaw_lower_limit) 
            {
                l_yaw -= yaw_change_value;
            }
            else {
                // do nothing
            }
        }
        if (button[6]) {                        // Increase pitch angle
            if (l_pitch < pitch_upper_limit) 
            {
                l_pitch += pitch_change_value;
            }
            else {
                // do nothing
            }
        }
        if (button[5]) {                        // Decrease pitch angle
            if (l_pitch > pitch_lower_limit) 
            {
                l_pitch -= pitch_change_value;
            }
            else {
                // do nothing
            }
        }
    }

    // Update new data to NVM

    Rte_Write_SetAngle_Fold_Signal( fold );
    Rte_Write_SetAngle_LeftYaw_Signal( l_yaw );
    Rte_Write_SetAngle_LeftPitch_Signal( l_pitch );
    Rte_Write_SetAngle_RightYaw_Signal( r_yaw );
    Rte_Write_SetAngle_RightPitch_Signal( r_pitch );

}

FUNC(Std_ReturnType, AUTOMATIC) Rte_Read_RP_Setting_ButtonArray( P2VAR(buttonValues, AUTOMATIC, RTE_APPL_DATA) button ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;
    if (button == NULL) {
        ret_val =  RTE_E_INVALID;
        return ret_val;
    }

    *button = buttonArrayVal;
    return ret_val;
}

FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Write_AppComTxRx_AtmResp_AtmResp_Sig_AddExp4( VAR(AUTOSAR_uint8, AUTOMATIC) data ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;
    VAR(Std_ReturnType, AUTOMATIC) ret;
    VAR(AUTOSAR_uint8, AUTOMATIC) tmp_data = data;

    ret = Com_SendSignal( ComConf_ComSignal_ComISignal_HS_CAN1_AtmResp_AtmResp_Sig_AddExp4, &tmp_data );
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
