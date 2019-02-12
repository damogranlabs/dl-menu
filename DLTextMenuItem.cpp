
#include "DLMenu.h"

///
/// ChoiceMenuItem
///

DLTextMenuItem::DLTextMenuItem(LiquidCrystal *lcd, const char *label, int address, const char *allowedCharacters, int length) : DLMenuItem(lcd, label, address){
    sections = length; // number of modifiable sections is equal to number of characters
    s = 0; // start at the first character

    // only use these characters
    allowedChars = allowedCharacters;
    nAllowedChars = strlen_P(allowedChars) - 1; // the null terminator is not allowed

    // the stored/new text
    text = new char[sections+1];
    
    // load text from eeprom and replace all non-allowed characters with defaults (first)
    for(int i = 0; i < sections; i++){
        text[i] = (char)EEPROM[address + i];
    }
    text[sections] = 0;
    normalize();
}

void DLTextMenuItem::show(bool endFirst = false){
    // print the label
    lcd->clear();
    progmem_to_lcd(lcd, 0, label);

    // print the text; read it from EEPROM
    lcd->setCursor(0, 1);
    lcd->print(text);

    // set cursor position
    if (endFirst) s = sections - 1;
    else s = 0;

    placeCursor();
}

void DLTextMenuItem::normalize(void){
    // replace all non-allowed characters with the default (first)
    for(int i = 0; i < sections; i++){
        text[i] = (char)pgm_read_byte_near(allowedChars + findIndex(text[i]));
    }
}

void DLTextMenuItem::save(){
    for(int i = 0; i < sections; i++){
        if(EEPROM[address+i] != text[i]){
            EEPROM[address+i] = text[i];
        }
    }
}

void DLTextMenuItem::hide(void){
    // write characters that are different than those in eeprom
    save();

    lcd->clear();
    lcd->noCursor();
}

int DLTextMenuItem::findIndex(char c){
    // returns the index of char c in allowedChars; if not found, return 
    // the default (first) character
    int i;
    for(i = nAllowedChars; i > 0; --i){
        if(c == (char)pgm_read_byte_near(allowedChars + i)) break;
    }

    return i;
}

void DLTextMenuItem::add(int direction){
    // find the current character
    int i = findIndex(text[s]);

    i += direction;
    if(i >= nAllowedChars) i = 0;
    if(i < 0) i = nAllowedChars-1;

    text[s] = (char)pgm_read_byte_near(allowedChars + i);

    lcd->setCursor(0, 1);
    lcd->print(text);
    placeCursor();
}

void DLTextMenuItem::increase(void) { add(1); }
void DLTextMenuItem::decrease(void) { add(-1); }

void DLTextMenuItem::setValue(char *value){
    strncpy(text, value, sections);
    normalize();
}
