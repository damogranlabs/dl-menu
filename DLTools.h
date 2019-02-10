#ifndef _DLTOOLS_H
#define _DLTOOLS_H

#include <LiquidCrystal.h>

void progmem_to_lcd(LiquidCrystal *lcd, int line, const char *text);
void progmem_table_to_lcd(LiquidCrystal *lcd, int line, const char * const *table, int iEntry);

#endif