//
// Created by 34254 on 2026/1/10.
//

#ifndef F407_LEARN_PIDBASE_H
#define F407_LEARN_PIDBASE_H
#pragma once

#ifdef __cplusplus

#include <algorithm>

class PIDbase{
public:

    float Kp;
    float Ki;
    float Kd;

    float max_output; // 最大输出 mini_output = - max_output

    float integral;
    float max_integral; // 最大积分 mini_integral = -max_inegral

    float precError; //记录上次错误
    float pretarget; // 防止反转超调(过零处理）


    PIDbase(float kp,float ki,float kd,float maxOut,float maxIntegral):
    Kp(kp) ,Ki(ki),Kd(kd),
    max_output(maxOut),
    max_integral(maxIntegral){
      integral = 0.0f;
      pretarget = 0.0f;
      precError = 0.0f;
    };
    virtual ~PIDbase(){};
    virtual void PID_clear(){
      integral = 0.0f;
      precError = 0.0f;
    }
    virtual  float PID_Calculate(float target,float current,float dt){
      float error = target - current; //计算当前错误

      if(pretarget * target < 0){
        integral = 0.0f;
      } // 过零处理
      float der = (error - precError) / dt; //
      float output = Kp * error + Kd * der;
      if(output < max_output && output > -max_output){
        integral += Ki * error * dt;
        integral = std::clamp(integral,-max_integral,max_integral);
      }
      output +=  integral ;
      output = std::clamp(output,-max_output,max_output);

      precError = error;
      pretarget = target;
      return output;
    }
};

#endif

#endif //F407_LEARN_PIDBASE_H
