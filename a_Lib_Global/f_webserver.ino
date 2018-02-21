static void writeLED(bool);


// Current LED status
bool ClockStatus;

// Commands sent through Web Socket
const char RUN[] = "run";
const char PAUSE[] = "pause";
const char RESET[] = "reset";
const char PLUS[] = "plus";
const char MINUS[] = "minus";

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  Serial.printf("webSocketEvent(%d, %d, ...)\r\n", num, type);
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\r\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\r\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        // Send the current LED status
        if (ClockStatus) {
          webSocket.sendTXT(num, RUN, strlen(RUN));
        }
        else if (ClockStatus) {
          webSocket.sendTXT(num, PAUSE, strlen(PAUSE));
        }
        else if (ClockStatus) {
          webSocket.sendTXT(num, RESET, strlen(RESET));
        }
        else if (ClockStatus) {
          webSocket.sendTXT(num, PLUS, strlen(PLUS));
        }
        else if (ClockStatus) {
          webSocket.sendTXT(num, MINUS, strlen(MINUS));
        }
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] get Text: %s\r\n", num, payload);

      if (strcmp(RUN, (const char *)payload) == 0) {
        pause = LOW;
      }
      else if (strcmp(PAUSE, (const char *)payload) == 0) {
        pause = HIGH;
      }
       else if (strcmp(RESET, (const char *)payload) == 0) {
        mintens = resetmtens;
        minunits = resetmunit;
        sectens = resetstens;
        secunits = resetsunit;
      }
       else if (strcmp(PLUS, (const char *)payload) == 0) {
        writeLED(false);
      }
       else if (strcmp(MINUS, (const char *)payload) == 0) {
        writeLED(true);
      }
      else {
        Serial.println("Unknown command");
      }
      // send data to all connected clients
      webSocket.broadcastTXT(payload, length);
      break;
    case WStype_BIN:
      Serial.printf("[%u] get binary length: %u\r\n", num, length);
      hexdump(payload, length);

      // echo data back to browser
      webSocket.sendBIN(num, payload, length);
      break;
    default:
      Serial.printf("Invalid WStype [%d]\r\n", type);
      break;
  }
}

void handleRoot()
{
  server.send_P(200, "text/html", INDEX_HTML);
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

static void writeLED(bool CLOCKstart)
{
  ClockStatus = CLOCKstart;
  // Note inverted logic for Adafruit HUZZAH board
  if (CLOCKstart) {
//    digitalWrite(LEDPIN, 0);
  }
  else {
//    digitalWrite(LEDPIN, 1);
  }
}
