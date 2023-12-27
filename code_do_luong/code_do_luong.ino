const int potPin = 26;
float lux=0.00;
float ADC_value=0.0008;
float LDR_value;

void setup() 
{
  Serial.begin(115200);   //initialize serial monitor
  analogReadResolution(10);
  delay(1000);
}

void loop() 
{
  LDR_value=analogRead(potPin);
  lux=(8.250000/(ADC_value*LDR_value))- 2.500000;
  Serial.println(lux);
  delay(1000);

}
