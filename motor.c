/*
 * EGG OpenSource EBike firmware
 *
 * Copyright (C) Casainho, 2015, 2106, 2017.
 *
 * Released under the GPL License, Version 3
 */

#include <stdint.h>
#include <stdio.h>
#include "stm8s_gpio.h"
#include "stm8s_tim1.h"
#include "motor.h"
#include "gpio.h"
#include "motor.h"
#include "pwm.h"

uint16_t ui16_log_counter = 0;
//uint16_t ui16_log_time_counter = 0;
//uint16_t ui16_log_time[100];
uint8_t ui8_log_motor_state[LOG_COUNTER_MAX];
uint16_t ui16_log_PWM_cycles_counter[LOG_COUNTER_MAX];
uint16_t ui16_log_PWM_cycles_counter_total[LOG_COUNTER_MAX];
uint8_t ui8_log_motor_rotor_position[LOG_COUNTER_MAX];


uint16_t ui16_PWM_cycles_counter = 0xffff;
uint16_t ui16_motor_speed_erps = 0;
uint16_t ui16_speed_inverse = 0;
uint8_t ui8_motor_rotor_position = 0; // in 360/256 degrees
uint8_t ui8_motor_rotor_absolute_position = 0; // in 360/256 degrees
uint8_t ui8_position_correction_value = 0; // in 360/256 degrees
uint16_t ui16_PWM_cycles_counter_total = 0;
uint16_t ui16_PWM_cycles_counter_total_div_4 = 0;
uint8_t ui8_interpolation_angle = 0;

uint16_t ui16_adc_current_phase_B = 0;
uint16_t ui16_adc_current_phase_B_accumulated = 0;
uint16_t ui16_adc_current_phase_B_filtered = 0;

uint8_t ui8_motor_state;
//uint8_t ui8_motor_state = MOTOR_STATE_RUNNING;

uint8_t ui8_startup_counter = 0;

uint8_t ui8_startup = 0;
uint8_t ui8_run = 0;
uint8_t ui8_interpolation = 0;

int8_t hall_sensors;
int8_t hall_sensors_last = 0;

void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void) __interrupt(TIM1_UPD_OVF_TRG_BRK_IRQHANDLER)
{
  hall_sensors_read_and_action ();

  /****************************************************************
  * Motor control: angle interpolation and PWM control
  */
  motor_fast_loop ();
  /****************************************************************/

  // clear the interrupt pending bit for TIM1
  TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
}

void hall_sensor_init (void)
{
  GPIO_Init(HALL_SENSORS__PORT,
	    (GPIO_Pin_TypeDef)(HALL_SENSOR_A__PIN | HALL_SENSOR_B__PIN | HALL_SENSOR_C__PIN),
	    GPIO_MODE_IN_FL_NO_IT);
}

