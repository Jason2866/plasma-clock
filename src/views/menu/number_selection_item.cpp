#include <views/menu/number_selection_item.h>
#include <graphics/font.h>
#include <input/keys.h>

MenuNumberSelectorView::MenuNumberSelectorView(const char * title, int min_, int max_, int step_, int initialValue, std::function<void(bool, Renderable*)> onActivated_, std::function<void(int)> onChange_):
    label(new StringScroll(find_font(FONT_STYLE_UI_TEXT), title)),
    value(new StringScroll(find_font(FONT_STYLE_UI_TEXT), std::to_string(initialValue).c_str())),
    currentValue(initialValue),
    min(min_),
    max(max_),
    increment(step_),
    onChange(onChange_),
    onActivated(onActivated_),
    isActive(false),
    currentValueStr {0} {
        value->set_y_position(label->font->height);
        value->align_to_right = true;
        value->start_at_visible = true;
        value->holdoff = 100;
        label->start_at_visible = true;
        label->holdoff = 100;
        add_composable(label);
        add_composable(value);
        itoa(currentValue, currentValueStr, 10);
        value->set_string(currentValueStr);
    }

MenuNumberSelectorView::~MenuNumberSelectorView() {
    delete label;
    delete value;
}

void MenuNumberSelectorView::step() {
    Composite::step();

    if(isActive) {
        if(hid_test_key_state_repetition(KEY_UP) == KEYSTATE_HIT) {
            currentValue += increment;
            if(currentValue > max) currentValue = min;
            onChange(currentValue);
        } else if(hid_test_key_state_repetition(KEY_DOWN) == KEYSTATE_HIT) {
            currentValue -= increment;
            if(currentValue < min) currentValue = max;
            onChange(currentValue);
        } else if(hid_test_key_state(KEY_LEFT)) {
            onActivated(false, this);
            isActive = false;
        }
    } else {
        if(hid_test_key_state(KEY_RIGHT) == KEYSTATE_HIT) {
            onActivated(true, this);
            isActive = true;
        }
    }

    itoa(currentValue, currentValueStr, 10);
    value->set_string(currentValueStr);
}

void MenuNumberSelectorView::render(FantaManipulator *fb) {
    Composite::render(fb);
    if(isActive) {
        fb->put_glyph(value->font, 0x2195 /* '↕' UTF16 */, 0, 8);
    }
}
