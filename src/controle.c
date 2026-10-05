/**
  ******************************************************************************
  * @file    umart_lite_plus_teste/src/controle.c
  * @author  Handel Mateus
  * @version V0.0.1
  * @date    17-fevereiro-2025
  * @brief   Funcões para lidar com o controle embarcado
  ******************************************************************************
  */

// Includes
#include "controle.h"

// Definicoes de funcoes

/**
 * @brief converte um valor recebido entre 0% e 100% para os valores de setMotores
 * @param val valor a ser convertido
 * @return valor para ser colocado na função setMotores()
 */
int normIn(float val)
{
	float normVal, a, b; // valores normalizado
	a = 0.82; //coeficiente angular da reta
	b = 13.0; //coeficiente linear da reta
	normVal = a*val + b; // convertendo o valor recebido entre 0 e 100

	//arredondando para o inteiro mais próximo
	if(normVal - (int)normVal < 0.5)
	{
		return (int)normVal;
	}
	else
	{
		return (int)normVal + 1;
	}

}

/**
 * @brief converte o valor de saída lido em um valor inteiro entre 0% e 100%, arredondando para o inteiro mais próximo (descontinuado o arredondamento)
 * @param val valor a ser normalizado
 * @return valor normalizado entre 0% e 100%
 */
float normOut(float val)
{
	float out, a, b; // valor normalizado
	a = 0.0796; //100/1257=0.07956 | coeficiente angular da reta (alterado para o novo motor)
	b = 0.0; //coeficiente linear da reta
	out = a*val + b; //normalizando a saída entre 0% e 100%

	return out;
//	//arredondando para o inteiro mais próximo
//	if(out - (int)out < 0.5)
//	{
//		return (int)out;
//		return out;
//	}
//	else
//	{
//		return (int)out + 1;
//		return out + 1;
//	}

}

float normOut_Angular(float velocidadeAngular)
{
    const float W_MAX_RAD_S = MAXIMA_VEL_ANGULAR_RAD; // limite angular máximo considerado
    float valorNormalizado;

    // Saturação entre -W_MAX e +W_MAX
    if (velocidadeAngular > W_MAX_RAD_S)
        velocidadeAngular = W_MAX_RAD_S;

    if (velocidadeAngular < -W_MAX_RAD_S)
        velocidadeAngular = -W_MAX_RAD_S;

    // Converte de [-W_MAX, +W_MAX] para [-100, +100]
    valorNormalizado = (velocidadeAngular / W_MAX_RAD_S) * 100.0f;

    return valorNormalizado;
}

/**
 * @brief calcula um valor de sinal de controle conforme parametros tabelados em ZN2 (feito para ser usado dentro do loop)
 * @param Ts periodo de amostragem
 * @param Kcr ganho critico (a partir do metodo do rele)
 * @param Tcr periodo critico (a partir do metodo do rele)
 * @param u valor u(k-1) do vetor u
 * @param e0 valor erro(k) do vetor erro
 * @param e1 valor erro(k-1) do vetor erro
 * @param e2 valor erro(k-2) do vetor erro
 * @return valor do sinal de controle
 */
int pidZN2(float Ts, float Kcr, float Tcr, int u, int e0, int e1, int e2)
{
//	Variaveis de controle
	float Kprop, Ti, Td, Ki, Kd, g0, g1, g2;
	float sinalControle;

	float Tss = Ts/1000; //convertendo pra milissegundos
//	Parâmetros do controlador
	Kprop=0.6*Kcr ; Ti=0.5*Tcr  ; Td=0.125*Tcr; // Valores tabelados conforme o ZN2

	Ki=Kprop/Ti; //ganho integrativo
	Kd=Kprop*Td; //ganho derivativo

//	Valores do controlador PID
	g0=Kprop + ((Ki*Tss)/2) + (Kd/Tss);
	g1= ((Ki*Tss)/2) - Kprop - ((2*Kd)/Tss);
	g2=Kd/Tss;

//	Sinal de Controle calculado a partir do ZN2
	sinalControle = u + g0*e0 + g1*e1 + g2*e2;

//	Limitando o sinal de controle entre 0% e 100%
	if (sinalControle > 100.0) sinalControle = 100.0;
	if (sinalControle < -100.0) sinalControle = -100.0;

//	Arredondando para o inteiro mais próximo
	if(sinalControle - (int)sinalControle < 0.5)
	{
		return (int)sinalControle;
	}
	else
	{
		return (int)sinalControle + 1;
	}

}

/**
 * @brief aplica um sinal de controle baseado nos ganhos do PID
 * @param g0 ganho do controlador
 * @param g1 ganho do controlador
 * @param g2 ganho do controlador
 * @param u valor u(k-1) do vetor u
 * @param e0 valor erro(k) do vetor erro
 * @param e1 valor erro(k-1) do vetor erro
 * @param e2 valor erro(k-2) do vetor erro
 * @return valor do sinal de controle
 */
float PID(float g0, float g1, float g2, float u, float e0, float e1, float e2)
{
//	Variaveis de controle
	float sinalControle;

//	Sinal de Controle calculado a partir do ZN2
	sinalControle = u + g0*e0 + g1*e1 + g2*e2;

//	Limitando o sinal de controle entre 0% e 100% (teste sem saturacao)
	if (sinalControle > 100.0) sinalControle = 100.0;
	if (sinalControle < -100.0) sinalControle = -100.0;

//	Arredondando para o inteiro mais próximo
	return sinalControle;
//	if(sinalControle - (int)sinalControle < 0.5)
//	{
//		return (int)sinalControle;
//	}
//	else
//	{
//		return (int)sinalControle + 1;
//	}

}


/**
 * @brief aplica um sinal de controle baseado nos ganhos do PID com o uso de um filtro derivativo
 * @param p0 ganho do controlador
 * @param p1 ganho do controlador
 * @param p2 ganho do controlador
 * @param u1 valor u(k-1) do vetor u
 * @param u2 valor u(k-2) do vetor u
 * @param e0 valor erro(k) do vetor erro
 * @param e1 valor erro(k-1) do vetor erro
 * @param e2 valor erro(k-2) do vetor erro
 * @return valor do sinal de controle
 */
int PID_FD(float q1, float p0, float p1, float p2, int u1, int u2, int e0, int e1, int e2)
{
//	Variaveis de controle
	float sinalControle;

//	Sinal de Controle calculado a partir do incremento do filtro derivativo
	sinalControle = -q1*u2 + (1+q1)*u1 + p0*e0 + p1*e1 + p2*e2;

//	Limitando o sinal de controle entre 0% e 100%
	if (sinalControle > 100) sinalControle = 100;
	if (sinalControle < 0) sinalControle = 0;

//	Arredondando para o inteiro mais próximo
	if(sinalControle - (int)sinalControle < 0.5)
	{
		return (int)sinalControle;
	}
	else
	{
		return (int)sinalControle + 1;
	}

}


float percentToRadS(float percentual)
{
    const float W_MAX_RAD_S = MAXIMA_VEL_ANGULAR_RAD;

    // Saturação entre -100% e +100%
    if (percentual > 100.0f)
        percentual = 100.0f;

    if (percentual < -100.0f)
        percentual = -100.0f;

    return (percentual / 100.0f) * W_MAX_RAD_S;
}
