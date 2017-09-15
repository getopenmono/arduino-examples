#include <mono.h>

/*
* We have 3 extra functions:
*
* * `reset`: Resets the counter to *00:00.00*.
* * `toggle`: Starts or stops the counter (toggles a *Timer* object)
* * `increment`: Increments the counter value by 10 ms.
*
* One thing to note is we store the timestamp in two distinct objects.
* An `unsigned integer` stores the millisecond component of the counter.
* Every time it reaches 1000 ms we increment the other timestamp
* (a *DateTime* object), that stores the minutes and seconds.
*/

using mono::ui::TextLabelView; // import the classes into the global namespace
using mono::ui::ButtonView;

TextLabelView lbl;
ButtonView resetCntBtn, toggleBtn;
mono::Timer tim;
mono::DateTime count;
uint32_t countMs;

void reset() // Reset the counter, and update display
{
    count = mono::DateTime(0,0,0,0,0,0);
    countMs = 0;
    lbl.setText(mono::String::Format("%02d:%02d.%02d",
    	count.Minutes(), count.Seconds(), countMs/10));
}

void toggle() // start/stop the timer and update button text
{
    if (tim.Running()) {
        toggleBtn.setText("Start");
        tim.stop();
    } else {
        toggleBtn.setText("Pause");
        tim.start();
    }
}

void increment() // increment the milliseconds, and update timestamp if needed
{
    countMs += 10; // add 10 ms (the timers interval)

    if (countMs >= 1000) { // if more than 1 sec, increment the timestamp object
        countMs = 0;
        count = count.addSeconds(1);
    }

    lbl.setText(mono::String::Format("%02d:%02d.%02d",
    	count.Minutes(), count.Seconds(), countMs/10));
}

void setup() // add text label, buttons and the timer
{
    lbl = TextLabelView(mono::geo::Rect(50,10,156,70),"00:00.00");
    lbl.show();

    reset(); // set the initial count to zero

    resetCntBtn = ButtonView(mono::geo::Rect(20,160, 136, 40), "Reset Count");
    resetCntBtn.setClickCallback(&reset);
    resetCntBtn.show();

    toggleBtn = ButtonView(mono::geo::Rect(20,100, 136, 40), "Start");
    toggleBtn.setClickCallback(&toggle);
    toggleBtn.show();

    tim.setInterval(10); // set the timer interval to 10 ms
    tim.setCallback(&increment); // the timers callback function
}

void loop() {

}