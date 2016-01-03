//Kazán vezérlő beta
//Szerző: Szép Norbert

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display APA

#define ONE_WIRE_BUS 6
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int heatPin = 10;
const int fanPin = 11;
const int motorPin = 12;
const int ledPin = 13;
boolean ledState = HIGH;
boolean motorState = HIGH;   // unsigned int volt
boolean fanState = HIGH;

const int bal = 2;
const int fel = 3;
const int le = 4;
const int jobb = 5;

const int buttonDebounce = 100;   //perges mentesites értékek
const int arrowDebounce = 350;   //perges mentesites nyilak

//Menü oldal valtozok///////////
byte page = 1;
byte menuTimer = 0;

//Beállítások változói///////////
byte motorStop = 3;           // Fűtés üzem
byte motorStart = 4;

byte motorStop2 = 3;          // Tűztartás üzem     
byte motorStart2 = 4;

byte motorTest = 2;
byte fanDelay = 10;
boolean manual = false;
boolean bLight = true;
boolean dataChanged = false;
boolean reqHeat = false;
/////////////// Levegő késleltetés //////////////////////////////
byte fanTime = 0;
boolean fanTimeout = true;
boolean upDated = false;
//////////////// Hőmérséklet szabályozás ////////////////////////
byte setTemp = 60;
byte histeresis = 3;
float tempC = 0;
boolean thermostat = true;

//Timer valtozok/////////////////////////////////////////////////
unsigned long elozoMillis = 0;   // LCD frissites
const long lcdUpdate = 1000;      // LCD frissites

const long egyezer = 1000;       //másodperc
const long hatvanezer = 60000;   //perc

boolean valtozas = false;

unsigned long previousMillis = 0;
unsigned long OnTime = 0;
unsigned long OffTime = 0;

//////////////////////////////////////////////////////////////////

void setup() {

  Serial.begin(9600);
  sensors.begin();
  lcd.init();                      // initialize the lcd

  OnTime = motorStart * egyezer;
  OffTime = motorStop * egyezer;

  lcd.backlight();
  lcd.print(" Kazan vezerlo ");
  lcd.setCursor(0, 1);
  lcd.print(" Ver: 16.01.01  ");

  pinMode(heatPin, INPUT);
  digitalWrite(heatPin, HIGH);

  pinMode(fanPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(bal, INPUT);
  pinMode(fel, INPUT);
  pinMode(le, INPUT);
  pinMode(jobb, INPUT);

  digitalWrite(fanPin, fanState);
  digitalWrite(motorPin, motorState);
  delay(1000);

  lcd.clear();

  lcd.print("   MOTOR TESZT  ");
  digitalWrite(motorPin, LOW);
  delay(motorTest * 1000);
  digitalWrite(motorPin, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("    TESZT OK    ");
  delay(500);
  lcd.clear();
  Serial.println("Program indul..");

  memRead();                    //Változók beolvasása EEPROM-ból
}

void loop() {

  ///////////////////////////////// KIJELZŐ FRISSÍTÉS /////////////////////////////////
  unsigned long mostaniMillis = millis();

  if (mostaniMillis - elozoMillis >= lcdUpdate) {      // LCD frissites

    elozoMillis = mostaniMillis;
    lcdUpd();                             // Kijelző frissítés másodpercenként

    if (page != 1 && page != 13) menuTimer++;         // Vissza a főmenübe 20 mp múlva
    if (menuTimer >= 20) {
      page = 1;
      menuTimer = 0;
    }

    debug();                                         // Soros port hibakeresés
    
    ///////////////////////SZÍVVERÉS/////////////////////////////////////////////
    if (ledState == HIGH) {
      ledState = LOW;
      digitalWrite(ledPin, HIGH);
      lcd.setCursor(0, 0);
      if (page==1) {
      lcd.print("*");
      }
      sensors.requestTemperatures();
    } else {
      ledState = HIGH;
      digitalWrite(ledPin, LOW);
      lcd.setCursor(0, 0);
      if (page==1) {
      lcd.print(" ");
      }
      tempC = sensors.getTempCByIndex(0);
    }

  }

  readInput();
  readButtons();
  updVar();

  ////////////////////////////////// CSIGA VEZÉRLÉS //////////////////////////////
  unsigned long currentMillis = millis();

  if ((motorState == LOW) && (currentMillis - previousMillis >= OnTime))
  {
    if (page != 12) {
      motorState = HIGH;  // Turn it off
      previousMillis = currentMillis;
      digitalWrite(motorPin, motorState);
    }
  }
  else if ((motorState == HIGH) && (currentMillis - previousMillis >= OffTime))
  {
    if (page != 12) {
      motorState = LOW;  // turn it on
      previousMillis = currentMillis;
      digitalWrite(motorPin, motorState);
    }
  }
  /////////////////////////////////////////////////////////////////////////////////
}
