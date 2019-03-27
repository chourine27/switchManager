#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <EEPROM.h>

const char* ssid     = "Aumont";
const char* password = "Marie est nee le 30 novembre 2008";

WiFiUDP UDPServer;
unsigned int UDPPort = 27600;

const int packetSize = 60;
byte packetBuffer[packetSize];

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;

String serverName;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  delay(10);

  // Connexion Wifi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  WiFi.config(IPAddress(192, 168, 45, 101), IPAddress(192, 168, 45, 254), IPAddress(255, 255, 255, 0));
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connexion au Wifi avec l'IP :");
  Serial.println(WiFi.localIP());

  // Lit la mémoire EEPROM
  for (int i = 0; i < 32; ++i)
    {
      serverName += char(EEPROM.read(i));
    }
  Serial.println("Chargement du nom :");
  Serial.println(serverName);

  // Configuration de la GPIO 0
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);
  Serial.println("Configuration de la GPIO 0 en Out et éteint");
  
  // Active le serveur UDP
  Serial.println("Démarrage du serveur UDP");
  UDPServer.begin(UDPPort);
}

void loop() {
   handleUDPServer();
   delay(1);
}

/** Traitement du contenu d'un message */
void handleUDPServer() {
  int cb = UDPServer.parsePacket();
  if (cb) {
    UDPServer.read(packetBuffer, packetSize);
    String myData = ""; 
    for(int i = 0; i < packetSize; i++) {
      myData += (char)packetBuffer[i];
    }
    Serial.println(myData);
    if (myData.startsWith("TonNom")) {
      SendMessage(serverName);
      }
    else {
      if (myData.startsWith("ChangeEtatBouton 1 0")) {
        UpdateValueGPIO(1, LOW);
        SendMessage("200");
        }
      else {
        if (myData.startsWith("ChangeEtatBouton 1 1")) {
          UpdateValueGPIO(1, HIGH);
          SendMessage("200"); // OK
          }
        else {
          if (myData.startsWith("RenommerTonNom")) {
            if (myData.length() > 60) {
              SendMessage("414"); // Trop long
              }
            else {
              serverName = myData.substring(15); // En retirant "RenommerTonNom "
              serverName.setCharAt(serverName.length()-1,'\0'); // Supprimer le caractère entrer à la fin
              saveToEEPROM();
              SendMessage("200"); // OK
              }
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
void SendMessage(String message) {
  // Envoyer une réponse au client avec les informations IP et port du client
  UDPServer.beginPacket(UDPServer.remoteIP(), UDPServer.remotePort());
  UDPServer.write(message.c_str());
  UDPServer.write("\n");
  UDPServer.endPacket();
  Serial.println(message);
}

/** Mise à jour de la GPIO*/
void UpdateValueGPIO(int index, bool value) {
  if (value) {
    digitalWrite(0, HIGH);
    Serial.println("Allumer");
    }
  else {
    digitalWrite(0, LOW);
    Serial.println("Eteindre");
  }
}

/** Sauvegarde en mémoire EEPROM le nom du serveur */
void saveToEEPROM() {
  for (int i = 0; i < 32; ++i) {
    EEPROM.write(i, 0);
    }
  for (int i = 0; i < 32; ++i) {
    EEPROM.write(i, serverName[i]);
    }
  EEPROM.commit();
  Serial.println("Sauvegarde du nouveau nom");
  Serial.println(serverName);
}
