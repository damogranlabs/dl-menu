#include "DLMenu.h"

///
/// ChoiceMenuItem
///
DLChoiceMenuItem::DLChoiceMenuItem(LiquidCrystal *lcd, char *label,	int address, const char **c) : DLMenuItem(lcd, label, address){
	
  choices = c;
  
  // determine length of choices list; the last element is ""
  for(int i = 0; i < 256; i++){ // there can be no more than 255 choices (stored as byte in EEPROM)
    if(choices[i] == NULL){
      len = i;
      break;
    }
  }

  sections = 1;
  s = 0;

  // load from EEPROM
  selected = EEPROM[address];
  //if(selected > len - 1) selected = 0; // the default choice
}

void DLChoiceMenuItem::show(bool endFirst = false){
  // endFirst is ignored here because this item has one section only
  lcd->clear();

  // print label
  lcd->setCursor(0, 0);
  lcd->print(label);

  // print current setting
  lcd->setCursor(0, 1);
  lcd->print(choices[selected]);

  // show cursor (only symbolic)
  lcd->setCursor(0, 1);
  lcd->cursor();
}

void DLChoiceMenuItem::hide(void){
  if(EEPROM[address] != selected) EEPROM[address] = selected;
  
  lcd->clear();
}

void DLChoiceMenuItem::add(int i){
  selected = constrain(selected + i, 0, len - 1);

  show();
}

void DLChoiceMenuItem::increase(void){ add(1); }
void DLChoiceMenuItem::decrease(void){ add(-1); }