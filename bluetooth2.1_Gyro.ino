//http://blog.naver.com/roboholic84/220461640274//
#include <Wire.h>
#include <GY80.h>
#include <SoftwareSerial.h>
int middle = 0;
int start=0;
SoftwareSerial BTSerial(2, 3); // SoftwareSerial(TX, RX)

GY80 sensor = GY80(); //create GY80 instance

void setup()
{
  BTSerial.begin(9600);
  // initialize serial communication at 115200 bits per second:
  Serial.begin(9600);
  sensor.begin();       //initialize sensors
}

void loop()
{
  
  
  while (BTSerial.available()) { // if BT sends something
    byte data = BTSerial.read();
    if(data!='S'){
      BTSerial.write(data);
    }
    if(data=='S'){
      BTSerial.write("Lamp");
    }
    Serial.write(data); // write it to serial(serial monitor)
  }

  while (Serial.available()) { // if Serial has input(from serial monitor)
    byte data = Serial.read();
    BTSerial.write(data); // write it to BT
  }

  GY80_scaled val = sensor.read_scaled();       //get values from all sensors
  // print out values

  Serial.println(val.m_x);

  int sum = val.g_x + val.g_y + val.g_z;

  
  
  if (val.m_x < 37 )
  {
    Serial.println("Scanning Right");
    BTSerial.write("{1}");
  }

  if (39 < val.m_x && val.m_x < 41 )
  {
    Serial.println("Stop scanning");
    BTSerial.write("{00}");
  }

  if (42 < val.m_x ) {
    Serial.println("Scanning left");
    BTSerial.write("{0}");
    BTSerial.read();
  }

  delay(250);        // delay in between reads for stability
}




