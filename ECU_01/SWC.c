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

extern VAR(buttonValues, AUTOMATIC) yaw_upper_limit;
extern VAR(buttonValues, AUTOMATIC) yaw_lower_limit;
extern VAR(buttonValues, AUTOMATIC) yaw_change_value;

extern VAR(buttonValues, AUTOMATIC) pitch_upper_limit;
extern VAR(buttonValues, AUTOMATIC) pitch_lower_limit;
extern VAR(buttonValues, AUTOMATIC) pitch_change_value;

extern VAR(uint8, AUTOMATIC) fold;                     // fold angle value
extern VAR(uint8, AUTOMATIC) l_yaw;                    // left mirror yaw angle value
extern VAR(uint8, AUTOMATIC) l_pitch;                  // left mirror pitch angle value
extern VAR(uint8, AUTOMATIC) r_yaw;                    // right mirror yaw angle value
extern VAR(uint8, AUTOMATIC) r_pitch;                  // right mirror pitch angle value

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

    // read data from ParamSWC
}

FUNC(void, RTE_CODE_EcucPartition_0) GetUserOption_10ms(void) {
    VAR(buttonValues, AUTOMATIC) button;
    
    // read pin state
    Rte_Call_RP_IoHwAb_Dio_ReadChannel(DioChannelId1, &button[0]);
    Rte_Call_RP_IoHwAb_Dio_ReadChannel(DioChannelId2, &button[1]);
    Rte_Call_RP_IoHwAb_Dio_ReadChannel(DioChannelId3, &button[2]);
    Rte_Call_RP_IoHwAb_Dio_ReadChannel(DioChannelId4, &button[3]);
    Rte_Call_RP_IoHwAb_Dio_ReadChannel(DioChannelId5, &button[4]);
    Rte_Call_RP_IoHwAb_Dio_ReadChannel(DioChannelId6, &button[5]);
    Rte_Call_RP_IoHwAb_Dio_ReadChannel(DioChannelId7, &button[6]);

    Rte_Write_PP_Position_ButtonArray(button);
    // scheduled for runnale UpdatePossition
    SetEvent(TASK_CONTROL, OSEvent_UpdatePosition);
}

FUNC(void, RTE_CODE_EcucPartition_0) UpdatePossition(void) 
{
    VAR(buttonValues, AUTOMATIC) button;
    VAR(uint8, AUTOMATIC) is_change = 0;

    Rte_Read_RP_Setting_ButtonArray(&button);

    if (button[2] == 1) 
    {                                           // press fold button, chage fold state
        if (fold == 90)         
            fold = 0;
        else if (fold == 0) {
            fold = 90;
        }
        is_change = 1;
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
            is_change = 1;
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
            is_change = 1;
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
            is_change = 1;
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
            is_change = 1;
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
            is_change = 1;
        }
        if (button[5]) {                        // Decrease yaw angle
            if (l_yaw > yaw_lower_limit) 
            {
                l_yaw -= yaw_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
        if (button[6]) {                        // Increase pitch angle
            if (l_pitch < pitch_upper_limit) 
            {
                l_pitch += pitch_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
        if (button[5]) {                        // Decrease pitch angle
            if (l_pitch > pitch_lower_limit) 
            {
                l_pitch -= pitch_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
    }

    // Update new data to NVM
    if (is_change) {

    }

    // Send Signal to ComM
    Rte_Write_SetAngle_Fold_Signal( fold );
    Rte_Write_SetAngle_LeftYaw_Signal( l_yaw );
    Rte_Write_SetAngle_LeftPitch_Signal( l_pitch );
    Rte_Write_SetAngle_RightYaw_Signal( r_yaw );
    Rte_Write_SetAngle_RightPitch_Signal( r_pitch );
}

/* End of SWC.c */
