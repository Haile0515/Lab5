/*
 * cmd_uart_fsm.h
 *
 *  Created on: Dec 5, 2024
 *      Author: ADMIN
 */

#ifndef INC_CMD_UART_FSM_H_
#define INC_CMD_UART_FSM_H_

#include "main.h"
#include "softwareTimer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT 0

#define READING 1

#define STOP 2

#define RST 8

#define OK 9

#define MAX_CMD_SIZE 3

#define MAX_BUFFER_SIZE 30

extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;

void cmd_parser_fsm();

void uart_comms_fsm();


#endif /* INC_CMD_UART_FSM_H_ */
