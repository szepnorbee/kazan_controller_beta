void lcdUpd() {
  lcd.setCursor(0, 0);

  if (page == 1) {
    lcd.setCursor(2, 0);
    if (reqHeat == true) {
      lcd.print(F("FUTES       "));
    }
    else {
      lcd.print(F("TARTAS      "));
    }
    lcd.setCursor(0, 1);
    lcd.print((millis() / 1000) / 60); lcd.print("min");
    lcd.setCursor(10, 1);
    lcd.print(tempC, 1);
    lcd.print(" C");   // 'xxxxxxxxxx25.5 C'

    if (motorState == LOW) {
      lcd.setCursor(14, 0);
      lcd.print(">>");
    } else {
      lcd.setCursor(14, 0);
      lcd.print("--");
    }
  }

  if (page == 2) {
    lcd.setCursor(0, 0);
    lcd.print(F("Futes START ido "));
    lcd.setCursor(0, 1);
    lcd.print("T= "); lcd.print(motorStart); lcd.print(F(" s         "));
  }

  if (page == 3) {
    lcd.setCursor(0, 0);
    lcd.print(F("Futes STOP ido  "));
    lcd.setCursor(0, 1);
    lcd.print("T= "); lcd.print(motorStop); lcd.print(F(" s          "));
  }

  if (page == 4) {
    lcd.setCursor(0, 0);
    lcd.print(F("Tuztartas START "));
    lcd.setCursor(0, 1);
    lcd.print("T= "); lcd.print(motorStart2); lcd.print(F(" s          "));
  }

  if (page == 5) {
    lcd.setCursor(0, 0);
    lcd.print(F("Tuztartas STOP  "));
    lcd.setCursor(0, 1);
    lcd.print("T= "); lcd.print(motorStop2); lcd.print(F(" perc      "));
  }

  if (page == 6) {
    lcd.setCursor(0, 0);
    lcd.print(F("Motor teszt ido "));
    lcd.setCursor(0, 1);
    lcd.print("T= "); lcd.print(motorTest); lcd.print(F(" s          "));
  }

  if (page == 7) {
    lcd.setCursor(0, 0);
    lcd.print(F("Hattervilagitas "));
    lcd.setCursor(0, 1);
    lcd.print("Ertek= "); lcd.print(bLight); lcd.print(F("        "));

    if (bLight == true) {                          //Háttérvilágitás beállítása
      lcd.backlight();
    } else {
      lcd.noBacklight();
    }
  }

  if (page == 8) {
    lcd.setCursor(0, 0);
    lcd.print(F("Levego kesleltet"));
    lcd.setCursor(0, 1);
    lcd.print("T= "); lcd.print(fanDelay); lcd.print(F(" s INACTIVE  "));
  }

  if (page == 9) {
    lcd.setCursor(0, 0);
    lcd.print(F("Viz homerseklet "));
    lcd.setCursor(0, 1);
    lcd.print(setTemp); lcd.print(F(" C            "));
  }

  if (page == 10) {
    lcd.setCursor(0, 0);
    lcd.print(F("Hiszterezis     "));
    lcd.setCursor(0, 1);
    lcd.print(histeresis); lcd.print(F(" C             "));
  }

  if (page == 11) {
    lcd.setCursor(0, 0);
    lcd.print(F("Termosztat      "));
    lcd.setCursor(0, 1);
    if (thermostat == true) {
      lcd.print(F("BE              "));
    } else {
      lcd.print(F("KI              "));
    }
  }

  if (page == 12) {
    lcd.setCursor(0, 0);
    lcd.print(F("Beall. mentes   "));
    lcd.setCursor(0, 1);
    lcd.print(F("    + vagy -    "));
  }

  if (page == 13) {
    lcd.setCursor(0, 0);
    lcd.print(F("KEZI Motor: "));
    if (motorState == HIGH) {
      lcd.print("KI  ");
    } else {
      lcd.print("BE  ");
    }
    lcd.setCursor(0, 1);
    lcd.print(F("UZEM Venti: "));
    if (fanState == HIGH) {
      lcd.print("KI  ");
    } else {
      lcd.print("BE  ");
    }
  }

  if (page == 14) {
    lcd.setCursor(0, 0);
    lcd.print(F("  Serial debug  "));
    lcd.setCursor(0, 1);
    if (serDebug == true) {
      lcd.print(F("BE              "));
    } else {
      lcd.print(F("KI              "));
    }
  }

  if (page == 15) {
    lcd.setCursor(0, 0);
    lcd.print(F("ReadError:")); lcd.print(readError); lcd.print(F("  "));       // Olvasási hibák
    //lcd.print(F("MEM:")); lcd.print(freeRam()); lcd.print(F(" bytes  "));     // Szabad memória
    lcd.setCursor(0, 1);
    lcd.print(F("Vin:")); lcd.print(readVcc()); lcd.print(F(" mVolt  "));       // Tápfeszültség
  }

  if (page == 16) {
    lcd.setCursor(0, 0);
    lcd.print(F("   SW author    "));
    lcd.setCursor(0, 1);
    lcd.print(F("  Szep Norbert  "));
  }
}

