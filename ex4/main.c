#include "stm32f103xb.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_flash.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_rcc.h"
#include "stm32f1xx_hal_rcc_ex.h"

void init() {
  HAL_Init();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;

  RCC_OscInitTypeDef osc_struct = {0};
  osc_struct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  osc_struct.HSEState = RCC_HSE_ON;
  osc_struct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  osc_struct.PLL.PLLState = RCC_PLL_ON;
  osc_struct.PLL.PLLMUL = RCC_PLL_MUL9;
  osc_struct.PLL.PLLSource = RCC_PLLSOURCE_HSE;

  RCC_ClkInitTypeDef clock_stuct = {0};
  clock_stuct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  clock_stuct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  clock_stuct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clock_stuct.APB1CLKDivider = RCC_HCLK_DIV2;
  clock_stuct.APB2CLKDivider = RCC_HCLK_DIV1;

  HAL_RCC_OscConfig(&osc_struct);
  HAL_RCC_ClockConfig(&clock_stuct, FLASH_LATENCY_2);
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

int main() {
  init();
  while (1) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    HAL_Delay(200);
  }
}
