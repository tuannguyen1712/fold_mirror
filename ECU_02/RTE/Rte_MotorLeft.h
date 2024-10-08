#ifndef RTE_MOTORLEFT_H
#define RTE_MOTORLEFT_H

#include <stdint.h>
#include "DataType.h"

FUNC(void, RTE_CODE_EcucPartition_2) Rte_ChangeLeft(VAR(void, AUTOMATIC));
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_2) Rte_Read_RP_ChangeLeftAngle_Angles(angles_t* angles);
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_2) Rte_Call_RP_IO_Hwab_MotorControl(VAR(uint8_t, AUTOMATIC) id, VAR(uint8_t, AUTOMATIC) adc_value);
#endif