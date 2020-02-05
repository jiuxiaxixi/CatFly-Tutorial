/****************************************Copyright (c)****************************************************
**                                   CatFly WSN无线测试平台
**                                        @jiuxiaxixi           
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:               adc_driver.c
** Last modified Date:      2018-06-28
** Last Version:            v1.0
** Description:             adc驱动
** 
**--------------------------------------------------------------------------------------------------------
** Created By:              张校源
** Created date:            2018-06-28
** Version:                 v1.0
** Descriptions:            The original version 初始版本
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Description:             
**
*********************************************************************************************************/
#include "adc_driver.h"

#include <stdarg.h>
#include "hal/arch/inc/arch_io_memmap.h"
#include "hal/arch/inc/arch_io_reg.h"
#include "hal/arch/inc/arch_io_rcc.h"
#include "hal/arch/inc/arch_io_gpio.h"
#include "hal/CortexM3/hal_io_level.h"

/*********************************************************************************************************
**  配置
*********************************************************************************************************/
#define RCC_ADC_PERIPHERAL      RCC_PERIPHERAL_ADC2   
//基地址配置
 /*!< Peripheral base address in the alias region */
#define PERIPH_BASE             ((uint32_t)0x40000000)
#define APB1PERIPH_BASE         PERIPH_BASE
#define APB2PERIPH_BASE         (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE          (PERIPH_BASE + 0x20000)
//ADC2配置
#define ADC2_BASE               (APB2PERIPH_BASE + 0x2800)
#define ADC2                    ((ADC_TypeDef *) ADC2_BASE)
//RCC配置
#define RCC_BASE_TEST           (AHBPERIPH_BASE + 0x1000)
#define RCC                     ((RCC_TypeDef *) RCC_BASE_TEST)

#define LIGHT_SENSOR_CHANNEL    10
/*********************************************************************************************************
** Function name:       adc_init
** Descriptions:        adc初始化
** Input parameters:    无
** Output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void adc_init(void)
{
  RCC->APB2ENR= RCC->APB2ENR | 1<<4;    
  RCC->APB2ENR|=1<<10;      
  RCC->APB2RSTR|=1<<10;   
  RCC->APB2RSTR&=~(1<<10); 
  RCC->CFGR&=~(3<<14);   //PCLK2 8分频后作为ADC时钟
  RCC->CFGR|=2<<14;      	
  
  // 配置GPIO口时钟和输入模式
  //SystemPeripheralEnable(RCC_PERIPHERAL_IOPC);
  GPIOConfigSet(GPIOC_BASE, GPIO_PIN_0, GPIO_DIR_IN_Analog);
  
  ADC2->CR1&=0XF0FFFF;   //工作模式清0
  ADC2->CR1|=0<<16;      //独立工作模式  
  ADC2->CR1&=~(1<<8);    //非扫描模式	  
  ADC2->CR2&=~(1<<1);    //单词转换模式
  ADC2->CR2&=~(7<<17);	   
  ADC2->CR2|=7<<17;	   //软件控制转换
  ADC2->CR2|=1<<20;      //使用外部触发
  ADC2->CR2&=~(1<<11);   //右对齐 
  ADC2->SQR1&=~(0XF<<20);
  ADC2->SQR1|=0<<20;     //1个转换在规则序列中 也就是只转换规则序列1
  //设置通道1采样的时间
  ADC2->SMPR1&=~(3*0);   //设置ADC采样时间寄存器1 通道11采样时间清空  
  ADC2->SMPR1|=7<<(3*0); //通道11 239.5周期 提高采样时间可以提高
  ADC2->CR2|=1<<0;	   //开启AD转换器	 
  ADC2->CR2|=1<<3;       //使能复位校准
  while(ADC2->CR2&1<<3); //	 等待校准结束
  ADC2->CR2|=1<<2;        //开启AD校准   
  while(ADC2->CR2&1<<2);  //等待校准结束
}
/*********************************************************************************************************
** Function name:       get_adc_value
** Descriptions:        read adc2 value 
** Input parameters:    channel 
** Output parameters:   无
** Returned value:      value of input channel
*********************************************************************************************************/
uint16_t get_adc_value(uint8_t ch)
{
  ADC2->SQR3&=0XFFFFFFE0;
  ADC2->SQR3|=ch;		  			    
  ADC2->CR2|=1<<22;       
  while(!(ADC2->SR&1<<1)); 	   
  return ADC2->DR;
}
/*********************************************************************************************************
** Function name:       get_light_value
** Descriptions:        read light sensor value
** Input parameters:    void
** Output parameters:   无
** Returned value:      value of light sensor z
*********************************************************************************************************/
uint16_t get_light_value(void)
{
  return get_adc_value(LIGHT_SENSOR_CHANNEL);
  
}
