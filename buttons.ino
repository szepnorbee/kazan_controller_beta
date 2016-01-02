void readButtons() {

  int valB = debouncerB.read();
  int valF = debouncerF.read();
  int valL = debouncerL.read();
  int valJ = debouncerJ.read();

  if (valB == LOW) {
    dataChanged = true;
    menuTimer = 0;
    lcd.clear();
    if (page < 14) page++;
  }

  if (valJ == LOW) {
    dataChanged = true;
    menuTimer = 0;
    lcd.clear();
    if (page > 1) page -= 1;
  }


  if (valF == LOW) {
    menuTimer = 0;
    dataChanged = true;
    switch (page) {
      case 2:
        motorStart++;
        lcdUpd();
        break;
      case 3:
        motorStop++;
        lcdUpd();
        break;
      case 4:
        motorStart2++;
        lcdUpd();
        break;
      case 5:
        motorStop2++;
        lcdUpd();
        break;
      case 6:
        motorTest++;
        lcdUpd();
        break;
      case 7:
        if (bLight == true) {
          bLight = false;
        } else {
          bLight = true;
        }
        lcdUpd();
        break;
      case 8:
        fanDelay++;
        lcdUpd();
        break;
      case 9:
        if (setTemp < 95) setTemp += 5;  //
        lcdUpd();
        break;
      case 10:
        if (histeresis < 5) histeresis += 1;
        lcdUpd();
        break;
      case 11:
        if (thermostat == true) {
          thermostat = false;
        } else {
          thermostat = true;
        }
        lcdUpd();
        break;
      case 12:
        ////////////EEPROM mentés///////////
        memWrite();
        ////////////////////////////////////
        lcdUpd();
        break;
      case 13:
        if (fanState == HIGH) {
          fanState = LOW;
        } else {
          fanState = HIGH;
        }
        digitalWrite(fanPin, fanState);
        lcdUpd();
        break;
    }
  }

  if (valL == LOW) {
    menuTimer = 0;
    dataChanged = true;
    switch (page) {
      case 2:
        motorStart--;
        lcdUpd();
        break;
      case 3:
        motorStop--;
        lcdUpd();
        break;
      case 4:
        motorStart2--;
        lcdUpd();
        break;
      case 5:
        motorStop2--;
        lcdUpd();
        break;
      case 6:
        motorTest--;
        lcdUpd();
        break;
      case 7:
        if (bLight == true) {
          bLight = false;
        } else {
          bLight = true;
        }
        lcdUpd();
        break;
      case 8:
        fanDelay--;
        lcdUpd();
        break;
      case 9:
        if (setTemp > 40) setTemp -= 5;
        lcdUpd();
        break;
      case 10:
        if (histeresis > 0) histeresis -= 1;
        lcdUpd();
        break;
      case 11:
        if (thermostat == true) {
          thermostat = false;
        } else {
          thermostat = true;
        }
        lcdUpd();
        break;
      case 12:
        ////////////EEPROM mentés///////////
        memWrite();
        ////////////////////////////////////
        lcdUpd();
        break;
      case 13:
        if (motorState == HIGH) {
          motorState = LOW;
        } else {
          motorState = HIGH;
        }
        digitalWrite(motorPin, motorState);
        lcdUpd();
        break;
    }
  }
} //EOF

//////////////////////////ÜZEMMÓD VÁLTÁS - BEMENETI JEL//////////////////////////
void readInput() {
  int valH = debouncerH.read();

  if (thermostat == false) {         // Bemenet vezérelt üzemmód

    if (valH == LOW) {                   // Ha alacsony akkor fűtűnk
      reqHeat = true;
      digitalWrite(fanPin, LOW);         // Ventillátor bekapcsolása
    } else {
      reqHeat = false;
      digitalWrite(fanPin, HIGH);        // Ventillátor kikapcsolása
    }

  } else if (thermostat == true) {   // Thermostat vezérelt üzemmód
    //valami
    if (tempC < setTemp - histeresis && valH == LOW) {
      reqHeat = true;
      digitalWrite(fanPin, LOW);         // Ventillátor bekapcsolása
    }
    if (tempC >= setTemp || valH == HIGH) {
      reqHeat = false;
      digitalWrite(fanPin, HIGH);         // Ventillátor kikapcsolása
    }
  }
}

