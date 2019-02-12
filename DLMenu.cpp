#include "DLMenu.h"

DLMenu::DLMenu(LiquidCrystal *disp, Button *bl, Button *br, Button *bu, Button *bd, DLMenuItem **mi)
{
    lcd = disp;
    bLeft = bl;
    bRight = br;
    bUp = bu;
    bDown = bd;

    items = mi;

    // find out the number of menu items; the last one is NULL
    len = 0;
    while(items[len] != NULL){
        len += 1;
    }

    tTouched = millis();
    index = -1; // the menu is currently not shown
}

bool DLMenu::quit(void){
    index = -1;
    lcd->noCursor();

    return false;
}

bool DLMenu::check(void){
    // returns false when menu has timed out or the user has navigated back to main screen.

    // if no buttons were pressed, return false if the menu has timed out.
    // if a button was pressed, check if the menu is already shown:
    //   - if not shown, show the first (or the last) item
    //   - if shown, send a next() (od previous()) command to the current item:
    //      - if current item returns true, return true and don't change anything
    //      - if current item returns false, go to the next (previous) item and return true;

    // see which buttons were pressed;
    static bool bl, br, bu, bd;
    bl = bLeft->uniquePress();
    br = bRight->uniquePress();
    bu = bUp->uniquePress();
    bd = bDown->uniquePress();

    // if none of the buttons has been pressed, check if the menu has timed out
    if(!(bl || br || bu || bd)){
        if(index == -1)
            return false; // there's nothing going on anyway
        else if(millis() - tTouched > M_TIMEOUT)
            return quit(); // timeout! quit
        else
            return true;
    }
    else{
        // a button has been pressed, don't quit the menu
        tTouched = millis(); // reset the timeout

        if(index == -1){
            // the menu is currently not shown, show the first (or last) item
            if(bl){
                index = len - 1;
                items[index]->show(true); // start from the end
            }
            else if(br){
                index = 0;
                items[index]->show(false); // start from the first section of this item
            }
        }
        else{
            // the menu is shown already, send a next/previous to current item
            if(bl){
                // next()/previous() return false if next/prev item should be displayed
                if (!items[index]->previous())
                {
                    items[index]->hide();
                    index--;

                    if (index == -1)
                        return quit();
                    else
                        items[index]->show(true);
                }
            }
            else if(br){
                if(!items[index]->next()){
                    items[index]->hide();
                    index++;

                    if(index == len) return quit();
                    else items[index]->show(false);
                }
            }
            else if(bu) items[index]->increase();
            else if(bd) items[index]->decrease();
        }

        return true;
    }
}

void DLMenuItem::placeCursor(void){
    lcd->setCursor(s, 1);
    lcd->cursor();
}

bool DLMenuItem::next(void){
    s += 1;
    if (s >= sections) return false;

    placeCursor();
    return true;
};

bool DLMenuItem::previous(void){
    s -= 1;
    if (s < 0)  return false;

    placeCursor();
    return true;
};