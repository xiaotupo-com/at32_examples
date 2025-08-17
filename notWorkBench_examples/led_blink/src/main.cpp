/**
 **************************************************************************
 * @file     main.cpp
 * @brief    main program
 **************************************************************************
 *
 **************************************************************************
 */

/* includes ------------------------------------------------------------------*/
#include "at32f435_437_clock.h"
#include "freertos_app.h"
#include "gpio_init.h"
#include "nvic_config.h"

/**
 * @brief  init rtc clock function
 * @param  none
 * @retval none
 */
void mx_rtc_clock_init(void)
{
    /* enable pwc periph clock */
    crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);
    /* enable battery powered domain access */
    pwc_battery_powered_domain_access(TRUE);

    if (CRM->bpdc_bit.ertcsel != CRM_ERTC_CLOCK_LEXT)
    {
        /* reset battery powered domain */
        crm_battery_powered_domain_reset(TRUE);
        crm_battery_powered_domain_reset(FALSE);

        /* config ertc clock source */
        crm_ertc_clock_select(CRM_ERTC_CLOCK_LEXT);
    }

    /* check lext enabled or not */
    if (crm_flag_get(CRM_LEXT_STABLE_FLAG) == RESET)
    {
        crm_clock_source_enable(CRM_CLOCK_SOURCE_LEXT, TRUE);
        while (crm_flag_get(CRM_LEXT_STABLE_FLAG) == RESET)
            ;
    }
}


/**
 * @brief  main function.
 * @param  none
 * @retval none
 */
int main(void)
{
    nvic_config();

    system_clock_config();

    mx_rtc_clock_init();

    xtp::gpio::init();
    freertos_app_init();

    while (1) {}
}
