/**
  ******************************************************************************
  * @file    umart_lite_plus_teste/include/user.h
  * @author  Handel Mateus
  * @version V0.0.1
  * @date    04-setembro-2024
  * @brief   Cabecalho para o modulo user.c
  ******************************************************************************
  */
/* Define para previnir a inclus�o recursiva ---------------------------------*/
#ifndef _USER_H
#define _USER_H

/* Includes ------------------------------------------------------------------*/
#include "leds.h"
#include "motores.h"
#include "encoders.h"
#include "usart1.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

/* Definicao de constantes ---------------------------------------------------*/
#define PI 3.14159
#define RAIO_PNEU_MM 16   // Raio em do pneu em mm
#define VREF_ADC_MV 3600   // Tensão de referência do ADC em mV (3.6 V)
#define ADC_RESOLUTION 4095 // Resolução do ADC (12 bits)
#define GYRO_SENSITIVITY 0.67 // Sensibilidade do giroscópio em mV/°/s
#define TEMPO_MEDICAO_MS PERIODO_AMOSTRAGEM_MS*0.5 // Tempo usado para medir a velocidadade (em ms)
#define COMPRIMENTO_MOUSE_MM 89.7 //Distancia entre as rodas do micromouse em mm
#define COMPRIMENTO_MOUSE_M 0.0897 //Distancia entre as rodas do micromouse em m
#define AMPLIFICADOR 10000 //Fator de amplificacao dos valores enviados via print
#define RAIO_CURVA_TRANSL_LABIRINTO_M 0.18 //Raio da curva de translacao do micromouse no labirinto em m

/* Variaveis globais ---------------------------------------------------------*/
extern int OFFSET_GYRO; // variavel de offset do gyro a ser modificada por uma função de calibragem
extern int LF_OFFSET; // variável para o offset do sensor frontal esquerdo
extern int L_OFFSET; // variável para o offset do sensor esquerdo
extern int R_OFFSET; // variável para o offset do sensor direito
extern int RF_OFFSET; // variável para o offset do sensor frontal direito

/* Prototipos de funcões -----------------------------------------------------*/
void posicParede(int num);
void turnLeft(int PWM);
void turnRight(int PWM);
void turnBack(int PWM);
float velRight();
void velRL(float *vl, float *vr);
void velRL_media(float *vl, float *vr);
float velLeft();
int str2int(const char* str);
void configMotor(char* velconcat);
float getVrefMV();
int calibrateGyro();
int getAngularVelocity();
float randomize(float val, int margem);
float prbs(float val, int margem);
float velAng(float velE, float velD);
float velAngGrau(float velE, float velD);
float velLin(float velE, float velD);
void calibrateWallSensors();
int amplify(float val);
int ref2ref(float refLin, float refAng, int lado);
float ref2ref_corrigida(float refLin, float refAng, int lado);

#endif // _USER_H
