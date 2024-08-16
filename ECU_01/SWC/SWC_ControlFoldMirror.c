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

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : GetParram                                                    */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Read calibration data from SWC Calibration and mirror angle  */
/*               data from NV                                                 */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Descriptor  : Read data from NV block                                      */
/* Note        :                                                              */
/******************************************************************************/

FUNC(void, RTE_CODE) GetParram(void) {
    // read data from NV
    Rte_Call_NV_NvM_ReadBlock(&AngleValue);

    // read data from ParamSWC
    Rte_Read_Parameter_AngleParamValue(&ParamValue);
}

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : GetUserOption_10ms                                           */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Read button state value and send to MirrorControl SWC        */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Descriptor  : Read data from NV block                                      */
/* Note        :                                                              */
/******************************************************************************/

FUNC(void, RTE_CODE) GetUserOption_10ms(void) {
    // read pin state
    VAR(uint8, AUTOMATIC) button_state;

    Rte_Call_RP_IO_IoHwAb_Dio_ReadChannelGroup(Dio_Button_GroupID, button_state);
    button[0] = (button_state & 0x01);                  // get bit 0
    button[1] = (button_state & 0x02) >> 0x01;
    button[2] = (button_state & 0x04) >> 0x02;
    button[3] = (button_state & 0x08) >> 0x03;
    button[4] = (button_state & 0x10) >> 0x04;
    button[5] = (button_state & 0x20) >> 0x05;
    button[6] = (button_state & 0x40) >> 0x06;          // get bit 6

    Rte_Write_PP_Position_ButtonArray(button);
}

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : GetUserOption_10ms                                           */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Calculate angle and send value to ECU_02 and ECU_03          */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Descriptor  : Read data from NV block                                      */
/* Note        :                                                              */
/******************************************************************************/

FUNC(void, RTE_CODE) UpdatePossition(void) 
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
        if (button[3]) 
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
        if (button[4])
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
        if (button[5]) 
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
        if (button[6]) 
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
        if (button[3]) {                        // Increase yaw angle
            if (AngleValue.right_yaw_angle < ParamValue.yaw_upper_limit) 
            {
                AngleValue.right_yaw_angle += ParamValue.yaw_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
        if (button[4]) {                        // Decrease yaw angle
            if (AngleValue.right_yaw_angle > ParamValue.yaw_lower_limit) 
            {
                AngleValue.right_yaw_angle -= ParamValue.yaw_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
        if (button[5]) {                        // Increase pitch angle
            if (AngleValue.right_pitch_angle < ParamValue.pitch_upper_limit) 
            {
                AngleValue.right_pitch_angle += ParamValue.pitch_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
        if (button[6]) {                        // Decrease pitch angle
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
        Rte_Call_NV_NvM_WriteBlock(&AngleValue);
    }

    // Send Signal to ComM
    Rte_Write_SetAngle_AngleValue_SignalGroup(AngleValue);
}

/* End of SWC.c */
