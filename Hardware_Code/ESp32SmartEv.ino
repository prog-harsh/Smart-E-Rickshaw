#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

#include <Wire.h>
String deviceID = "EV1";

// 1. Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>
// 2. Define the RTDB URL
#define DATABASE_URL "smart-ev-f653f-default-rtdb.firebaseio.com"
// 3. Define the Firebase Data object
FirebaseData fbdo;

// 4. Define the FirebaseAuth data for authentication data
FirebaseAuth auth;

// 5. Define the FirebaseConfig data for config data
FirebaseConfig config;

// 6. Setting path
String pathPassenger = "/" + deviceID + "/Passenger/";
String pathLocation = "/" + deviceID + "/Location";
String pathTemperature = "/" + deviceID + "/Temperature/";
String pathGyro = "/" + deviceID + "/Gyro/";
String pathUser = "/" + deviceID + "/User/";

WiFiClient client;

const char* WIFI_SSID = "Nishkarsh";
const char* WIFI_PASSWORD = "12345677";
const char* host = "172.16.78.20";
const char* appKey = "889dc99e-17b1-4633-a4c1-77e47b17f269";
const int Port = 7080;
String alt_str = "0";
String lat_str = "0", lng_str = "0";

const char Thing_Temp[] = "SmartEV_Temp";
const char Thing_Gyro[] = "SmartEV_Gyro";
const char Thing_Piezo[] = "SmartEV_Piezo";
const char Thing_GPS[] = "SmartEV_GPS";
const char Thing_RPM[] = "SmartEV_RPM";

const char Property1[] = "TempMotor";
const char Property2[] = "TempBS1";
const char Property3[] = "TempBS2";
const char Property4[] = "Gyro_X";
const char Property5[] = "Gyro_Y";
const char Property6[] = "Gyro_Z";
const char Property7[] = "Piezo1";
const char Property8[] = "Piezo2";
const char Property9[] = "Piezo3";
const char Property10[] = "Piezo4";
const char Property11[] = "Location";
const char Property12[] = "Speed_RPM";

