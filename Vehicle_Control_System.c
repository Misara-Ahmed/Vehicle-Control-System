/*
 * Vehicle_Control_System.c
 *
 *  Created on: Sep 25, 2022
 *      Author: Misara
 */

#include <stdio.h>
#include <math.h>
// preprocessor directive to control the engine temperature controller.
#define WITH_ENGINE_TEMP_CONTROLLER 1

// Global structure that contains the variables needed.
struct Engine_State
{
	int Engine_state;
	int AC_state;
	int ETC_state;
	int Vehicle_speed;
	int Room_temp;
	int Engine_temp;

}Estate; // Object from the structure.

enum Engine // Engine states.
{
	Engine_OFF=0 , Engine_ON=1
};

enum AC // AC states.
{
	AC_OFF=0 , AC_ON=1
};

#if WITH_ENGINE_TEMP_CONTROLLER
enum Engine_temp_Controller // Engine temperature controller states.
{
	ETC_OFF=0 , ETC_ON=1
};
#endif

// Functions prototype:
void display ( void ); // Function to display the required output.
void startupMenu( void ); // Function that will be called at first.
void sensorsMenu( void ); // Function of the sensors set menu.
void traffic( void ); // Function to choose the color of the traffic light required.
void roomTemp( void ); // Function of the room temperature.
void engineTemp( void ); // Function of the engine temperature.
void checkVehicleSpeed( void ); // Function to check the speed of the vehicle before displaying the states of the engine.

// Functions:
void checkVehicleSpeed( void )
{
	if (Estate.Vehicle_speed == 30)
	{
		Estate.AC_state = AC_ON;
#if WITH_ENGINE_TEMP_CONTROLLER
		Estate.ETC_state= ETC_ON;
		Estate.Engine_temp =  (Estate.Engine_temp) * (5.0/4) + 1;
#endif
		Estate.Room_temp =   (Estate.Room_temp) * (5.0/4) + 1;
	}
}

void display ( void )
{
	printf("\n");
	checkVehicleSpeed();
	switch (Estate.Engine_state)
	{
	case Engine_OFF :
		printf("Engine state: OFF \n");
		break;
	case Engine_ON :
		printf("Engine state: ON \n");
		break;
	}
	switch(Estate.AC_state){
	case AC_OFF :
		printf("AC: OFF \n");
		break;
	case AC_ON :
		printf("AC: ON \n");
		break;
	}
	printf("Vehicle speed: %d km/hr \n", Estate.Vehicle_speed );
	printf("Room temperature: %d\n", Estate.Room_temp );
#if WITH_ENGINE_TEMP_CONTROLLER
	switch(Estate.ETC_state){
	case ETC_ON :
		printf("Engine temperature controller state: ON \n");
		break;
	case ETC_OFF :
		printf("Engine temperature controller state: OFF \n");
	}
	printf("Engine temperature: %d \n", Estate.Engine_temp);
	fflush(stdout);
#endif
	printf("\n");
}

void traffic( void )
{
	char input;
	printf("Color required: ");
	fflush(stdout);
	scanf(" %c",&input);
	switch (input){
	case 'R':
	case 'r':
		Estate.Vehicle_speed = 0;
		break;
	case 'O':
	case 'o':
		Estate.Vehicle_speed = 30;
		break;
	case 'G':
	case 'g':
		Estate.Vehicle_speed = 100;
		break;
	default: // Checks if the input is non of the cases.
		printf("Wrong input. \n");
		fflush(stdout);
		traffic();
	}
	display();
	sensorsMenu();
}

void roomTemp( void )
{
	int input;
	printf("Room temperature: ");
	fflush(stdout);
	scanf("%d",&input);
	if (input <= 10 || input >= 30)
	{
		Estate.Room_temp = 20;
		Estate.AC_state = AC_ON;
	}
	else
	{
		Estate.AC_state = AC_OFF;
	}
	display();
	sensorsMenu();
}

#if WITH_ENGINE_TEMP_CONTROLLER
void engineTemp( void )
{
	int input;
	printf("Engine temperature: ");
	fflush(stdout);
	scanf("%d",&input);
	if (input <= 100 || input >= 150)
	{
		Estate.Engine_temp = 125;
		Estate.ETC_state= ETC_ON;
	}
	else
	{
		Estate.ETC_state = ETC_OFF;
	}
	display();
	sensorsMenu();
}
#endif

void sensorsMenu( void )
{
	char input;
	printf("Sensors set menu: \n");
	printf("a. Turn off the engine. \n");
	printf("b. Set the traffic light color. \n");
	printf("c. Set the room temperature. \n");
#if WITH_ENGINE_TEMP_CONTROLLER
	printf("d. Set the engine temperature. \n");
#endif
	printf("\n");
	fflush(stdout);
	scanf(" %c",&input);
	switch (input)
	{
	case 'a':
		Estate.Engine_state = Engine_OFF;
		display();
		startupMenu();
		break;
	case 'b':
		traffic();
		break;
	case 'c':
		roomTemp();
		break;
#if WITH_ENGINE_TEMP_CONTROLLER
	case 'd':
		engineTemp();
		break;
#endif
	default: // Checks if the input is non of the cases.
		printf("Wrong input. \n");
		fflush(stdout);
		sensorsMenu();
	}
}

void startupMenu( void )
{
	char input;
	printf("Choose one of the options: \n");
	printf("a. Turn on the vehicle engine. \n");
	printf("b. Turn off the vehicle engine. \n");
	printf("c. Quit the system. \n\n");
	fflush(stdout);
	scanf(" %c",&input);
	switch (input)
	{
	case 'a':
		Estate.Engine_state = Engine_ON;
		printf("Turn on the Vehicle Engine. \n\n");
		fflush(stdout);
		sensorsMenu();
		break;
	case 'b':
		Estate.Engine_state = Engine_OFF;
		printf("Turn off the Vehicle Engine. \n\n");
		fflush(stdout);
		display();
		startupMenu();
		break;
	case 'c':
		printf("Quit the system. \n\n");
		fflush(stdout);
		break;
	default: // Checks if the input is non of the cases.
		printf("Wrong input. \n");
		fflush(stdout);
		startupMenu();
	}
}

int main()
{
	// Initialization:
	enum Engine Engine_state = Engine_OFF;
	enum AC AC_state = AC_OFF;
#if WITH_ENGINE_TEMP_CONTROLLER
	enum Engine_temp_Controller ETC_state = ETC_OFF;
	Estate.ETC_state = ETC_state;
	Estate.Engine_temp = 130;
#endif
	Estate.Engine_state = Engine_state;
	Estate.AC_state = AC_state;
	Estate.Vehicle_speed = 0;
	Estate.Room_temp = 25;
	Estate.Engine_temp = 130;
	startupMenu();
}
