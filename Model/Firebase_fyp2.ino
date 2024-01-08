#include <Adafruit_MPU6050.h> 
#include <Adafruit_Sensor.h> 
#include <Wire.h> 
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "qershi"
#define WIFI_PASSWORD "abdu0000"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDncvMIpMZ2I8xEETIA4G2apFN_X63GikE"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://esp32glovedataset-default-rtdb.asia-southeast1.firebasedatabase.app" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;


Adafruit_MPU6050 mpu; 
 
const String name  = "Qershi";  
const int age = 23;  
const char gender = 'M' ;  
const String label = "Hello";  

const int flexPinP = 39;  
const int flexPinR = 34;  
const int flexPinM = 35;    
const int flexPinI = 32;  
const int flexPinT = 33;  

void setup(){
  Serial.begin(115200);

  delay(1000);


  if (!mpu.begin()) { 
    Serial.println("Failed to find MPU6050 chip"); 
    while (1) { 
      delay(10); 
    } 
  } 

   // set accelerometer range to +-8G 
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G); 

   // set filter bandwidth to 21 Hz 
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); 


  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop(){



  sensors_event_t a, g, temp; 
  mpu.getEvent(&a, &g, &temp); 
 
  int flexValueP = analogRead(flexPinP); 
  int flexValueR = analogRead(flexPinR); 
  int flexValueM = analogRead(flexPinM); 
  int flexValueI = analogRead(flexPinI); 
  int flexValueT = analogRead(flexPinT); 
 
  String t_value = String(map(flexValueT, 0, 130, 0, 5000)) ;
  String i_value = String(map(flexValueI, 0, 520, 0, 5000)) ;
  String m_value = String(map(flexValueM, 0, 520, 0, 5000));  
  String r_value = String(map(flexValueR, 0, 520, 0, 5000)) ;  
  String p_value = String(map(flexValueP, 0, 130, 0, 5000)) ;  
 


  Serial.print(name +"\t"+ age +"\t"+ gender +"\t" + p_value + "\t" + r_value + "\t" + m_value + "\t" + i_value + "\t" + t_value +"\t"); 
  Serial.print(a.acceleration.x); 
  Serial.print("\t"); 
  Serial.print(a.acceleration.y); 
  Serial.print("\t"); 
  Serial.println(label); 




  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 2000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setString(&fbdo, "test/Thumb", t_value)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }


    if (Firebase.RTDB.setString(&fbdo, "test/Index", i_value)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }


    if (Firebase.RTDB.setString(&fbdo, "test/Middle", m_value)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }


    if (Firebase.RTDB.setString(&fbdo, "test/Ring", r_value)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }


    if (Firebase.RTDB.setString(&fbdo, "test/Pinky", p_value)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  
    // Write an Float number on the database path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "test/X", a.acceleration.x)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }


    if (Firebase.RTDB.setFloat(&fbdo, "test/Y",a.acceleration.y )){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    if (Firebase.RTDB.setString(&fbdo, "test/Label", label)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
}