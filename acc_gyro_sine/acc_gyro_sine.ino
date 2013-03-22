#include <avr/pgmspace.h>
#include <TimerOne.h>
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

// table of values of a sine wave
PROGMEM  prog_uchar sine256[]  = {
  127,130,133,136,139,143,146,149,152,155,158,161,164,167,170,173,176,178,181,184,187,190,192,195,198,200,203,205,208,210,212,215,217,219,221,223,225,227,229,231,233,234,236,238,239,240,
  242,243,244,245,247,248,249,249,250,251,252,252,253,253,253,254,254,254,254,254,254,254,253,253,253,252,252,251,250,249,249,248,247,245,244,243,242,240,239,238,236,234,233,231,229,227,225,223,
  221,219,217,215,212,210,208,205,203,200,198,195,192,190,187,184,181,178,176,173,170,167,164,161,158,155,152,149,146,143,139,136,133,130,127,124,121,118,115,111,108,105,102,99,96,93,90,87,84,81,78,
  76,73,70,67,64,62,59,56,54,51,49,46,44,42,39,37,35,33,31,29,27,25,23,21,20,18,16,15,14,12,11,10,9,7,6,5,5,4,3,2,2,1,1,1,0,0,0,0,0,0,0,1,1,1,2,2,3,4,5,5,6,7,9,10,11,12,14,15,16,18,20,21,23,25,27,29,31,
  33,35,37,39,42,44,46,49,51,54,56,59,62,64,67,70,73,76,78,81,84,87,90,93,96,99,102,105,108,111,115,118,121,124,127
};

int motorStepPin = 4;
int motorDirPin = 6;
int motorEnablePin = 5;
int stepsperrev = 6400;

float sinefreq = 0;
float sineamp = 0;
float sinestep;

word d;
long cmdpos;
unsigned int count = 0;

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
  
  Timer1.initialize(1000);
  Timer1.attachInterrupt(doStep);
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
  long mindelay;
  
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
    else if (cmd == 'f') {
      sinefreq = Serial.parseFloat();
      sineamp = Serial.parseFloat();
      
      sinestep = sineamp/360 * stepsperrev / 127; //sineamp/360 * stepsperrev / 127;
      d = 256/(4*sinestep);
  
      mindelay = 1000000/sinefreq/(65536/d);

      if ((mindelay <= 10) && (4*sinestep > 256)) {
        //Serial.println("Error: movement too fast");
        sinefreq = 0;
      }
      else {
        Timer1.setPeriod(mindelay);
      }
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

void doStep()
{
  int a, b;
  unsigned char ind;
  int mid;
  int ab;
  long newpos;
  
  if (sinefreq > 0) {
    //ind = count >> 8;
    //mid = count % 256;
    ind = count >> 8;
    mid = count % 256;
    
    ab = pgm_read_word_near(sine256 + ind);    
    a = lowByte(ab);
    b = highByte(ab);
    
    newpos = (a-127)*sinestep + (b-a)*mid*sinestep/256;
    if (newpos > cmdpos) {
      // Serial.println(newpos);
      digitalWrite(motorStepPin, HIGH);
      digitalWrite(motorStepPin, LOW);
      digitalWrite(motorDirPin, HIGH);
    }
    else if (newpos < cmdpos) {
      // Serial.println(newpos);
      digitalWrite(motorStepPin, HIGH);
      digitalWrite(motorStepPin, LOW);
      digitalWrite(motorDirPin, LOW);
    }
    cmdpos = newpos;    
    count += d;
  }
}

