/**
  ******************************************************************************
  * @file    umart_lite_plus_teste/src/user.c
  * @author  Handel Mateus
  * @version V0.0.1
  * @date    04-setembro-2024
  * @brief   Funcões criadas pelo usuario
  ******************************************************************************
  */

// Includes
#include "user.h"


// Funcões

/**
  * @brief Resultado da deteccão de paredes
  * @param 'num' = retorno do getSensoresParedes
  * @return Nenhum
  */
void posicParede(int num)
{
	// Defines
	#define QUINA "+"
	#define PAREDE_H "--"
	#define PAREDE_V "|"
	#define LIVRE " "

	if (num == 0) //0b000
	{
//		printf("SEM PAREDES!!!\n"); //pode ser alterado para gerar um doc
		printf(LIVRE);
		allLEDs(LOW);
	}
	else if (num == 1) //0b001
	{
//		printf("PAREDE A DIREITA!!!\n"); //pode ser alterado para gerar um doc
		printf(PAREDE_V);
		setLED(LED3, HIGH);
		delay_ms(100);
		setLED(LED3, LOW);
	}
	else if (num == 2) //0b010
	{
//		printf("PAREDE FRONTAL!!!\n"); //pode ser alterado para gerar um doc
		printf(PAREDE_H);
		setLED(LED2, HIGH);
		delay_ms(100);
		setLED(LED2, LOW);
	}
	else if (num == 3) //0b011
	{
//		printf("PAREDE FRONTAL E A DIREITA!!!\n"); //pode ser alterado para gerar um doc
//		printf(PAREDE_V); printf(PAREDE_H);
		setLED(LED3, HIGH);
		setLED(LED2, HIGH);
		delay_ms(100);
		setLED(LED3, LOW);
		setLED(LED2, LOW);
	}
	else if (num == 4) //0b100
	{
//		printf("PAREDE A ESQUERDA !!!\n"); //pode ser alterado para gerar um doc
		printf(PAREDE_V);
		setLED(LED1, HIGH);
		delay_ms(100);
		setLED(LED1, LOW);
	}
	else if (num == 5) //0b101
	{
//		printf("PAREDE A ESQUERDA E A DIREITA!!!\n"); //pode ser alterado para gerar um doc
//		printf(PAREDE_V);printf(PAREDE_V);
		setLED(LED3, HIGH);
		setLED(LED1, HIGH);
		delay_ms(100);
		setLED(LED3, LOW);
		setLED(LED1, LOW);
	}
	else if (num == 6) //0b110
	{
//		printf("PAREDE FRONTAL E A ESQUERDA!!!\n"); //pode ser alterado para gerar um doc
		setLED(LED1, HIGH);
		setLED(LED2, HIGH);
		delay_ms(100);
		setLED(LED1, LOW);
		setLED(LED2, LOW);
	}
	else if (num == 7) //0b111
	{
		printf("PAREDE EM TODAS AS DIREÇÕES!!!\n"); //pode ser alterado para gerar um doc
		allLEDs(HIGH);
		delay_ms(100);
		allLEDs(LOW);
	}

}


/**
  * @brief Curva de 90graus para a esquerda
  * @param PWM que indica a velocidade da curva
  * @return Nenhum
  */
void turnLeft(int PWM)
{
	//	Variaveis ---------------------------------------------------------------
	int32_t encD; // leitura da encoder direita
	float rCurva = 0.082/2; // raio da curva
	float rPneu = 0.032/2; // raio do pneu
	float arco = 0; // comprimento do arco
	float passo; //quantidade de passos a serem dados
	float rev; //comprimento da revolucao de um pneu | 1 rev = 360 pasos
	//int32_t lf = 0, l = 0, r = 0, rf = 0;

	//Calculo da curva a ser feita ----------------------------------------------
	arco = (PI*rCurva)/2; //arco de pi/2 radianos
	rev = 2*PI*rPneu;
	passo = (arco*360)/rev; //calculando o numero de passos

	delay_ms(200);
	resetEncoderDireita(); // zerando a leitura da encoder
	encD = getEncoderDireita();
	while(encD <= passo)
	{
		setMotores(-PWM, PWM); //curva na intensidade do PWM
		encD = getEncoderDireita();
	}
	setMotores(0,0);

}



/**
  * @brief Curva de 90graus para a direita
  * @param PWM que indica a velocidade da curva
  * @return Nenhum
  */
