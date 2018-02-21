/*
 * Bomb Squad Countdown Clock
 */
//------------------------------------

#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <Hash.h>
#include <ESP8266WebServer.h>


static const char ssid[] = "TheJonesHouse2.4GHz"; //"TheJonesHouse2.4GHz" "CodeRed" "Bomb Squad"
static const char password[] = "bajablast123!";  //"bajablast123!" "BahaBlast" "frcteam16"

MDNSResponder mdns;

ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

//-----------------------------------------------------------------------------------------------

int mintens = 0;
int minunits = 2;
int sectens = 3;
int secunits = 0;
int timeleft = 0;

int pause = HIGH;

unsigned long previousdotMillis = 0; 
unsigned long previousMillis = 0;

int tile [4];

const byte digitTable [10] = {
  B11011110,    // 0 B01111110
  B00000110,    // 1 B00010010
  B10111010,    // 2 B01001111
  B10101110,    // 3 B01010111
  B01100110,    // 4 B00110011
  B11101100,    // 5 B01110101
  B11111100,    // 6 B01111101
  B10000110,    // 7 B01010010
  B11111110,    // 8 B01111111
  B11101110  }  // 9 B01110111
;   

const byte blanked = B00000000;
int dotState;

int mintendisp;
int minunitsdisp;
int sectensdisp;
int secunitsdisp;

int plus;
int minus;
int runbutton;
int pausebutton;

int running;
//int hornPin = ;  // Maybe a horn or buzzer can be added at a later date

int resetsunit = 0;
int resetstens = 3;
int resetmunit = 2;
int resetmtens = 0;
