#include <mono.h>

/*
 * In this example we declare a `TextLabelView` and a `ButtonView`
 * along with a function (`buttonClick`), to handle the button click event.
 *
 * The `setup` function initializes both the text-label and button, sets the
 * label's text alignment and initial empty string value. The function `buttonClick`
 * is set as the *click callback handler* on the button.
 */

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

void loop() {

}
