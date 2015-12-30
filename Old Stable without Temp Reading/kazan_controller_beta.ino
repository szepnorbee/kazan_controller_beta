//Kazán vezérlő beta
//Szerző: Szép Norbert

//#include <OneWire.h>
//#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display APA

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

const int buttonDebounce = 150;   //perges mentesites értékek
const int arrowDebounce = 450;   //perges mentesites nyilak

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
int setTemp = 60;
int histeresis = 0;

//Timer valtozok/////////////////////////////////////////////////
unsigned long elozoMillis = 0;   // LCD frissites
const long interval = 1000;      // LCD frissites

long egyezer = 1000;       //másodperc
long hatvanezer = 60000;   //perc

boolean valtozas = false;

unsigned long previousMillis = 0;
long OnTime = 0;
long OffTime = 0;

//////////////////////////////////////////////////////////////////

void setup() {

  Serial.begin(9600);
  lcd.init();                      // initialize the lcd
  
  OnTime = motorStart * egyezer;
  OffTime = motorStop * egyezer;

  lcd.backlight();
  lcd.print(" Kazan vezerlo ");
  lcd.setCursor(0, 1);
  lcd.print(" Ver: 15.12.28  ");

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

  if (mostaniMillis - elozoMillis >= interval) {      // LCD frissites

    elozoMillis = mostaniMillis;
    lcdUpd();                             // Kijelző frissítés másodpercenként

    if (page != 1) menuTimer++;           // Vissza a főmenübe 20 mp múlva
    if (menuTimer >= 20) {
      page = 1;
      menuTimer = 0;
    }


  ///////////////////////SZÍVVERÉS/////////////////////////////////////////////
    if (ledState == true) {
      ledState = false;
      digitalWrite(ledPin, HIGH);
      lcd.setCursor(15, 1);
      lcd.print("*");
    } else {
      ledState = true;
      digitalWrite(ledPin, LOW);
      lcd.setCursor(15, 1);
      lcd.print(" ");
    }
    
  }

  readInput();
  readButtons();
  UpdVar();
  
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
