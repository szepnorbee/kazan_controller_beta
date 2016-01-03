void readButtons() {

  if (digitalRead(bal) == HIGH) {
    delay(arrowDebounce);
    if (digitalRead(bal) == HIGH) {
      menuTimer = 0;
      page++;
      //lcd.clear();
      if (page > 16) {
        page = 1;
        lcd.clear();
      }
    }
  }

  if (digitalRead(jobb) == HIGH) {
    delay(arrowDebounce);
    if (digitalRead(jobb) == HIGH) {
      menuTimer = 0;
      page--;
      //lcd.clear();
      if (page < 1) {
        page = 16;
        lcd.clear();
      }
    }
  }

  if (digitalRead(fel) == HIGH) {
    menuTimer = 0;
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
        if (motorTest > 5) motorTest = 5;
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
      case 14:
        if (serDebug == false) {
          serDebug = true;
        } else {
          serDebug = false;
        }
        break;
    }
  }

  if (digitalRead(le) == HIGH) {
    menuTimer = 0;
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
        if (motorTest < 0) motorTest = 0;
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
      case 14:
        if (serDebug == false) {
          serDebug = true;
        } else {
          serDebug = false;
        }
        break;
    }
  }
} //EOF

//////////////////////////ÜZEMMÓD VÁLTÁS - BEMENETI JEL//////////////////////////
void readInput() {
  if (thermostat == false) {         // Bemenet vezérelt üzemmód

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
  } else if (thermostat == true) {   // Thermostat vezérelt üzemmód
    //valami
    if (tempC < setTemp - histeresis && digitalRead(heatPin) == LOW) {
      reqHeat = true;
      digitalWrite(fanPin, LOW);         // Ventillátor bekapcsolása
    }
    if (tempC >= setTemp || digitalRead(heatPin) == HIGH) {
      reqHeat = false;
      digitalWrite(fanPin, HIGH);         // Ventillátor kikapcsolása
    }
  }
}

int freeRam ()                           // Dinamikus memória mérése
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

long readVcc() {                         // Tápfeszültség mérése
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  return result;
}
