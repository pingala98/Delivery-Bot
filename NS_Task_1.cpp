#include "NS_Task_1_Sandbox.h"

int main(int argc, char* argv[])
{
	init();
	std::thread t_1(threadCalls);
	/* 
	*  Your code will be called below this. Before Submitting encapsulate your code in a single function.
	*  That is, in your submission there should only be a single function called as shown below.
	*/
	//Square();		//For Testing The Square Shape
	//Task_1_1();	//For executing your Task 1.1
	Task_1_2();	//For executing your Task 1.2
	
	//left_turn_wls(0);
	//right_turn_wls(0);
	//_delay_ms(5000);
	
	//while (1) printf("%d\n", ADC_Conversion(4));
	//forward_wls(1);
	//right();
	//velocity(150, 150);
	//_delay_ms(330);
	
	cleanUp();
	t_1.detach();
}