# dl-menu
A simple one-level settings menu framework for Arduino 16x2 LiquidCrystal display.

https://damogranlabs.com/2018/10/arduino-settings-menu/  
https://www.youtube.com/watch?v=qS__iG2UIRg

## Quick description
If your program contains parameters that change over time
(like measurement reference or calibration data, i.e. desired temperature),
those parameters are most easily changed using an LCD and a menu.

This is a set of a handful of lcd menu sections for three data types, integer,
float and arbitrary text 'choice'. Values are stored in EEPROM and read by the Arduino 
program where/when needed.

## Usage
It's very simple as long as you stick to the recipe:
### 1. Initialize hardware:
An lcd display: see the default LiquidCrystal arduino library
```
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
```
4 buttons, up, down, left and right; use the [Button HAL library](http://playground.arduino.cc/Code/Button)
```
#include <Button.h>
Button bLeft(A0, PULLDOWN);
Button bRight(A1, PULLDOWN);
Button bUp(A2, PULLDOWN);
Button bDown(A3, PULLDOWN);
```
### 2. Initialize your menu sections (one section, one variable)
See the included example for
```
DLIntMenuItem *miCount = new DLIntMenuItem(
    &lcd, // address of display object
    "Sheep count:", // label (max. 15 characters) (see the example for PROGMEM-saved texts)
    0, // EEPROM address (will use 4 bytes)
    3); // number of digits that will be displayed
```
### 4. Initialize the menu
```
DLMenuItem *menuItems[] = {
  miCount, miWeight, miColor, NULL
};

DLMenu menu(&lcd, &bLeft, &bRight, &bUp, &bDown, menuItems);
```

### 5. Check what's going on with user input in `loop()`
```
if(menu.check() == false){ // the menu is not active, lcd can be written to
  // write the data that has been set using the menu
  lcd.setCursor(0, 0);
  lcd.print(miCount->getValue());
}
```
## Examples and documentation
See the attached example sketch; it is verbosely documented so you should get by fine. The code itself is well-documented as well in case you'll need tweaks and hacks.

## More?
More different sections/data types can be added (and will be in case we'll need something in the future).
The whole little framework is written using object-oriented paradigm. It's a little heavy on resources, especially
Flash memory, but from our experience the 32kB of Atmega328 is not very easy to fill completely.
All labels and choice texts are saved to PROGMEM to avoid eating up too much RAM.
 
This code uses MIT license so you're free to do whatever with it and actually very welcome to do so. Feedback is also appreciated.
