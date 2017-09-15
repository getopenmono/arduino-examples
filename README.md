# Develop Mono apps in Arduino IDE

**Hi all! As the summer is coming to an end, we would like to show off the possibilities of using _Arduino IDE_ and Mono together. If you develop _Arduino_ software or intend to, this update is for you! If you do not know about _Arduino_, then feel free to skip this writing or read on anyways.**

We feel the need to get the word out. We have a working development environment for Mono, integrated directly into *Arduino IDE*. Everyone familiar with Arduino's `setup` and `loop` scheme, should know you can use this to create Mono applications.

### Adding Mono support in Arduino IDE

Arduino added a great feature to their version 1.6 of the _Arduino IDE_; the _Board Manager_. This tool allows you to easily add extensions to the *IDE*, making it very quick and simple to build Arduino sketches for Mono.

If you find the examples below interesting, we really encourage you to take a look at our [Arduino *Getting started* guide](http://developer.openmono.com/en/latest/getting-started/arduino-hackers.html) on our developer site.

## Quick Examples

Just to demonstrate how quick and agile our APIs are inside the _Arduino IDE_, we shall look at some very brief examples, starting with the basic ones.

### Display text on the screen

First, we shall see a simple sketch that shows a static text on the screen. The code below adds a `TextLabelView` object and initializes it inside the `setup` function. We also give the text a neat color to make it appear more *Arduino like*.

```cpp
#include <mono.h>

mono::ui::TextLabelView lbl;

void setup()
{
    lbl = mono::ui::TextLabelView(
        mono::geo::Rect(10,10,156,70),
        "Say hi through the\nArduino IDE"
    );

    lbl.setText(mono::display::TurquoiseColor);
    lbl.show();
}

void loop() { }
```

### Toggle a button

Now that you have seen how to add text to the screen, let us also add a button. When pressed a text should appear as response to the button press.

In this example we declare a `TextLabelView` and a `ButtonView` along with a function (`buttonClick`), to handle the button click event.

The `setup` function initializes both the text-label and button, sets the label's text alignment and initial empty string value. The function `buttonClick` is set as the *click callback handler* on the button.

```cpp
#include <mono.h>

mono::ui::ButtonView btn;
mono::ui::TextLabelView lbl;

void buttonClick() {
    lbl.setText("Hooray!");
}

void setup() {
    lbl = mono::ui::TextLabelView(mono::geo::Rect(20, 60, 136,40), "");
    lbl.setAlignment(mono::ui::TextLabelView::ALIGN_CENTER);
    lbl.show();

    btn = mono::ui::ButtonView(mono::geo::Rect(20, 100, 136, 40), "Click me");
    btn.setClickCallback(&buttonClick);
    btn.show();
}

void loop() { }
```

### Stop watch

Our last example is a fully functioning stop watch, that counts 10th of milliseconds. We add two buttons to toggle the timer and reset the count value.

Before we get to the example code, let us examine the extra functions in this app. Besides to two familiar `setup` and `loop` functions, we have 3 extra functions:

* `reset`: Resets the counter to *00:00.00*.
* `toggle`: Starts or stops the counter (toggles a *Timer* object)
* `increment`: Increments the counter value by 10 ms.

One thing to note is we store the timestamp in two distinct objects. An `unsigned integer` stores the millisecond component of the counter. Every time it reaches 1000 ms we increment the other timestamp (a *DateTime* object), that stores the minutes and seconds.

```cpp
#include <mono.h>

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

void loop() { }
```

Again, we use the `setup` function to initialize all our components: `TextLabelView`, `ButtonView` and `Timer`.

This was three quick examples of Mono apps coded in Arduino IDE. We hope you found some inspiration and want to try out our Arduino SDK yourself. As said earlier, a good place to start is at [developer.openmono.com](http://developer.openmono.com/en/latest/getting-started/arduino-hackers.html).

As always, the best regards from  
*Andreas, Jens Peter, Kristoffer & Lasse*