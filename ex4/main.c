#include "stm32f103xb.h"
#include "stm32f1xx_hal.h"
#include <stdint.h>

void SystemClock_Config(void) {
  RCC_OscInitTypeDef osc = {0};
  RCC_ClkInitTypeDef clk = {0};

  osc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  osc.HSIState = RCC_HSI_ON;
  osc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  osc.PLL.PLLState = RCC_PLL_NONE;
  HAL_RCC_OscConfig(&osc);

  clk.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  clk.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clk.APB1CLKDivider = RCC_HCLK_DIV1;
  clk.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_0);
}

int main(void) {
  HAL_Init();
  SystemClock_Config();

  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitTypeDef gpio = {0};
  gpio.Pin = GPIO_PIN_5;
  gpio.Mode = GPIO_MODE_OUTPUT_PP;
  gpio.Pull = GPIO_NOPULL;
  gpio.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &gpio);
  // uncomment below if you want to debug an incorrect init
  // HAL_GPIO_Init((GPIO_TypeDef *)66, &gpio);

  while (1) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    HAL_Delay(500);
  }
}

void SysTick_Handler(void) { HAL_IncTick(); }
void assert_failed(uint8_t *file, uint32_t line) {
  while (1)
    ;
}
