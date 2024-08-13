#include "Rte_SwcMirrorControl.h"

extern VAR(buttonValues, AUTOMATIC) buttonArrayVal;

VAR(buttonValues, AUTOMATIC) yaw_upper_limit;
VAR(buttonValues, AUTOMATIC) yaw_lower_limit;
VAR(buttonValues, AUTOMATIC) yaw_change_value;

VAR(buttonValues, AUTOMATIC) pitch_upper_limit;
VAR(buttonValues, AUTOMATIC) pitch_lower_limit;
VAR(buttonValues, AUTOMATIC) pitch_change_value;

FUNC(void, RTE_CODE_EcucPartition_0) GetParram(void) 
{
    
}

FUNC(void, RTE_CODE_EcucPartition_0) UpdatePossition(void) 
{
    VAR(buttonValues, AUTOMATIC) button;
    
    VAR(uint8, AUTOMATIC) fold;                 // fold angle value
    VAR(uint8, AUTOMATIC) l_yaw;                // left mirror yaw angle value
    VAR(uint8, AUTOMATIC) l_pitch;              // left mirror pitch angle value
    VAR(uint8, AUTOMATIC) r_yaw;                // right mirror yaw angle value
    VAR(uint8, AUTOMATIC) r_pitch;              // right mirror pitch angle value

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

    // Send data to control swc
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


