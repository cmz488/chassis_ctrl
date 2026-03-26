//
// Created by 34254 on 2026/2/11.
//

#include "../Inc/LED.h"
#include  "main.h"

void LED_ON(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
}

void LED_OFF(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
}

void LED_Toggle(void)
{
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
}