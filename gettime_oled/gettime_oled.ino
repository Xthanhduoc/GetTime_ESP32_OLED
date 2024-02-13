#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

const char *ssid     = "ThanhDuoc"; // tên wiffi
const char *password = "0329799336"; // mật khẩu wiffi

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  timeClient.begin();
  timeClient.setTimeOffset(25200);

  display.display(); // Hiển thị "splash screen"
  delay(2000);
  display.clearDisplay();
}

void loop() {
  timeClient.update();
  int h = timeClient.getHours();
  int m = timeClient.getMinutes();
  int s = timeClient.getSeconds();
  Serial.print(h);
  Serial.print(":");
  Serial.print(m);
  Serial.print(":");
  Serial.println(s);
  delay(1000);

  display.clearDisplay();
  display.setTextSize(3);//kích cỡ
  display.setTextColor(WHITE);//màu 
  display.setCursor(10, 20);//tọa độ
  display.println(h);
  display.setCursor(25,20);//tọa độ
  display.println(":");
  display.setCursor(40, 20);//tọa độ
  display.println(m);
  display.setCursor(70, 20);//tọa độ
  display.println(":");
  display.setCursor(85, 20);//tọa độ
  display.println(s);
  display.display(); 
}
