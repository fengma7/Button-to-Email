/* 
 *  Bollard Button Code
 *  M. Feng
 *  
 *  Used components of Rupak Poddar's Example Code - https://github.com/Rupakpoddar/ESP8266Webhook/blob/master/examples/IFTTT_Webhooks/IFTTT_Webhooks.ino
 *  Used components of Ian Bucklery's Code - https://www.makeuseof.com/tag/wifi-connected-button-esp8266-tutorial/
 *  
 *  The program will make it so that when a button is pressed, the arduino sends
 *  out a message using a webhook through the method of email to a certain user. It will also
 *  play a noise through a buzzer when pressed.
 *
 * Algorithm
 *  START
 *  Initalize libraries
 *  Intialize Pins
 *  Define the SSID, Password, Webhook Key, and Webhook Event
 *  Startup Function
 *  Set pins equal to input and output
 *  Execute the connectToWifi Method
 *    connectToWiFi
 *    START
 *    Print connecting to SSID and attempting to connect
 *    int i = 100
 *    Start While
 *    While wifi status is not connected and i is greater than 0
 *      Execute WiFi connection function
 *      print countdown
 *    END WHILE
 *    Once connected state connected and then print the local IP
 *    END connectToWiFi
 *  Loop Function
 *  If the button is pressed
 *    play the buzzer
 *    trigger the webhook
 *   else
 *    do not trigger the webhook
 *  END
*/

#include <ESP8266Webhook.h>
#include <ESP8266WiFi.h>

#define ssid "NodeMCU-TestA"      // Your WiFi SSID
#define password "TestingForNodeMCUA"  // Your WiFi Password
#define KEY "cWw-TO26fMTeG-m-CU6FvG"        // Webhooks Key
#define EVENT "button_pressed"      // Webhooks Event Name

Webhook webhook(KEY, EVENT);    // Create an object.

const int buttonPin = 4;     
const int ledPin =  5;      
const int buzzerPin = 14;
int buttonState = 0;
int response = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  connectToWifi();
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 200, 10000);
    response = webhook.trigger();
  } else {
    digitalWrite(ledPin, LOW);
    response = 0;
  }
}

void connectToWifi() {
  Serial.print("Connecting to: SSID NAME"); 
  WiFi.begin(ssid, password);
  Serial.println(" ");
  Serial.print("Attempting to connect: ");
  int i = 100;
  while (WiFi.status() != WL_CONNECTED && i >= 0) {
    delay(1000);
    Serial.print(i);
    Serial.print(", ");
    i--;
  }
  Serial.println(" ");
  //print connection result
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected.");
    Serial.println(" ");
    Serial.print("NodeMCU ip address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed - check your credentials or connection");
  }
}
