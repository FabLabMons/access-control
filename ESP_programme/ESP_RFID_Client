
#include <WiFi.h>
#include <WiFiClient.h> //https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFiClient.h
#include <WebServer.h>  //https://github.com/bbx10/WebServer_tng
#include <SPI.h>
#include <RFID.h>       

RFID rfid(5,22);
WiFiServer server(80);
int UID[5];
const char* ssid     = "FabLabMons";
const char* password = "F@bL@bM0ns!";
String msg="maheration95";
// Client variables 
// set variables RFID
    int serNum0;
    int serNum1;
    int serNum2;
    int serNum3;
    int serNum4;
    int ledPin=2;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  SPI.begin();
  rfid.init();
  connectToWifi();
  server.begin();
  
}

void loop() {
 
//server.handleClient();
 ESP_clien();
  
 gett();
 //delay(500);
 
}

void connectToWifi()
{
 

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void gett(){
    
      if (rfid.isCard()) {
        if (rfid.readCardSerial()) {
            if (rfid.serNum[0] != serNum0
                && rfid.serNum[1] != serNum1
                && rfid.serNum[2] != serNum2
                && rfid.serNum[3] != serNum3
                && rfid.serNum[4] != serNum4
            ) {digitalWrite(ledPin, HIGH); 
              delay(400);
               for(int i=0;i<=4;i++)
            {
              UID[i]=rfid.serNum[i];
             // Serial.print(UID[i],DEC);
            //  Serial.print(".");
            //  delay(500); 
            }
                /* With a new cardnumber, show it. */
                Serial.println(" ");
                Serial.println("Card found");
                serNum0 = rfid.serNum[0];
                serNum1 = rfid.serNum[1];
                serNum2 = rfid.serNum[2];
                serNum3 = rfid.serNum[3];
                serNum4 = rfid.serNum[4];
               
                //Serial.println(" ");
                Serial.println("Cardnumber:");
                Serial.print("Dec: ");
    Serial.print(rfid.serNum[0],DEC);
                Serial.print(", ");
    Serial.print(rfid.serNum[1],DEC);
                Serial.print(", ");
    Serial.print(rfid.serNum[2],DEC);
                Serial.print(", ");
    Serial.print(rfid.serNum[3],DEC);
                Serial.print(", ");
    Serial.print(rfid.serNum[4],DEC);
                Serial.println(" ");
                        
                Serial.print("Hex: ");
    Serial.print(rfid.serNum[0],HEX);
                Serial.print(", ");
    Serial.print(rfid.serNum[1],HEX);
                Serial.print(", ");
    Serial.print(rfid.serNum[2],HEX);
                Serial.print(", ");
    Serial.print(rfid.serNum[3],HEX);
                Serial.print(", ");
    Serial.print(rfid.serNum[4],HEX);
                Serial.println(" ");
    if ((UID[0]==38)&&(UID[1]==208)&&(UID[2]==98)&&(UID[3]==172)&&(UID[4]==56)){
              
              Serial.print("Voila l'objet bleu: " );
              msg="Voila l'objet bleu";
              //lcd.print("l'objet bleu");
              for(int i=0;i<=4;i++)
              {
              Serial.print(UID[i],DEC);
              Serial.print("-");
              }
            }
              if ((UID[0]==141)&&(UID[1]==111)&&(UID[2]==124)&&(UID[3]==35)&&(UID[4]==189)){
              
              Serial.print("Voila Monsieur MATHLOUTHI_Maher: " );
              msg="MATHLOUTHI_Maher";
              
              
              
              for(int i=0;i<=4;i++)
              {
              Serial.print(UID[i],DEC);
              Serial.print("-");
              }
             
            }
            
              if ((UID[0]==240)&&(UID[1]==103)&&(UID[2]==18)&&(UID[3]==164)&&(UID[4]==33)){
              
              Serial.print("Voila l'objet blanc: " );
              msg="Voila l'objet blanc:";
              //lcd.print("l'objet blanc");
              for(int i=0;i<=4;i++)
              {
              Serial.print(UID[i],DEC);
              Serial.print(".");
              }
            }
             } else {
              
              msg="initialization";
              
                   
               /* If we have the same ID, just write a dot. */
               //Serial.print(".");
             }
          }
    }
    
    rfid.halt();
    digitalWrite(ledPin, LOW); 
    delay(400);
}
void ESP_clien(){
  
   // listen for incoming clients
  WiFiClient client = server.available();
  client.println("<!DOCTYPE HTML><html><head>");
          client.println("<meta http-equiv='refresh' content='2'/></head>");
          client.println("<h1>ESP32 - Liste</h1>");
          client.print (msg);
          client.println("</html>");
}
