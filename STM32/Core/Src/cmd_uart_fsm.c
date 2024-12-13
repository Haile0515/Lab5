/*
 * cmd_uart_fsm.c
 *
 *  Created on: Dec 5, 2024
 *      Author: ADMIN
 */

#include "cmd_uart_fsm.h"

extern ADC_HandleTypeDef hadc1;

extern UART_HandleTypeDef huart2;

int status = INIT;
int ADC_value = 0;

uint8_t temp;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;

uint8_t cmd_flag = INIT;
uint8_t cmd_data[MAX_CMD_SIZE];
uint8_t cmd_data_index = 0;

int isRST(uint8_t str[]) {
	if (str[0] == 'R' && str[1] == 'S' && str[2] == 'T')
		return 1;
	else
		return 0;
}

int isOK(uint8_t str[]) {
	if (str[0] == 'O' && str[1] == 'K')
		return 1;
	else
		return 0;
}

void cmd_parser_fsm() {
	switch (status) {
	case INIT:
		if (temp == '!')
			status = READING;
		break;
	case READING:
		if (temp != '!' && temp != '#') {
//			if (cmd_data_index < MAX_CMD_SIZE) {
				cmd_data[cmd_data_index] = temp;
				cmd_data_index++;
//			} else {
//				char cmd_overflow[] = "\r\nInput exceeded MAX_CMD_SIZE!\r\n";
//				HAL_UART_Transmit(&huart2, (uint8_t*)cmd_overflow, sizeof(cmd_overflow) - 1, 500);
//				status = INIT;
//				cmd_data_index = 0;
//			}
		}
		if (temp == '#') {
			status = STOP;
			cmd_data_index = 0;
		}
		break;
	case STOP:
		if (isRST(cmd_data) == 1) {
			cmd_flag = RST;
//			HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n", 2, 100);
			setTimer1(10);
		} else if (isOK(cmd_data) == 1) {
			cmd_flag = OK;
		}
		status = INIT;
		break;
	default:
		break;
	}
}

void uart_comms_fsm() {
	char str[50];

	switch (cmd_flag) {
	case RST:
		if (timer1_flag == 1) {
			ADC_value = HAL_ADC_GetValue(&hadc1);
			HAL_UART_Transmit(&huart2, (void*) str, sprintf(str, "!ADC=%d#\r\n", ADC_value), 500);
			//time out 500ms: wait from cmd to uart
			//ADC trong STM32 là 13 bit -> 5V = 4096 DEC -> 3.3V ~ 2073 DEC
			// !ADC=1234#\r\n -> 12 kí tự -> thời gian truyền 1 kí tự = (1/baud_rate) x 10
			// 10 bit = 1 bit start + 8 bit data + 1 bit stop. baud_rate = 9600
			// time truyền 12 kí tự = 12x1/9600x10 = 12.5 ms < 500 ms
			setTimer1(3000);
		}
		break;
	case OK:
		ADC_value = -1;
		cmd_flag = INIT;
		break;
	default:
		break;
	}
}














