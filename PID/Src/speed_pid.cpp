//
// Created by 34254 on 2025/12/21.
//


#include "speed_pid.h"

float clamp(float val, float lo, float hi){
  return val<hi ? (val>lo ? val : lo) : hi;
}

SpeedPID::SpeedPID(float kp, float ki, float kd, float maxOutput, float maxIntegral)
: kp(kp) ,ki(ki) ,kd(kd),maxOutput(maxOutput),minOutput(-maxOutput), maxIntegral(maxIntegral){}

void SpeedPID::speed_PID_clear() {
  integral = 0.0f;
  precError = 0.0f;
}

float SpeedPID::speed_PID_calculate(float target, float current, float dt) {
  float error = target - current;

  if(pretarget * target < 0){
    integral = 0.0f;
  }

  float der = (error - precError) * dt;
  float output = kp * error + kd * der;
  if(output < maxOutput && output > minOutput){
    integral += ki * error * dt;
    integral = clamp(integral,-maxIntegral,maxIntegral);
  }
  output += integral;
  output = clamp(output,-maxOutput,maxOutput);

  precError = error;
  pretarget = target;
  return output;
}

extern "C"{
  SpeedPID speedPID(1.0f,0.01f,0.001f,5000,250);
  void  SpeedPID_clear(){
    speedPID.speed_PID_clear();
  }
  float SpeedPID_calculate(float target,float current,float dt){
    return speedPID.speed_PID_calculate(target,current,dt);
  }
}