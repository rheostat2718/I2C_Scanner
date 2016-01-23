

#define BAUDRATE 11500
#define BUFFER_LENGTH 256

#include <stdio.h>
#include <Wire.h>


char buf[BUFFER_LENGTH]
char * cp;


void setup()
{
  Wire.begin();
  cp = buf;
  Serial.begin(BAUDRATE);
  delay(100);
  
  
}


void loop()
{
  int error, address;
  int n;

  Serial.println("Scanning...");

  n = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
	
	sprintf(buf,"Address 0x%02h : error code %d%c%c", address, error, 0x0d,0x0a);
	
	Serial.print(buf);
      
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);           // wait 5 seconds for next scan
}