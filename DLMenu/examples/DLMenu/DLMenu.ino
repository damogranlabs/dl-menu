/*
 * DLMenu menu framework;
 */
// the required hardware: liquid crystal
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// buttons: left, right, up down
#include <Button.h>
Button bLeft(A0, PULLDOWN);
Button bRight(A1, PULLDOWN);
Button bUp(A2, PULLDOWN);
Button bDown(A3, PULLDOWN);

// the menu:
#include <DLMenu.h>

// first, menu items ("sections"):
// each needs a reference to LCD display, a label and an EEPROM address for storing data;
// and a few specific settings

// Integer menu item:
DLIntMenuItem *miCount = new DLIntMenuItem(&lcd, // address of display object
  "Sheep count:", // label (max. 15 characters)
  0, // EEPROM address (will use 4 bytes)
  3); // number of digits that will be displayed

// Float menu item
DLFloatMenuItem *miWeight = new DLFloatMenuItem(&lcd, // address of display object
  "Sheep weight", // label
  4, // EEPROM address (will use 4 bytes)
  4); // number of significant digits

// Choice menu item
// First, define choices; it's a list of strings - THE LAST MEMBER MUST BE NULL!
const char *sheepColor[] = {"White", "Black", "Green", NULL}; 

DLChoiceMenuItem *miColor = new DLChoiceMenuItem(&lcd, // address of lcd display
  "Sheep color:", // label
  8, // EEPROM address (will only use 1 byte)
  sheepColor);

// Init the menu:
DLMenuItem *menuItems[] = {
  miCount, miWeight, miColor, NULL // THE LAST MEMBER MUST BE NULL
};

DLMenu menu(&lcd, &bLeft, &bRight, &bUp, &bDown, menuItems);

void setup() {
  // set up the LCD
  lcd.begin(16, 2);
}

void loop() {
  // check what's going on with the menu;
  // if menu.check() returns true, don't touch the display
  // because the menu is doing its job;
  // if menu.check() returns false, you can write whatever to display
  if(menu.check() == false){
    // the user quit the menu, write our own data to the display;
    lcd.setCursor(0, 0);
    
    // write the data that has been set in the menu
    lcd.print(miCount->getValue()); // returns unsigned long
    lcd.print(" ");
    lcd.print(sheepColor[miColor->getValue()]); // returns index of selected
    lcd.print(" sheep");
    
    lcd.setCursor(0, 1);
    lcd.print(miWeight->getValue());
    lcd.print(" kg each");
  }
  
  // a slight delay instead of complicated debouncing. or whatever
  delay(20);
}
