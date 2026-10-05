/**
  ******************************************************************************
  * @file    umart_lite_plus_teste/include/usb_user.h
  * @author  Kleber Lima da Silva (kleber.ufu@hotmail.com)
  * @version V1.0.1
  * @date    20-Abril-2015
  * @brief   Cabe�alho para o m�dulo usb_user.c
  ******************************************************************************
  */

/* Define para previnir a inclus�o recursiva ---------------------------------*/
#ifndef __USB_USER_H
#define __USB_USER_H


/* Includes ------------------------------------------------------------------*/
#include <sys/stat.h>
#include <stdio.h>
#include "../USB/Core/Inc/usbd_core.h"
#include "../USB/CDC/Inc/usbd_cdc.h"
#include <usbd_cdc_if_template.h>
#include <usbd_desc.h>
#include "stm32f4xx.h"
#include "main.h"

/* Constantes ----------------------------------------------------------------*/
/* Prot�tipos das Fun��es --------------------------------------------------- */
void usbConfig (void);

/* Vari�veis ---------------------------------------------------------------- */


#endif /* __USB_USER_H */
