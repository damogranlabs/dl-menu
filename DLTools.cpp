#include <LiquidCrystal.h>
#include "DLMenu.h"

void progmem_to_lcd(LiquidCrystal *lcd, int line, const char *text){
    // reads a string from PROGMEM and outputs it to LiquidCrystal
    char c;
    int i;

    for(i = 0; i < strlen_P(text); i++){
        c = pgm_read_byte_near(text + i);
        lcd->setCursor(i, line);
        lcd->print(c);
    }
}

void progmem_table_to_lcd(LiquidCrystal *lcd, int line, const char * const *table, int iEntry){
    // reads an entry from a string table stored in PROGMEM
    // https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
    #define BUFSIZE 32
    char buffer[BUFSIZE];
    memset(buffer, 0, BUFSIZE);

    strncpy_P(buffer, (char*)pgm_read_word(&(table[iEntry])), BUFSIZE-1);
    lcd->setCursor(0, line);
    lcd->print(buffer);
}