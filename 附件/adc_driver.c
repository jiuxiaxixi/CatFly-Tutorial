/****************************************Copyright (c)****************************************************
**                                   CatFly WSN���߲���ƽ̨
**                                        @jiuxiaxixi           
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:               adc_driver.c
** Last modified Date:      2018-06-28
** Last Version:            v1.0
** Description:             adc����
** 
**--------------------------------------------------------------------------------------------------------
** Created By:              ��УԴ
** Created date:            2018-06-28
** Version:                 v1.0
** Descriptions:            The original version ��ʼ�汾
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
**  ����
*********************************************************************************************************/
#define RCC_ADC_PERIPHERAL      RCC_PERIPHERAL_ADC2   
//����ַ����
 /*!< Peripheral base address in the alias region */
#define PERIPH_BASE             ((uint32_t)0x40000000)
#define APB1PERIPH_BASE         PERIPH_BASE
#define APB2PERIPH_BASE         (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE          (PERIPH_BASE + 0x20000)
//ADC2����
#define ADC2_BASE               (APB2PERIPH_BASE + 0x2800)
#define ADC2                    ((ADC_TypeDef *) ADC2_BASE)
//RCC����
#define RCC_BASE_TEST           (AHBPERIPH_BASE + 0x1000)
#define RCC                     ((RCC_TypeDef *) RCC_BASE_TEST)

#define LIGHT_SENSOR_CHANNEL    10
/*********************************************************************************************************
** Function name:       adc_init
** Descriptions:        adc��ʼ��
** Input parameters:    ��
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void adc_init(void)
{
  RCC->APB2ENR= RCC->APB2ENR | 1<<4;    
  RCC->APB2ENR|=1<<10;      
  RCC->APB2RSTR|=1<<10;   
  RCC->APB2RSTR&=~(1<<10); 
  RCC->CFGR&=~(3<<14);   //PCLK2 8��Ƶ����ΪADCʱ��
  RCC->CFGR|=2<<14;      	
  
  // ����GPIO��ʱ�Ӻ�����ģʽ
  //SystemPeripheralEnable(RCC_PERIPHERAL_IOPC);
  GPIOConfigSet(GPIOC_BASE, GPIO_PIN_0, GPIO_DIR_IN_Analog);
  
  ADC2->CR1&=0XF0FFFF;   //����ģʽ��0
  ADC2->CR1|=0<<16;      //��������ģʽ  
  ADC2->CR1&=~(1<<8);    //��ɨ��ģʽ	  
  ADC2->CR2&=~(1<<1);    //����ת��ģʽ
  ADC2->CR2&=~(7<<17);	   
  ADC2->CR2|=7<<17;	   //�������ת��
  ADC2->CR2|=1<<20;      //ʹ���ⲿ����
  ADC2->CR2&=~(1<<11);   //�Ҷ��� 
  ADC2->SQR1&=~(0XF<<20);
  ADC2->SQR1|=0<<20;     //1��ת���ڹ��������� Ҳ����ֻת����������1
  //����ͨ��1������ʱ��
  ADC2->SMPR1&=~(3*0);   //����ADC����ʱ��Ĵ���1 ͨ��11����ʱ�����  
  ADC2->SMPR1|=7<<(3*0); //ͨ��11 239.5���� ��߲���ʱ��������
  ADC2->CR2|=1<<0;	   //����ADת����	 
  ADC2->CR2|=1<<3;       //ʹ�ܸ�λУ׼
  while(ADC2->CR2&1<<3); //	 �ȴ�У׼����
  ADC2->CR2|=1<<2;        //����ADУ׼   
  while(ADC2->CR2&1<<2);  //�ȴ�У׼����
}
/*********************************************************************************************************
** Function name:       get_adc_value
** Descriptions:        read adc2 value 
** Input parameters:    channel 
** Output parameters:   ��
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
** Output parameters:   ��
** Returned value:      value of light sensor z
*********************************************************************************************************/
uint16_t get_light_value(void)
{
  return get_adc_value(LIGHT_SENSOR_CHANNEL);
  
}
