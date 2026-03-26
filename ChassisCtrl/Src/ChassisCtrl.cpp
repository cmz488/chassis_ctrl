//
// Created by 34254 on 2026/2/12.
//

#include "../Inc/ChassisCtrl.h"
#include <algorithm>
ChassisCtrl chassisCtrl(2.0f, 3.0f, 0.0f, 20, 150,
                        5.0f, 0.0f, 0.05f, 100, 100,
                        4.0f, 10.0f, 0.054f, 50, 20);

extern "C" {
}

ChassisCtrl::ChassisCtrl(float speed_kp, float speed_ki, float speed_kd, float speed_maxOut, float speed_maxIntegral,
                         float angle_kp, float angle_ki, float angle_kd, float angle_maxOut, float angle_maxIntegral,
                         float turn_kp, float turn_ki, float turn_kd, float turn_maxOut,
                         float turn_maxIntegral) : anglePid(AnglePID(angle_kp, angle_ki, angle_kd, angle_maxOut,
                                                                     angle_maxIntegral)),

                                                   speedPid(SpeedPID(speed_kp, speed_ki, speed_kd, speed_maxOut,
                                                                     speed_maxIntegral)),
                                                   turnPid(SpeedPID(turn_kp, turn_ki, turn_kd, turn_maxOut,
                                                                    turn_maxIntegral)) {
}

void ChassisCtrl::Calculate(float target, float diff_speed, float angle, float dt) {
  float speedOutput = speedPid.speed_PID_calculate(target, avgSpeed, dt);
  float angleOutput = anglePid.AnglePID_Calculate(speedOutput, angle, dt);
  float avgPWM = -static_cast<int16_t>(angleOutput);
  float diffPWM = turnPid.speed_PID_calculate(diff_speed, diffSpeed, dt);
  leftPWM = std::clamp(static_cast<int16_t>(avgPWM + diffPWM/2), static_cast<int16_t>(-100), static_cast<int16_t>(100));
  rightPWM = std::clamp(static_cast<int16_t>(avgPWM - diffPWM/2), static_cast<int16_t>(-100), static_cast<int16_t>(100));
}

void ChassisCtrl::PID_clear() {
  anglePid.PID_clear();
  speedPid.speed_PID_clear();
  turnPid.speed_PID_clear();
}

int16_t ChassisCtrl::get_avg_PWM() const {
  return avgSpeed;
}

int16_t ChassisCtrl::get_left_PWM() const {
  return leftPWM;
}

int16_t ChassisCtrl::get_right_PWM() const {
  return rightPWM;
}
