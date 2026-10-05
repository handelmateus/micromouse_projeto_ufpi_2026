/**
  ******************************************************************************
  * @file    umart_lite_plus_teste/include/main.h
  * @author  Kleber Lima da Silva (kleber.ufu@hotmail.com)
  * @version V1.0.1
  * @date    20-Abril-2015
  * @brief   Inclus�o das bibliotecas de usu�rio e defini��o de par�metros
  ******************************************************************************
  */

/* Define para previnir a inclus�o recursiva ---------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H


/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "delays.h"
#include "buzzer.h"
#include "leds.h"
#include "botao.h"
#include "motores.h"
#include "sensores.h"
#include "encoders.h"
#include "usart1.h"
#include "usb_user.h"
#include "flash.h"
#include "user.h" 	  //biblioteca feita pelo usuario
#include "controle.h" //biblioteca de controle
#include "mlp.h" //biblioteca de rede neural

/* Defini��es ----------------------------------------------------------------*/
#define STDIO_UART	// STDIO_UART ou STDIO_USB: direciona as fun��es de escrita
				    // e leitura (printf, scanf, putc...) para a UART ou para a USB
//#define STDIO_USB

/* Constantes ----------------------------------------------------------------*/
/* Macros --------------------------------------------------------------------*/
/* Prot�tipos das Fun��es --------------------------------------------------- */
void systick(void);


#endif /* __MAIN_H */
