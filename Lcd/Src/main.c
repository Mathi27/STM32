/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
   uint32_t *Clockreg = (uint32_t*)0x40023830; //AHB1ENR address (RCC->AH1BENR)
   uint32_t *moderreg = (uint32_t*)0x40020800;//GPIOC->MODER for LED
   uint32_t *ModeregB = (uint32_t*)0x40020400; //(GPIOB->MODER) PORTB address for SW1
   uint32_t *odrreg = (uint32_t*)0x40020814; //(GPIOC->ODR) Portc address+offset address of ODR
   uint32_t *Inputreg = (uint32_t*)0x40020410; //(GPIOB->IDR) Portb address+offset address of IDR
   uint32_t *pullreg = (uint32_t*)0x4002040C; //(GPIOB->PUPDR)
   *Clockreg |=(1<<2);//enable clock portc
   *Clockreg |=(1<<1);//enable clock portb
   *moderreg |=(1<<12);//PC6 as output
   *moderreg &=~(1<<13);//PC6 as output
   *ModeregB &=~(3<<14); //B7 as input
   *pullreg &=~(3<<14); // no pullup no pulldown at PB7

   while(1)
   {
	   uint8_t btn_status = (uint8_t)(*Inputreg & (1<<7));//read from PB7
	   if(btn_status==0)
	   {
	   *odrreg &=~(1<<6);
	   }
	   else
	   {
	   *odrreg |=(1<<6);
	   }
   }
}
