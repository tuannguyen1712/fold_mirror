#include "ECU_02_Rte.h"


typedef struct {
    uint8_t Fold;
    uint8_t Yaw;
    uint8_t Pitch;
} Angles_t;

static uint8_t OSEvent_ChangeLeft;
static Angles_t Rte_Angles;
static uint8_t Rte_ArrayAngle[3];

FUNC(void, RTE_CODE_EcucPartition_0) Rte_ChangeLeft( VAR(void, AUTOMATIC) ) {
    Rte_ChangeLeft();
}

FUNC(void, RTE_CODE_EcucPartition_2) Rte_COMCbk_ECU_02_Rx(void) {

    (void)Com_ReceiveSignalGroup(ComConf_ComSignal_ComISignal_HS_CAN1_SetAngle);

    (void)Com_ReceiveSignal(ComConf_ComSignal_ComISignal_HS_CAN1_SetAngle_Fold_Signal, &Rte_Angles);         /*angle_Fold*/
    (void)Com_ReceiveSignal(ComConf_ComSignal_ComISignal_HS_CAN1_SetAngle_LeftYaw_Signal, &Rte_ArrayAngle[1]);      /*angle_Yaw*/
    (void)Com_ReceiveSignal(ComConf_ComSignal_ComISignal_HS_CAN1_SetAngle_LeftPitch_Signal, &Rte_ArrayAngle[2]);    /*angle_Pitch*/

    (void)SetEvent(TASK_MIRROR_LEFT, OSEvent_ChangeLeft);
}

FUNC(void, RTE_CODE_EcucPartition_2) Rte_Read_RP_Angle(uint8_t* ArrayAngle) {
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

FUNC(void, RTE_CODE_EcucPartition_2) Rte_Call_Motor_Control(VAR(uint8, AUTOMATIC) id, VAR(uint8, AUTOMATIC, RTE_APPL_DATA) angle) {
    Hwabst_MotorControl(id, angle);
}