void turnRight(int PWM)
{
	//	Variaveis ---------------------------------------------------------------
	int32_t encE; // leitura da encoder direita
	float rCurva = 0.082/2; // raio da curva
	float rPneu = 0.032/2; // raio do pneu
	float arco = 0; // comprimento do arco
	float passo; //quantidade de passos a serem dados
	float rev; //comprimento da revolucao de um pneu | 1 rev = 360 pasos
	//int32_t lf = 0, l = 0, r = 0, rf = 0;

	//Calculo da curva a ser feita ----------------------------------------------
	arco = (PI*rCurva)/2; //arco de pi/2 radianos
	rev = 2*PI*rPneu;
	passo = (arco*360)/rev; //calculando o numero de passos

	delay_ms(200);
	resetEncoderEsquerda(); // zerando a leitura da encoder
	encE = getEncoderEsquerda();
	while(encE <= passo)
	{
		setMotores(PWM, -PWM); //curva na intensidade do PWM
		encE = getEncoderEsquerda();
	}
	setMotores(0,0);

}
/**
  * @brief Curva de 180graus
  * @param PWM que indica a velocidade da curva
  * @return Nenhum
  */
void turnBack(int PWM)
{
	//	Variaveis ---------------------------------------------------------------
	int32_t encE; // leitura da encoder direita
	float rCurva = 0.082/2; // raio da curva
	float rPneu = 0.032/2; // raio do pneu
	float arco = 0; // comprimento do arco
	float passo; //quantidade de passos a serem dados
	float rev; //comprimento da revolucao de um pneu | 1 rev = 360 pasos
	//int32_t lf = 0, l = 0, r = 0, rf = 0;

	//Calculo da curva a ser feita ----------------------------------------------
	arco = (PI*rCurva); //arco de pi radianos
	rev = 2*PI*rPneu;
	passo = (arco*360)/rev; //calculando o numero de passos

	delay_ms(200);
	resetEncoderEsquerda(); // zerando a leitura da encoder
	encE = getEncoderEsquerda();
	while(encE <= passo)
	{
		setMotores(PWM, -PWM); //curva na intensidade do PWM
		encE = getEncoderEsquerda();
	}
	setMotores(0,0);

}
/**
  * @brief calcula a velocidade da roda direita a partir da variação da encoder
  * @param Nenhum
  * @return Velocidade da roda direita
  */
float velRight()
{
	int tInit = 0, tEnd = 0; //variáveis de tempo
    float encD1, encD2, encD; //variável da encoder
    float distD, velD; //distancia e velocidade
    //float rotD; //numero de rotacoes

    //    resetEncoderDireita();
    encD1 = getEncoderDireita();
    tInit = micros();           // Inicia contagem de tempo
    elapse_us(TEMPO_MEDICAO_MS*1000, tInit);
    tEnd = micros();            // Tempo final
    encD2 = getEncoderDireita();
    encD = encD2 - encD1; //pegando o quanto a roda avançou

    // Calcula distância (evitando divisão inteira)
    distD = 2 * PI * RAIO_PNEU_MM * (encD / 360.0f); // em mm
//    rotD = 60000*((float)encD / 360.0f); // 60000 para por a escala de ms para min

    // Calcula velocidade (tempo real em segundos)
    float tempo = (tEnd - tInit) / 1000000.0f; // Converter ms para s
    velD = distD / tempo;       // Velocidade em mm/s
        //    velD = distD / (TEMPO_MEDICAO_MS/1000);
    //    velD = rotD / (TEMPO_MEDICAO_MS); //velocidade em rpm
    return velD; // Retorna int
}

/**
  * @brief calcula a velocidade da roda esquerda e da direita a partir da variação da encoder
  * @param ponteiros que apontam para as velocidades (no main)
  * @return Nenhum
  */
