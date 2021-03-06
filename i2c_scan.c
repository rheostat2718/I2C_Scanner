//    WORKING I2C SCANNER


#define BAUDRATE 115200
#define BUFFER_LENGTH 256

#include <stdio.h>
#include <Wire.h>


char clearSerialInput(void);

char buf[BUFFER_LENGTH];
char ibuf[BUFFER_LENGTH];
char * cp;
char wflag;

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

    sprintf(buf,"Starting New Scan...");
    Serial.println(buf);

	    wflag = 0;
    while (wflag == 0)
    {
        if (Serial.available())
        {
            wflag = 1; // Wait for Input Flag is set to 1, so you can exit WAIT LOOP
            clearSerialInput();
        }
	delay(250);
    }

	
    n = 0;
    for(address = 1; address < 127; address++ ) 
	{
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        Wire.write(address); // Try to Write To I2C Bus
        error = Wire.endTransmission();
	
		if (error == 0)
		{
			sprintf(buf,"Address 0x%02x : error code %d", address, error);
			Serial.println(buf);
			n++;
		}	        
	
	
	}
    
    if (n == 0)
    {
	    
		sprintf(buf,"No devices found (n=%d)",n);
        Serial.println(buf);
    }
    else
    {
        	    
		sprintf(buf,"%d device(s) found on I2C Bus 3",n);
        Serial.println(buf);
    }
    


    //delay(5000);
}


char clearSerialInput(void)
{
	int c;
	c = 0;
	
	while (Serial.available() )
	{
		
		Serial.read(); // While there are new characters in serial input buffer
							     // read them into ibuf (INPUT_BUFFER);
		
		c=c+1;				     // Increment Character Counter, counts the # of characters in STRING
							     // NOT including NULL CHARACTER;
	}
	
	if (c > 0)
	{
		
		return 1; // Clear Bytes from Serial Input Buffer
	}
	else
	{
		
		return 0; // Nothing in Serial Input Buffer to Clear
	}
    return 0;
}