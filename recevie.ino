#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


// WiFi parameters
#define HOST "pieddeck.com/Getstatus.php"          // Enter HOST URL without "http:// "  and "/" at the end of URL

#define WIFI_SSID "cebelimestan"            // WIFI SSID here     
                              
#define WIFI_PASSWORD "f7c44Q4cbj"        // WIFI password here

String  payload;
int led = 2;
//host to send data
String  postData;
  
HTTPClient http;    // http object of clas HTTPClient
WiFiClient wclient; 
void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(115200); 
Serial.println("Communication Started \n\n");  
delay(1000);
  
 


WiFi.mode(WIFI_STA);           
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
Serial.print("Connecting to ");
Serial.print(WIFI_SSID);
while (WiFi.status() != WL_CONNECTED) 
{ Serial.print(".");
    delay(500); }

Serial.println();
Serial.print("Connected to ");
Serial.println(WIFI_SSID);
Serial.print("IP Address is : ");
Serial.println(WiFi.localIP());    //print local IP address

delay(30);
}
void loop() {


http.begin(wclient, "http://pieddeck.com/Getstatus.php");              // Connect to host where MySQL databse is hosted
http.addHeader("Content-Type", "application/x-www-form-urlencoded");            //Specify content-type header
int httpCode = http.GET(); 

 if (httpCode == 200) { Serial.println("Values uploaded successfully."); Serial.println(httpCode); 
String webpage = http.getString();    // Get html webpage output and store it in a string
Serial.println(webpage + "\n"); 
  if(webpage == "1")  // if data == 1 -> LED ON
  {
    digitalWrite(led,HIGH);
    }
   if (webpage == "0") // if data == 0 -> LED OFF
   {
    digitalWrite(led,LOW);
    }
}

else { 
  Serial.println(httpCode); 
  Serial.println("Failed to upload values. \n"); 
  http.end(); 
  return; }




  

}