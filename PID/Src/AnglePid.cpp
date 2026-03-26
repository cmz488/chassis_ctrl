//
// Created by 34254 on 2026/2/12.
//

#include "../Inc/AnglePid.h"


extern "C" {
}

AnglePID::AnglePID(float kp,float ki,float kd,float maxOut,float maxIntegral):PIDbase(kp, ki, kd,maxOut,maxIntegral),offset(3) {}

float AnglePID::AnglePID_Calculate(float target, float current, float dt) {
  float error = target - current; //计算当前错误

  if(pretarget * target < 0){
    integral = 0.0f;
  } // 过零处理
  float der = (current - last_current) / dt; //使用微分先行
  float output = Kp * error - Kd * der;
  if(output < max_output && output > -max_output){
    integral += Ki * error * dt;
    integral = std::clamp(integral,-max_integral,max_integral);
  }
  output +=  integral ;
  if (output>0) output += offset;
  if (output<0) output -= offset;
  output = std::clamp(output,-max_output,max_output);

  precError = error;
  pretarget = target;
  last_current = current;
  return output;
}