void velRL(float*vl, float *vr)
{
	int tInit = 0, tEnd = 0; //variáveis de tempo
    float encD1, encD2, encD; //variável da encoder
    float distD, velD; //distancia e velocidade
    float encE, encE1, encE2; //variáveis da encoder
    float distE, velE; //distancia e velocidade
    //float rotD; //numero de rotacoes

    //    resetEncoderDireita();
    encD1 = getEncoderDireita();
	encE1 = getEncoderEsquerda();
    tInit = micros();           // Inicia contagem de tempo
    elapse_us(1*1000*PERIODO_AMOSTRAGEM_MS, tInit);
    tEnd = micros();            // Tempo final
    encD2 = getEncoderDireita();
    encD = encD2 - encD1; //pegando o quanto a roda avançou
	encE2 = getEncoderEsquerda();
	encE = encE2 - encE1;

    // Calcula distância (evitando divisão inteira)
    distD = 2 * PI * RAIO_PNEU_MM * (encD / 720.0f); // em mm
    distE = 2 * PI * RAIO_PNEU_MM * (encE / 720.0f); // em mm

    // Calcula velocidade (tempo real em segundos)
    float tempo = (tEnd - tInit) / 1000000.0f; // Converter ms para s
    *vr = (float)((-1)*distD / tempo); // -1 para inverter e corrigir o erro de medicao (provavelmente pinos trocados na placa)
    *vl = (float)((-1)*distE / tempo);
}


/**
  * @brief calcula a velocidade da roda esquerda e da direita a partir da variação da encoder a partir de uma média das velocidades de 5 coletas
  * @param ponteiros que apontam para as velocidades (no main)
  * @return Nenhum
  */
void velRL_media(float *vl, float *vr)
{
	int tInit = 0, tEnd = 0; //variáveis de tempo
    float encD1, encD2, encD; //variável da encoder
    float distD, velD; //distancia e velocidade
    float encE, encE1, encE2; //variáveis da encoder
    float distE, velE; //distancia e velocidade
    int numMedidas = 5, i; //numero de medidas e contador
    float encEhistory = 0, encDhistory = 0; //recebe e armazena temporariamente a velocidade lida
    float encEmedia, encDmedia; //media das velocidades lidas

    //zerando toda vez que a função é chamada
    encEhistory = 0; encDhistory = 0;
    encEmedia = 0, encDmedia = 0;

    for(i = 0; i < numMedidas; i++)
    {
        encD1 = getEncoderDireita();
    	encE1 = getEncoderEsquerda();
        tInit = micros();           // Inicia contagem de tempo
        elapse_us(1000*PERIODO_AMOSTRAGEM_MS, tInit);
        tEnd = micros();            // Tempo final
        encD2 = getEncoderDireita();
        encD = encD2 - encD1; //pegando o quanto a roda avançou
    	encE2 = getEncoderEsquerda();
    	encE = encE2 - encE1;
    	encDhistory += encD;
    	encEhistory += encE;
    }

    //calculando a media das medidas realizadas
    encDmedia = encDhistory/numMedidas;
    encEmedia = encEhistory/numMedidas;

    // Calcula distância (evitando divisão inteira)
    distD = 2 * PI * RAIO_PNEU_MM * (encDmedia / 360.0f); // em mm
    distE = 2 * PI * RAIO_PNEU_MM * (encEmedia / 360.0f); // em mm

    // Calcula velocidade (tempo real em segundos)
    float tempo = (tEnd - tInit) / 1000000.0f; // Converter ms para s
    *vr = (float)((-1)*distD / tempo);
    *vl = (float)((-1)*distE / tempo);
}


/**
  * @brief calcula a velocidade da roda esquerda a partir da variação da encoder
  * @param Nenhum
  * @return Velocidade da roda esquerda
  */
float velLeft()
{
    int tInit = 0, tEnd = 0; //variáveis de tempo
    float encE, encE1, encE2; //variáveis da encoder
    float distE, velE; //distancia e velocidade
    //float rotE; //numero de rotacoes

	encE1 = getEncoderEsquerda();
	tInit = micros();           // Inicia contagem de tempo
	elapse_us(TEMPO_MEDICAO_MS*1000, tInit);               // Delay não preciso (apenas exemplo)
	tEnd = micros();            // Tempo final
	encE2 = getEncoderEsquerda();
	encE = encE2 - encE1;

    // Calcula distância (evitando divisão inteira)
    distE = 2 * PI * RAIO_PNEU_MM * (encE / 360.0f); // em mm
    //    rotE = 60000*((float)encE / 360.0f); // 60000 para por a escala de ms para min

    // Calcula velocidade (tempo real em segundos)
    float tempo = (tEnd - tInit) / 1000000.0f; // Converter ms para s
    velE = distE / tempo;       // Velocidade em mm/s
    //    velE = rotE / (TEMPO_MEDICAO_MS); //velocidade em rpm
    //    velE = distE / (TEMPO_MEDICAO_MS/1000); //mm/s
    return velE; // Retorna float
}



