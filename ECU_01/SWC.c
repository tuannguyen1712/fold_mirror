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

FUNC(void, RTE_CODE_EcucPartition_0) GetParram(void)   
{ 
/*
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
*/

    // read data from NV

    #define MY_NVM_BLOCK_ID 1 // Example Block ID

    FUNC(NvM_ReturnType, RTE_CODE_EcucPartition_0) Rte_Read_NV_PreviousNvValue(NvM_BlockIdType BlockId, uint8* DataBuffer)
    {
        
            NvM_ReturnType result = RTE_E_OK;

            // Call the NvM_ReadBlock function with the specified BlockId, buffer, and length
            result = NvM_ReadBlock(BlockId, DataBuffer);

            // Handle the return value to check if the operation was successful
            return result;

    }

    FUNC(NvM_ReturnType, RTE_CODE_EcucPartion_0) Rte_Write_NV_LastNvValue(NvM_BlockIdType BlockId, const uint8* DataBuffer)
    {
        // Call the NvM_WriteBlock function with the specified BlockId, buffer
        NvM_ReturnType result = NvM_WriteBlock(BlockId, DataBuffer);

        // Handle the return value to check if the operation was successful
        if (result != NVM_REQ_OK) {
        // Error handling can be implemented here: log error, retry the operation, .v.v
        
        }

        return result;

    }


    // read data from ParamSWC

    FUNC(void, RTE_CODE_EcucPartition_0) Rte_Read_RP_Parameter_Limit_value(const ParamConfig* config, AUTOSAR_Angle* Limit_value)
    {
        yaw_upper_limit = config->yaw_upper_limit;
        yaw_lower_limit = config->yaw_lower_limit;
        yaw_change_value = config->yaw_change_value;

    }

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
}

FUNC(void, RTE_CODE_EcucPartition_0) UpdatePossition(void) 
{
    VAR(buttonValues, AUTOMATIC) button;
    VAR(AUTOSAR_Angle, AUTOMATIC) AngleValue;
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
            if (AngleValue.left_yaw_angle < yaw_upper_limit) 
            {
                AngleValue.left_yaw_angle += yaw_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
        if (button[5])
        {                                       // Decrease yaw angle
            if (AngleValue.left_yaw_angle > yaw_lower_limit) 
            {
                AngleValue.left_yaw_angle -= yaw_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
        if (button[6]) 
        {                                       // Increase pitch angle
            if (AngleValue.left_pitch_angle < pitch_upper_limit) 
            {
                AngleValue.left_pitch_angle += pitch_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
        if (button[5]) 
        {                                       // Decrease pitch angle
            if (AngleValue.left_pitch_angle > pitch_lower_limit) 
            {
                AngleValue.left_pitch_angle -= pitch_change_value;
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
            if (AngleValue.right_yaw_angle < yaw_upper_limit) 
            {
                AngleValue.right_yaw_angle += yaw_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
        if (button[5]) {                        // Decrease yaw angle
            if (AngleValue.right_yaw_angle > yaw_lower_limit) 
            {
                AngleValue.right_yaw_angle -= yaw_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
        if (button[6]) {                        // Increase pitch angle
            if (AngleValue.right_pitch_angle < pitch_upper_limit) 
            {
                AngleValue.right_pitch_angle += pitch_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
        if (button[5]) {                        // Decrease pitch angle
            if (AngleValue.right_pitch_angle > pitch_lower_limit) 
            {
                AngleValue.right_pitch_angle -= pitch_change_value;
            }
            else {
                // do nothing
            }
            is_change = 1;
        }
    }

    // Update new data to NVM
    if (is_change) 
    {  


    }

    // Send Signal to ComM
    Rte_Write_SetAngle_AngleValue_SignalGroup(AngleValue);
}

/* End of SWC.c */
