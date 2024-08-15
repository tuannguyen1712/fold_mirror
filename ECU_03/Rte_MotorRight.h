#ifndef RTE_MOTORRIGHT_H
#define RTE_MOTORRIGHT_H

#include <stdint.h>
#include "DataType.h"

FUNC(void, RTE_CODE_EcucPartition_3) Rte_ChangeRight( VAR(void, AUTOMATIC) );
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_3) Rte_Read_RP_ChangeRightAngle_Angles(Angles_t* Angles);
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_3) Rte_Call_RP_IO_Hwab_MotorControl(VAR(uint8, AUTOMATIC) id, VAR(uint8, AUTOMATIC) angle);

#endif