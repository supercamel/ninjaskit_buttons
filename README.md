<h1>Ninjaskit Keypad Library</h1>

This is an easy keypad library for digital 'column scanning' type keypads such as <a href="http://core-electronics.com.au/keypad-12-button.html/?acc=1f0e3dad99908345f7439f8ffabdffc4">this</a>.<br><br>
The keypad library is event-driven; it doesn't just tell you the state of the buttons, instead it creates 'button pressed' and 'button released' events. <br><br>
To ensure the keypad is responsive, the application should call the 'read_keypad' function approximately every 10 milliseconds. This function checks the state of the keypad and if necessary it generates pressed/released events. <br><br>
The application can check if there are events pending using 'get_n_events'. If there are events, they can be retrieved and processed using the 'get_event' function.
