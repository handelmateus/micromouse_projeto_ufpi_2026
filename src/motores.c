/**
  ******************************************************************************
  * @file    umart_lite_plus_teste/src/motores.c
  * @author  Kleber Lima da Silva (kleber.ufu@hotmail.com)
  * @version V1.0.0
  * @date    16-Fevereiro-2015
  * @brief   Funções para acionamento dos motores
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "motores.h"


/** @defgroup Variáveis privadas
  * @{
  */
// Arrays que armazenam as portas e pinos GPIO usados para controle dos motores
GPIO_TypeDef* MOTORES_PORT[N_PINS] =
			{L_IN1_PORT, L_IN2_PORT, R_IN1_PORT, R_IN2_PORT, STBY_PORT};

const uint16_t MOTORES_PIN[N_PINS] =
			{L_IN1_PIN, L_IN2_PIN, R_IN1_PIN, R_IN2_PIN, STBY_PIN};

// Manipulador de timer para controle de PWM
TIM_HandleTypeDef TimHandle;
/**
  * @}
  */


/**
  * @brief Configuração dos GPIOs e PWMs para acionamento dos Motores
  * @param Nenhum
  * @return Nenhum
  */
void motoresConfig(void)
{
	// Habilita o barramento de clock do GPIO do drive dos motores
	MOTORES_CLK;

	// Configura os GPIOs do drive dos motores como saídas push/pull
	GPIO_InitTypeDef GPIO_InitStructure;
	for (int i = 0; i < N_PINS; i++)
	{
		GPIO_InitStructure.Pin = MOTORES_PIN[i];
		GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; // Modo de saída push/pull
		GPIO_InitStructure.Pull = GPIO_PULLUP; // Habilita o resistor pull-up
		GPIO_InitStructure.Speed = GPIO_SPEED_FAST; // Velocidade alta de operação
		HAL_GPIO_Init(MOTORES_PORT[i], &GPIO_InitStructure); // Inicializa o GPIO com as configurações definidas
	}

	// Ativa o pino de STBY para habilitar o driver dos motores
	HAL_GPIO_WritePin(STBY_PORT, STBY_PIN, GPIO_PIN_SET); //original = set

	// Configura os GPIOs de PWM como função alternativa (AF)
	GPIO_InitStructure.Pin = L_PWM_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP; // Modo de função alternativa push/pull
	GPIO_InitStructure.Pull = GPIO_NOPULL; // Sem resistor pull-up/down
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST; // Velocidade alta de operação
	GPIO_InitStructure.Alternate = PWM_AF_TIM; // Seleciona a função alternativa para o PWM
	HAL_GPIO_Init(L_PWM_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = R_PWM_PIN;
	HAL_GPIO_Init(R_PWM_PORT, &GPIO_InitStructure);

	// Configuração da base de tempo do PWM
	// Frequência do PWM: f = [(168M / 2) / (PS + 1) ] / T
	TimHandle.Instance = PWM_TIM;
	TimHandle.Init.Period = PWM_PERIOD; // Define o período do PWM
	TimHandle.Init.Prescaler = PWM_PRESCALER; // Define o prescaler para ajuste da frequência
	TimHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // Sem divisão adicional de clock
	TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP; // Contador em modo crescente
	HAL_TIM_PWM_Init(&TimHandle); // Inicializa o PWM com as configurações definidas

	// Configuração do Output Compare do PWM
	TIM_OC_InitTypeDef sConfig;
	sConfig.OCMode = TIM_OCMODE_PWM1; // Configura o PWM no modo 1 (PWM ativo enquanto o contador está abaixo do valor de comparação)
	sConfig.OCPolarity = TIM_OCPOLARITY_HIGH; // Sinal de saída é ativo em nível alto
	sConfig.OCFastMode = TIM_OCFAST_DISABLE; // Desabilita o modo rápido do PWM
	sConfig.Pulse = 999; // Define o valor inicial do pulso (duty cycle)
	HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, L_PWM_CHANNEL); // Configura o canal PWM para o motor esquerdo
	HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, R_PWM_CHANNEL); // Configura o canal PWM para o motor direito

	// Inicia a geração do PWM nos canais configurados
	HAL_TIM_PWM_Start(&TimHandle, L_PWM_CHANNEL);
	HAL_TIM_PWM_Start(&TimHandle, R_PWM_CHANNEL);
}


/**
  * @brief Atualiza o PWM dos motores da esquerda e da direita
  * @param pwm_esquerda: -1000 a 1000 (controle do motor esquerdo)
  * @param pwm_direita: -1000 a 1000 (controle do motor direito)
  * @return Nenhum
  */
void setMotores(int16_t pwm_esquerda, int16_t pwm_direita)
{
	// Acionamento do motor da esquerda
	if (pwm_esquerda < 0)
	{
		pwm_esquerda *= -1; // Inverte o sinal para obter o valor absoluto

		// Configura o sentido de rotação do motor esquerdo
		HAL_GPIO_WritePin(L_IN1_PORT, L_IN1_PIN, GPIO_PIN_RESET); // Desativa IN1
		HAL_GPIO_WritePin(L_IN2_PORT, L_IN2_PIN, GPIO_PIN_SET); // Ativa IN2
	}
	else
	{
		// Configura o sentido de rotação do motor esquerdo
		HAL_GPIO_WritePin(L_IN1_PORT, L_IN1_PIN, GPIO_PIN_SET); // Ativa IN1
		HAL_GPIO_WritePin(L_IN2_PORT, L_IN2_PIN, GPIO_PIN_RESET); // Desativa IN2
	}

	// Acionamento do motor da direita
	if (pwm_direita < 0)
	{
		pwm_direita *= -1; // Inverte o sinal para obter o valor absoluto

		// Configura o sentido de rotação do motor direito
		HAL_GPIO_WritePin(R_IN1_PORT, R_IN1_PIN, GPIO_PIN_RESET); // Desativa IN1
		HAL_GPIO_WritePin(R_IN2_PORT, R_IN2_PIN, GPIO_PIN_SET); // Ativa IN2
	}
	else
	{
		// Configura o sentido de rotação do motor direito
		HAL_GPIO_WritePin(R_IN1_PORT, R_IN1_PIN, GPIO_PIN_SET); // Ativa IN1
		HAL_GPIO_WritePin(R_IN2_PORT, R_IN2_PIN, GPIO_PIN_RESET); // Desativa IN2
	}

	// Verifica se o valor do PWM está dentro do intervalo permitido (0 a 1000)
	if (pwm_esquerda > 1000)
	{
		pwm_esquerda = 1000; // Limita o valor máximo a 1000
	}

	if (pwm_direita > 1000)
	{
		pwm_direita = 1000; // Limita o valor máximo a 1000
	}

	// Atualiza os valores de PWM para os motores
	L_PWM_CCR = pwm_esquerda;
	R_PWM_CCR = pwm_direita;
}
