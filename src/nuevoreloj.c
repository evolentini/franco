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

/** \brief Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
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
#include "nuevoreloj.h"       /* <= own header */
#include "chip.h"

/*==================[macros and definitions]=================================*/

#define COUNT_DELAY 3000000

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
int hora_reloj[4]={0,0,0,0};//[0]=hora mas significativo - [3]=minuto menos significativo
int hora_display[4]={0,0,0,0};
int hora_alarma[4]={0,0,0,0};
int hora_tmp[4]={0,0,0,0};
uint8_t segundos=0,cuenta_mod_hora=0,cuenta_mod_alarma=0,cuenta_parpadeo_min=0,cuenta_parpadeo_hora=0;
char tipo_mod='0';
bool parpadeo=false, estado_alarma=false, boton_ver_alarma=false;

/*==================[internal functions definition]==========================*/
void seg7(uint8_t nro_seg)
{
    if(nro_seg==0){

        //SEGMENTO A
        // Configurar funcion y caracteristicas electricas del terminal
        Chip_SCU_PinMux(SEG_A_MUX_GROUP, SEG_A_MUX_PIN, MD_PUP, FUNC0);
        // Poner los bit digitales en cero
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_A_GPIO_PORT, 1 << SEG_A_GPIO_PIN);
        // Configurar los bits digitales como salidas
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_A_GPIO_PORT, 1 << SEG_A_GPIO_PIN, SALIDA);
        //Poner los bit digitales en uno
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_A_GPIO_PORT,1<<SEG_A_GPIO_PIN);

        //SEGMENTO B
        Chip_SCU_PinMux(SEG_B_MUX_GROUP, SEG_B_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_B_GPIO_PORT, 1 << SEG_B_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_B_GPIO_PORT, 1 << SEG_B_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_B_GPIO_PORT,1<<SEG_B_GPIO_PIN);

        //SEGMENTO C
        Chip_SCU_PinMux(SEG_C_MUX_GROUP, SEG_C_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_C_GPIO_PORT, 1 << SEG_C_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_C_GPIO_PORT, 1 << SEG_C_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_C_GPIO_PORT,1<<SEG_C_GPIO_PIN);

        //SEGMENTO D
        Chip_SCU_PinMux(SEG_D_MUX_GROUP, SEG_D_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_D_GPIO_PORT,1<<SEG_D_GPIO_PIN);

        //SEGMENTO E
        Chip_SCU_PinMux(SEG_E_MUX_GROUP, SEG_E_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_E_GPIO_PORT,1<<SEG_E_GPIO_PIN);

        //SEGMENTO F
        Chip_SCU_PinMux(SEG_F_MUX_GROUP, SEG_F_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT,1<<SEG_F_GPIO_PIN);


    }

    if(nro_seg==1){
        //SEGMENTO E
        Chip_SCU_PinMux(SEG_E_MUX_GROUP, SEG_E_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_E_GPIO_PORT,1<<SEG_E_GPIO_PIN);

        //SEGMENTO F
        Chip_SCU_PinMux(SEG_F_MUX_GROUP, SEG_F_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT,1<<SEG_F_GPIO_PIN);

    }

    if(nro_seg==2){

        //SEGMENTO D
        Chip_SCU_PinMux(SEG_D_MUX_GROUP, SEG_D_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_D_GPIO_PORT,1<<SEG_D_GPIO_PIN);

        //SEGMENTO E
        Chip_SCU_PinMux(SEG_E_MUX_GROUP, SEG_E_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_E_GPIO_PORT,1<<SEG_E_GPIO_PIN);

        //SEGMENTO G
        Chip_SCU_PinMux(SEG_G_MUX_GROUP, SEG_G_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_G_GPIO_PORT, 1 << SEG_G_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_G_GPIO_PORT, 1 << SEG_G_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_G_GPIO_PORT,1<<SEG_G_GPIO_PIN);

        //SEGMENTO B
        Chip_SCU_PinMux(SEG_B_MUX_GROUP, SEG_B_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_B_GPIO_PORT, 1 << SEG_B_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_B_GPIO_PORT, 1 << SEG_B_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_B_GPIO_PORT,1<<SEG_B_GPIO_PIN);

        //SEGMENTO A
         // Configurar funcion y caracteristicas electricas del terminal
        Chip_SCU_PinMux(SEG_A_MUX_GROUP, SEG_A_MUX_PIN, MD_PUP, FUNC0);
        // Poner los bit digitales en cero
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_A_GPIO_PORT, 1 << SEG_A_GPIO_PIN);
        // Configurar los bits digitales como salidas
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_A_GPIO_PORT, 1 << SEG_A_GPIO_PIN, SALIDA);
        //Poner los bit digitales en uno
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_A_GPIO_PORT,1<<SEG_A_GPIO_PIN);



    }

    if(nro_seg==3){

        //SEGMENTO D
        Chip_SCU_PinMux(SEG_D_MUX_GROUP, SEG_D_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_D_GPIO_PORT,1<<SEG_D_GPIO_PIN);

        //SEGMENTO E
        Chip_SCU_PinMux(SEG_E_MUX_GROUP, SEG_E_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_E_GPIO_PORT,1<<SEG_E_GPIO_PIN);

        //SEGMENTO G
        Chip_SCU_PinMux(SEG_G_MUX_GROUP, SEG_G_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_G_GPIO_PORT, 1 << SEG_G_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_G_GPIO_PORT, 1 << SEG_G_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_G_GPIO_PORT,1<<SEG_G_GPIO_PIN);

        //SEGMENTO F
        Chip_SCU_PinMux(SEG_F_MUX_GROUP, SEG_F_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT,1<<SEG_F_GPIO_PIN);


        //SEGMENTO A
         // Configurar funcion y caracteristicas electricas del terminal
        Chip_SCU_PinMux(SEG_A_MUX_GROUP, SEG_A_MUX_PIN, MD_PUP, FUNC0);
        // Poner los bit digitales en cero
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_A_GPIO_PORT, 1 << SEG_A_GPIO_PIN);
        // Configurar los bits digitales como salidas
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_A_GPIO_PORT, 1 << SEG_A_GPIO_PIN, SALIDA);
        //Poner los bit digitales en uno
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_A_GPIO_PORT,1<<SEG_A_GPIO_PIN);



    }

    if(nro_seg==4){

        //SEGMENTO C
        Chip_SCU_PinMux(SEG_C_MUX_GROUP, SEG_C_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_C_GPIO_PORT, 1 << SEG_C_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_C_GPIO_PORT, 1 << SEG_C_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_C_GPIO_PORT,1<<SEG_C_GPIO_PIN);


        //SEGMENTO E
        Chip_SCU_PinMux(SEG_E_MUX_GROUP, SEG_E_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_E_GPIO_PORT,1<<SEG_E_GPIO_PIN);

        //SEGMENTO F
        Chip_SCU_PinMux(SEG_F_MUX_GROUP, SEG_F_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT,1<<SEG_F_GPIO_PIN);

        //SEGMENTO G
        Chip_SCU_PinMux(SEG_G_MUX_GROUP, SEG_G_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_G_GPIO_PORT, 1 << SEG_G_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_G_GPIO_PORT, 1 << SEG_G_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_G_GPIO_PORT,1<<SEG_G_GPIO_PIN);

    }

    if(nro_seg==5){

        //SEGMENTO D
        Chip_SCU_PinMux(SEG_D_MUX_GROUP, SEG_D_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_D_GPIO_PORT,1<<SEG_D_GPIO_PIN);


        //SEGMENTO C
        Chip_SCU_PinMux(SEG_C_MUX_GROUP, SEG_C_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_C_GPIO_PORT, 1 << SEG_C_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_C_GPIO_PORT, 1 << SEG_C_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_C_GPIO_PORT,1<<SEG_C_GPIO_PIN);

        //SEGMENTO G
        Chip_SCU_PinMux(SEG_G_MUX_GROUP, SEG_G_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_G_GPIO_PORT, 1 << SEG_G_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_G_GPIO_PORT, 1 << SEG_G_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_G_GPIO_PORT,1<<SEG_G_GPIO_PIN);

        //SEGMENTO F
        Chip_SCU_PinMux(SEG_F_MUX_GROUP, SEG_F_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT,1<<SEG_F_GPIO_PIN);

        //SEGMENTO A
         // Configurar funcion y caracteristicas electricas del terminal
        Chip_SCU_PinMux(SEG_A_MUX_GROUP, SEG_A_MUX_PIN, MD_PUP, FUNC0);
        // Poner los bit digitales en cero
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_A_GPIO_PORT, 1 << SEG_A_GPIO_PIN);
        // Configurar los bits digitales como salidas
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_A_GPIO_PORT, 1 << SEG_A_GPIO_PIN, SALIDA);
        //Poner los bit digitales en uno
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_A_GPIO_PORT,1<<SEG_A_GPIO_PIN);



   }

   if(nro_seg==6){

       //SEGMENTO D
       Chip_SCU_PinMux(SEG_D_MUX_GROUP, SEG_D_MUX_PIN, MD_PUP, FUNC0);
       Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN);
       Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN, SALIDA);
       Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_D_GPIO_PORT,1<<SEG_D_GPIO_PIN);


       //SEGMENTO C
       Chip_SCU_PinMux(SEG_C_MUX_GROUP, SEG_C_MUX_PIN, MD_PUP, FUNC0);
       Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_C_GPIO_PORT, 1 << SEG_C_GPIO_PIN);
       Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_C_GPIO_PORT, 1 << SEG_C_GPIO_PIN, SALIDA);
       Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_C_GPIO_PORT,1<<SEG_C_GPIO_PIN);

       //SEGMENTO G
       Chip_SCU_PinMux(SEG_G_MUX_GROUP, SEG_G_MUX_PIN, MD_PUP, FUNC0);
       Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_G_GPIO_PORT, 1 << SEG_G_GPIO_PIN);
       Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_G_GPIO_PORT, 1 << SEG_G_GPIO_PIN, SALIDA);
       Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_G_GPIO_PORT,1<<SEG_G_GPIO_PIN);

       //SEGMENTO F
       Chip_SCU_PinMux(SEG_F_MUX_GROUP, SEG_F_MUX_PIN, MD_PUP, FUNC0);
       Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN);
       Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN, SALIDA);
       Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT,1<<SEG_F_GPIO_PIN);

       //SEGMENTO A
       // Configurar funcion y caracteristicas electricas del terminal
       Chip_SCU_PinMux(SEG_A_MUX_GROUP, SEG_A_MUX_PIN, MD_PUP, FUNC0);
       // Poner los bit digitales en cero
       Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_A_GPIO_PORT, 1 << SEG_A_GPIO_PIN);
       // Configurar los bits digitales como salidas
       Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_A_GPIO_PORT, 1 << SEG_A_GPIO_PIN, SALIDA);
       //Poner los bit digitales en uno
       Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_A_GPIO_PORT,1<<SEG_A_GPIO_PIN);

       //SEGMENTO B
       Chip_SCU_PinMux(SEG_B_MUX_GROUP, SEG_B_MUX_PIN, MD_PUP, FUNC0);
       Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_B_GPIO_PORT, 1 << SEG_B_GPIO_PIN);
       Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_B_GPIO_PORT, 1 << SEG_B_GPIO_PIN, SALIDA);
       Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_B_GPIO_PORT,1<<SEG_B_GPIO_PIN);

   }

    if(nro_seg==7){

        //SEGMENTO D
        Chip_SCU_PinMux(SEG_D_MUX_GROUP, SEG_D_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_D_GPIO_PORT,1<<SEG_D_GPIO_PIN);


        //SEGMENTO E
        Chip_SCU_PinMux(SEG_E_MUX_GROUP, SEG_E_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_E_GPIO_PORT,1<<SEG_E_GPIO_PIN);

        //SEGMENTO F
        Chip_SCU_PinMux(SEG_F_MUX_GROUP, SEG_F_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT,1<<SEG_F_GPIO_PIN);


    }

    if(nro_seg==8){

        //SEGMENTO A
        // Configurar funcion y caracteristicas electricas del terminal
        Chip_SCU_PinMux(SEG_A_MUX_GROUP, SEG_A_MUX_PIN, MD_PUP, FUNC0);
        // Poner los bit digitales en cero
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_A_GPIO_PORT, 1 << SEG_A_GPIO_PIN);
        // Configurar los bits digitales como salidas
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_A_GPIO_PORT, 1 << SEG_A_GPIO_PIN, SALIDA);
        //Poner los bit digitales en uno
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_A_GPIO_PORT,1<<SEG_A_GPIO_PIN);

        //SEGMENTO B
        Chip_SCU_PinMux(SEG_B_MUX_GROUP, SEG_B_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_B_GPIO_PORT, 1 << SEG_B_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_B_GPIO_PORT, 1 << SEG_B_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_B_GPIO_PORT,1<<SEG_B_GPIO_PIN);

        //SEGMENTO C
        Chip_SCU_PinMux(SEG_C_MUX_GROUP, SEG_C_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_C_GPIO_PORT, 1 << SEG_C_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_C_GPIO_PORT, 1 << SEG_C_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_C_GPIO_PORT,1<<SEG_C_GPIO_PIN);

        //SEGMENTO D
        Chip_SCU_PinMux(SEG_D_MUX_GROUP, SEG_D_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_D_GPIO_PORT,1<<SEG_D_GPIO_PIN);

        //SEGMENTO E
        Chip_SCU_PinMux(SEG_E_MUX_GROUP, SEG_E_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_E_GPIO_PORT,1<<SEG_E_GPIO_PIN);

        //SEGMENTO F
        Chip_SCU_PinMux(SEG_F_MUX_GROUP, SEG_F_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT,1<<SEG_F_GPIO_PIN);

        //SEGMENTO G
        Chip_SCU_PinMux(SEG_G_MUX_GROUP, SEG_G_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_G_GPIO_PORT, 1 << SEG_G_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_G_GPIO_PORT, 1 << SEG_G_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_G_GPIO_PORT,1<<SEG_G_GPIO_PIN);

    }

    if(nro_seg==9){

        //SEGMENTO C
        Chip_SCU_PinMux(SEG_C_MUX_GROUP, SEG_C_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_C_GPIO_PORT, 1 << SEG_C_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_C_GPIO_PORT, 1 << SEG_C_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_C_GPIO_PORT,1<<SEG_C_GPIO_PIN);

        //SEGMENTO D
        Chip_SCU_PinMux(SEG_D_MUX_GROUP, SEG_D_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_D_GPIO_PORT,1<<SEG_D_GPIO_PIN);

        //SEGMENTO E
        Chip_SCU_PinMux(SEG_E_MUX_GROUP, SEG_E_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_E_GPIO_PORT,1<<SEG_E_GPIO_PIN);

        //SEGMENTO F
        Chip_SCU_PinMux(SEG_F_MUX_GROUP, SEG_F_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT,1<<SEG_F_GPIO_PIN);

        //SEGMENTO G
        Chip_SCU_PinMux(SEG_G_MUX_GROUP, SEG_G_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_G_GPIO_PORT, 1 << SEG_G_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_G_GPIO_PORT, 1 << SEG_G_GPIO_PIN, SALIDA);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, SEG_G_GPIO_PORT,1<<SEG_G_GPIO_PIN);

    }

}

