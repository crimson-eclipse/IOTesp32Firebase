#include <FirebaseESP32.h>

#include <WiFi.h>

#define FIREBASE_HOST "YOUR_REALTIME_DB"
#define FIREBASE_AUTH "YOUR_DB_SECRET_CODE"
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASS"

#define ldr 39
#define trigPin 13
#define echoPin 27

FirebaseData firebaseData;

String path = "/Node1";

int oldAdcLdr;
int newAdcLdr;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ldr,INPUT);
    
  initWifi();
  oldAdcLdr = analogRead(ldr);
}

void loop() {
  delay(500);

  
  
  long duration;
  float distance;
   digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(500);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
    if(distance > 255){
        distance = 255;
      }
  Serial.println(distance);
  Firebase.setInt(firebaseData, path + "/distance", distance);

   newAdcLdr = analogRead(ldr);
  Serial.println(newAdcLdr);
  if(newAdcLdr != oldAdcLdr){
    Firebase.setDouble(firebaseData, path + "/ldr", newAdcLdr);
    oldAdcLdr = newAdcLdr;
  }
  
  //ambil nilai dari sensor ultarsonic dan kirim ke firebase
//  newDistance = distanceSensor.measureDistanceCm();
//  Serial.println(newDistance);
//  if(newDistance != oldDistance){
//    Firebase.setInt(firebaseData, path + "/distance", newDistance);
//    oldDistance = newDistance; 
//  }

  //ambil nilai dari sensor LDR dan kirim ke firebase
}

void initWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}
