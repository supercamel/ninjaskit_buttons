#include "ninjaskit/ninjaskit.h"
#include "keypad/keypad.h"

int main()
{
	clock_setup();
	
	Serial1.begin(57600);
	
	gpio_pin rows[] = { {PA, 0}, {PA, 1}, {PA, 2}, {PA, 3} };
	gpio_pin cols[] = { {PA, 4}, {PA, 5}, {PA, 6}, {PA, 7 }};
	Keypad<4, 4> keypad(rows, cols);
							
	while(true)
	{
		etk::sleep_ms(10);
		keypad.read_keypad();
		if(keypad.get_n_events())
		{
			auto event = keypad.get_event();
			Serial1.print("Event\r\n");
			(event.type == BUTTON_PRESS_EVENT) ? Serial1.print("press ") : Serial1.print("release ");
			Serial1.print(event.button, "\r\n");
		}
	}
}

