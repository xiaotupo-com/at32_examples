/* add user code begin Header */
/**
 **************************************************************************
 * @file     main.c
 * @brief    main program
 **************************************************************************
 *                       Copyright notice & Disclaimer
 *
 * The software Board Support Package (BSP) that is made available to
 * download from Artery official website is the copyrighted work of Artery.
 * Artery authorizes customers to use, copy, and distribute the BSP
 * software and its related documentation for the purpose of design and
 * development in conjunction with Artery microcontrollers. Use of the
 * software is governed by this copyright notice and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
 * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
 * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
 * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
 * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 **************************************************************************
 */
/* add user code end Header */

/* Includes ------------------------------------------------------------------*/
#include "at32f435_437_wk_config.h"
#include "wk_exint.h"
#include "wk_gpio.h"
#include "wk_system.h"
#include "wk_usart.h"

/* private includes ----------------------------------------------------------*/
/* add user code begin private includes */
#include "sf_buzzer.h"
#include "sf_system.h"
#include "sf_utils.h"
#include <stdio.h>

/* add user code end private includes */

/* private typedef -----------------------------------------------------------*/
/* add user code begin private typedef */

/* add user code end private typedef */

/* private define ------------------------------------------------------------*/
/* add user code begin private define */

/* add user code end private define */

/* private macro -------------------------------------------------------------*/
/* add user code begin private macro */

/* add user code end private macro */

/* private variables ---------------------------------------------------------*/
/* add user code begin private variables */

/* add user code end private variables */

/* private function prototypes --------------------------------------------*/
/* add user code begin function prototypes */

/* add user code end function prototypes */

/* private user code ---------------------------------------------------------*/
/* add user code begin 0 */

/* add user code end 0 */

/**
 * @brief main function.
 * @param  none
 * @retval none
 */
int main(void)
{
    /* add user code begin 1 */

    /* add user code end 1 */

    /* system clock config. */
    wk_system_clock_config();

    /* config periph clock. */
    wk_periph_clock_config();

    /* nvic config. */
    wk_nvic_config();

    /* timebase config. */
    wk_timebase_init();

    /* usart1 already supports printf. */
    /* init usart1 function. */
    wk_usart1_init();

    /* init exint function. */
    wk_exint_config();

    /* init gpio function. */
    wk_gpio_config();

    /* add user code begin 2 */
    printf("初始化结束...\n");
    /* add user code end 2 */

    while (1) {
        /* add user code begin 3 */
        // 按键长按判断
        while (GET_BIT(sf_sys.key_state, KEY_INT_BIT) &&
               (gpio_input_data_bit_read(SW1_GPIO_PORT, SW1_PIN) == SET)) {
            sf_sys.key_state = SET_BIT(sf_sys.key_state, KEY_COUNT_BIT); // 置位计数标志位

            // 判断按键按下超过 500ms
            if (sf_sys.long_down_count >= 1000) {
                printf("long_down_count>=500\n");
                sf_sys.key_state = CLEAR_BIT(sf_sys.key_state, KEY_COUNT_BIT);
                // 按键长按成功
                sf_sys.key_state = CLEAR_BIT(sf_sys.key_state, KEY_INT_BIT);
                SELF_LOGICAL_NOT(sf_sys.buzzer_flag); // 反转蜂鸣器的开关状态
                BUZZER_ON();
                wk_delay_ms(5);
                BUZZER_OFF();
                wk_delay_ms(5);
                // 判断蜂鸣器标志位，向串口打印蜂鸣器开启状态
                switch (sf_sys.buzzer_flag) {
                case BUZZER_FLAG_ON:
                    printf("蜂鸣器已打开\n");
                    break;
                case BUZZER_FLAG_OFF:
                    printf("蜂鸣器已关闭\n");
                    break;
                default:
                    break;
                }
            }
        }
        sf_sys.key_state = CLEAR_BIT(sf_sys.key_state, KEY_COUNT_BIT); // 清除计数标志位

        // 按键单击操作判断
        if (GET_BIT(sf_sys.key_state, KEY_INT_BIT) &&
            (gpio_input_data_bit_read(SW1_GPIO_PORT, SW1_PIN) == RESET)) {
            // 判断蜂鸣器标志位
            if (sf_sys.buzzer_flag == BUZZER_FLAG_ON) { 
                BUZZER_ON();
                wk_delay_ms(10);
                BUZZER_OFF();
                wk_delay_ms(10);
            }

            SELF_LOGICAL_NOT(sf_sys.led2_flag); // 自身逻辑取反
            gpio_bits_write(LED2_GPIO_PORT, LED2_PIN, sf_sys.led2_flag);
            sf_sys.key_state = CLEAR_BIT(sf_sys.key_state, KEY_INT_BIT);
        }
        /* add user code end 3 */
    }
}

/* add user code begin 4 */

/* add user code end 4 */