void activar_seg(uint8_t segmento)
{

  if(segmento==1)
  {
    //DISPLAY H1
    Chip_SCU_PinMux(DISP_H1_MUX_GROUP, DISP_H1_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, DISP_H1_GPIO_PORT, 1 << DISP_H1_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, DISP_H1_GPIO_PORT, 1 << DISP_H1_GPIO_PIN, SALIDA);
    Chip_GPIO_SetValue(LPC_GPIO_PORT, DISP_H1_GPIO_PORT,1<<DISP_H1_GPIO_PIN);
  }

  if(segmento==2)
  {
    //DISPLAY H2
    Chip_SCU_PinMux(DISP_H2_MUX_GROUP, DISP_H2_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, DISP_H2_GPIO_PORT, 1 << DISP_H2_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, DISP_H2_GPIO_PORT, 1 << DISP_H2_GPIO_PIN, SALIDA);
    Chip_GPIO_SetValue(LPC_GPIO_PORT, DISP_H2_GPIO_PORT,1<<DISP_H2_GPIO_PIN);
   }

  if(segmento==3)
  {

    //DISPLAY S1
    Chip_SCU_PinMux(DISP_S1_MUX_GROUP, DISP_S1_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, DISP_S1_GPIO_PORT, 1 << DISP_S1_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, DISP_S1_GPIO_PORT, 1 << DISP_S1_GPIO_PIN, SALIDA);
    Chip_GPIO_SetValue(LPC_GPIO_PORT, DISP_S1_GPIO_PORT,1<<DISP_S1_GPIO_PIN);
  }

  if(segmento==4)
  {

    //DISPLAY S2
    Chip_SCU_PinMux(DISP_S2_MUX_GROUP, DISP_S2_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, DISP_S2_GPIO_PORT, 1 << DISP_S2_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, DISP_S2_GPIO_PORT, 1 << DISP_S2_GPIO_PIN, SALIDA);
    Chip_GPIO_SetValue(LPC_GPIO_PORT, DISP_S2_GPIO_PORT,1<<DISP_S2_GPIO_PIN);
   }
}


