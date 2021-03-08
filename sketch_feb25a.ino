#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define  trig  D2
#define  echo  D1

long duration;
int distance;

// You should get Auth Token in the Blynk App.

char auth[] = "zCEJ27yqPOpIorC4_jB4bEpTFmgn56as";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "TP-Link_D456";
char pass[] = "Bishal2000";

BlynkTimer timer;

void setup()
{
  // Debug console
  pinMode(trig, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echo, INPUT);   // Sets the echoPin as an Inpu
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
void sendSensor()
{
  digitalWrite(trig, LOW);   // Makes trigPin low
  delayMicroseconds(2);       // 2 micro second delay

  digitalWrite(trig, HIGH);  // tigPin high
  delayMicroseconds(10);      // trigPin high for 10 micro seconds
  digitalWrite(trig, LOW);   // trigPin low

  duration = pulseIn(echo, HIGH);   //Read echo pin, time in microseconds
  distance = duration * 0.034 / 2;   //Calculating actual/real distance

  Serial.print("Distance = ");        //Output distance on arduino serial monitor
  Serial.println(distance);
  
  if(distance <=0)
  {
    Blynk.tweet("Hand Sanitizer is working");
    Blynk.notify("Post has been twitted");
  }
  Blynk.virtualWrite(V0, distance);
  delay(10);                        //Pause for 3 seconds and start measuring distance again
}
