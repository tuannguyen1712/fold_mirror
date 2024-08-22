#ifndef SWC_H
#define SWC_H

#define ID_MOTOR_FOLD   0
#define ID_MOTOR_YAW    1
#define ID_MOTOR_PITCH  2

#define RANGE_FOLD_ANGLE    90  /* Angle */
#define RANGE_FOLD_ADC      180 /* ADC */

#define RANGE_YAW_ANGLE     60  /* Angle */
#define RANGE_YAW_ADC       120 /* ADC */

#define RANGE_PITCH_ANGLE   20  /* Angle */
#define RANGE_PITCH_ADC     40  /* ADC */

typedef struct {
    uint8_t fold_adc_value;
    uint8_t yaw_adc_value;
    uint8_t pitch_adc_value;
} adc_values_t

#endif