void desactivar_seg()
{

    //DISPLAY H1
    Chip_SCU_PinMux(DISP_H1_MUX_GROUP, DISP_H1_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, DISP_H1_GPIO_PORT, 1 << DISP_H1_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, DISP_H1_GPIO_PORT, 1 << DISP_H1_GPIO_PIN, SALIDA);
    //DISPLAY H2
    Chip_SCU_PinMux(DISP_H2_MUX_GROUP, DISP_H2_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, DISP_H2_GPIO_PORT, 1 << DISP_H2_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, DISP_H2_GPIO_PORT, 1 << DISP_H2_GPIO_PIN, SALIDA);
    //DISPLAY S1
    Chip_SCU_PinMux(DISP_S1_MUX_GROUP, DISP_S1_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, DISP_S1_GPIO_PORT, 1 << DISP_S1_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, DISP_S1_GPIO_PORT, 1 << DISP_S1_GPIO_PIN, SALIDA);
    //DISPLAY S2
    Chip_SCU_PinMux(DISP_S2_MUX_GROUP, DISP_S2_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, DISP_S2_GPIO_PORT, 1 << DISP_S2_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, DISP_S2_GPIO_PORT, 1 << DISP_S2_GPIO_PIN, SALIDA);

}

void parpadeo_minuto()
{
    for(uint8_t apagado=0;apagado<600;apagado++){
        parpadeo=false;
       /* //DISPLAY S1
        Chip_SCU_PinMux(DISP_S1_MUX_GROUP, DISP_S1_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, DISP_S1_GPIO_PORT, 1 << DISP_S1_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, DISP_S1_GPIO_PORT, 1 << DISP_S1_GPIO_PIN, SALIDA);
        //DISPLAY S2
        Chip_SCU_PinMux(DISP_S2_MUX_GROUP, DISP_S2_MUX_PIN, MD_PUP, FUNC0);
        Chip_GPIO_ClearValue(LPC_GPIO_PORT, DISP_S2_GPIO_PORT, 1 << DISP_S2_GPIO_PIN);
        Chip_GPIO_SetDir(LPC_GPIO_PORT, DISP_S2_GPIO_PORT, 1 << DISP_S2_GPIO_PIN, SALIDA);*/

    }
    for(uint8_t prendido=0;prendido<600;prendido++){
        parpadeo=true;/*
        Chip_GPIO_SetValue(LPC_GPIO_PORT, DISP_S1_GPIO_PORT,1<<DISP_S1_GPIO_PIN);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, DISP_S2_GPIO_PORT,1<<DISP_S2_GPIO_PIN);*/
    }

    if(parpadeo==false){
        Chip_GPIO_SetValue(LPC_GPIO_PORT, DISP_S1_GPIO_PORT,1<<DISP_S1_GPIO_PIN);
        Chip_GPIO_SetValue(LPC_GPIO_PORT, DISP_S2_GPIO_PORT,1<<DISP_S2_GPIO_PIN);
    }

}
/*

void parpadeo_hora()
{

    //DISPLAY H1
    Chip_SCU_PinMux(DISP_H1_MUX_GROUP, DISP_H1_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, DISP_H1_GPIO_PORT, 1 << DISP_H1_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, DISP_H1_GPIO_PORT, 1 << DISP_H1_GPIO_PIN, SALIDA);
    //DISPLAY H2
    Chip_SCU_PinMux(DISP_H2_MUX_GROUP, DISP_H2_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, DISP_H2_GPIO_PORT, 1 << DISP_H2_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, DISP_H2_GPIO_PORT, 1 << DISP_H2_GPIO_PIN, SALIDA);
    //DISPLAY S1
    Chip_SCU_PinMux(DISP_S1_MUX_GROUP, DISP_S1_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, DISP_S1_GPIO_PORT, 1 << DISP_S1_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, DISP_S1_GPIO_PORT, 1 << DISP_S1_GPIO_PIN, SALIDA);
    //DISPLAY S2
    Chip_SCU_PinMux(DISP_S2_MUX_GROUP, DISP_S2_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, DISP_S2_GPIO_PORT, 1 << DISP_S2_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, DISP_S2_GPIO_PORT, 1 << DISP_S2_GPIO_PIN, SALIDA);

}
*/

