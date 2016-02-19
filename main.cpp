#include "ninjaskit/ninjaskit.h"
#include "keypad/keypad.h"

int main()
{
	clock_setup();
	
	Serial1.begin(57600);
	
	//create a list of row pins
	gpio_pin rows[] = { {PA, 0}, {PA, 1}, {PA, 2}, {PA, 3} };
	
	//create a list of column pins
	gpio_pin cols[] = { {PA, 4}, {PA, 5}, {PA, 6}, {PA, 7 }};
	
	//create a keypad with four rows and four columns - 16 buttons total
	Keypad<4, 4> keypad(rows, cols);
							
	while(true)
	{
		etk::sleep_ms(10);
		
		//read the state of the keypad and generate events if necessary
		keypad.read_keypad();
		
		//while there are events queued up
		while(keypad.get_n_events())
		{
			//get the next event
			auto event = keypad.get_event();
			
			//if it's a button press
			if(event.type == BUTTON_PRESS_EVENT)
				Serial1.print("button ", event.button, " has been pressed\r\n");
				
			//if it's a button release
			if(event.type == BUTTON_RELEASE_EVENT)
				Serial1.print("button ", event.button, " has been released\r\n");
		}
	}
}

