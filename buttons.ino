void readButtons() {

  if (digitalRead(bal) == HIGH) {
    delay(arrowDebounce);
    if (digitalRead(bal) == HIGH) {
      dataChanged = true;
      menuTimer = 0;
      if (page < 12) page++;
    }
  }

  if (digitalRead(jobb) == HIGH) {
    delay(arrowDebounce);
    if (digitalRead(jobb) == HIGH) {
      dataChanged = true;
      menuTimer = 0;
      if (page > 1) page -= 1;
    }
  }

  if (digitalRead(fel) == HIGH) {
    menuTimer = 0;
    dataChanged = true;
    delay(buttonDebounce);
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
        if (setTemp < 95) setTemp = setTemp +5;
        break;
      case 10:
        if (histeresis < 5) histeresis = histeresis + .25;
        break;
      case 11:
        ////////////EEPROM mentés///////////
        memWrite();
        ////////////////////////////////////
        lcd.setCursor(0, 1);
        lcd.print("    + vagy -  OK");
        delay(500);
        lcdUpd();
        break;
      case 12:
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

  if (digitalRead(le) == HIGH) {
    menuTimer = 0;
    dataChanged = true;
    delay(buttonDebounce);
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
        if (setTemp > 40) setTemp = setTemp -5;
        break;
      case 10:
        if (histeresis > 0) histeresis = histeresis - .25;  
        break;
      case 11:
        ////////////EEPROM mentés///////////
        memWrite();
        ////////////////////////////////////
        lcd.setCursor(0, 1);
        lcd.print("    + vagy -  OK");
        delay(500);
        lcdUpd();
        break;
      case 12:
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
    if (digitalRead(heatPin) == LOW) {       // Ha alacsony akkor fűtűnk
    delay(400);
    if (digitalRead(heatPin) == LOW) {
      reqHeat = true;
      digitalWrite(fanPin, LOW);         // Ventillátor bekapcsolása
    } else {
      reqHeat = false;
      digitalWrite(fanPin, HIGH);        // Ventillátor kikapcsolása
    }
  }
}

