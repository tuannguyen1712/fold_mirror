#include "ECU_02_Rte.h"

FUNC(void, RTE_CODE_EcucPartition_2) ChangeLeft(void) {
    uint8_t ArrayAngle[3];
    VAR(Std_ReturnType, AUTOMATIC) ret_val = Rte_Read_RP_Angle(ArrayAngle);
    if (ret_val = RTE_E_INVALID) {
        /* ERROR */
        return;
    }
    Rte_Call_WdgMCheckpointReached(SE_MA_FnO_CP_ID_1);
    Rte_Call_Control_Motor_Fold(ID_MOTOR_FOLD, ArrayAngle[0]); /* Control Fold */
    Rte_Call_WdgMCheckpointReached(SE_MA_FnO_CP_ID_2);

    Rte_Call_WdgMCheckpointReached(SE_MA_LnR_CP_ID_1);
    Rte_Call_Control_Motor_Fold(ID_MOTOR_YAW, ArrayAngle[1]); /* Control Yaw */
    Rte_Call_WdgMCheckpointReached(SE_MA_LnR_CP_ID_2);

    Rte_Call_WdgMCheckpointReached(SE_MA_UnD_CP_ID_1);
    Rte_Call_Control_Motor_Fold(ID_MOTOR_PITCH, ArrayAngle[2]); /* Control Pitch */
    Rte_Call_WdgMCheckpointReached(SE_MA_UnD_CP_ID_2);
}