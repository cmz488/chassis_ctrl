//
// Created by 34254 on 2026/2/12.
//

#ifndef PARADE_CAR_ANGLEPID_H
#define PARADE_CAR_ANGLEPID_H

#ifdef __cplusplus
#include "PIDBase.h"
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
class AnglePID:public PIDbase {
  float last_current;
  float offset;
public:
  AnglePID(float kp,float ki,float kd,float maxOut,float maxIntegral);

  float AnglePID_Calculate(float target,float current,float dt);
};
#endif


#endif //PARADE_CAR_ANGLEPID_H