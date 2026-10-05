# umart_lite_plus_teste

Firmware bare-metal em C para um robô **Micromouse** baseado na placa **uMart Lite Plus** (STM32F405). O projeto reúne os drivers dos periféricos, o controle de velocidade em malha fechada (PID discreto) e a infraestrutura para identificação de sistema e para uma MLP embarcada.

> **Status:** em desenvolvimento. O `main.c` atual é uma aplicação de teste e coleta de dados (identificação e validação de malha de velocidade). O algoritmo de resolução de labirinto ainda não está nesta base de código.

## Sumário

- [Hardware](#hardware)
- [Funcionalidades](#funcionalidades)
- [Estrutura do repositório](#estrutura-do-repositório)
- [Toolchain e dependências](#toolchain-e-dependências)
- [Build](#build)
- [Gravação](#gravação)
- [Uso](#uso)
- [Configuração](#configuração)
- [Créditos](#créditos)

## Hardware

| Item | Detalhe |
|---|---|
| MCU | STM32F405 (`STM32F405xx`), Cortex-M4F |
| Clock | HSE de 8 MHz, PLL (M = 8, N = 336, P = 2), SYSCLK de **168 MHz** |
| Memória | 1 MB de Flash, 128 KB de RAM e 64 KB de CCM RAM |
| Atuação | 2 motores DC por ponte H TB6612FNG, PWM em TIM4 (PB6/PB7) |
| Sensoriamento | Encoders nas duas rodas, 4 sensores infravermelhos de parede (LF, L, R, RF), giroscópio LY3200ALH (ADC) |
| Interface | UART1 (9600 baud, padrão do `printf`), USB CDC, botão SW1, LEDs, buzzer (PB4) |
| Armazenamento | Flash interna (setor 11, `0x080E0000`) para dados persistentes |

Parâmetros mecânicos usados nos cálculos (em `include/user.h`): raio da roda de 16 mm e distância entre rodas de 89,7 mm.

Datasheets e manuais estão no repositório de documentação do projeto (pasta `Manuais-e-instrucoes`).

## Funcionalidades

- **Drivers dos periféricos:** motores (PWM), encoders, sensores IR, giroscópio, LEDs, botão, buzzer, UART, USB CDC e Flash.
- **Cálculo de velocidades:** velocidade de cada roda a partir dos encoders, e velocidades linear e angular do robô por cinemática diferencial.
- **Calibração:** offset do giroscópio e dos sensores de parede na inicialização.
- **Controle:** PID discreto em forma de velocidade (`PID(g0, g1, g2, ...)`), com ganhos sintonizados pelo método de Åström. Há também funções de Ziegler-Nichols e de PID com filtro derivativo.
- **Malha em cascata:** controladores de velocidade linear e angular geram as referências dos controladores individuais dos motores.
- **Identificação de sistema:** geração de sinais PRBS e coleta de 900 amostras (Ts = 10 ms), com envio dos dados em CSV pela serial.
- **Redes neurais:** pesos de uma MLP exportados do treinamento externo (`hiddenlayer1.c`, `hiddenlayer2.c`, `outputlayer.c`). A inferência (`mlp.c`) ainda não está implementada.

## Estrutura do repositório

```
umart_lite_plus_teste/
├── src/          # Código-fonte (aplicação e drivers)
├── include/      # Cabeçalhos do projeto e configuração do HAL
├── system/       # CMSIS, HAL STM32F4, newlib e diagnóstico (bibliotecas de terceiros)
├── USB/          # Pilha USB Device (Core e CDC)
├── ldscripts/    # Linker scripts (mem.ld, sections.ld, libs.ld)
├── Debug/        # Saída do build Debug (gerada, ignorada pelo Git)
├── Release/      # Saída do build Release (gerada, ignorada pelo Git)
├── .cproject     # Configuração do projeto Eclipse (CDT)
└── .project
```

Módulos principais em `src/`:

| Módulo | Função |
|---|---|
| `main.c` | Aplicação de teste: coleta de dados de malha fechada |
| `user.c` | Velocidades, giroscópio, PRBS, conversão de referências, curvas |
| `controle.c` | PID, normalização de entrada e saída, Ziegler-Nichols |
| `motores.c`, `encoders.c`, `sensores.c` | Drivers de atuação e sensoriamento |
| `usart1.c`, `usb_user.c`, `usbd_*.c` | Comunicação serial e USB |
| `flash.c` | Leitura e escrita na Flash |
| `leds.c`, `botao.c`, `buzzer.c`, `delays.c` | Periféricos auxiliares e temporização |
| `mlp.c`, `hiddenlayer*.c`, `outputlayer.c` | Rede neural (pesos exportados) |

## Toolchain e dependências

- **IDE:** Eclipse CDT com o plugin GNU ARM Eclipse (build gerenciado).
- **Compilador:** `arm-none-eabi-gcc` (os tutoriais usam a versão 5.4 2016q3).
- **Build tools:** GNU ARM Eclipse Build Tools 2.6 (make).
- **C library:** newlib-nano (`-specs=nano.specs`), com `-nostartfiles`.
- **Defines do projeto:** `STM32F405xx`, `USE_HAL_DRIVER`, `HSE_VALUE=8000000` e `USE_FULL_ASSERT`.
- **Gravação:** bootloader USB DFU da própria MCU (driver WinUSB via Zadig no Windows).

O passo a passo de instalação do ambiente (Eclipse, compilador, driver DFU) está nos PDFs da pasta `Manuais-e-instrucoes/INSTRUÇÕES PARA PREPARAR O IDE`, no repositório de documentação do projeto.

## Build

1. No Eclipse, importe o projeto: **File → Import → General → Existing Projects into Workspace**.
2. Selecione a configuração **Release** ou **Debug**.
3. Compile com **Project → Build Project**.

Os artefatos ficam em `Release/` (`.elf`, `.hex`, `.bin` e `.map`). Essas pastas são geradas e estão no `.gitignore`.

## Gravação

1. Coloque a placa em modo bootloader: segure o botão de boot e pressione reset.
2. Confirme que o dispositivo aparece como **STM32 BOOTLOADER** no Gerenciador de Dispositivos (driver WinUSB instalado).
3. Grave o `.bin` ou o `.hex` por DFU (por exemplo com o DfuSe ou com a automação configurada no Eclipse).

## Uso

A aplicação de teste (`main.c`) funciona como máquina de dois estados, controlada pelo botão **SW1**:

1. **Estado 0 – coleta:** o robô executa uma sequência de referências (velocidade linear constante e referência angular em três patamares), roda a malha em cascata e armazena as 900 amostras.
2. **Estado 1 – envio:** os dados são enviados pela UART em CSV, uma linha por amostra:

```
k, uV, uW, yV, yW, t
```

Os valores são inteiros amplificados por `AMPLIFICADOR` (10000). Divida pela constante para recuperar a unidade original.

Para capturar, abra um terminal serial em **9600 8N1** e salve a saída. Um buzzer sinaliza cada transição de estado.

## Configuração

| Parâmetro | Arquivo | Descrição |
|---|---|---|
| `PERIODO_AMOSTRAGEM_MS` | `include/controle.h` | Período de amostragem do controle (10 ms) |
| `BAUD_RATE` | `include/usart1.h` | Baud rate da UART (9600) |
| `STDIO_UART` / `STDIO_USB` | `include/main.h` | Destino do `printf` e `scanf` |
| `HSE_VALUE` | `.cproject` (defines) | Frequência do cristal (8 MHz) |
| `ADDR_FLASH_SECTOR` | `include/flash.h` | Setor de Flash para dados persistentes |
| Ganhos `g0`, `g1`, `g2` | `src/main.c` | Ganhos dos PIDs dos motores e das velocidades linear e angular |

## Créditos

- Base do firmware e drivers dos periféricos: **Kleber Lima da Silva** (2015).
- Módulos `user`, `controle` e `mlp`, e a aplicação de identificação: **Handel Mateus** (2026).
- Bibliotecas de terceiros: STMicroelectronics (CMSIS e HAL STM32F4, pilha USB Device). Consulte os cabeçalhos dos arquivos em `system/` e `USB/` para as licenças.