void hall_sensors_read_and_action (void)
{
  // read hall sensors signal pins and mask other pins
  hall_sensors = (GPIO_ReadInputData (HALL_SENSORS__PORT) & (HALL_SENSORS_MASK));
  if (hall_sensors != hall_sensors_last)
  {
    hall_sensors_last = hall_sensors;

    switch (hall_sensors)
    {
      case 3:
      if (ui8_motor_state == MOTOR_STATE_STARTUP)
      {
	//1
	pwm_phase_a_enable_low (ui8_duty_cycle);
	pwm_phase_b_disable (ui8_duty_cycle);
	pwm_phase_c_enable_pwm (ui8_duty_cycle);
      }
      else
      {
	ui8_motor_rotor_absolute_position = (uint8_t) (ANGLE_120 + MOTOR_ROTOR_DELTA_PHASE_ANGLE_RIGHT);
	ui8_motor_rotor_position = ui8_motor_rotor_absolute_position;
      }
      break;

      case 1:
      if (ui8_motor_state == MOTOR_STATE_STARTUP)
      {
	//2
	pwm_phase_a_enable_low (ui8_duty_cycle);
	pwm_phase_b_enable_pwm (ui8_duty_cycle);
	pwm_phase_c_disable (ui8_duty_cycle);
      }
      else
      {
	ui8_motor_rotor_absolute_position = (uint8_t) (ANGLE_180 + MOTOR_ROTOR_DELTA_PHASE_ANGLE_RIGHT);
	ui8_motor_rotor_position = ui8_motor_rotor_absolute_position;
      }
      break;

      case 5:
      if (ui8_motor_state == MOTOR_STATE_STARTUP)
      {
	//3
	pwm_phase_a_disable (ui8_duty_cycle);
	pwm_phase_b_enable_pwm (ui8_duty_cycle);
	pwm_phase_c_enable_low (ui8_duty_cycle);
      }
      else
      {
	ui8_motor_rotor_absolute_position = (uint8_t) (ANGLE_240 + MOTOR_ROTOR_DELTA_PHASE_ANGLE_RIGHT);
	ui8_motor_rotor_position = ui8_motor_rotor_absolute_position;
      }
      break;

      // start of phase B current sinusoid
      case 4:
      ui16_PWM_cycles_counter_total = ui16_PWM_cycles_counter;
      ui16_PWM_cycles_counter_total_div_4 = ui16_PWM_cycles_counter_total >> 2;
      ui16_PWM_cycles_counter = 0;

      ui16_motor_speed_erps = PWM_CYCLES_SECOND / ui16_PWM_cycles_counter_total; // this division takes ~4.2us

//      // update MOTOR_STATE_RUNNING based on motor speed
//      if ((ui8_motor_state != MOTOR_STATE_STARTUP) &&
//	  (ui16_PWM_cycles_counter_total > SPEED_INVERSE_MOTOR_START_RUN))
//      {
//        ui8_motor_state = MOTOR_STATE_STARTUP;
//        pwm_init_6_steps ();
//
//        ui8_startup_counter = 0;
//      }
//      else if ((ui8_motor_state != MOTOR_STATE_RUNNING) &&
//	  (ui8_startup_counter > 16))
//      {
//debug_pin_set ();
//        ui8_motor_state = MOTOR_STATE_RUNNING;
//        pwm_init_bipolar_4q ();
//debug_pin_reset ();
//      }


      // update MOTOR_STATE_RUNNING based on motor speed
      if (ui8_startup == 1)
      {
	ui8_startup = 0;
        ui8_motor_state = MOTOR_STATE_STARTUP;
        pwm_init_6_steps ();

        ui8_startup_counter = 0;
      }
      if (ui8_run == 1)
      {
	ui8_run = 0;
debug_pin_set ();
        ui8_motor_state = MOTOR_STATE_RUNNING;
        pwm_init_bipolar_4q ();
debug_pin_reset ();
      }

      ui8_startup_counter++;

      if (ui8_motor_state == MOTOR_STATE_STARTUP)
      {
	//4
	pwm_phase_a_enable_pwm (ui8_duty_cycle);
	pwm_phase_b_disable (ui8_duty_cycle);
	pwm_phase_c_enable_low (ui8_duty_cycle);
      }
      else
      {
	ui8_motor_rotor_absolute_position = (uint8_t) (ANGLE_300 + MOTOR_ROTOR_DELTA_PHASE_ANGLE_RIGHT);
	ui8_motor_rotor_position = ui8_motor_rotor_absolute_position;
      }
      break;

      case 6:
      if (ui8_motor_state == MOTOR_STATE_STARTUP)
      {
	//5
	pwm_phase_a_enable_pwm (ui8_duty_cycle);
	pwm_phase_b_enable_low (ui8_duty_cycle);
	pwm_phase_c_disable (ui8_duty_cycle);
      }
      else
      {
	ui8_motor_rotor_absolute_position = (uint8_t) (ANGLE_1 + MOTOR_ROTOR_DELTA_PHASE_ANGLE_RIGHT);
	ui8_motor_rotor_position = ui8_motor_rotor_absolute_position;
      }
      break;

      case 2:
      if (ui8_motor_state == MOTOR_STATE_STARTUP)
      {
	//6
	pwm_phase_a_disable (ui8_duty_cycle);
	pwm_phase_b_enable_low (ui8_duty_cycle);
	pwm_phase_c_enable_pwm (ui8_duty_cycle);
      }
      else
      {
	ui8_motor_rotor_absolute_position = (uint8_t) (ANGLE_60 + MOTOR_ROTOR_DELTA_PHASE_ANGLE_RIGHT);
	ui8_motor_rotor_position = ui8_motor_rotor_absolute_position;
      }
      break;

      default:
      return;
      break;
    }
  }
}

// runs every 64us (PWM frequency)
void motor_fast_loop (void)
{
  // count number of fast loops / PWM cycles
  if (ui16_PWM_cycles_counter < PWM_CYCLES_COUNTER_MAX)
  {
    ui16_PWM_cycles_counter++;
  }
  else
  {
    ui16_PWM_cycles_counter = 0xffff;
    ui16_PWM_cycles_counter_total = 0xffff; //(SVM_TABLE_LEN_x1024) / PWM_CYCLES_COUNTER_MAX;
    ui16_speed_inverse = 0xffff;

    if (ui8_startup == 1)
    {
      ui8_interpolation_angle = 0;
      ui8_motor_state = MOTOR_STATE_STARTUP;
  //    pwm_init_6_steps ();
      hall_sensors_last = 0;
      hall_sensors_read_and_action ();
    }

//    // next code is need for motor startup correctly
//    ui8_interpolation_angle = 0;
//    ui8_motor_state = MOTOR_STATE_STARTUP;
////    pwm_init_6_steps ();
//    hall_sensors_last = 0;
//    hall_sensors_read_and_action ();
  }

#define DO_INTERPOLATION 1 // may be usefull when debugging
#if DO_INTERPOLATION == 1

//  if (ui8_motor_state == MOTOR_STATE_RUNNING)
  if (ui8_interpolation == 1)
  {
    // calculate the interpolation angle
    // interpolation seems a problem when motor starts, so don't do it at very low speed
    ui8_interpolation_angle = (uint8_t) ((((uint32_t) ui16_PWM_cycles_counter) << 8) / ui16_PWM_cycles_counter_total);
    ui8_motor_rotor_position = (uint8_t) (ui8_motor_rotor_absolute_position + ui8_position_correction_value + ui8_interpolation_angle);
  }
#endif

  pwm_duty_cycle_controller ();

//  ui16_log_time_counter++;
  if (ui16_log_counter < (LOG_COUNTER_MAX - 1))
  {
//    ui16_log_time[ui16_log_counter] = ui16_log_time_counter;
    ui8_log_motor_state[ui16_log_counter] = ui8_motor_state;
    ui16_log_PWM_cycles_counter[ui16_log_counter] = ui16_PWM_cycles_counter;
    ui16_log_PWM_cycles_counter_total[ui16_log_counter] = ui16_PWM_cycles_counter_total;
    ui8_log_motor_rotor_position[ui16_log_counter] = ui8_motor_rotor_position;
  }
  ui16_log_counter++;
}

int8_t get_motor_rotation_direction (void)
{
  return LEFT;
}
