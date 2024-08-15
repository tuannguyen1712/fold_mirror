#ifndef DATATYPE_H
#define DATATYPE_H

#define NUM_BUTTONS 7
typedef uint8 buttonValues[NUM_BUTTONS];
typedef struct 
{
    uint8 fold_angle;
    uint8 left_yaw_angle;
    uint8 left_pitch_angle;
    uint8 right_yaw_angle;
    uint8 right_pitch_angle;
} AUTOSAR_Angle;
 

#endif