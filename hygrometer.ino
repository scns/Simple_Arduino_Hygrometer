#include <SPI.h>
#include <Wire.h>
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT22 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
DHT dht(DHTPIN, DHTTYPE);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



void setup() {
   Serial.begin(9600);
     dht.begin();
   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
   Serial.println(F("SSD1306 allocation failed"));
   for(;;); // Don't proceed, loop forever
          }
          
  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 5);
  // Display static text
  display.println("Welcome");
  display.setCursor(0, 15);
  display.println("To");
  display.setCursor(0, 25);
  display.println("HydroSchmm"); 
  display.display();
  delay(2000);
 
}

void loop()
{
  delay (2000);
  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  float h = dht.readHumidity();     //Reading the humidity value
  
  //display.println(h);
    
  float t = dht.readTemperature();     //Reading the temperature value
 
  //display.println(t);
  
  float fah = dht.readTemperature(true); //Reading the temperature in Fahrenheit
  if (isnan(h) || isnan(t) || isnan(fah)) {   //Checking if we are receiving the values or not
  Serial.println("Failed to read from DHT sensor!");

  return;
  
  }
  
  float heat_index = dht.computeHeatIndex(fah, h); //Calculating the heat index in Fahrenheit
  float heat_indexC = dht.convertFtoC(heat_index);    //Calculating the heat index in Celsius

    display.println("Temp: ");
  display.setCursor(0, 15); 
  display.println("Hum: ");
  display.setCursor(0, 30); 
  display.println("Hi: ");
  display.setCursor(60,0);
  display.println(t);
  display.setCursor(60,15);
  display.println(h);
  display.setCursor(60,30);
  display.println(heat_indexC);
  
  display.setCursor(105,0);
  display.println(" C");
    display.setCursor(105,15);
  display.println(" %");
    display.setCursor(105,30);
  display.println(" %");
  display.display();
}