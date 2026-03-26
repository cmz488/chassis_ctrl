//
// Created by 34254 on 2026/2/12.
//

#include "../Inc/Mpu6050Task.h"
#include <cmath>
#define DT 0.01f //单位秒
#define ALPHA 0.01f

extern "C" {
#include "MPU6050.h"
#include "OLED.h"

void MPU6050_Task() {
  static MPU6050Task mpu6050Task; // 创建 MPU6050 任务实例
  mpu6050Task.start(const_cast<char*> ("mpu6050Task"), 512, osPriorityAboveNormal); // 启动 MPU6050 任务
}
}

int16_t a[3];
int16_t g[3];
int16_t gy;
float pitch;
float pitchacc;
float pitchgyr;

void MPU6050Task::run() {
  for (;;) {
    //计算pitch
    MPU6050_GetData(&a[0], &a[1], &a[2], &g[0], &g[1], &g[2]);
    g[1] -= 16;
    pitchacc = -static_cast<float>(std::atan2(a[0], a[2]) / M_PI * 180);
    pitchacc += 1.5f;
    pitchgyr = pitch + static_cast<float>(g[1]) / 32768.0f * 2000 * DT;
    pitch = ALPHA * pitchacc + (1 - ALPHA) * pitchgyr; //融合滤波
    osDelay(DT * 1000);
  }
}
