/*
 * fsm_automatic.c
 *
 *  Created on: Dec 6, 2022
 *      Author: ASUS
 */


#include "fsm_automatic.h"

int timered = 5000;		// time led RED
int timegreen = 3000;	// time led GREEN
int timeyellow = 2000;	// time led YELLOW

//////// TRAFFIC 11111111

void red_1_on()	// 10
{
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, 1);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 0);
}

void yellow_1_on()	// 11
{
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, 0);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 0);
}

void green_1_on()	// 01
{
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, 0);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 1);
}

void traffic_1_off()	// 00
{
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, 1);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 1);
}

//////// TRAFFIC 222222222

void red_2_on()	// 10
{
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 1);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 0);
}

void yellow_2_on()	// 11
{
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 0);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 0);
}

void green_2_on()	// 01
{
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 0);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 1);
}

void traffic_2_off()	// 00
{
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 1);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 1);
}

/////////// FSM 1111111

void fsm_automatic_1_run()
{
	switch(status_1)
	{
	case INIT_1:

		traffic_1_off();

		status_1 = AUTO_RED_1;
		setTimer1(timered);
		break;
	case AUTO_RED_1:
		red_1_on();

		if(timer1_flag == 1)
		{
			setTimer1(timegreen);
			status_1 = AUTO_GREEN_1;
		}
		break;
	case AUTO_GREEN_1:
		green_1_on();

		if(timer1_flag == 1)
		{
			setTimer1(timeyellow);
			status_1 = AUTO_YELLOW_1;
		}
		break;
	case AUTO_YELLOW_1:
		yellow_1_on();

		if(timer1_flag == 1)
		{
			setTimer1(timered);
			status_1 = AUTO_RED_1;
		}
		break;
	default:
		break;
	}
}

////// FSM 22222222

void fsm_automatic_2_run()
{
	switch(status_2)
	{
	case INIT_2:
		traffic_2_off();

		status_2 = AUTO_GREEN_2;
		setTimer2(timegreen);
		break;
	case AUTO_RED_2:
		red_2_on();

		if(timer2_flag == 1)
		{
			setTimer2(timegreen);
			status_2 = AUTO_GREEN_2;
		}
		break;
	case AUTO_GREEN_2:
		green_2_on();

		if(timer2_flag == 1)
		{
			setTimer2(timeyellow);
			status_2 = AUTO_YELLOW_2;
		}
		break;
	case AUTO_YELLOW_2:
		yellow_2_on();

		if(timer2_flag == 1)
		{
			setTimer2(timered);
			status_2 = AUTO_RED_2;
		}
		break;
	default:
		break;
	}
}



