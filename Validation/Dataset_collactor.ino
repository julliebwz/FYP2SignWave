#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

const String name = "Zahra";
const int age = 23;
const char gender = 'M';
const String label = "I love you";

const int flexPinP = 39;
const int flexPinR = 34;
const int flexPinM = 35;
const int flexPinI = 32;
const int flexPinT = 33;

void setup(void) {
  Serial.begin(115200);

  delay(1000);
  Serial.println("Name\t\t\t Age\t Gender\t Pinky\t Ring\t Middle\t Index\t Thumb\t Label\t");


  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // // set gyro range to +- 500 deg/s
  // mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  int flexValueP = analogRead(flexPinP);
  int flexValueR = analogRead(flexPinR);
  int flexValueM = analogRead(flexPinM);
  int flexValueI = analogRead(flexPinI);
  int flexValueT = analogRead(flexPinT);

  long p_value = map(flexValueP, 0, 130, 0, 5000);
  long r_value = map(flexValueR, 0, 520, 0, 5000);
  long m_value = map(flexValueM, 0, 520, 0, 5000);
  long i_value = map(flexValueI, 0, 520, 0, 5000);
  long t_value = map(flexValueT, 0, 130, 0, 5000);

  /* Print out the values */
  Serial.print(name + "\t" + age + "\t" + gender + "\t" + p_value + "\t" + r_value + "\t" + m_value + "\t" + i_value + "\t" + t_value + "\t");
  Serial.print(a.acceleration.x);
  Serial.print("\t");
  Serial.print(a.acceleration.y);
  Serial.print("\t");
  Serial.println(label);


  // Serial.print(a.acceleration.z);
  // Serial.print(", ");
  // Serial.print(g.gyro.x);
  // Serial.print(",");
  // Serial.print(g.gyro.y);
  // Serial.print(",");
  // Serial.print(g.gyro.z);

  delay(1000);
}