void desactivar_pin_7seg(){
    //SEGMENTO A
    Chip_SCU_PinMux(SEG_A_MUX_GROUP, SEG_A_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_A_GPIO_PORT, 1 << SEG_A_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_A_GPIO_PORT, 1 << SEG_A_GPIO_PIN, SALIDA);


    //SEGMENTO B
    Chip_SCU_PinMux(SEG_B_MUX_GROUP, SEG_B_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_B_GPIO_PORT, 1 << SEG_B_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_B_GPIO_PORT, 1 << SEG_B_GPIO_PIN, SALIDA);


    //SEGMENTO C
    Chip_SCU_PinMux(SEG_C_MUX_GROUP, SEG_C_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_C_GPIO_PORT, 1 << SEG_C_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_C_GPIO_PORT, 1 << SEG_C_GPIO_PIN, SALIDA);


    //SEGMENTO D
    Chip_SCU_PinMux(SEG_D_MUX_GROUP, SEG_D_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_D_GPIO_PORT, 1 << SEG_D_GPIO_PIN, SALIDA);


    //SEGMENTO E
    Chip_SCU_PinMux(SEG_E_MUX_GROUP, SEG_E_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_E_GPIO_PORT, 1 << SEG_E_GPIO_PIN, SALIDA);


    //SEGMENTO F
    Chip_SCU_PinMux(SEG_F_MUX_GROUP, SEG_F_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_F_GPIO_PORT, 1 << SEG_F_GPIO_PIN, SALIDA);


    //SEGMENTO G
    Chip_SCU_PinMux(SEG_G_MUX_GROUP, SEG_G_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEG_G_GPIO_PORT, 1 << SEG_G_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, SEG_G_GPIO_PORT, 1 << SEG_G_GPIO_PIN, SALIDA);


}

