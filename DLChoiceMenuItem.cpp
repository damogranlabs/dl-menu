#include "DLMenu.h"

///
/// ChoiceMenuItem
///
DLChoiceMenuItem::DLChoiceMenuItem(LiquidCrystal *lcd, const char *label, int address, const char *const *choiceTable, int nChoices, int dval) : DLMenuItem(lcd, label, address)
{
    choices = choiceTable;
    len = nChoices;
    sections = 1;
    s = 0;

    // load from EEPROM
    if ((long)EEPROM[address] == EEPROM_NULL)
        selected = dval;
    else
        selected = EEPROM[address];

    if (selected > len - 1)
        selected = 0; // the default choice
}

void DLChoiceMenuItem::show(bool endFirst = false)
{
    // endFirst is ignored here because this item has one section only
    lcd->clear();

    // print label
    progmem_to_lcd(lcd, 0, label);

    // print current setting
    //lcd->setCursor(0, 1);
    //lcd->print(choices[selected]);
    progmem_table_to_lcd(lcd, 1, choices, selected);

    // show cursor (only symbolic)
    lcd->setCursor(0, 1);
    lcd->cursor();
}

void DLChoiceMenuItem::hide(void)
{
    if (EEPROM[address] != selected)
        EEPROM[address] = selected;

    lcd->clear();
}

void DLChoiceMenuItem::add(int i)
{
    selected = constrain(selected + i, 0, len - 1);

    show();
}

void DLChoiceMenuItem::increase(void) { add(1); }
void DLChoiceMenuItem::decrease(void) { add(-1); }