//
// Created by 34254 on 2026/2/12.
//

#include "../Inc/ChassisRun.h"
#include <cmath>
#include "ChassisCtrl.h"
#include "cstring"
#define DT 0.01f
#define pitch_bias 3.4f

extern "C" {
#include "Motor.h"
#include "Encoder.h"
#include "Serial.h"
#include  "OLED.h"
#include "key.h"

ChassisRun chassisRun; // 创建 ChassisRun 任务实例
void ChassisRun_Task() {
  chassisRun.start(const_cast<char*> ("chassisRun"), 256, osPriorityNormal); // 启动 ChassisRun 任务
}
}

uint8_t runFlag = 0;
uint8_t keyNum = 0;
int8_t LH;
int8_t LV;
float leftspeed;
float rightspeed;
extern float pitch;
extern int16_t g[3];
extern ChassisCtrl chassisCtrl;

void ChassisRun::run() {
  for (;;) {
    keyNum = key_get_num();
    if (keyNum == 1) {
      runFlag = !runFlag;
    }
    if (pitch > 50 || pitch < -50) {
      runFlag = 0;
    }
    if (runFlag) {
      if (Serial_RxFlag == 1) {
        char *Tag = strtok(Serial_RxPacket, ",");
        if (strcmp(Tag, "joystick") == 0) {
          LH = atoi(strtok(NULL, ","));
          LV = atoi(strtok(NULL, ","));
        }

        Serial_RxFlag = 0;
      }

      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
      leftspeed = Encoder_Get(1) / 44.0f / 0.01f / 9.27666f;
      rightspeed = Encoder_Get(2) / 44.0f / 0.01f / 9.27666f;
      chassisCtrl.set_avgSpeed((leftspeed + rightspeed) / 2);
      chassisCtrl.set_diffSpeed(leftspeed - rightspeed);
      chassisCtrl.Calculate(LV / 25, LH / 25, pitch + pitch_bias, DT);
      Motor_SetPWM(1, chassisCtrl.get_left_PWM());
      Motor_SetPWM(2, chassisCtrl.get_right_PWM());
    } else {
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
      chassisCtrl.PID_clear();
      Motor_SetPWM(1, 0);
      Motor_SetPWM(2, 0);
    }
    osDelay(DT * 1000);
  }
}
