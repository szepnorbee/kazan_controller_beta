void debug() {
      Serial.print("Temp   : ");Serial.println(tempC, 1);
      Serial.print("setTemp: ");Serial.println(setTemp);
      Serial.print("Hister : ");Serial.println(histeresis);
      Serial.print("Thermos: ");Serial.println(thermostat); 
      Serial.print("mTimer : ");Serial.println(menuTimer); 
      Serial.print(F("reqHeat (1-Futes / 0-Tartas : "));Serial.println(reqHeat); 
      Serial.print(F("Input pin state : ")); Serial.println(digitalRead(heatPin));
      Serial.print("Free mem: ");Serial.println(freeRam());
      Serial.println("--------------");
}

