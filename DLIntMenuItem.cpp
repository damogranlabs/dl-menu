#include "DLMenu.h"

///
/// FloatMenuItem
///
DLIntMenuItem::DLIntMenuItem(LiquidCrystal *lcd, const char *label, int address, int d, int dval) : DLMenuItem(lcd, label, address)
{
    // prepare stuff
    n = new DLNumber(address);
    if (n->getUintValue() == EEPROM_NULL)
        n->setValue((unsigned long)dval);

    digits = d;
    sections = digits;
    numerals = new char[digits];
    explode();
}

void DLIntMenuItem::explode(void)
{
    unsigned long r = n->getUintValue();
    int i, m;

    // if stored number is bigger than number of digits, drop everything
    m = 1;
    for (i = 0; i < digits; i++)
    {
        m *= 10;
    }

    if (i >= m)
    {
        n->setValue((unsigned long)0);
        r = 0;
    }

    for (i = 0; i < digits; i++)
    {
        numerals[digits - i - 1] = r % 10;
        r = r / 10;
    }
}

void DLIntMenuItem::printNumber(void)
{
    lcd->setCursor(0, 1);

    for (int i = 0; i < digits; i++)
    {
        lcd->print((int)numerals[i]);
    }
}

void DLIntMenuItem::placeCursor(void)
{
    lcd->setCursor(s, 1);
    lcd->cursor();
}

void DLIntMenuItem::add(int i)
{
    numerals[s] = constrain(numerals[s] + i, 0, 9);

    printNumber();
    placeCursor();
}

void DLIntMenuItem::increase(void) { add(1); };
void DLIntMenuItem::decrease(void) { add(-1); };

void DLIntMenuItem::show(bool endFirst)
{
    // print the label
    lcd->clear();
    progmem_to_lcd(lcd, 0, label);

    // set cursor position
    if (endFirst)
        s = sections - 1;
    else
        s = 0;

    printNumber();
    placeCursor();
}

void DLIntMenuItem::hide(void)
{
    // assemble an integer from numerals and save
    unsigned long v = 0;
    unsigned long m = 1; // 'magnitude'

    for (int i = 0; i < digits; i++)
    {
        v += numerals[digits - i - 1] * m;
        m *= 10;
    }

    if (n->getUintValue() != v)
        n->setValue(v);

    lcd->clear();
}

bool DLIntMenuItem::next(void)
{
    s += 1;
    if (s >= sections)
        return false;

    placeCursor();
    return true;
};

bool DLIntMenuItem::previous(void)
{
    s -= 1;
    if (s < 0)
        return false;

    placeCursor();
    return true;
};
