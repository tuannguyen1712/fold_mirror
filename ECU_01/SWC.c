/******************************************************************************/
/* Copyright   : Autosar_02_G2                                                */
/* System Name : AUTOSAR BSW                                                  */
/* File Name   : SWC.c                                                        */
/* Version     : v2.2.2                                                       */
/* Contents    : Ecu Configuration(Ecuc)                                      */
/* Author      : QINeS Ecuc Generator 2019.12 (Java)                          */
/* Note        :                                                              */
/******************************************************************************/

#include "Rte_Adjuster.h"
#include "Rte_MirrorControl.h"
#include "DataType.h"

VAR(Angle_Param, AUTOMATIC) ParamValue;

VAR(AUTOSAR_Angle, AUTOMATIC) AngleValue;

/*  Use button to determine user control. BTNx = 1 (press), = 0 (release)
    - Use BTN1 and BTN2  to choose what mirror want to control: 
        + BTN1 = 1, BTN2 = 0: Left mirror
        + BTN1 = 0, BTN2 = 1: Right mirror
        + BTN1 = 0, BTN2 = 0 and BTN1 = 1, BTN2 = 1: No conntrol
    - Use BTN3 to control Fold Angle of both mirror
        + BTN3 = 1: change state (0 or 90)
    - Use BTN4 to increase Yaw Angle of the selected mirror
        + BTN4 = 1: increase Yaw Angle
    - Use BTN5 to decrease Yaw Angle of the selected mirror
        + BTN5 = 1: decrease Yaw Angle
    - Use BTN6 to increase Pitch Angle of the selected mirror
        + BTN6 = 1: increase Pitch Angle
    - Use BTN7 to decrease Pitch Angle of the selected mirror
        + BTN7 = 1: decrease Pitch Angle
*/

FUNC(void, RTE_CODE_EcucPartition_0) GetParram(void) {
    // read data from NV
    Rte_Call_NV_NvM_ReadBlock(NV_ANGLE_BLOCK_ID, &AngleValue);

    // read data from ParamSWC
    Rte_Read_Parameter_AngleParamValue(&ParamValue);
}

FUNC(void, RTE_CODE_EcucPartition_0) GetUserOption_10ms(void) {
    // read pin state
    Rte_Call_RP_IO_IoHwAb_Dio_ReadChannelGroup(Dio_Button_GroupID, button);

    Rte_Write_PP_Position_ButtonArray(button);
}

FUNC(void, RTE_CODE_EcucPartition_0) UpdatePossition(void) 
{
    VAR(buttonValues, AUTOMATIC) button;
    VAR(uint8, AUTOMATIC) is_change = 0;

    Rte_Read_RP_Setting_ButtonArray(&button);

    if (button[2] == 1) 
    {                                           // press fold button, chage fold state
        if (AngleValue.fold_angle == 90)         
            AngleValue.fold_angle = 0;
        else if (AngleValue.fold_angle == 0) {
            AngleValue.fold_angle = 90;
        }
        is_change = 1;
    }

    if (button[0] && !button[1])                // Left mirror
    { 
        if (button[4]) 
        {                                       // Increase yaw angle
            if (AngleValue.left_yaw_angle < ParamValue.yaw_upper_limit) 
            {
                AngleValue.left_yaw_angle += ParamValue.yaw_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
        if (button[5])
        {                                       // Decrease yaw angle
            if (AngleValue.left_yaw_angle > ParamValue.yaw_lower_limit) 
            {
                AngleValue.left_yaw_angle -= ParamValue.yaw_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
        if (button[6]) 
        {                                       // Increase pitch angle
            if (AngleValue.left_pitch_angle < ParamValue.pitch_upper_limit) 
            {
                AngleValue.left_pitch_angle += ParamValue.pitch_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
        if (button[5]) 
        {                                       // Decrease pitch angle
            if (AngleValue.left_pitch_angle > ParamValue.pitch_lower_limit) 
            {
                AngleValue.left_pitch_angle -= ParamValue.pitch_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
    }

    else if (!button[0] && button[1])           // Right mirror
    { 
        if (button[4]) {                        // Increase yaw angle
            if (AngleValue.right_yaw_angle < ParamValue.yaw_upper_limit) 
            {
                AngleValue.right_yaw_angle += ParamValue.yaw_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
        if (button[5]) {                        // Decrease yaw angle
            if (AngleValue.right_yaw_angle > ParamValue.yaw_lower_limit) 
            {
                AngleValue.right_yaw_angle -= ParamValue.yaw_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
        if (button[6]) {                        // Increase pitch angle
            if (AngleValue.right_pitch_angle < ParamValue.pitch_upper_limit) 
            {
                AngleValue.right_pitch_angle += ParamValue.pitch_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
        if (button[5]) {                        // Decrease pitch angle
            if (AngleValue.right_pitch_angle > ParamValue.pitch_lower_limit) 
            {
                AngleValue.right_pitch_angle -= ParamValue.pitch_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
    }

    // Update new data to NVM
    if (is_change) {
        Rte_Call_NV_NvM_WriteBlock(NV_ANGLE_BLOCK_ID, &AngleValue);
    }

    // Send Signal to ComM
    Rte_Write_SetAngle_AngleValue_SignalGroup(AngleValue);
}

/* End of SWC.c */
