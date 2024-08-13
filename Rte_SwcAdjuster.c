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

    button[0] = Dio_ReadChannel(DioChannelId1);
    button[1] = Dio_ReadChannel(DioChannelId2);
    button[2] = Dio_ReadChannel(DioChannelId3);
    button[3] = Dio_ReadChannel(DioChannelId4);
    button[4] = Dio_ReadChannel(DioChannelId5);
    button[5] = Dio_ReadChannel(DioChannelId6);
    button[6] = Dio_ReadChannel(DioChannelId7);

    Rte_Write_PP_Position_ButtonArray(&button);
}

VAR(buttonValues, AUTOMATIC) buttonArrayVal;

FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Write_PP_Position_ButtonArray( VAR(buttonValues, AUTOMATIC) button ) {
    VAR (Std_ReturnType, AUTOMIC) ret_val = RTE_E_OK
    if (button == NULL) {
        ret_val = RTE_E_INVALID;
        return ret_val;
    }

    for (VAR(uint8, AUTOMATIC) i = 0; i < NUM_BUTTONS; i++)
    {
        buttonArrayVal[i] = button[i];
    }
    
    return ret_val;
}