float tempMotor = 0, tempBS1 = 0, tempBS2 = 0;
int seat1 = 0, seat2 = 0, seat3 = 0, seat4 = 0;
String locat;
char c;
void setup() {
  Serial.println("=====================================");

  Wire.begin(4, 5);
  Serial.begin(115200);
  wifiConnect();

  /* Assign the database URL(required) */
  config.database_url = DATABASE_URL;
  config.signer.test_mode = true;
  /* Initialize the library with the Firebase authen and config */
  Firebase.begin(&config, &auth);
}
void loop() {
  // put your main code here, to run repeatedly:
  Wire.requestFrom(8, 80);
  char array[80];
  int i = 0;
  while ( Wire.available() > 0)
  {
    c = Wire.read();
    array[i++] = c;
  }
  for (int j = 0; j < 80; j++)
  {
    Serial.print(array[j]);
  }
  Serial.println();
  char *strings[15];
  char *ptr = NULL;
  byte index = 0;
  ptr = strtok(array, ",");
  while (ptr != NULL)
  {
    strings[index] = ptr;
    Serial.println(String(strings[index]));
    index++;
    ptr = strtok(NULL, ",");
  }
  delay(100);
  Serial.println(locat);

  //  Serial.printf("Set MOTORTEMP %s\n", Firebase.setFloat(fbdo, pathTemperature + "MotorTemp", atof(strings[0])) ? "ok" : fbdo.errorReason().c_str());
  //  Serial.printf("Set BATT1TEMP %s\n", Firebase.setFloat(fbdo, pathTemperature + "Batt1Temp", atof(strings[1])) ? "ok" : fbdo.errorReason().c_str());
  //  Serial.printf("Set BATT2TEMP %s\n", Firebase.setFloat(fbdo, pathTemperature + "Batt2Temp", atof(strings[2])) ? "ok" : fbdo.errorReason().c_str());
  //
  //  Serial.printf("Set SEAT1 %s\n", Firebase.set(fbdo, pathPassenger + "Seat1", String(strings[3])) ? "ok" : fbdo.errorReason().c_str());
  //  Serial.printf("Set SEAT2 %s\n", Firebase.set(fbdo, pathPassenger + "Seat2", String(strings[4])) ? "ok" : fbdo.errorReason().c_str());
  //  Serial.printf("Set SEAT3 %s\n", Firebase.set(fbdo, pathPassenger + "Seat3", String(strings[5])) ? "ok" : fbdo.errorReason().c_str());
  //  Serial.printf("Set SEAT4 %s\n", Firebase.set(fbdo, pathPassenger + "Seat4", String(strings[6])) ? "ok" : fbdo.errorReason().c_str());
  //
  //  Serial.printf("Set User ID %s\n", Firebase.setInt(fbdo, pathUser + "ID", 191500513) ? "ok" : fbdo.errorReason().c_str());
  //  Serial.printf("Set User ID %s\n", Firebase.set(fbdo, pathUser + "Name", "Nishkarsh") ? "ok" : fbdo.errorReason().c_str());
  //  Serial.printf("Set User ID %s\n", Firebase.set(fbdo, pathUser + "STATUS", "OFF") ? "ok" : fbdo.errorReason().c_str());
  //
  //  Serial.printf("Set User ID %s\n", Firebase.setFloat(fbdo, pathLocation + "Latitude", atof("0.00")) ? "ok" : fbdo.errorReason().c_str());
  //  Serial.printf("Set User ID %s\n", Firebase.setFloat(fbdo, pathLocation + "Longitude",atof("0.00")) ? "ok" : fbdo.errorReason().c_str());
  //  Serial.printf("Set User ID %s\n", Firebase.setFloat(fbdo, pathLocation + "Altitude", atof("0.00")) ? "ok" : fbdo.errorReason().c_str());
  //
  //  Serial.printf("Set User ID %s\n", Firebase.setFloat(fbdo, pathGyro + "X", atof("0.00")) ? "ok" : fbdo.errorReason().c_str());
  //  Serial.printf("Set User ID %s\n", Firebase.setFloat(fbdo, pathGyro + "Y", atof("0.00")) ? "ok" : fbdo.errorReason().c_str());
  //  Serial.printf("Set User ID %s\n", Firebase.setFloat(fbdo, pathGyro + "Z", atof("0.00")) ? "ok" : fbdo.errorReason().c_str());
  //
  //
  //
  //
  //
  //
  //  Put(Thing_Temp, Property1, String(strings[0]));
  //
  //  Put(Thing_Temp, Property2, String(strings[1]));
  //  Put(Thing_Temp, Property3, String(strings[2]));
  //
  //  Put(Thing_Gyro, Property4, String(""));
  //  Put(Thing_Gyro, Property5, String(""));
  //  Put(Thing_Gyro, Property6, String(""));
  //
  //  Put(Thing_Piezo, Property7, String(strings[3]));
  //  Put(Thing_Piezo, Property8, String(strings[4]));
  //  Put(Thing_Piezo, Property9, String(strings[5]));
  //  Put(Thing_Piezo, Property10, String(strings[6]));
  //
  //  Put(Thing_GPS, Property11, locat);

  delay(500);
}
void wifiConnect() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void Put(String ThingName, String ThingProperty, String Value)
{
  Serial.println(host);
  if (!client.connect(host, Port))
  {
    Serial.println("connection failed");
    return;
  } else

  {
    Serial.println("Connected to ThingWorx.");
  }
  String url = "/Thingworx/Things/" + ThingName + "/Properties/" + ThingProperty;
  //  Serial.print("requesting URL: ");
  //  Serial.println(url);

  String strPUTReqVal = "{\"" + ThingProperty + "\":\"" + Value + "\"}";
  Serial.print("PUT Value: ");
  Serial.println(strPUTReqVal);

  String thingURL = String("PUT ") + url + " HTTP/1.1\r\n" +
                    "Host: " + host + "\r\n" +
                    "appKey:" + appKey + "\r\n" +
                    "x-thingworx-session: false" + "\r\n" +
                    "Accept: application/json" + "\r\n" +
                    "Connection: close" + "\r\n" +
                    "Content-Type: application/json" + "\r\n" +
                    "Content-Length: " + String(strPUTReqVal.length()) + "\r\n\r\n" +
                    strPUTReqVal + "\r\n\r\n";
  Serial.println(thingURL);
  client.print(thingURL);

  while (client.connected())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  client.stop();
  delay(10);
}
