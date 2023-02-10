#include<SoftwareSerial.h>// uart communication
#include <Wire.h>// for i2c communication 
#include<TinyGPS++.h>//gps
#include <TinyMPU6050.h>
#include <SPI.h>
#include <MFRC522.h>

#define GPSSerial Serial3

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);

  
static const uint16_t Baudrate = 9600;//default baudrate

static const uint8_t tempMotorPin =  A0;
static const uint8_t tempBattery1Pin = A1;
static const uint8_t tempBattery2Pin = A2;
float tempMotor = -1, tempBattery1 = -1, tempBattery2 = -1;

static const uint16_t PassengerTHRESHOLD = 700;
static const uint8_t pasenger1 = A8;
static const uint8_t pasenger2 = A9;
static const uint8_t pasenger3 = A10;
static const uint8_t pasenger4 = A11;
static const uint8_t pasenger1LedPin = 7;
static const uint8_t pasenger2LedPin = 6;
static const uint8_t pasenger3LedPin = 5;
static const uint8_t pasenger4LedPin = 4;
uint8_t seat1, seat2, seat3, seat4;


//volt amp meter pin configuration
static const uint8_t VVM_TX_pin = 12; //R11
static const uint8_t VVM_RX_pin = 13; //R12
SoftwareSerial vvmSerial(VVM_RX_pin, VVM_TX_pin);

//Gps pin configuration- Neo_6M
TinyGPSPlus gps;
//static const uint16_t GPSBAUD = 9600;//default baudrate
String alt_str = "0";
String lat_str = "0", lng_str = "0";

//Constructing MPU-6050
MPU6050 mpu (Wire);

String Data;
void setup() {

  pinMode(pasenger1LedPin, OUTPUT);
  pinMode(pasenger2LedPin, OUTPUT);
  pinMode(pasenger3LedPin, OUTPUT);
  pinMode(pasenger4LedPin, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  Wire.begin(8);
  Wire.onRequest(sendEvent);
  GPSSerial.begin(GPSBAUD);
  delay(100);
  vvmSerial.begin(VVMBAUD);
  delay(100);
  Serial.println("=====================================");
  mfrc522.PCD_Init();    // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  delay(100);
  mpuCalib();
  delay(1000);
}
void loop() {

  for (int i = 0; i < 15; i++) {
    Serial.println(F("Location: "));
    while (GPSSerial.available() > 0)
      if (gps.encode(GPSSerial.read()))
        displayInfo();

    if (millis() > 5000 && gps.charsProcessed() < 10)
    {
      Serial.println(F("No GPS detected: check wiring."));
    }
    delay(100);
  }
  //Temperature sensing code
  tempMotor = temperature(tempMotorPin);
  tempBattery1 = temperature(tempBattery1Pin);
  tempBattery2 = temperature(tempBattery2Pin);

  Serial.print(F("Current Temperature of the motor: "));
  Serial.print(tempMotor);
  Serial.print("\xC2\xB0");
  Serial.println("C  |  ");

  Serial.print(F("Current Temperature of Battery Set1: "));
  Serial.print(tempBattery1);
  Serial.print("\xC2\xB0");
  Serial.println("C  |  ");

  Serial.print(F("Current Temperature of Battery Set2: "));
  Serial.print(tempBattery2);
  Serial.print("\xC2\xB0");
  Serial.println("C  |  ");
  Serial.println("");


  seat1 = pasengerSensing(pasenger1, pasenger1LedPin);
  seat2 = pasengerSensing(pasenger2, pasenger2LedPin);
  seat3 = pasengerSensing(pasenger3, pasenger3LedPin);
  seat4 = pasengerSensing(pasenger4, pasenger4LedPin);
  while (vvmSerial.available() > 0) {
    Serial.print(vvmSerial.read());
  }
  Serial.println("");

  String locat = "{\"Location\":{\"latitude\":\"" + lat_str + "\",\"longitude\":\"" + lng_str + "\",\"elevation\":\"" + alt_str + "\"}}";
  Data = String(tempMotor) + "," + String(tempBattery1) + "," + String(tempBattery2) + "," + seat1 + "," + seat2 + ","
         + seat3 + "," + seat4 + "," + lat_str + "," + lng_str + "," + alt_str + "," + "191500513" + "," + "Nishakrsh" + "," + "on" + ",";
  Serial.println(Data);
  delay(1000);
  Serial.println("");
}

void location() {
  for (int i = 0; i < 15; i++) {
    Serial.println(F("Location: "));
    while (Serial3.available() > 0)
      if (gps.encode(Serial3.read()))
        displayInfo();

    if (millis() > 5000 && gps.charsProcessed() < 10)
    {
      Serial.println(F("No GPS detected: check wiring."));
    }
    delay(100);
  }
}
void displayInfo()
{

  if (gps.location.isValid())
  {
    lat_str = String(gps.location.lat(), 6);
    lng_str = String(gps.location.lng(), 6);

    Serial.print(lat_str);
    Serial.print(F(","));
    Serial.print(lng_str);
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.print(F("  Elevation: "));
  if (gps.altitude.isValid())
  {
    alt_str = gps.altitude.meters();
    Serial.print(alt_str);
  }
  else {
    Serial.print(F("INVALID"));
  }
  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
//MPU DATA FUNCTION
void mpuCalib() {

  Serial.println("Starting MPU calibration...");
  //  mpu.Calibrate();
  Serial.println("Calibration complete!");
  Serial.println("Offsets:");
  Serial.print("GyroX Offset = ");
  Serial.println(mpu.GetGyroXOffset());
  Serial.print("GyroY Offset = ");
  Serial.println(mpu.GetGyroYOffset());
  Serial.print("GyroZ Offset = ");
  Serial.println(mpu.GetGyroZOffset());
  delay(500);
}

//I2C DATA SLAVE SENDING DATA
void sendEvent(int howmany)
{

  for (int k = 0; k < 80; k++)
  {
    Wire.write(Data[k]);
  }

}

//TEMPERATURE FUNCTION
float temperature(int sensorPin) {
  delay(500);
  int reading = analogRead(sensorPin);
  float voltage = reading * (5.0 / 1024.0);
  float temperature = voltage * 100;
  return temperature;
}

//PASSENGER SENSING FUNCTION
uint8_t pasengerSensing(int FORCE_SENSOR_PIN, int ledPin) {
  delay(500);
  int sensorValue = analogRead(FORCE_SENSOR_PIN);
  Serial.print("Force sensor reading  " + String(FORCE_SENSOR_PIN) + " = ");
  Serial.println(sensorValue); // print the analog reading

  if (sensorValue >= PassengerTHRESHOLD) {
    digitalWrite(ledPin, HIGH);
    return 1;
  }
  else {
    digitalWrite(ledPin, LOW);
    return 0;
  }

}
