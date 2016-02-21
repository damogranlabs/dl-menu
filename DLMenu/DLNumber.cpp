#include "DLNumber.h"

DLNumber::DLNumber(int a){
  address = a;

  load();
}

bool DLNumber::load(void){
  for(int i = 0; i < sizeof(data.b); i++){
    data.b[i] = EEPROM[address + i];
  }
  
  if(data.l == 0xFFFFFFFF){
    data.f = 0;
    save();
    return false; // a default value was used
  }
  else{
    return true; // loaded successfully
  }
}

void DLNumber::save(void){
  int i;
  
  for(i = 0; i < sizeof(data.b); i++){
    EEPROM[address + i] = data.b[i];
  }
}

float DLNumber::getFloatValue(void){
  return data.f;
}

unsigned long DLNumber::getUintValue(void){
	return data.l;
}

void DLNumber::setValue(unsigned long l){
	data.l = l;
	save();
}

void DLNumber::setValue(float f){
  data.f = f;
  save();
}