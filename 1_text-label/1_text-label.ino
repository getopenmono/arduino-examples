#include <mono.h>

/*
 * A simple sketch that shows a static text on the screen. The code below adds
 * a `TextLabelView` object and initializes it inside the `setup` function.
 * We also give the text a neat color to make it appear more *Arduino like*.
 */

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

void loop() {

}
