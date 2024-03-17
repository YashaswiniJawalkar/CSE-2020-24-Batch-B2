#include <DHT11.h>
#include<LiquidCrystal.h>
#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"
DFRobotDFPlayerMini player;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
DHT11 dht11(A6);
const int pulse = A0;
const int gas = A2;
const int xaxis = A10;
const int yaxis = A11;
const int ir = 8;
float millivolt,voltage;
float tempertureC,temp;
int p,i,cl,x,y,p1,h;
float val;
int gas1;
int temp1,hum;
#define DEBUG 1 
String network = "project";                         
String password = "project1234";                 
#define IP "184.106.153.149"                        // IP address of thingspeak.com
String GET = "GET /update?key=HRC0CN3IOGNVLAFQ"; //S2XWZDGUM3QGVKIV
char input[30];
char bsinput[30];
String rfid;
int cnt;
#include <TinyGPS.h>
TinyGPS gps;
float flat=0, flon=0;
void setup()
{
 Serial.begin(9600);
 Serial1.begin(115200);
 Serial2.begin(9600);
  Serial3.begin(9600);
   if (player.begin(Serial2)) {
    Serial.println("OK");
    player.volume(30);
    // Play the "0001.mp3" in the "mp3" folder on the SD card
    player.playMp3Folder(1);

  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
 lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  pinMode(xaxis,INPUT);
  pinMode(yaxis,INPUT);
  pinMode(pulse,INPUT); 
  pinMode(gas,INPUT); 
  pinMode(ir,INPUT); 
  lcd.begin(16,2);
  lcd.print("SMART HELMENT");
  lcd.setCursor(0,1);
  lcd.print("FOR MINING ");
  delay(1000);
 lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TURN ON HOTSPOT");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SET SSID:project");
  lcd.setCursor(0,1);
  lcd.print("pwd:project1234");
  setupEsp8266();
  delay(1000);
 Serial3.println("AT");
 delay(500);
 Serial3.println("AT+CNMI=2,2,0,0,0");
 delay(500);
 Serial3.println("AT+CMGF=1");
 delay(1000);
 Serial3.println("AT+CMGF=1");
  welcome_note();

 
 //send_sms();
}
void loop()
{
  read_gps();

  Serial.println(i);
  //dht11
    // Read the humidity from the sensor.
    int humidity = dht11.readHumidity();

    // Read the temperature from the sensor.
    int temperature = dht11.readTemperature();

    // If the temperature and humidity readings were successful, print them to the serial monitor.
    if (temperature != -1 && humidity != -1)
    {
       
        lcd.setCursor(2,0);    
  lcd.print(temperature); 
 lcd.setCursor(6,0);    
  lcd.print(humidity); 
 
    }
    else
    {
        // If the temperature or humidity reading failed, print an error message.
        Serial.println("Error reading data");
    }
 temp1 = temperature;
 hum = humidity;
    // Wait for 2 seconds before the next reading.
    // pulse
 p = analogRead(pulse);

  if(p < 50)
 {
  p1 = 0;
 }
 else
 {
  p1 = p;
 }
 p1 = map(p1,0,1023,0,120);

 lcd.setCursor(10,0);
 lcd.print(p1); 
  if(p1 > 100)
 {
  send_sms(1);
  Serial.println("WEAR HELMENT");
   player.playMp3Folder(4);
   delay(3000);
 Serial.println("WEAR HELMENT");
   player.playMp3Folder(4);
   delay(3000);
  Serial.println("WEAR HELMENT");
   player.playMp3Folder(4);
   delay(3000);
   Serial.println("sent"); 
 }
  //ir
  i = digitalRead(ir);
  if(i == LOW)
  {
   
  lcd.setCursor(15,1);
   lcd.print("N"); 
    send_sms(2);
   h = 1;
  Serial.println("WEAR HELMENT");
   player.playMp3Folder(6);
   delay(3000);
  Serial.println("WEAR HELMENT");
   player.playMp3Folder(6);
   delay(3000);
  Serial.println("WEAR HELMENT");
   player.playMp3Folder(6);
   delay(3000);
   Serial.println("sent"); 
   
  }
 else
 {
  lcd.setCursor(15,1);
   lcd.print("Y"); 
   h = 0;
   delay(500);
 }
 // mems
 x = analogRead(xaxis);
  y = analogRead(yaxis);
  lcd.setCursor(2,1);
   lcd.print(x);
   lcd.setCursor(7,1);
   lcd.print(y);
   if((x > 380) | (x < 320) | (y > 380) | (y < 320)) 
   {
    delay(2000);
    send_sms(3);
   Serial.println("WEAR HELMENT");
   player.playMp3Folder(5);
   delay(3000);
   Serial.println("WEAR HELMENT");
   player.playMp3Folder(5);
   delay(3000);
  Serial.println("WEAR HELMENT");
   player.playMp3Folder(5);
   delay(3000);
   Serial.println("sent"); 
    lcd.setCursor(15,1);
   lcd.print("p"); 
   delay(1000);
   
   
     }
   // gas
   gas1 = analogRead(gas);
  lcd.setCursor(13,0);
   lcd.print(gas1); 
   delay(1000);
   if(gas1 > 350)
   {
    send_sms(4);
   Serial.println("WEAR HELMENT");
   player.playMp3Folder(3);
   delay(3000);
  Serial.println("WEAR HELMENT");
   player.playMp3Folder(3);
   delay(3000);
  Serial.println("WEAR HELMENT");
   player.playMp3Folder(3);
   delay(3000);
   Serial.println("sent"); 
   
   }
   if(temperature > 40)
   {
    send_sms(5);
   Serial.println("WEAR HELMENT");
   player.playMp3Folder(1);
   delay(3000);
 Serial.println("WEAR HELMENT");
   player.playMp3Folder(1);
   delay(3000);
  Serial.println("WEAR HELMENT");
   player.playMp3Folder(1);
   delay(3000);
   Serial.println("sent"); 
   
   }
    if(humidity > 50)
   {
    send_sms(6);
    Serial.println("WEAR HELMENT");
   player.playMp3Folder(2);
   delay(3000);
  Serial.println("WEAR HELMENT");
   player.playMp3Folder(2);
   delay(3000);
  Serial.println("WEAR HELMENT");
   player.playMp3Folder(2);
   delay(3000);
   Serial.println("sent"); 
   
   }
  
  cl = cl + 1;
  // Serial.print("cnt = ");
  // Serial.println(cl);
   if(cl > 5)
   {
    Serial.println("AT");
    lcd.setCursor(11,1);
  lcd.print("cloud update");
    updateTemp(String(temperature),String(humidity),String(gas1),String(p1),String(h),String(x),String(y));
   cl = 0;
   lcd.setCursor(10,1);
  lcd.print(" HEL:        ");
   }
}

