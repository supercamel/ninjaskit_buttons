#ifndef KEYPAD_H_INCLUDED
#define KEYPAD_H_INCLUDED

#include "ninjaskit/ninjaskit.h"


const int KEYPAD_EVENT_BUFFER_SIZE = 4;

enum EVENT_TYPE
{
    BUTTON_PRESS_EVENT,
    BUTTON_RELEASE_EVENT
};

struct KeypadEvent
{
    EVENT_TYPE type;
    uint32 button;
    etk::Time time;
};


template <uint8 N_ROWS, uint8 N_COLS> class Keypad
{
public:
    Keypad(gpio_pin row_pins[N_ROWS], gpio_pin col_pins[N_COLS]) : ringbuf(event_buffer, KEYPAD_EVENT_BUFFER_SIZE)
    {
        for(uint32 i = 0; i < N_ROWS; i++)
        {
            configure_as_input(row_pins[i], INPUT_PULLDOWN);
            row_pin[i] = row_pins[i];
        }

        for(uint32 i = 0; i < N_COLS; i++)
        {
            configure_as_output(col_pins[i]);
            col_pin[i] = col_pins[i];
        }

        for(auto i : etk::range(N_COLS))
        {
            for(auto j : etk::range(N_ROWS))
                button_states[j][i] = false;
        }
    }

    void read_keypad()
    {
        for(auto i : etk::range(N_COLS))
        {
            set_pin(col_pin[i], true);

            for(auto j : etk::range(N_ROWS))
            {
                bool state = read_pin(row_pin[j]);
                if(state != button_states[j][i])
                {
                    //append event
                    KeypadEvent event;
                    event.time = etk::now();
                    event.button = j*N_ROWS + i;
                    state ? event.type = BUTTON_PRESS_EVENT : event.type = BUTTON_RELEASE_EVENT;

                    ringbuf.put(event);

                    button_states[j][i] = state;
                }
            }

            set_pin(col_pin[i], false);

            //pause for a *very* short moment just incase the lines are very long / have some stray capacitance and need a moment to switch low
            //i really don't know this is necessary, but whatever.
            while(etk::static_range(3))
                asm("nop");
        }
    }

    uint32 get_n_events()
    {
        return ringbuf.available();
    }

    KeypadEvent get_event()
    {
        if(get_n_events())
            return ringbuf.get();
        return KeypadEvent();
    }

private:
    bool button_states[N_ROWS][N_COLS];
    gpio_pin row_pin[N_ROWS];
    gpio_pin col_pin[N_COLS];

    KeypadEvent event_buffer[KEYPAD_EVENT_BUFFER_SIZE];
    etk::RingBuffer<KeypadEvent> ringbuf;
};


#endif