void multiplexar_seg_parpadeo_min(uint8_t nro_seg1,uint8_t nro_seg2,uint8_t nro_seg3,uint8_t nro_seg4,uint8_t segmento_activo){


    desactivar_seg();

    /*
     * HORA REPRESENTADA EN LOS 4 DISPLAY - H1H2:S1S2
     * segmento_activo=1 - es H1
     * segmento_activo=2 - es H2
     * segmento_activo=3 - es S1
     * segmento_activo=4 - es S2
    */
     if(segmento_activo==1){
        desactivar_pin_7seg();
        activar_seg(segmento_activo);
        seg7(nro_seg1);
     }

     if(segmento_activo==2){
            desactivar_pin_7seg();
            activar_seg(segmento_activo);
            seg7(nro_seg2);

     }
     if(cuenta_parpadeo_min==9){
         if(segmento_activo==3){
                desactivar_pin_7seg();
                activar_seg(segmento_activo);
                seg7(nro_seg3);

         }
     }
     if(cuenta_parpadeo_min==10){
          if(segmento_activo==4){
                desactivar_pin_7seg();
                activar_seg(segmento_activo);
                seg7(nro_seg4);

          }
     cuenta_parpadeo_min=0;
     }


}

void multiplexar_seg_parpadeo_hora(uint8_t nro_seg1,uint8_t nro_seg2,uint8_t nro_seg3,uint8_t nro_seg4,uint8_t segmento_activo){


    desactivar_seg();

    /*
     * HORA REPRESENTADA EN LOS 4 DISPLAY - H1H2:S1S2
     * segmento_activo=1 - es H1
     * segmento_activo=2 - es H2
     * segmento_activo=3 - es S1
     * segmento_activo=4 - es S2
    */
    if(cuenta_parpadeo_hora==9){
        if(segmento_activo==1){
               desactivar_pin_7seg();
               activar_seg(segmento_activo);
               seg7(nro_seg1);

        }
    }
    if(cuenta_parpadeo_hora==10){
         if(segmento_activo==2){
               desactivar_pin_7seg();
               activar_seg(segmento_activo);
               seg7(nro_seg2);

         }
    cuenta_parpadeo_hora=0;
    }

    if(segmento_activo==3){
        desactivar_pin_7seg();
        activar_seg(segmento_activo);
        seg7(nro_seg3);
     }

     if(segmento_activo==4){
            desactivar_pin_7seg();
            activar_seg(segmento_activo);
            seg7(nro_seg4);

     }
}


