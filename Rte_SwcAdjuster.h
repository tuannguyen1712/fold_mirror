#ifndef RTE_SWCADJUSTER_H
#define RTE_SWCADJUSTER_H

#include "Rte_Type.h"

#define NUM_BUTTONS 7

typedef uint8 buttonValues[NUM_BUTTONS];

FUNC(void, RTE_CODE_EcucPartition_0) GetUserOption_10ms(void);
FUNC(Std_ReturnType, AUTOMATIC) Rte_Write_PP_Position_ButtonArray( VAR(buttonValues, AUTOMATIC) button );

#endif