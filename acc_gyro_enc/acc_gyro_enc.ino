#include <Wire.h>
#include <Encoder.h>

const int MPUaddress = B1101000;  // 7 bit I2C address
byte data[6]; //all the bytes read back from the gyro 
byte gyro_data[6]; //all the bytes read back from the gyro 
byte accel_data[6]; //all the bytes read back from the accel 
word wgyro[3]; //gyro value as words (2 bytes)
int c;
byte err;

// Encoder pins.  Need to have interrupts on the pins, and on
// this Arduino, that's only 2 and 3
Encoder encoder(2, 3);
long encpos;

void setup()
{
  //pinMode(I2Cenablepin, OUTPUT);
  //digitalWrite(I2Cenablepin, HIGH);

  Serial.begin(57600);    // start serial comm

  Wire.begin();      // join I2C bus as master
  Wire.setTimeout(100);
  
  Wire.beginTransmission(MPUaddress);
  Wire.write(0x6B);    // power management 1
  Wire.write(B00000000);    // wake up, reset to defaults
  Wire.endTransmission();

  Wire.beginTransmission(MPUaddress);
  Wire.write(0x38);    // interrupt enable
  Wire.write(B00000001);    // interrupt on data ready
  Wire.endTransmission();

  //selftest();
  //delay(100);
  
  Wire.beginTransmission(MPUaddress);
  Wire.write(0x1B);    // Gyro config
  Wire.write(B00000000);    // 250 deg/s full scale range
  Wire.endTransmission();
   

  Wire.beginTransmission(MPUaddress);
  Wire.write(0x1C);    // Accel config
  Wire.write(B00010000);    // turn off accel self test 8g range
  Wire.endTransmission();
}

void selftest()
{
  byte trim1, trim2;
  byte g_trim[3];
  byte g_selftest[6];
  byte g_base[6];
  byte a_trim[3];
  byte a_selftest[6];
  byte a_base[6];
  int n;
  
  // do self tests... (maybe)
  // Serial.println("These might be the gyro factory trim values.");
  Wire.beginTransmission(MPUaddress);
  Wire.write(13);    // Gyro config
  Wire.endTransmission();
  
  Wire.requestFrom(MPUaddress, 4);
  for (n=0;n<3;n++) {
    trim1 = Wire.read(); // receive a byte 
    g_trim[n] = trim1 & B00011111;
    
    // upper three bits of a 5 bit accel trim
    a_trim[n] = trim1 & B11100000;
    a_trim[n] = a_trim[n] >> 3;  
  }
  
  // get the last two bits of each accelerometer trim value
  trim1 = Wire.read();
  trim2 = trim1 & B00110000;
  trim2 = trim2 >> 4;
  a_trim[0] += trim2;
  
  trim2 = trim1 & B00001100;
  trim2 = trim2 >> 2;
  a_trim[1] += trim2;

  trim2 = trim1 & B00000011;
  a_trim[2] += trim2;

  Wire.endTransmission();

  // start self test
  Wire.beginTransmission(MPUaddress);
  Wire.write(0x1B);    // Gyro config
  Wire.write(B11100000);    // turn on gyro self test
  Wire.endTransmission();
  
  // read gyro output
  Wire.beginTransmission(MPUaddress);
  Wire.write(0x43);        // gyro address
  Wire.endTransmission();

  // Serial.println("Gyro output with self test");
  Wire.requestFrom(MPUaddress, 6);    // request 6 bytes
  for (n=0;n<6;n++) {
    g_selftest[n] = Wire.read(); // receive a byte 
  }
  Wire.endTransmission();
 
  // clear self test register
  Wire.beginTransmission(MPUaddress);
  Wire.write(0x1B);    // Gyro config
  Wire.write(B00000000);    // turn off gyro self test
  Wire.endTransmission();
  
  // read gyro output again without self test
  // Serial.println("Gyro output without self test");
  Wire.beginTransmission(MPUaddress);
  Wire.write(0x43);        // gyro address
  Wire.endTransmission();

  Wire.requestFrom(MPUaddress, 6);    // request 6 bytes
  for (n=0;n<6;n++) {
    g_base[n] = Wire.read(); // receive a byte 
  }
  Wire.endTransmission();

 // config accel and run self test
  Wire.beginTransmission(MPUaddress);
  Wire.write(0x1C);    // Accel config
  Wire.write(B11110000);    // self test on, 8 g full scale range
  Wire.endTransmission();
  
  // read accel output
  Wire.beginTransmission(MPUaddress);
  Wire.write(0x3B);        // accel address
  Wire.endTransmission();

  // Serial.println("Accel output with self test");
  Wire.requestFrom(MPUaddress, 6);    // request 6 bytes
  for (n=0;n<6;n++) {
    a_selftest[n] = Wire.read(); // receive a byte 
  }
  Wire.endTransmission();
  
  // clear self test register
  Wire.beginTransmission(MPUaddress);
  Wire.write(0x1C);    // Accel config
  Wire.write(B00010000);    // turn off accel self test, 8g range
  Wire.endTransmission();
  
  // read accel output again without self test
  // Serial.println("Accel output without self test");
  Wire.beginTransmission(MPUaddress);
  Wire.write(0x3B);        // accel address
  Wire.endTransmission();

  Wire.requestFrom(MPUaddress, 6);    // request 6 bytes
  for (n=0;n<6;n++) {
    a_base[n] = Wire.read(); // receive a byte 
  }
  Wire.endTransmission();
  
  Serial.write(49);
  Serial.write(g_trim, 3);
  Serial.write(g_selftest, 6);
  Serial.write(g_base,6);
  
  Serial.write(a_trim, 3);
  Serial.write(a_selftest, 6);
  Serial.write(a_base,6);
  Serial.write(49);
}

void loop()
{
  boolean ready=false; //boolean flag to say when data is ready
  byte stat; //status byte
  int n;
  char cmd;
  int err = 0;
  int nbytes = 0;
  
  Wire.beginTransmission(MPUaddress);
  Wire.write(0x3A);    // interrupt status
  err += Wire.endTransmission();

  Wire.requestFrom(MPUaddress, 1);
  stat = Wire.read();
  ready = bitRead(stat,0);
  
  if (ready) {
    Wire.beginTransmission(MPUaddress);
    Wire.write(0x43);        // gyro address
    err += Wire.endTransmission();

    Wire.requestFrom(MPUaddress, 6);    // request 6 bytes
    for (n=0;n<6;n++) {
      gyro_data[n] = Wire.read(); // receive a byte 
    }
    err += Wire.endTransmission();

    Wire.beginTransmission(MPUaddress);
    Wire.write(0x3B);        // accel address
    err += Wire.endTransmission();

    Wire.requestFrom(MPUaddress, 6);    // request 6 bytes
    for (n=0;n<6;n++) {
      accel_data[n] = Wire.read(); // receive a byte 
    }
  
    err += Wire.endTransmission();
    //if (err > 0) {
     // Serial.print("Errors: ");
      //Serial.println(err);
    //}
    //else {
    //  Serial.println("data");  
    //}
  }
  
  if (Serial.available() > 0) {
    cmd = Serial.read();

    if (cmd == 's') {
      selftest();
    }
    else {
      nbytes = 0;
      encpos = encoder.read();

      nbytes += Serial.write(42);
      nbytes += Serial.write(gyro_data, 6);
      nbytes += Serial.write(accel_data, 6);
      Serial.write((const uint8_t *)&encpos,4);
      nbytes += Serial.write(42);
    }
  }
}
    
