/*
BTL: Kỹ thuật đo lường điện tử
Thành viên:
  Trần Bá Thành
  Đào Bích Thương
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// #include <math.h>

#define SCREEN_WIDTH 128  // OLED display width,  in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define I2C_ADDR 0x3C

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Khai báo biến và chân ADC
const int potPin = 26;
float lux = 0.00;
float ADC_value = 0.0008056640625;  //0.00322265625
float LDR_value;

// Khai báo lại chân I2C0 trên mạch Pi Pico
const byte PICO_I2C_SDA =8897
 20;
const byte PICO_I2C_SCL = 21;

void setup() {
  Wire.setSDA(PICO_I2C_SDA);
  Wire.setSCL(PICO_I2C_SCL);
  Wire.begin();
  //pinMode(potPin,INPUT);
  Serial.begin(115200);  //initialize serial monitor
  //analogReadResolution(10); // Maybe RP1024 doesnt allow this
  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, I2C_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true)
      ;
  }
  // đợi hệ thống khởi động
  delay(2000);

  oled.clearDisplay();                 // clear display
  oled.setTextSize(2);                 // text size
  oled.setTextColor(WHITE);            // text color
  oled.setCursor(0, 10);               // position to display
  oled.println("System turning on!");  // text to display
  oled.display();                      // show on OLED
}

void loop() {
  // read ADC pin and convert it to lux
  LDR_value = analogRead(potPin);
  lux = (165.0000 / (ADC_value * LDR_value)) - 50.00000;
  Serial.print(lux);
  Serial.println(" lux");
  // Serial.println(LDR_value);
  // Serial.println("__________________");
  

  // Print the lux value to OLED screen
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 10);
  oled.println("Lux value:");
  oled.setCursor(0, 35);
  oled.print(lux);
  oled.println(" lux");
  oled.display();

  delay(1000);
}