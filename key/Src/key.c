//
// Created by 34254 on 2026/2/11.
//

#include "../Inc/key.h"

uint8_t key_num;

uint8_t key_get_num() {
  uint8_t temp = key_num;
  key_num = 0;
  return temp;
}

uint8_t key_get_state() {
  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET) {
    return 1;
  }
  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET) {
    return 2;
  }
  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_RESET) {
    return 3;
  }
  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_RESET) {
    return 4;
  }
  return 0;
}

void key_scan() {
  static uint8_t CurrState, PrevState;
  PrevState = CurrState;
  CurrState = key_get_state();

  if (CurrState == 0 && PrevState != 0) {
    key_num = PrevState;
  }
}
