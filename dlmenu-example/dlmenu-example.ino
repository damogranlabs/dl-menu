/*
 * PREREQUISITES
 */
// already in standard Arduino package
#include <LiquidCrystal.h>
// http://playground.arduino.cc/Code/Button
#include <Button.h>
// https://github.com/damogranlabs/dl-menu
#include <DLMenu.h>

/*
 * HARDWARE and pins
 */
// 4 push buttons
#define PB_LEFT   11
#define PB_RIGHT  12
#define PB_UP     10
#define PB_DOWN   13

// LCD connections
#define PD_RS     A0
#define PD_E      A1
#define PD_DB4    A2
#define PD_DB5    A3
#define PD_DB6    A4
#define PD_DB7    A5
#define PD_LIGHT  4

/*
 * DLMenu settings
 */
#define DLM_FLOAT_DIGITS  5
#define DLM_INT_DIGITS    3

// EEPROM addresses and default values for menu items
// integer value
#define DLM_ADDR_TESTINT        0
#define DLM_DEFAULT_TESTINT     42

// float value;
#define DLM_ADDR_TESTFLOAT      4
#define DLM_DEFAULT_TESTFLOAT   1.01325e+5

// choice menu;
#define DLM_ADDR_TESTCHOICE     8
#define DLM_DEFAULT_TESTCHOICE  1 // the index of the default choice in choices array (0-based)
// these values can be stored in flash memory instead of RAM; see PROGMEM keyword in Arduino documentation
const char *testChoices[] = {"Male", "Female", "Yes, please", NULL}; // ACHTUNG, the last entry must be NULL

/* 
 * INITIALIZATION 
 */
LiquidCrystal lcd(PD_RS, PD_E, PD_DB4, PD_DB5, PD_DB6, PD_DB7);

Button bLeft(PB_LEFT, PULLUP);
Button bRight(PB_RIGHT, PULLUP);
Button bUp(PB_UP, PULLUP);
Button bDown(PB_DOWN, PULLUP);

// menu items (it would be wise to store a lot of texts in PROGMEM)
DLIntMenuItem *miTestInt = new DLIntMenuItem(
  &lcd,                 // your LiquidCrystal object
  "The Number",         // the title of this setting (first line)
  DLM_ADDR_TESTINT,     // EEPROM address of the setting
  DLM_INT_DIGITS,       // menu-item-specific setting (number of digits in this case)
  DLM_DEFAULT_TESTINT); // item-specific default value
  
DLFloatMenuItem *miTestFloat = new DLFloatMenuItem(
  &lcd,
  "Pressure [Pa]",
  DLM_ADDR_TESTFLOAT,
  DLM_FLOAT_DIGITS, 
  DLM_DEFAULT_TESTFLOAT);

DLChoiceMenuItem *miTestChoice = new DLChoiceMenuItem(
  &lcd,
  "Sex", DLM_ADDR_TESTCHOICE,
  testChoices,
  DLM_DEFAULT_TESTCHOICE);

DLMenuItem *menuItems[] = {
  miTestInt, miTestFloat, miTestChoice, NULL // ACHTUNG, the last entry must be NULL
};

// create the menu
DLMenu menu(&lcd, &bLeft, &bRight, &bUp, &bDown, menuItems);

/*
 * THE STUFF
 */
void setup() {
  Serial.begin (9600);
  lcd.begin(16, 2);

  pinMode(PD_LIGHT, OUTPUT);
  digitalWrite(PD_LIGHT, HIGH);
}

void loop(){
  if(menu.check()){
    // showing menu, do nothing
  }
  else{
    // the menu is not activated; do whatever your gizmo does in 'normal' mode
    lcd.setCursor(0, 0);
    lcd.print("On for ");
    lcd.print(millis()/1000);
    lcd.print(" seconds");

    // be careful when using delays or blocking functions that take long to complete;
    // the menu.check() won't be able to check for button presses in the meanwhile;
    // short button presses will not be detected and if functions take too long,
    // buttons will be disabled altogether;
    delay(20);
  }  
}

