//
// Created by 34254 on 2026/2/12.
//

#ifndef PARADE_CAR_CHASSISCTRL_H
#define PARADE_CAR_CHASSISCTRL_H
#pragma once
#include "main.h"
#ifdef __cplusplus
#include "AnglePid.h"
#include "speed_pid.h"
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
class ChassisCtrl {
  AnglePID anglePid;
  SpeedPID speedPid;
  SpeedPID turnPid;

  int16_t avgSpeed;
  int16_t diffSpeed;

  int16_t leftPWM;
  int16_t rightPWM;

public:
  ChassisCtrl(float speed_kp,float speed_ki,float speed_kd,float speed_maxOut,float speed_maxIntegral,
             float angle_kp,float angle_ki,float angle_kd,float angle_maxOut,float angle_maxIntegral,
             float turn_kp,float turn_ki,float turn_kd,float turn_maxOut,float turn_maxIntegral);
  ~ChassisCtrl() = default;

  void Calculate(float target, float diff_speed, float angle, float dt);

  void PID_clear();

  void set_avgSpeed(int16_t avgSpeed) {this->avgSpeed = avgSpeed;}
  void set_diffSpeed(int16_t diffSpeed) {this->diffSpeed = diffSpeed;}

  void set_diffPWM(int16_t diffPWM) {this->diffSpeed = diffPWM;}

  int16_t get_avg_PWM() const ;
  int16_t get_left_PWM() const ;
  int16_t get_right_PWM() const ;
};
#endif


#endif //PARADE_CAR_CHASSISCTRL_H