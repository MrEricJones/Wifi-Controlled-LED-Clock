#define latchPin 14  // D5
#define clockPin 12  // D6
#define dataPin 13   // D7

#define plusPin 0   // D3
#define minusPin 4   // D2
#define runPin 2   // D4
#define pausePin 5   // D1 

int blank = HIGH;
//------------------------------------------------------------------------
//const int LEDPIN = 2; 

ESP8266WiFiMulti WiFiMulti;

void setup()
{
  Serial.begin(115200);
  blank == HIGH;
  Serial.println("setup");
  pinMode ( latchPin, OUTPUT);
  pinMode ( clockPin, OUTPUT);
  pinMode ( dataPin, OUTPUT);
  
  pinMode ( plusPin, INPUT_PULLUP);
//  digitalWrite(plusPin, HIGH); // set pullups
  pinMode ( minusPin, INPUT_PULLUP);
//  digitalWrite(minusPin, HIGH);
  pinMode ( runPin, INPUT_PULLUP);
//  digitalWrite (runPin, HIGH);
  pinMode ( pausePin, INPUT_PULLUP);
//  digitalWrite(pausePin, HIGH);
//  pinMode ( temp, INPUT_PULLUP);
  
  digitalWrite(latchPin, LOW);      // blanking all displays
  for ( int k=0; k<=3; k++ ){
    shiftOut(dataPin, clockPin, LSBFIRST, blank);
    delay (5);
  }
  digitalWrite(latchPin, HIGH); 
 // pinMode ( hornPin, INPUT);
 // digitalWrite(hornPin, LOW);
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

//  pinMode(LEDPIN, OUTPUT);
//  writeLED(false);

  //Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for(uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] BOOT WAIT %d...\r\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFiMulti.addAP(ssid, password);

  while(WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("espWebSock", WiFi.localIP())) {
    Serial.println("MDNS responder started");
    mdns.addService("http", "tcp", 80);
    mdns.addService("ws", "tcp", 81);
  }
  else {
    Serial.println("MDNS.begin failed");
  }
  Serial.print("Connect to http://espWebSock.local or http://");  
//  Serial.print("Connect to http://BombSquadClockWebSock.local or http://");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.begin();

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}