/**
  * @brief Configura os motores com as velocidades recebidas da string lida na serial
  * @param String que contém as informações
  * @return Nenhum
  */
void configMotor(char* velconcat)
{
    int pwmR = 0, pwmL = 0;
    char velR[5] = {0}, velL[5] = {0}; // Strings para armazenar as velocidades (4 caracteres + '\0')
    uint8_t i = 0, split = 0, j = 0;

    // Verifica se a string de entrada é válida
    if (velconcat == NULL || strlen(velconcat) > 9) { // Exemplo: "-100,-200" tem 9 caracteres
        return;
    }

    // Separa as velocidades
    for (i = 0; i < strlen(velconcat); i++) {
        if (velconcat[i] == ',') {
            split = 1; // Indica que a próxima parte é a velocidade direita
            j = 0; // Reinicia o índice para a string velR
        } else
        {
            if (split == 0)
            {
                if (j < 4)
                { // Garante que não ultrapasse o tamanho máximo
                    velL[j] = velconcat[i];
                }
            } else
            {
                if (j < 4)
                { // Garante que não ultrapasse o tamanho máximo
                    velR[j] = velconcat[i];
                }
            }
            j++;
        }
    }

    // Termina as strings com '\0'
    velL[4] = '\0';
    velR[4] = '\0';

    // Converte as strings em inteiros
    pwmL = str2int(velL);
    pwmR = str2int(velR);

    // Configura os motores (função hipotética)
    setMotores(pwmL, pwmR);
}


/**
  * @brief Transforma uma string de números em inteiro
  * @param str: string a ser convertida
  * @return Valor inteiro representado pela string
  */
int str2int(const char* str) {
    // Verifica se a string está vazia ou tem mais de 3 caracteres
    if (str == NULL || strlen(str) > 4)
    {
        return 0;
    }

    int resultado = 0;
    uint inicio = 0;
    int negativo = 0;
    uint i;
    // Verifica se o primeiro caractere é um sinal de negativo
    if (str[0] == '-') {
        negativo = 1;
        inicio = 1;
    }

    // Converte cada caractere para o dígito correspondente
    for (i = inicio; i < strlen(str); i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            resultado = resultado * 10 + (str[i] - '0');
        } else
        {
            return 0;
        }
    }

    // Aplica o sinal negativo, se necessário
    if (negativo)
    {
        resultado = -resultado;
    }

    return resultado;
}


/**
  * @brief Obtém a tensão de referência (VREF) do giroscópio em mV.
  * @details Esta função lê o valor RAW do canal de referência do giroscópio (G_VREF_CH)
  *          e converte esse valor para milivolts (mV) usando a tensão de referência do ADC
  *          e sua resolução.
  * @param Nenhum
  * @return Tensão de referência do giroscópio em mV.
  */
float getVrefMV()
{
    uint32_t rawVref = getRawADC(G_VREF_CH); // Lê o valor RAW do canal de referência
    float vrefMV = (rawVref * VREF_ADC_MV) / ADC_RESOLUTION; // Converte para mV
    return vrefMV;
}


/**
  * @brief Calibra o giroscópio realizando múltiplas medições
  * @param Nenhum
  * @return OFFSET usado para corrigir as medições futuras.
  */
//const int OFFSET_GYRO = 0; // Inicialização do offset
int OFFSET_GYRO = 0;

int calibrateGyro()
{
	/* Bloco para coletar a média das leituras do gyroscopio*/
	int numero_amostras = 100; // contagem de amostras pra fazer a média
	int contador_amostragem = 0;// contador para realizar as amostragens
	int soma_amostras = 0; // soma das n amostras

	for(contador_amostragem = 0; contador_amostragem < numero_amostras; contador_amostragem++)
	{
		soma_amostras += getGyro(); //a cada amostragem ele pega o valor do gyroscopio
	}

	int offset = soma_amostras/numero_amostras; // media aritimética simples gera o offset a ser dado na medição do giroscópio

//	*((int*)&OFFSET_GYRO) = offset; //gambiarra
	OFFSET_GYRO = offset;
}


