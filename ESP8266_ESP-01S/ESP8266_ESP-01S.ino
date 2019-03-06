#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <EEPROM.h>

const char* ssid     = "Aumont";
const char* password = "Marie est nee le 30 novembre 2008";

WiFiUDP UDPTestServer;
unsigned int UDPPort = 27600;

const int packetSize = 2;
byte packetBuffer[packetSize];

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;

char serverName[30];

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  WiFi.config(IPAddress(192, 168, 45, 210), IPAddress(192, 168, 45, 254), IPAddress(255, 255, 255, 0));
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Lit la mémoire EEPROM
  EEPROM.get(0, serverName);
  Serial.println(serverName);
    
  UDPTestServer.begin(UDPPort);
  
}

void loop() {
   handleUDPServer();
   delay(1);
}

void handleUDPServer() {
  int cb = UDPTestServer.parsePacket();
  if (cb) {
    UDPTestServer.read(packetBuffer, packetSize);
    String myData = ""; 
    for(int i = 0; i < packetSize; i++) {
      myData += (char)packetBuffer[i];
    }
    Serial.println(myData);
    if (myData == "TonNom") {
      SendMessage("MonNom");
      }
    else {
      if (myData == "ChangeEtatBouton 1 0") {
        UpdateValueGPIO(1, LOW);
        SendMessage("200");
        }
      else {
        if (myData == "ChangeEtatBouton 1 1") {
          UpdateValueGPIO(1, HIGH);
          SendMessage("200"); // OK
          }
        else {
          if (myData.startsWith("RenommerTonNom")) {
            if (myData.length() > 45) {
              SendMessage("414"); // Trop long
            }
            myData.substring(15).toCharArray(serverName, 30); // En retirant "RenommerTonNom "
            saveToEEPROM();
            SendMessage("200"); // OK
            }
            else {
              SendMessage("404"); // OK
            }
          }
        }
      }
   }
}

/** Retourne un message au client*/
void SendMessage(char *message) {
  Serial.println(message);
}

/** Mise à jour de la GPIO*/
void UpdateValueGPIO(int index, bool value) {
  if (value) {
    Serial.println("Allumer");
    }
  else {
    Serial.println("Eteindre");
  }
}

/** Sauvegarde en mémoire EEPROM le nom du serveur */
void saveToEEPROM() {
  EEPROM.put(0, serverName);
}
