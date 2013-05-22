#include <Wire.h>

const int MPUaddress = B1101000;  // 7 bit I2C address
const int TRIGGERPIN = 3;

byte data[6]; //all the bytes read back from the gyro 
byte gyro_data[6]; //all the bytes read back from the gyro 
byte accel_data[6]; //all the bytes read back from the accel 
word wgyro[3]; //gyro value as words (2 bytes)
int c;
boolean ready=false; //boolean flag to say when data is ready
unsigned long framenum = 0;
byte istrigger = 0;
unsigned long triggertime;
unsigned long microsecval;

void setup()
{
  unsigned long err;
  
  // set trigger line for input
  pinMode(TRIGGERPIN, INPUT);

  Serial.begin(57600);    // start serial comm
  
  Wire.begin();      // join I2C bus as master
  Wire.setTimeout(100);
  
  Wire.beginTransmission(MPUaddress);
  Wire.write(0x6B);    // power management 1
  Wire.write(B00000000);    // wake up, reset to defaults
  bitWrite(err, 0, Wire.endTransmission());

  Wire.beginTransmission(MPUaddress);
  Wire.write(0x38);    // interrupt enable
  Wire.write(B00000001);    // interrupt on data ready
  bitWrite(err, 1, Wire.endTransmission());

  //selftest();
  //delay(100);
  
  Wire.beginTransmission(MPUaddress);
  Wire.write(0x1B);    // Gyro config
  Wire.write(B00000000);    // 250 deg/s full scale range
  bitWrite(err, 2, Wire.endTransmission());
   
  Wire.beginTransmission(MPUaddress);
  Wire.write(0x1C);    // Accel config
  Wire.write(B00000000);    // turn off accel self test 2g range
  bitWrite(err, 3, Wire.endTransmission());
  
  // attachInterrupt(1, triggercounter, FALLING);
  
  /* Serial.print("First: ");
  Serial.println(err); */
  
  framenum = 0;
}

void loop()
{
  char cmd;
  unsigned long err;
  
  if (Serial.available() > 0) {
    cmd = Serial.read();

    microsecval = micros();
    err = readacc();
    istrigger = digitalRead(TRIGGERPIN);
    
    Serial.write(42);
    Serial.write((const uint8_t *)&microsecval, 4);
    if (istrigger == HIGH) {
      Serial.write(1);
    }
    else {
      Serial.write(0);
    }
    // Serial.write(istrigger);
    Serial.write(gyro_data, 6);
    Serial.write(accel_data, 6);
    Serial.write((const uint8_t *)&err, 4);
    Serial.write(42);
    delay(5);
  }
  else {
    delay(5);
  }
}

void framecounter()
{
  framenum++;
}

void triggercounter()
{
  triggertime = micros();
}

unsigned long readacc()
{
  byte stat; //status byte
  int n;
  unsigned long err = 0;
  
  Wire.beginTransmission(MPUaddress);
  Wire.write(0x3A);    // interrupt status
  err = err << 3;
  err |= Wire.endTransmission();

  Wire.requestFrom(MPUaddress, 1);
  stat = Wire.read();
  ready = bitRead(stat,0);
  
  if (ready) {
    Wire.beginTransmission(MPUaddress);
    Wire.write(0x43);        // gyro address
    err = err << 3;
    err |= Wire.endTransmission();

    Wire.requestFrom(MPUaddress, 6);    // request 6 bytes
    for (n=0;n<6;n++) {
      gyro_data[n] = Wire.read(); // receive a byte 
    }
    err = err << 3;
    err |= Wire.endTransmission();

    Wire.beginTransmission(MPUaddress);
    Wire.write(0x3B);        // accel address
    err = err << 3;
    err |= Wire.endTransmission();

    Wire.requestFrom(MPUaddress, 6);    // request 6 bytes
    for (n=0;n<6;n++) {
      accel_data[n] = Wire.read(); // receive a byte 
    }
    err = err << 3;
    err |= Wire.endTransmission();
    
    /* if (err > 0) {
      Serial.print("Error: ");
      Serial.println(err);
      Serial.println(err1);
    } */
  }
  return err;
}  