/**
  * @brief Calcula a velocidade angular do giroscópio em graus por segundo (°/s).
  * @details Esta função obtém o valor do giroscópio remove um offset gerado pela media de n leituras e converte
  *          esse valor para velocidade angular usando a sensibilidade do giroscópio,
  *          a tensão de referência (VREF) e a resolução do ADC (obtida no datasheet).
  * @param Nenhum
  * @return Velocidade angular em graus por segundo (°/s).
  */
int getAngularVelocity()
{
	// valor com o offset corrigido
	int valor_gyro_corrigido = getGyro() - OFFSET_GYRO;


	/*Bloco para calcular a velocidade angular*/
	//    int32_t rawValue = getGyro(); // Obtém o valor RAW do giroscópio
    float vrefMV = getVrefMV();   // Obtém a tensão de referência em mV
    float angularVelocity = (valor_gyro_corrigido * vrefMV) / (GYRO_SENSITIVITY * ADC_RESOLUTION); // Converte para °/s
    //    return valor_gyro_corrigido;
    return (int)angularVelocity;
}

/**
 *
 * @param val
 * @param margem
 * @return
 */
float randomize(float val, int margem)
{
	int opera;
	float randVal;
	float result;

	opera = rand()%2;
	randVal = rand()%(margem+1);

	if(opera == 0)
	{
		result = (val - randVal);
	}
	else if(opera == 1)
	{
		result = (val + randVal);
	}

	return result;
}

/**
 * @brief gera um prbs
 * @param val
 * @param margem
 * @return
 */
float prbs(float val, int margem)
{
    static unsigned int lfsr = 0xACE1u;
    int bit;

    bit  = ((lfsr >> 15) ^ (lfsr >> 14)) & 1;
    lfsr = (lfsr << 1) | bit;

    return bit ? (val + margem) : (val - margem);
}

/**
 *
 * @param velE
 * @param velD
 * @return velocidade angular em rad/s
 */
float velAng(float velE, float velD)
{

	    float velocidadeAngular;
	    // Calcula a velocidade angular em radianos por segundo
	    velocidadeAngular = (velD - velE)/COMPRIMENTO_MOUSE_MM;

	    // velocidadeAngular = velocidadeAngular/(2*PI); // Normalizando (botando em função de um arco completo) = numero de rotacoes
	    return velocidadeAngular; // Retorna a velocidade em rad/s
}

/**
 * @param velE Velocidade do motor esquerdo (mm/s)
 * @param velD Velocidade do motor direito (mm/s)
 * @return Velocidade angular em graus por segundo
 */
float velAngGrau(float velE, float velD)
{
    float velocidadeAngular;

    // Calcula a velocidade angular em radianos por segundo
    velocidadeAngular = (velD - velE) / COMPRIMENTO_MOUSE_MM;

    // Converte radianos por segundo para graus por segundo
    velocidadeAngular = velocidadeAngular * (180.0 / PI);

    return velocidadeAngular; // Retorna como inteiro
}

/**
 *
 * @param velE
 * @param velD
 * @return velocidade linear em mm/s
 */
float velLin(float velE, float velD)
{

	    float velocidadeLinear;
	    velocidadeLinear = (velD + velE)/2;

	    return velocidadeLinear; // Retorna int
}


/**
  * @brief ------
  * @details ----
  * @param Nenhum
  * @return ------
  */

int LF_OFFSET = 0, L_OFFSET = 0, R_OFFSET = 0, RF_OFFSET = 0; // inicializando os offsets
void calibrateWallSensors()
{
	// Variáveis
	int32_t lfsens, lsens, rsens, rfsens; // variaveis para os sensores
	int32_t suml = 0, sumlf = 0, sumr = 0, sumrf = 0; // soma das medidas
	int numMedidas = 100; // numero de medidas a serem realizadas

	//	printf("Calibrando os sensores de parede\n");

	int contador = 0;
	for (contador = 0; contador < numMedidas; contador++)
	{
		int parede;
		parede = getSensoresParede(&lfsens, &lsens, &rsens, &rfsens);

		// Soma recursiva das medições
		suml += lsens; sumlf += lfsens; sumr += rsens; sumrf += rfsens;

		// Delay para operação
		delay_ms(20);
	}

	// Calculando os offsets
	LF_OFFSET = sumlf/numMedidas;
	L_OFFSET = suml/numMedidas;
	R_OFFSET = sumr/numMedidas;
	RF_OFFSET = sumrf/numMedidas;

	//	printf("Fim da calibração\n");
}


