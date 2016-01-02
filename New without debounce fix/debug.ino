void debug() {
      Serial.print("Temp   : ");Serial.println(tempC, 1);
      Serial.print("setTemp: ");Serial.println(setTemp);
      Serial.print("Hister : ");Serial.println(histeresis);
      Serial.print("Thermos: ");Serial.println(thermostat); 
      Serial.print("mTimer : ");Serial.println(menuTimer); 
      Serial.print("reqHeat (1-Futes / 0-Tartas : ");Serial.println(reqHeat); 
}

