/*******************************************************************************
  * @file    umart_lite_plus_teste/include/controle.h
  * @author  Handel Mateus
  * @version V0.0.1
  * @date    17-fevereiro-2025
  * @brief   Cabecalho para o modulo controle.c
  ******************************************************************************
  */


/* Define para previnir a inclus�o recursiva ---------------------------------*/
#ifndef _CONTROLE_H
#define _CONTROLE_H

//Includes
#include "user.h"

//Defines
#define PERIODO_AMOSTRAGEM_MS 10
#define MAXIMA_VEL_ANGULAR_RAD 10.0

//Declarações de funções
int normIn(float val);
float normOut(float val);
float normOut_Angular(float velocidadeAngular);
int pidZN2(float Ts, float Kcr, float Tcr, int u, int e0, int e1, int e2);
float PID(float g0, float g1, float g2, float u, float e0, float e1, float e2);
int PID_FD(float q1, float p0, float p1, float p2, int u1, int u2, int e0, int e1, int e2);
float percentToRadS(float percentual);

#endif // _CONTROLE_H
