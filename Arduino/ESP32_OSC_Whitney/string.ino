
void readConductiveString() {
  sensorValue = analogRead(sensorPin);
  int values[6]; //Tiri don't forget to change this
  for (int i = 0; i < 6; i++) {  //and this.. don't forget to change this number
    values[i] = analogRead(sensorPins[i]);
  }
  char payload[512];
  //  sprintf(payload, "{\n \"state\":{\n\"floor\": [%d, %d, %d, %d, %d, %d, %d, %d] \n }\n}", values[0] , values[1], values[2], values[3], values[4], values[5], values[6], values[7] );
  sprintf(payload, "%d %d %d %d %d %d", values[0] , values[1], values[2], values[3], values[4], values[5] );

  sendOSC(payload);
  Serial.println(payload);
  Serial.println("");

}
