/******************************************************************************/
/* Copyright   : Autosar_02_G2                                                */
/* System Name : AUTOSAR BSW                                                  */
/* File Name   : Rte_SwcAdjuster.c                                            */
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
#include "Rte_SwcAdjuster.h"



/*  Use button to determine use control. BTNx = 1 (press), = 0 (release)
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


FUNC(void, RTE_CODE_EcucPartition_0) GetUserOption_10ms(void) {
    VAR(buttonValues, AUTOMATIC) button;

    Rte_Call_RP_IO_Dio_ReadChannel(DioChannelId1, &button[0]);
    Rte_Call_RP_IO_Dio_ReadChannel(DioChannelId2, &button[1]);
    Rte_Call_RP_IO_Dio_ReadChannel(DioChannelId3, &button[2]);
    Rte_Call_RP_IO_Dio_ReadChannel(DioChannelId4, &button[3]);
    Rte_Call_RP_IO_Dio_ReadChannel(DioChannelId5, &button[4]);
    Rte_Call_RP_IO_Dio_ReadChannel(DioChannelId6, &button[5]);
    Rte_Call_RP_IO_Dio_ReadChannel(DioChannelId7, &button[6]);
    Rte_Call_RP_IO_Dio_ReadChannel(DioChannelId8, &button[7]);

    Rte_Write_PP_Position_ButtonArray(&button);
}

VAR(buttonValues, AUTOMATIC) buttonArrayVal;

FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Write_PP_Position_ButtonArray( VAR(buttonValues, AUTOMATIC) button ) {
    VAR (Std_ReturnType, AUTOMIC) ret_val = RTE_E_OK

    for (VAR(uint8, AUTOMATIC) i = 0; i < NUM_BUTTONS; i++)
    {
        buttonArrayVal[i] = button[i];
    }
    
    return ret_val;
}

FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Call_RP_IO_Dio_ReadChannel( VAR(AppIo_IoHwAb_Q_AdcIdType, AUTOMATIC) id, P2VAR(AppIo_IoHwAb_Q_AdcGroupStatusType, AUTOMATIC, RTE_APPL_DATA) value ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;
    if (value == NULL) {
        ret_val = RTE_E_INVALID;
        return ret_val;
    }
    *value = Dio_ReadChannel( id );
    return ret_val;
}

