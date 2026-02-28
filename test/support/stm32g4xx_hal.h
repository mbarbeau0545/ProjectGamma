#pragma once

#include <stdint.h>

#ifndef DMA_CIRCULAR
#define DMA_CIRCULAR (0u)
#endif

#ifndef DMA_NORMAL
#define DMA_NORMAL (1u)
#endif

typedef struct { uint32_t dummy; } ADC_HandleTypeDef;
typedef struct { uint32_t dummy; } USART_HandleTypeDef;
typedef struct { uint32_t dummy; } UART_HandleTypeDef;
typedef struct { uint32_t dummy; } SPI_HandleTypeDef;
typedef struct { uint32_t dummy; } TIM_HandleTypeDef;
typedef struct { uint32_t dummy; } DMA_HandleTypeDef;
typedef struct { uint32_t dummy; } FDCAN_HandleTypeDef;
typedef struct { uint32_t dummy; } HRTIM_HandleTypeDef;
