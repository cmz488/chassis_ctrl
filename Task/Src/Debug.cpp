//
// Created by 34254 on 2026/2/12.
//

#include "../Inc/Debug.h"


extern "C" {
#include "OLED.h"
#include "Serial.h"

void Debug_Task() {
  static debug debugTask; // 创建 debug 任务实例
  debugTask.start((char *) "debugTask", 256, osPriorityNormal); // 启动 debug 任务
}
}

extern float pitch;
extern float g[3];

void debug::run() {
  for (;;) {
    OLED_Clear();
    OLED_Printf(0, 0, OLED_6X8, "%f", pitch);
    OLED_Printf(0, 16, OLED_6X8, "%f", g[1]);
    OLED_Update();
    osDelay(500);
  }
}
