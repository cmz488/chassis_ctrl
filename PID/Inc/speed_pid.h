//
// Created by 34254 on 2025/12/21.
//

#ifndef F407_LEARN_SPEED_PID_H
#define F407_LEARN_SPEED_PID_H

#pragma once
#ifdef __cplusplus

float clamp(float val, float lo, float hi);

class SpeedPID {
private:
    float kp;
    float ki;
    float kd;
    float maxOutput;
    float minOutput;
    float integral;
    float maxIntegral;
    float precError;
    float pretarget;

public:
    SpeedPID(float kp, float ki, float kd, float maxOutput, float maxIntegral);

    void speed_PID_clear();

    float speed_PID_calculate(float target,float current,float dt);

};
#endif

#ifdef __cplusplus
extern "C"{
#endif

  void SpeedPID_clear();
  float SpeedPID_calculate(float target,float current,float dt);

#ifdef __cplusplus
};
#endif

#endif //F407_LEARN_SPEED_PID_H