/**
 * @brief transforma em um valor inteiro amplificado para ser enviado pelo microcontrolador
 * @param valor a ser amplificado
 * @return velocidade multiplicado pelo fator de amplificacao e no formato inteiro
 */
int amplify(float val)
{
	return (int)(AMPLIFICADOR*val);
}

/**
 * @brief recebe as velocidades de referencias linear e angular e calcula o valor da referencia para o valor de setMotores()
 * @param refLin referencia de velocidade linear (porcentagem)
 * @param refAng referencia de velocidade angular (rad/s)
 * @param lado (0 = direito | 1 = esquerdo)
 * @return valor percentual para usar em setMotores
 */
int ref2ref(float refLin, float refAng, int lado)
{
	/* Deve se mais a frente ver como os resultados se saem com a colocacao do raio R da curva
	 * 1 - este inicial com R = 18cm = 0.18m (tamanho da celula do lab)*/
	float a1 = 1.74/100.0; //1.74 m/s é a velocidade maxima linear do robo
	float velLin = refLin*a1; // velocidade linear em m/s
	float v_lado = 0; // velocidade do lado, podendo ser direita (R) ou esquerda (L)

	if(lado == 0) // direita
	{
		// inicialmente configurou-se o raio como "1"
		//		v_lado = (2*velLin + COMPRIMENTO_MOUSE_M*refAng)/(2*RAIO_CURVA_TRANSL_LABIRINTO_M); // velocidade usando a formula cinematica
		v_lado = (2*velLin + COMPRIMENTO_MOUSE_M*refAng)/(2*1); // velocidade usando a formula cinematica com R = 1
	}
	else if(lado == 1) // esquerda
	{
		// inicialmente configurou-se o raio como "1"
		//		v_lado = (2*velLin - COMPRIMENTO_MOUSE_M*refAng)/(2*RAIO_CURVA_TRANSL_LABIRINTO_M); // velocidade usando a formula cinematica
		v_lado = (2*velLin - COMPRIMENTO_MOUSE_M*refAng)/(2*1); // velocidade usando a formula cinematica com R = 1
	}

	int v_percent; // valor percentual para o setMotores
	v_percent = (int)(v_lado*100.0/11.232); // normalizacao no intervalo de 0 a 100
	return v_percent;

}


/**
 * @brief Converte velocidades de referência linear e angular para valores percentuais dos motores
 * @param refLin Referência de velocidade linear (0-100%)
 * @param refAng Referência de velocidade angular (rad/s)
 * @param lado (0 = direito, 1 = esquerdo)
 * @return Valor percentual para setMotores (0-100), saturando se necessário
 */
float ref2ref_corrigida(float refLin, float refAng, int lado)
{
    // Parâmetros do robô
    const float VEL_MAX_M_S = 1.74f;        // Velocidade máxima linear em m/s
    const float L = COMPRIMENTO_MOUSE_M;    // Distância entre rodas em metros
//    const float R_WHEEL = RAIO_RODA_M;      // Raio da roda em metros (se necessário)

    // Converter refLin de porcentagem para m/s
    float velLin = (refLin / 100.0f) * VEL_MAX_M_S;

    // Calcular velocidades das rodas (fórmula cinemática correta)
    float v_lado;
    if(lado == 0) // roda direita
    {
        v_lado = velLin + (L/2.0f) * refAng;
    }
    else // roda esquerda
    {
        v_lado = velLin - (L/2.0f) * refAng;
    }

    // Converter velocidade linear da roda para % do motor
    // Considerando que velocidade máxima da roda = VEL_MAX_M_S + (L/2)*ANG_MAX
    const float VEL_MAX_RODA_M_S = VEL_MAX_M_S + (L/2.0f) * 10.0f; // Ex: 10 rad/s como ang máximo

//    float v_percent_float = (v_lado / VEL_MAX_RODA_M_S) * 100.0f;
    float v_percent_float = (v_lado / VEL_MAX_M_S) * 100.0f; // teste de outra normalizacao no percentual

    // Saturar entre 0 e 100
    if(v_percent_float > 100.0f) v_percent_float = 100.0f;
    if(v_percent_float < -100.0f) v_percent_float = -100.0f;

    // return (int)v_percent_float;
    return v_percent_float;
}
