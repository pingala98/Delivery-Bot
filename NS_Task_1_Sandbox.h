#include "NS_Task_1_Predef.h"
extern unsigned int color_sensor_pulse_count;
/*
* Function Name: forward_wls
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the nodes specified
* Example Call: forward_wls(2) //Goes forward by two nodes
*
*/
bool forward_wls(unsigned char node);

void left_turn_wls(int);

void right_turn_wls(int);

bool Square(void);

void Task_1_1(void);

void Task_1_2(void);

bool pathToMotion(void);

char detectColor(void);