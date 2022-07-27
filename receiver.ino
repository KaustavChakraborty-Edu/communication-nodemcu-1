

#include <ESP8266WiFi.h>
#include <espnow.h>
#include <ThingSpeak.h>


//receiver
//COM3





//int dist;

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[32];
    int b;
    float c;
    String d;
    bool e;
} struct_message;

// Create a struct_message called myData
struct_message myData;


  const char* ssid = "kAuStAv";           //********
  const char* pass = "87654321";          //********

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("Int: ");
  Serial.println(myData.b);
  Serial.print("Float: ");
  Serial.println(myData.c);
  Serial.print("String: ");
  Serial.println(myData.d);
  Serial.print("Bool: ");
  Serial.println(myData.e);
  Serial.println();


  
  
   
  

  
  
  



}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station

  WiFi.mode(WIFI_AP_STA);
  
   // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
    
  
  
}

void loop() {

  esp_now_register_recv_cb(OnDataRecv);
 
  Serial.println("Connecting to WiFi");   //********
  WiFi.begin(ssid,pass);                  //********
  while(WiFi.status()!= WL_CONNECTED){    //********
  Serial.print(".");                      //********
  delay(500);                             //********
  }
  Serial.println("WiFi Connected");       //********


  WiFiClient client ;                     //********
  long id  = 1769318;                     //********
  const char* api = "F71PXX7WWS66ZC8M" ;  //********
  char ip[] = "184.106.153.149";          //********
  ThingSpeak.begin(client);               //********
  

  

  ThingSpeak.setField(1,myData.b);        //********
  ThingSpeak.writeFields(id,api);         //********
  client.stop();                          //********
  
  delay(10000);                           //********
  

  
 
  }
    
    
