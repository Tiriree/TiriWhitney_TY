#include <ADCTouch.h>

int ref0, ref1, ref2, ref3, ref4;     //reference values to remove offset

void setup()
{
  // No pins to setup, pins can still be used regularly, although it will affect readings

  Serial.begin(9600);

  ref0 = ADCTouch.read(A0, 500);    //create reference values to
  ref1 = ADCTouch.read(A1, 500);    //account for the capacitance of the pad
  ref2 = ADCTouch.read(A2, 500);
  ref3 = ADCTouch.read(A3, 500);
  ref4 = ADCTouch.read(A4, 500);
}

void loop()
{
  int value0 = ADCTouch.read(A0);   //no second parameter
  int value1 = ADCTouch.read(A1);   //   --> 100 samples
  int value2 = ADCTouch.read(A2);
  int value3 = ADCTouch.read(A3);
  int value4 = ADCTouch.read(A4);

  value0 -= ref0;       //remove offset
  value1 -= ref1;
  value2 -= ref2;
  value3 -= ref3;
  value4 -= ref4;

  Serial.print(value0 > 40);    //send (boolean) pressed or not pressed
  Serial.print("\t");           //use if(value > threshold) to get the state of a button

  Serial.print(value1 > 40);
  Serial.print("\t");

  Serial.print(value2 > 40);    //send (boolean) pressed or not pressed
  Serial.print("\t");
  
  Serial.print(value3 > 40);    //send (boolean) pressed or not pressed
  Serial.print("\t");
  
  Serial.print(value4 > 40);    //send (boolean) pressed or not pressed
  Serial.print("\t\t");

  Serial.print(value0);             //send actual reading
  Serial.print("\t");


  Serial.print(value1);             //send actual reading
  Serial.print("\t");
  
  Serial.print(value2);             //send actual reading
  Serial.print("\t");
  
  Serial.print(value3);             //send actual reading
  Serial.print("\t");

  Serial.println(value4);
  delay(100);
}