void send_sms(int p)
{
   Serial3.println("AT");
   //Serial.println("AT");
    delay(500);
    Serial3.println("AT+CMGF=1");
    delay(500);
    Serial3.println("AT+CMGS=\"+917794844779\"\r"); // Replace x with mobile number917892606752
    delay(1000);
   if(p==1)
   {
    Serial.println("p=1");
    Serial3.println("PULSE RATE ELEVATED");
   }
    
    if(p==2)
     {
    Serial.println("p=2");
    Serial3.println("MINER HELMENT IS REMOVED");
   }
    if(p==3)
     {
    Serial.println("p=3");
    Serial3.println("SUDDEN FALL IS DETECTED");
   }
     if(p==4)
     {
    Serial.println("p=4");
    Serial3.println("HAZARDOUS GAS DETECTED");
   }
     if(p==5)
     {
    Serial.println("p=5");
    Serial3.println("ALERT HIGH TEMPERATURE DETECTED");
   }
   /*if(p==6)
     {
    Serial.println("p=6");
    Serial3.print("SPIKE IN HUMIDITY LEVEL DETECTED");
   }*/
    Serial3.print("TEMPERATURE:");
    Serial3.print(temp1);
     Serial3.print("HUMIDITY:");
    Serial3.print(hum);
      Serial3.print(",PULSE");
    Serial3.print(p1);
     Serial3.print(",HELMENT=");
    Serial3.print("YES");
     Serial3.print(",X-XAIS");
    Serial3.print(x);
    Serial3.print(",Y-XAIS");
    Serial3.print(y);
    Serial3.print(",GAS");
    Serial3.print(gas1);
    Serial3.println(",TROUBLE AT https://www.google.com/maps/place/14.7452, 77.6896");//14.7452° N, 77.6896° E
   /*Serial.println("TROUBLE AT https://www.google.com/maps/place/");
 Serial.println(String(flat,6));
Serial.println(String(flon,6));*/
   delay(1000);
    delay(1000);
    Serial3.println("");
    delay(100);
    Serial3.println((char)26); // ASCII code of CTRL+Z
    delay(1000);
}
   
   
void setupEsp8266()                                   
{
    Serial1.flush();
    Serial1.println(F("AT+RST"));
    delay(7000);
    if (Serial1.find("OK"))
    {
      if(DEBUG){
        //Serial.println("Found OK");
       // Serial.println("Changing espmode");
      }  
      Serial1.flush();
      changingMode();
      delay(5000);
      Serial1.flush();
      connectToWiFi();
    }
    else
    {
      if(DEBUG){
        //Serial.println("OK not found");
      }
    }
    connectToWiFi();
}
bool changingMode()
{
    Serial1.println(F("AT+CWMODE=1"));
    if (Serial1.find("OK"))
    {
      if(DEBUG){
        //Serial.println("Mode changed");
      }  
      return true;
    }
    else if(Serial1.find("NO CHANGE")){
      if(DEBUG){
        //Serial.println("Already in mode 1");
      }  
      return true;
    }
    else
    {
      if(DEBUG){
        //Serial.println("Error while changing mode");
      }  
      return false;
    }
}
bool connectToWiFi()
{
  if(DEBUG){
   // Serial.println("inside connectToWiFi");
  }  
  String cmd = F("AT+CWJAP=\"");
  cmd += network;
  cmd += F("\",\"");
  cmd += password;
  cmd += F("\"");
  Serial1.println(cmd);
  delay(15000);
  
  if (Serial1.find("OK"))
  {
    if(DEBUG){
      //Serial.println("Connected to Access Point");
    }  
    return true;
  }
  else
  {
    if(DEBUG){
     // Serial.println("Could not connect to Access Point");
    }  
    return false;
  }
}
void updateTemp(String veriable1,String veriable2,String veriable3,String veriable4,String veriable5,String veriable6,String veriable7)
{  
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";
 Serial1.println(cmd);
  delay(3000);
  if(Serial1.find("Error")){
    if(DEBUG){
      //Serial.println("ERROR while SENDING");
    }  
    return;
  }
  cmd = GET + "&field1=" + veriable1 + "&field2=" + veriable2 + "&field3=" + veriable3 + "&field4=" + veriable4 + "&field5=" + veriable5 + "&field6=" + veriable6 + "&field7=" + veriable7 + "\r\n";
  Serial1.print("AT+CIPSEND=");
  Serial1.println(cmd.length());
  delay(13000);
  if(Serial1.find(">"))
  {
    Serial1.print(cmd);
    if(DEBUG){
     // Serial.println("Data sent");
    }
  }else
  {
    Serial1.println("AT+CIPCLOSE");
    if(DEBUG){
      //Serial.println("Connection closed");
    }  
  }
}

 void welcome_note()
{
  lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("T:  H:  P:  G:");
   lcd.setCursor(0,1);
   lcd.print("X:   Y:    HEL: ");
  
   
}

void read_gps()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      if (gps.encode(c)) 
        newData = true;
    }
  }

  if (newData)
  {
    
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);

  }
}