void multiplexar_seg_sin_parpadeo(uint8_t nro_seg1,uint8_t nro_seg2,uint8_t nro_seg3,uint8_t nro_seg4,uint8_t segmento_activo){


    desactivar_seg();

    /*
     * HORA REPRESENTADA EN LOS 4 DISPLAY - H1H2:S1S2
     * segmento_activo=1 - es H1
     * segmento_activo=2 - es H2
     * segmento_activo=3 - es S1
     * segmento_activo=4 - es S2
    */
     if(segmento_activo==1){
        desactivar_pin_7seg();
        activar_seg(segmento_activo);
        seg7(nro_seg1);
     }

     if(segmento_activo==2){
            desactivar_pin_7seg();
            activar_seg(segmento_activo);
            seg7(nro_seg2);

     }

         if(segmento_activo==3){
                desactivar_pin_7seg();
                activar_seg(segmento_activo);
                seg7(nro_seg3);


     }

          if(segmento_activo==4){
                desactivar_pin_7seg();
                activar_seg(segmento_activo);
                seg7(nro_seg4);

          }

}


void actualizar_hora(void) {

    segundos++;

    if(segundos==60) {

       segundos=0;
       hora_reloj[3]++;
       if(hora_reloj[3]== 10) {
          hora_reloj[3]=0;
          hora_reloj[2]++;

          if(hora_reloj[2]==6) {
              hora_reloj[2]=0;
              hora_reloj[1]++;
              if((hora_reloj[1]==10) || (hora_reloj[0]==2 && hora_reloj[1]==4)) {
                  hora_reloj[1]=0;
                  hora_reloj[0]++;
                  if(hora_reloj[0]==3) {
                      hora_reloj[0]=0;
                  }
              }
          }
       }
    }
 }
void prepara_pulsadores(){
    //PULSADOR M
    Chip_SCU_PinMux(SWH_MUX_GROUP,SWH_MUX_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, SWH_GPIO_PORT,1<<SWH_GPIO_PIN,ENTRADA);

    //PULSADOR A
    Chip_SCU_PinMux(SWA_MUX_GROUP,SWA_MUX_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, SWA_GPIO_PORT,1<<SWA_GPIO_PIN,ENTRADA);

    //PULSADOR +
    Chip_SCU_PinMux(SWINCR_MUX_GROUP,SWINCR_MUX_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, SWINCR_GPIO_PORT,1<<SWINCR_GPIO_PIN,ENTRADA);

    //PULSADOR -
    Chip_SCU_PinMux(SWDECR_MUX_GROUP,SWDECR_MUX_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, SWDECR_GPIO_PORT,1<<SWDECR_GPIO_PIN,ENTRADA);

    //PULSADOR V/D
    Chip_SCU_PinMux(SWVD_MUX_GROUP,SWVD_MUX_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, SWVD_GPIO_PORT,1<<SWVD_GPIO_PIN,ENTRADA);

}
uint8_t leer_pulsador(){

    if (!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,SWH_GPIO_PORT,SWH_GPIO_PIN)){
        cuenta_mod_hora++;
        if(cuenta_mod_hora==1){
            hora_tmp[0]=hora_reloj[0];
            hora_tmp[1]=hora_reloj[1];
            hora_tmp[2]=hora_reloj[2];
            hora_tmp[3]=hora_reloj[3];
            //parpadeo=true;

        }


        tipo_mod='h';
        if(cuenta_mod_hora==2){
            hora_reloj[2]=hora_tmp[2];
            hora_reloj[3]=hora_tmp[3];
            tipo_mod='0';
            parpadeo=false;
        }
        //if(cuenta_mod_hora==3)// parpadeo=true;

        if(cuenta_mod_hora==4){
            hora_reloj[0]=hora_tmp[0];
            hora_reloj[1]=hora_tmp[1];
            hora_reloj[3]=hora_tmp[3];
            hora_reloj[4]=hora_tmp[4];
            cuenta_mod_hora=0;
            tipo_mod='0';
        }
        cuenta_mod_alarma=0;
    }

    if (!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,SWA_GPIO_PORT,SWA_GPIO_PIN)){
        cuenta_mod_alarma++;
        if(cuenta_mod_alarma==1){
            hora_tmp[0]=hora_alarma[0];
            hora_tmp[1]=hora_alarma[1];
            hora_tmp[2]=hora_alarma[2];
            hora_tmp[3]=hora_alarma[3];
        }


        tipo_mod='a';
        if(cuenta_mod_alarma==2){
            hora_alarma[2]=hora_tmp[2];
            hora_alarma[3]=hora_tmp[3];

        }
        if(cuenta_mod_alarma==4){
            hora_alarma[0]=hora_tmp[0];
            hora_alarma[1]=hora_tmp[1];
            hora_alarma[2]=hora_tmp[2];
            hora_alarma[3]=hora_tmp[3];
            cuenta_mod_alarma=0;
            tipo_mod='0';
            activar_led_alarma();
            estado_alarma=true;
        }

        cuenta_mod_hora=0;
    }
    if (!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,SWINCR_GPIO_PORT,SWINCR_GPIO_PIN)){
        mod_hora(1);// 1 - incrementa

    }
    if (!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,SWDECR_GPIO_PORT,SWDECR_GPIO_PIN)){
        mod_hora(-1);//-1 - decrementa

    }

    if (!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,SWVD_GPIO_PORT,SWVD_GPIO_PIN)){

            desactivar_alarma();

            mostrar_alarma();


    }

}

