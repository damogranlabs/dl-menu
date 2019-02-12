/*
 * PREREQUISITES
 */
// already in standard Arduino package
#include <LiquidCrystal.h>
// http://playground.arduino.cc/Code/Button
#include <Button.h>
// https://github.com/damogranlabs/dl-menu
#include <DLMenu.h>


// clears the eeprom for testing and demonstration purposes;
// remove this for real-life uses
#include <EEPROM.h>

/*
 * HARDWARE and pins
 */
// 4 push buttons
#define PB_LEFT A0
#define PB_UP A1
#define PB_DOWN A2
#define PB_RIGHT A3

// LCD connections: uses the default pinout from
// LiquidCrystal "Hello World" example
#define PD_RS 12
#define PD_E 11
#define PD_DB4 5
#define PD_DB5 4
#define PD_DB6 3
#define PD_DB7 2

/*
 * dl-menu initialization
 */
// hardware: display
LiquidCrystal lcd(PD_RS, PD_E, PD_DB4, PD_DB5, PD_DB6, PD_DB7);

Button bLeft(PB_LEFT, PULLDOWN);
Button bRight(PB_RIGHT, PULLDOWN);
Button bUp(PB_UP, PULLDOWN);
Button bDown(PB_DOWN, PULLDOWN);

// menu items:
// integer value
#define DLM_ADDR_TESTINT 0                           // the address of the value
#define DLM_INT_DIGITS 3                             // number of digits
const char miNumberLabel[] PROGMEM = {"The number"}; // the title saved in PROGMEM

DLIntMenuItem *miTestInt = new DLIntMenuItem( // the object
    &lcd,                                     // your LiquidCrystal object
    miNumberLabel,                            // the label of this setting (first line)
    DLM_ADDR_TESTINT,                         // EEPROM address of the setting
    DLM_INT_DIGITS                            // menu-item-specific setting (number of digits in this case)
);

// floating point value
#define DLM_FLOAT_DIGITS 5                             // number of digits
#define DLM_ADDR_TESTFLOAT 4                           // EEPROM address
const char miFloatLabel[] PROGMEM = {"Pressure [Pa]"}; // the label saved in PROGMEM

DLFloatMenuItem *miTestFloat = new DLFloatMenuItem(
    &lcd,
    miFloatLabel,
    DLM_ADDR_TESTFLOAT,
    DLM_FLOAT_DIGITS
);

// choice menu item:
#define DLM_ADDR_TESTCHOICE 8    // eeprom address of the index
#define DLM_DEFAULT_TESTCHOICE 1 // the index of the default choice in choices array (0-based)
const char miChoiceLabel[] PROGMEM = {"Sex"};
// these values must be stored in flash memory instead of RAM; see PROGMEM keyword in Arduino documentation
const char testChoice_0[] PROGMEM = "Male";
const char testChoice_1[] PROGMEM = "Female";
const char testChoice_2[] PROGMEM = "Yes, please";
const char *const testChoices[] PROGMEM = {testChoice_0, testChoice_1, testChoice_2};

DLChoiceMenuItem *miTestChoice = new DLChoiceMenuItem(
    &lcd,
    miChoiceLabel,
    DLM_ADDR_TESTCHOICE,
    testChoices, sizeof(testChoices) / sizeof(char *) // number of choices
);

// text menu item:
#define DLM_ADDR_TESTTEXT 9 // eeprom address of the text item
#define DLM_TEXT_LENGTH 8 // number of characters
const char miTextLabel[] PROGMEM  = {"Your name"};
// list of allowed characters: the user chooses between those;
// the default string is filled with the first character of this list
const char miTextAllowedChars[] PROGMEM = {"_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;+-"};

DLTextMenuItem *miTestText = new DLTextMenuItem(
    &lcd,
    miTextLabel,
    DLM_ADDR_TESTTEXT,
    miTextAllowedChars,
    DLM_TEXT_LENGTH
);

// initialize menu with all the items
DLMenuItem *menuItems[] = {
    miTestInt, miTestFloat, miTestChoice, miTestText, NULL // ACHTUNG, the last entry must be NULL
};

// create the menu
DLMenu menu(&lcd, &bLeft, &bRight, &bUp, &bDown, menuItems);

/*
 * THE STUFF
 */
void setup(){
    Serial.begin(9600);
    lcd.begin(16, 2);

    /* // setting default values:
    // clear the eeprom
    for (int i = 0 ; i < EEPROM.length(); i++) EEPROM.write(i, 0);

    // use the setValue() methods of each menu item to initialize/reset/set defaults
    miTestInt->setValue(231);
    miTestFloat->setValue(1.233);
    miTestChoice->setValue(2);
    miTestText->setValue((char *)"Slartibartfast"); */ 
}

void loop(){
    if (menu.check()){
        // showing menu, do nothing
    }
    else{
        // the menu is not activated; do whatever your gizmo does in 'normal' mode
        lcd.setCursor(0, 0);
        lcd.print("On for ");
        lcd.print(millis() / 1000);
        lcd.print(" s");

        lcd.setCursor(0, 1);
        lcd.print("Text: ");
        lcd.print(miTestText->getValue());

        // be careful when using delays or blocking functions that take long to complete;
        // the menu.check() won't be able to check for button presses in the meanwhile;
        // short button presses will not be detected and if functions take too long,
        // buttons will be disabled altogether;
        delay(20);
    }
}
