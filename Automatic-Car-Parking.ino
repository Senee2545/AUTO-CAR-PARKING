///////////////////////////////////////V3//////////////////////////////////////////
// Slider 
// Send data from HW to App
// Read Analog to the Gage
///////////////////////////////////////V3//////////////////////////////////////////

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define LED 17
const int SW_carin = 4; 
const int SW_carout = 16;

WidgetLCD lcd(V0);
WidgetLED led_in(V1);
WidgetLED led_out(V3);

char auth[] = "yBEiN0MnBrFH5oAlGwyu8_a1qonBWCVE";
char ssid[] = "Senee";
char pass[] = "12345543210";

int sw_in = 0;
int sw_out = 0;
int count = 0;
int reset;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, IPAddress(134, 122, 29, 169), 8080);
  pinMode(sw_in, INPUT);
  pinMode(sw_out, INPUT);
  pinMode(LED, OUTPUT); 
  lcd.print(0, 0, "COUNTER = "); 
}

void loop() {
  Blynk.run();
  sw_in = digitalRead(SW_carin);
  sw_out = digitalRead(SW_carout);
  if (reset == 1){
    count = 0;
    lcd.clear();
    lcd.print(0, 0, "COUNTER = ");
    lcd.print(10, 0, count); 
    lcd.print(1, 1, "PARKING EMPTY");
  }
  if (sw_in == 1){
    count = count + 1;
    led_in.on();
    lcd.clear();
    lcd.print(0, 0, "COUNTER = ");
    digitalWrite(LED, LOW);
    if(count >= 10){
      count = 10;
      lcd.print(1, 1, "PARKING FULL");
      digitalWrite(LED, HIGH);
    }
    lcd.print(10, 0, count);
  }
  else{
    led_in.off();
  }

 
  if (sw_out == 1){
    count = count - 1 ;
    led_out.on();
    digitalWrite(LED, LOW);
    lcd.clear();
    lcd.print(0, 0, "COUNTER = ");
      if (count <= 0){
        count = 0;
        lcd.print(1, 1, "PARKING EMPTY");
    }
    lcd.print(10, 0, count);
  }
  else{
    led_out.off();
  }
}

BLYNK_WRITE(V2) {
  reset = param.asInt();
}

 