void chequear_alarma(void){

    if(hora_reloj[0]==hora_alarma[0] && hora_reloj[1]==hora_alarma[1] && hora_reloj[2]==hora_alarma[2] && hora_reloj[3]==hora_alarma[3] && segundos==1 && estado_alarma){
        sonar_alarma();
    }

}

void mostrar_alarma(void){
    for(uint8_t i=0;i<4;i++){
        hora_display[i]=hora_alarma[i];
    }
}

void activar_led_alarma(void){
    Chip_SCU_PinMux(PTO_DEC_ALARM_MUX_GROUP, PTO_DEC_ALARM_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, PTO_DEC_ALARM_GPIO_PORT, 1 << PTO_DEC_ALARM_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, PTO_DEC_ALARM_GPIO_PORT, 1 << PTO_DEC_ALARM_GPIO_PIN, SALIDA);
    Chip_GPIO_SetValue(LPC_GPIO_PORT, PTO_DEC_ALARM_GPIO_PORT,1<<PTO_DEC_ALARM_GPIO_PIN);
}

void sonar_alarma(void){

    prender_buzzer();
    activar_led_alarma();

    //delay(500);
    //Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,BUZZER_GPIO_PORT,BUZZER_GPIO_PIN);
    //delay(500);

}
void prender_buzzer(){

    //ACTIVAR BUZZER
    Chip_SCU_PinMux(BUZZER_MUX_GROUP, BUZZER_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, BUZZER_GPIO_PORT, 1 << BUZZER_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, BUZZER_GPIO_PORT, 1 << BUZZER_GPIO_PIN, SALIDA);
    Chip_GPIO_SetValue(LPC_GPIO_PORT, BUZZER_GPIO_PORT,1<<BUZZER_GPIO_PIN);




}

void parpadeo_led_seg(void){

    //LED 1
    Chip_SCU_PinMux(LED_SEG_1_MUX_GROUP, LED_SEG_1_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, LED_SEG_1_GPIO_PORT, 1 << LED_SEG_1_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, LED_SEG_1_GPIO_PORT, 1 << LED_SEG_1_GPIO_PIN, SALIDA);

    //LED 2
    Chip_SCU_PinMux(LED_SEG_2_MUX_GROUP, LED_SEG_2_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, LED_SEG_2_GPIO_PORT, 1 << LED_SEG_2_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, LED_SEG_2_GPIO_PORT, 1 << LED_SEG_2_GPIO_PIN, SALIDA);
}

void desactivar_alarma(void){

    //APAGAR LED ALARMA
    Chip_SCU_PinMux(PTO_DEC_ALARM_MUX_GROUP, PTO_DEC_ALARM_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, PTO_DEC_ALARM_GPIO_PORT, 1 << PTO_DEC_ALARM_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, PTO_DEC_ALARM_GPIO_PORT, 1 << PTO_DEC_ALARM_GPIO_PIN, SALIDA);

    //APAGAR BUZZER
    Chip_SCU_PinMux(BUZZER_MUX_GROUP, BUZZER_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, BUZZER_GPIO_PORT, 1 << BUZZER_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, BUZZER_GPIO_PORT, 1 << BUZZER_GPIO_PIN, SALIDA);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, BUZZER_GPIO_PORT, 1 << BUZZER_GPIO_PIN);

    estado_alarma=false;


}


void apagar_buzzer(void){

    //DESACTIVAR BUZZER
    Chip_SCU_PinMux(BUZZER_MUX_GROUP, BUZZER_MUX_PIN, MD_PUP, FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, BUZZER_GPIO_PORT, 1 << BUZZER_GPIO_PIN);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, BUZZER_GPIO_PORT, 1 << BUZZER_GPIO_PIN, SALIDA);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, BUZZER_GPIO_PORT, 1 << BUZZER_GPIO_PIN);


}


