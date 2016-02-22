#include "ninjaskit/ninjaskit.h"
#include "keypad/keypad.h"


gpio_pin rows[] = { {PC, 13}, {PC, 15}, {PB, 9}, {PA, 11} };
gpio_pin cols[] = { {PB, 8}, {PB, 7}, {PA, 12}, {PB, 6 }};
Keypad<4, 4> keypad(rows, cols);


int main()
{
    clock_setup();

    Serial1.begin(57600);

    keypad.begin();
    
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

