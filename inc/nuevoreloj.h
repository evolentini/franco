/* Copyright 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, Pablo Ridolfi
 * Copyright 2014, Juan Cecconi
 * Copyright 2014, Gustavo Muro
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef BAREMETAL_H
#define BAREMETAL_H
/** \brief Bare Metal example header file
 **
 ** This is a mini example of the CIAA Firmware
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example header file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "stdint.h"
#include "stdbool.h"


/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
/*==================[PARAMETROS DEFINIDOS]================================================*/

#define ENTRADA 0
#define SALIDA  1

//SEGMENTO A
#define SEG_A_MUX_GROUP    4
#define SEG_A_MUX_PIN      0
#define SEG_A_GPIO_PORT    2
#define SEG_A_GPIO_PIN     0


//SEGMENTO B
#define SEG_B_MUX_GROUP    4
#define SEG_B_MUX_PIN      1
#define SEG_B_GPIO_PORT    2
#define SEG_B_GPIO_PIN     1

//SEGMENTO C
#define SEG_C_MUX_GROUP    4
#define SEG_C_MUX_PIN      2
#define SEG_C_GPIO_PORT    2
#define SEG_C_GPIO_PIN     2

//SEGMENTO D
#define SEG_D_MUX_GROUP    4
#define SEG_D_MUX_PIN      3
#define SEG_D_GPIO_PORT    2
#define SEG_D_GPIO_PIN     3

//SEGMENTO E
#define SEG_E_MUX_GROUP    4
#define SEG_E_MUX_PIN      4
#define SEG_E_GPIO_PORT    2
#define SEG_E_GPIO_PIN     4

//SEGMENTO F
#define SEG_F_MUX_GROUP    4
#define SEG_F_MUX_PIN      5
#define SEG_F_GPIO_PORT    2
#define SEG_F_GPIO_PIN     5

//SEGMENTO G
#define SEG_G_MUX_GROUP    4
#define SEG_G_MUX_PIN      6
#define SEG_G_GPIO_PORT    2
#define SEG_G_GPIO_PIN     6


/****************/
//DISPLAY S2
#define DISP_S2_MUX_GROUP    6
#define DISP_S2_MUX_PIN      1
#define DISP_S2_GPIO_PORT    3
#define DISP_S2_GPIO_PIN     0

//DISPLAY S1
#define DISP_S1_MUX_GROUP    6
#define DISP_S1_MUX_PIN      4
#define DISP_S1_GPIO_PORT    3
#define DISP_S1_GPIO_PIN     3

//DISPLAY H2
#define DISP_H2_MUX_GROUP    6
#define DISP_H2_MUX_PIN      5
#define DISP_H2_GPIO_PORT    3
#define DISP_H2_GPIO_PIN     4

//DISPLAY H1
#define DISP_H1_MUX_GROUP    6
#define DISP_H1_MUX_PIN      9
#define DISP_H1_GPIO_PORT    3
#define DISP_H1_GPIO_PIN     5

//PULSADOR H
#define SWH_MUX_GROUP        1
#define SWH_MUX_PIN 	      3
#define SWH_GPIO_PORT 	      0
#define SWH_GPIO_PIN 	      10

//PULSADOR A
#define SWA_MUX_GROUP         1
#define SWA_MUX_PIN 	         16
#define SWA_GPIO_PORT 	     0
#define SWA_GPIO_PIN 	     3

//PULSADOR +
#define SWINCR_MUX_GROUP         1
#define SWINCR_MUX_PIN 	         15
#define SWINCR_GPIO_PORT 	     0
#define SWINCR_GPIO_PIN 	     2

//PULSADOR -
#define SWDECR_MUX_GROUP        0
#define SWDECR_MUX_PIN 	     1
#define SWDECR_GPIO_PORT 	     0
#define SWDECR_GPIO_PIN 	     1

//PULSADOR V/D
#define SWVD_MUX_GROUP        0
#define SWVD_MUX_PIN 	     0
#define SWVD_GPIO_PORT 	     0
#define SWVD_GPIO_PIN 	     0

//BUZZER
#define BUZZER_MUX_GROUP         6
#define BUZZER_MUX_PIN           11
#define BUZZER_GPIO_PORT 	     3
#define BUZZER_GPIO_PIN 	     7


//LED 1
#define LED_SEG_1_MUX_GROUP         1
#define LED_SEG_1_MUX_PIN           4
#define LED_SEG_1_GPIO_PORT 	    0
#define LED_SEG_1_GPIO_PIN          11

//LED 2
#define LED_SEG_2_MUX_GROUP         1
#define LED_SEG_2_MUX_PIN           17
#define LED_SEG_2_GPIO_PORT 	     0
#define LED_SEG_2_GPIO_PIN          12

//PTO DECIMAL ALARMA
#define PTO_DEC_ALARM_MUX_GROUP         6
#define PTO_DEC_ALARM_MUX_PIN           10
#define PTO_DEC_ALARM_GPIO_PORT 	    3
#define PTO_DEC_ALARM_GPIO_PIN          6



/*******************/

/*==================[DECLARACION DE VARIABLES]==============================*/

/*==================[DECLARACION DE FUNCIONES]==============================*/
void seg7(uint8_t);
void activar_seg(uint8_t);
void desactivar_seg(void);
void prepara_pulsadores(void);
uint8_t leer_pulsador(void);
void desactivar_pin_7seg(void);
void multiplexar_seg_sin_parpadeo(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
void multiplexar_seg_parpadeo_min(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
void multiplexar_seg_parpadeo_hora(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
void actualizar_hora(void);
void mod_hora(int);
void prender_buzzer(void);
void parapadeo_minuto(void);
void apagar_buzzer(void);
void chequear_alarma(void);
void sonar_alarma(void);
void apaga_leds_seg(void);
void activar_led_alarma(void);
void desactivar_alarma(void);
void parpadeo_led_seg(void);


/*==================[external data declaration]==============================*/
#if (CPU == mk60fx512vlq15)
/* Reset_Handler is defined in startup_MK60F15.S_CPP */
void Reset_Handler( void );

extern uint32_t __StackTop;
#elif (CPU == lpc4337)
/** \brief Reset ISR
 **
 ** ResetISR is defined in cr_startup_lpc43xx.c
 **
 ** \remark the definition is in
 **         externals/drivers/cortexM4/lpc43xx/src/cr_startup_lpc43xx.c
 **/
extern void ResetISR(void);

/** \brief Stack Top address
 **
 ** External declaration for the pointer to the stack top from the Linker Script
 **
 ** \remark only a declaration is needed, there is no definition, the address
 **         is set in the linker script:
 **         externals/base/cortexM4/lpc43xx/linker/ciaa_lpc4337.ld.
 **/
extern void _vStackTop(void);
#else
#endif

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef BAREMETAL_H */