void mod_hora(int incto)
{
    /*
     * HORA REPRESENTADA EN LOS 4 DISPLAY - H1H2:S1S2
     * segmento_activo=1 - es H1 [0]
     * segmento_activo=2 - es H2 [1]
     * segmento_activo=3 - es S1 [2]
     * segmento_activo=4 - es S2 [3]
    */
    if(cuenta_mod_hora==1 || cuenta_mod_alarma==1){
        if(incto==1){
            if(hora_tmp[2]!=6){
                hora_tmp[3]++;
                if(hora_tmp[3]==10) {
                    hora_tmp[3]=0;
                    hora_tmp[2]++;
                    if(hora_tmp[2]==6) {
                        hora_tmp[2]=0;
                        hora_tmp[3]=0;
                    }
                }
             }else{
                hora_tmp[2]=0;
            }
         }else{
                if(incto==-1){
                    if(hora_tmp[3]>0){
                        hora_tmp[3]--;
                        if(hora_tmp[3]==0){
                            if(hora_tmp[2]>0){
                                hora_tmp[3]=9;
                                hora_tmp[2]--;
                            }else{
                                hora_tmp[2]=0;
                                hora_tmp[3]=0;
                            }
                        }
                    }else{
                        hora_tmp[3]=9;
                        if(hora_tmp[2]>0)hora_tmp[2]--;
                        else hora_tmp[2]=5;
                    }
                }
             }
    }
    if(cuenta_mod_hora==3 || cuenta_mod_alarma==3){
        if(incto==1){
            hora_tmp[1]++;
            if(hora_tmp[1]==10){
                hora_tmp[1]=0;
                hora_tmp[0]++;
            }
            if(hora_tmp[0]==2 && hora_tmp[1]==4) {
                hora_tmp[1]=0;
                hora_tmp[0]=0;
            }
        }else{
            if(incto==-1){
                if(hora_tmp[1]>0 && hora_tmp[0]>0){
                    if(hora_tmp[1]==0){
                        hora_tmp[1]=9;
                        hora_tmp[0]--;
                    }
                    hora_tmp[1]--;
                }else{
                    if(hora_tmp[1]==0 && hora_tmp[0]>0){
                        hora_tmp[1]=9;
                        hora_tmp[0]--;
                    }else{
                        if(hora_tmp[0]==0 && hora_tmp[1]>0) hora_tmp[1]--;
                        else{
                            hora_tmp[1]=3;
                            hora_tmp[0]=2;
                        }
                    }
                }
            }
        }
    }

}


void configurarInterrupcionInactiva(void) {
  /* Deshabilita interrupciones */
    __asm__ volatile ("cpsid i");

   /* Activate SysTick */
   SystemCoreClockUpdate();
   SysTick_Config(SystemCoreClock/1600);

   /* Update priority set by SysTick_Config */
   NVIC_SetPriority(SysTick_IRQn, (1  <<__NVIC_PRIO_BITS) - 1);

  /* Habilita interrupciones */
   __asm__ volatile ("cpsie i");
}


/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */

int mainviejo(void)
{

  Chip_GPIO_Init(LPC_GPIO_PORT);

  parpadeo_led_seg();
  prepara_pulsadores();

  configurarInterrupcion();


  while(1) {
      chequear_alarma();
    }
  return 0;
}

/**
 * @brief Funcion periodica que se ejecuta con el SysTick
 * 
 */
void SysTick_Handler_Inactiva(void) {
   static int contador = 0,segmento_activo=0,k=0, retardo_lect_pulsador=0;

   //control si se presiona un pulsador
   retardo_lect_pulsador++;
   if(retardo_lect_pulsador==250){
       retardo_lect_pulsador=0;
       leer_pulsador();
    }



   if(tipo_mod=='h' || tipo_mod=='a'){
       for(uint8_t i=0; i<4;i++){
           hora_display[i]=hora_tmp[i];
       }
   }else{
       for(uint8_t i=0; i<4;i++){
           hora_display[i]=hora_reloj[i];
       }
   }
/*
   if(tipo_mod=='0'){
       for(uint8_t i=0; i<4;i++){
           hora_display[i]=hora_reloj[i];
       }
   }
*/
   if(estado_alarma && boton_ver_alarma){
       mostrar_alarma();
       boton_ver_alarma=false;
   }

   k++;
   if(k==20){
       k=0;
       actualizar_hora();

   }

   contador++;

   if (contador == 5) {
       contador = 0;


       if(segmento_activo==4) segmento_activo=0;

       segmento_activo++;
       cuenta_parpadeo_min++;
       cuenta_parpadeo_hora++;
       if(cuenta_mod_hora==1 || cuenta_mod_alarma==1){
           multiplexar_seg_parpadeo_min(hora_display[0],hora_display[1],hora_display[2],hora_display[3],segmento_activo);

       }else{
           if(cuenta_mod_alarma==3 || cuenta_mod_hora==3){
               multiplexar_seg_parpadeo_hora(hora_display[0],hora_display[1],hora_display[2],hora_display[3],segmento_activo);
           }else{
               multiplexar_seg_sin_parpadeo(hora_display[0],hora_display[1],hora_display[2],hora_display[3],segmento_activo);
           }
       }

      //Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED1_GPIO_PORT,LED1_GPIO_PIN);
      /*************/

              /***********/
   }
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

