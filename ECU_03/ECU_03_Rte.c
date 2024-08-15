#include "ECU_02_Rte.h"

static uint8_t OSEvent_ChangeRight;
static uint8_t Rte_ArrayAngle[3];

FUNC(void, RTE_CODE_EcucPartition_3) Rte_ChangeRight( VAR(void, AUTOMATIC) ) {
    Rte_ChangeRight();
}

FUNC(void, RTE_CODE_EcucPartition_3) Rte_COMCbk_ECU_03_Rx(void) {

    (void)Com_ReceiveSignal(ComConf_ComSignal_ComISignal_HS_CAN1_SetAngle_Fold_Signal, &Rte_ArrayAngle[0]);         /*angle_Fold*/
    (void)Com_ReceiveSignal(ComConf_ComSignal_ComISignal_HS_CAN1_SetAngle_RightYaw_Signal, &Rte_ArrayAngle[1]);      /*angle_Yaw*/
    (void)Com_ReceiveSignal(ComConf_ComSignal_ComISignal_HS_CAN1_SetAngle_RightPitch_Signal, &Rte_ArrayAngle[2]);    /*angle_Pitch*/

    (void)SetEvent(TASK_MIRROR_RIGHT, OSEvent_ChangeRight);
}

FUNC(void, RTE_CODE_EcucPartition_3) Rte_Read_RP_Angle(uint8_t* ArrayAngle) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;
    if (ArrayAngle == Null) {
        ret_val =  RTE_E_INVALID;
        return ret_val;
    }
    for (VAR(uint8, AUTOMATIC) i = 0; i < NUM_ANGLES; i++)
    {
        ArrayAngle[i] = Rte_ArrayAngle[i];
    }
    return ret_val;
}

FUNC(void, RTE_CODE_EcucPartition_3) Rte_Call_Motor_Control(VAR(uint8, AUTOMATIC) id, VAR(uint8, AUTOMATIC, RTE_APPL_DATA) angle) {
    Hwabst_MotorControl(id, angle);
}
