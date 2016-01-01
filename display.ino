void lcdUpd() {
  lcd.setCursor(0, 0);

  if (page == 1) {
    lcd.setCursor(2, 0);
    if (reqHeat == true) {
      lcd.print("FUTES   ");
    }
    else {
      lcd.print("TARTAS  ");
    }
    lcd.setCursor(0, 1);
    lcd.print((millis() / 1000) / 60); lcd.print("min");
    lcd.setCursor(10, 1);
    lcd.print(tempC, 1); lcd.print(" C");   // 'xxxxxxxxxx25.5 C'

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
    lcd.print("Futes START ido ");
    lcd.setCursor(0, 1);
    lcd.print("T= "); lcd.print(motorStart); lcd.print(" s         ");
  }

  if (page == 3) {
    lcd.setCursor(0, 0);
    lcd.print("Futes STOP ido  ");
    lcd.setCursor(0, 1);
    lcd.print("T= "); lcd.print(motorStop); lcd.print(" s          ");
  }

  if (page == 4) {
    lcd.setCursor(0, 0);
    lcd.print("Tuztartas START ");
    lcd.setCursor(0, 1);
    lcd.print("T= "); lcd.print(motorStart2); lcd.print(" s          ");
  }

  if (page == 5) {
    lcd.setCursor(0, 0);
    lcd.print("Tuztartas STOP  ");
    lcd.setCursor(0, 1);
    lcd.print("T= "); lcd.print(motorStop2); lcd.print(" perc      ");
  }

  if (page == 6) {
    lcd.setCursor(0, 0);
    lcd.print("Motor teszt ido ");
    lcd.setCursor(0, 1);
    lcd.print("T= "); lcd.print(motorTest); lcd.print(" s          ");
  }

  if (page == 7) {
    lcd.setCursor(0, 0);
    lcd.print("Hattervilagitas ");
    lcd.setCursor(0, 1);
    lcd.print("Ertek= "); lcd.print(bLight); lcd.print("        ");

    if (bLight == true) {                          //Háttérvilágitás beállítása
      lcd.backlight();
    } else {
      lcd.noBacklight();
    }
  }

  if (page == 8) {
    lcd.setCursor(0, 0);
    lcd.print("Levego kesleltet");
    lcd.setCursor(0, 1);
    lcd.print("T= "); lcd.print(fanDelay); lcd.print(" s INACTIVE  ");
  }

  if (page == 9) {
    lcd.setCursor(0, 0);
    lcd.print("Viz homerseklet ");
    lcd.setCursor(0, 1);
    lcd.print(setTemp); lcd.print(" C            ");
  }

  if (page == 10) {
    lcd.setCursor(0, 0);
    lcd.print("Hiszterezis     ");
    lcd.setCursor(0, 1);
    lcd.print(histeresis); lcd.print(" C        ");
  }

  if (page == 11) {
    lcd.setCursor(0, 0);
    lcd.print("Termosztat      ");
    lcd.setCursor(0, 1);
    if (thermostat == true) {
      lcd.print("BE              ");
    } else {
      lcd.print("KI              ");
    }
  }

  if (page == 12) {
    lcd.setCursor(0, 0);
    lcd.print("Beall. mentes   ");
    lcd.setCursor(0, 1);
    lcd.print("    + vagy -    ");
  }

  if (page == 13) {
    lcd.setCursor(0, 0);
    lcd.print("KEZI Motor: ");
    if (motorState == HIGH) {
      lcd.print("KI  ");
    } else {
      lcd.print("BE  ");
    }
    lcd.setCursor(0, 1);
    lcd.print("UZEM Venti: ");
    if (fanState == HIGH) {
      lcd.print("KI  ");
    } else {
      lcd.print("BE  ");
    }
  }
}

