///////////////EEPROM olvasás////////////
void memRead() {
  motorStart = EEPROM.read(0);
  motorStop = EEPROM.read(1);
  motorStart2 = EEPROM.read(2);
  motorStop2 = EEPROM.read(3);
  motorTest = EEPROM.read(4);
  fanDelay = EEPROM.read(5);
  setTemp = EEPROM.read(6);
  histeresis = EEPROM.read(7);
  thermostat = EEPROM.read(8);
}

///////////////EEPROM írás////////////////
void memWrite() {
  EEPROM.write(0, motorStart);
  EEPROM.write(1, motorStop);
  EEPROM.write(2, motorStart2);
  EEPROM.write(3, motorStop2);
  EEPROM.write(4, motorTest);
  EEPROM.write(5, fanDelay);
  EEPROM.write(6, setTemp);
  EEPROM.write(7, histeresis);
  EEPROM.write(8, thermostat);
  lcd.setCursor(14, 0);
  lcd.print("OK");
  delay(100);
  lcd.clear();
  page = 1;
}
