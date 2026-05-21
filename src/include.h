/**
 * @file include.h
 * @brief include file to deal with board name
 * 
 * This file include common files
 * should be included in c files
 */

#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include "code_base/board_choice.h"


#if defined(two_cell_eval)
#define ADC_H "code_base/drivers/2-cell_eval/adc.h"
#define BOARD_H "code_base/drivers/2-cell_eval/board.h"
#define EUSART_H "code_base/drivers/2-cell_eval/eusart.h"
#define HAL_H "code_base/drivers/2-cell_eval/hal.h"
#define I2C_HOST_H "code_base/drivers/2-cell_eval/i2c_host.h"
#define MCU_CONFIG_H "code_base/drivers/2-cell_eval/mcu_config.h"
#elif defined(sk_8186_2cell_rev2)
#define ADC_H "code_base/drivers/sk-8186_2cell_rev2/adc.h"
#define BOARD_H "code_base/drivers/sk-8186_2cell_rev2/board.h"
#define EUSART_H "code_base/drivers/sk-8186_2cell_rev2/eusart.h"
#define HAL_H "code_base/drivers/sk-8186_2cell_rev2/hal.h"
#define I2C_HOST_H "code_base/drivers/sk-8186_2cell_rev2/i2c_host.h"
#define MCU_CONFIG_H "code_base/drivers/sk-8186/mcu_config.h"
#elif defined(sk_8659_2cell_rev3)
#define ADC_H "code_base/drivers/sk-8659_2cell_rev3/adc.h"
#define BOARD_H "code_base/drivers/sk-8659_2cell_rev3/board.h"
#define EUSART_H "code_base/drivers/sk-8659_2cell_rev3/eusart.h"
#define HAL_H "code_base/drivers/sk-8659_2cell_rev3/hal.h"
#define I2C_HOST_H "code_base/drivers/sk-8659_2cell_rev3/i2c_host.h"
#define MCU_CONFIG_H "code_base/drivers/sk-8659_2cell_rev3/mcu_config.h"
#elif defined(nano_pic18f47k42)
#define ADC_H "code_base/drivers/nano_pic18f47k42/adc.h"
#define BOARD_H "code_base/drivers/nano_pic18f47k42/board.h"
#define EUSART_H "code_base/drivers/nano_pic18f47k42/eusart.h"
#define HAL_H "code_base/drivers/nano_pic18f47k42/hal.h"
#define I2C_HOST_H "code_base/drivers/nano_pic18f47k42/i2c_host.h"
#define I2C_CLIENT_H "code_base/drivers/nano_pic18f47k42/i2c_client.h"
#define MCU_CONFIG_H "code_base/drivers/nano_pic18f47k42/mcu_config.h"
#elif defined(sk_8592_1cell_rev0)
#define ADC_H "code_base/drivers/sk-8592_1cell_rev0/adc.h"
#define BOARD_H "code_base/drivers/sk-8592_1cell_rev0/board.h"
#define EUSART_H "code_base/drivers/sk-8592_1cell_rev0/eusart.h"
#define HAL_H "code_base/drivers/sk-8592_1cell_rev0/hal.h"
#define I2C_HOST_H "code_base/drivers/sk-8592_1cell_rev0/i2c_host.h"
#define MCU_CONFIG_H "code_base/drivers/sk-8592_1cell_rev0/mcu_config.h"
#elif defined(sk_8595_mini)
#define BOARD_H "code_base/drivers/sk-8595_mini/board.h"
#define EUSART_H "code_base/drivers/sk-8595_mini/eusart.h"
#define HAL_H "code_base/drivers/sk-8595_mini/hal.h"
#define I2C_CLIENT_H "code_base/drivers/sk-8595_mini/i2c_client.h"
#define I2C_HOST_H "code_base/drivers/sk-8595_mini/i2c_host.h"
#define MCU_CONFIG_H "code_base/drivers/sk-8595_mini/mcu_config.h"
#endif

#endif /* _INCLUDE_H_ */