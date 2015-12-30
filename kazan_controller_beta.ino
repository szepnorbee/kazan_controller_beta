//Kazán vezérlő beta
//Szerző: Szép Norbert

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display APA

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int heatPin = 10;
int fanPin = 11;
int motorPin = 12;
int ledPin = 13;
boolean ledState = true;
int motorState = HIGH;
int fanState = HIGH;

int bal = 2;
int fel = 3;
int le = 4;
int jobb = 5;

const int buttonDebounce = 100;   //perges mentesites értékek
const int arrowDebounce = 350;   //perges mentesites nyilak

//Menü oldal valtozok///////////
byte page = 1;
byte menuTimer = 0;

//Beállítások változói///////////
byte motorStop = 3;                //Behajt üzem idő  3 volt
byte motorStart = 4;

byte motorStop2 = 3;                //Szünet üzem idő
byte motorStart2 = 4;

byte motorTest = 2;
byte fanDelay = 10;
boolean manual = false;
boolean bLight = true;
boolean dataChanged = false;
boolean debug = false;
boolean reqHeat = false;
/////////////// Levegő késleltetés //////////////////////////////
byte fanTime = 0;
boolean fanTimeout = true;
boolean upDated = false;
//////////////// Hőmérséklet szabályozás ////////////////////////
byte setTemp = 60;
byte histeresis = 1;
float tempC = 0;
boolean thermostat = true;

//Timer valtozok/////////////////////////////////////////////////
unsigned long elozoMillis = 0;   // LCD frissites
const long lcdUpdate = 1000;      // LCD frissites

long egyezer = 1000;       //másodperc
long hatvanezer = 60000;   //perc

boolean valtozas = false;

unsigned long previousMillis = 0;
long OnTime = 0;
long OffTime = 0;

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
  lcd.print(" Ver: 15.12.30  ");

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

    if (page != 1 && page!=13) menuTimer++;           // Vissza a főmenübe 20 mp múlva
    if (menuTimer >= 20) {
      page = 1;
      menuTimer = 0;
    }


  ///////////////////////SZÍVVERÉS/////////////////////////////////////////////
    if (ledState == true) {
      ledState = false;
      digitalWrite(ledPin, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("*");
      sensors.requestTemperatures();
    } else {
      ledState = true;
      digitalWrite(ledPin, LOW);
      lcd.setCursor(0, 0);
      lcd.print(" ");
      tempC = sensors.getTempCByIndex(0);
      Serial.println(tempC,1);
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
