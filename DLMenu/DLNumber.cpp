#include "DLNumber.h"

DLNumber::DLNumber(int a){
  address = a;

  load();
}

bool DLNumber::load(void){
  for(int i = 0; i < SIZE; i++){
    data.b[i] = EEPROM[address + i];
  }
  
  if(data.l == 0xFFFFFFFF){ // there's nothing in EEPROM
    data.f = 0;
    return false; // a default value was used
  }
  else{
    return true; // loaded successfully
  }
}

void DLNumber::save(void){
  int i;
  
  for(i = 0; i < SIZE; i++){
    EEPROM[address + i] = data.b[i];
  }
}

float DLNumber::getFloatValue(void){
  return data.f;
}

unsigned long DLNumber::getUintValue(void){
	return data.l;
}

void DLNumber::setValue(unsigned long val){
	data.l = val;
	save();
}

void DLNumber::setValue(float val){
  data.f = val;
  save();
}