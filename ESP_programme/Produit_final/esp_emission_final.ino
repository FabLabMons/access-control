#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <RFID.h> 
#include <WiFiUdp.h>
RFID rfid(5,22);
int UID[5];
    const char* ssid     = "FabLabMons";
    const char* password = "F@bL@bM0ns!";
    // set variables RFID
    int serNum0;
    int serNum1;
    int serNum2;
    int serNum3;
    int serNum4;
    int ledPin=2;
    int led =4;
    int a=2;
    String id="";
    String msg;
    //String poste  = "{\"timestamp\": 1526291679, \"tag_id\": \"ABCDEFGH\", \"signature\": \"9234E84CBA42\"}";
    String poste1 = "{\"timestamp\": ";
    String poste11 = ", \"tag_id\": \"";
    String poste2 = "\", \"signature\": \"9234E84CBA42\"}";
    String poste3;
    String times;

unsigned int localPort = 2390;      // local port to listen for UDP packets
IPAddress timeServerIP; // time.nist.gov NTP server address

const char* ntpServerName = "time.nist.gov";

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

void setup () {
  
  pinMode(ledPin, OUTPUT);
  pinMode(led,OUTPUT); 
  Serial.begin(115200);
  SPI.begin();
  rfid.init();
  Serial.println("Establishing WiFi connection");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.println("Connecting..");
    digitalWrite(led,LOW);
    //delay(10);
 
  }
  Serial.println("WiFi connection established");
  digitalWrite(ledPin,HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(50);
 
}
 
void loop() {
  gett();
  
  //envoie(); 
  
}
void envoie(){
  if ((WiFi.status() == WL_CONNECTED)) { //Check WiFi connection status
    Serial.println("Sending data to web server");

      //Declare an object of class HTTPClient
    HTTPClient http;  
    http.begin("https://access-control-203411.appspot.com/rest/readers/705324A4AE30/events");  //Specify request destination
    http.addHeader("Content-Type","application/json");
    //String poste  = "{\"timestamp\": 1526291679, \"tag_id\": \"54873251290\", \"signature\": \"9234E84CBA42\"}";
    int httpResponseCode = http.POST(poste3);
    if (httpResponseCode != 201) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
 
    }
    Serial.println("Request sent");
    delay(200);
    http.end();   //Close connection
    delay(200);
    
 
  }
}
//=======================================================================
//  send an NTP request to the time server at the given address
//=======================================================================
unsigned long sendNTPpacket(IPAddress& address)
{
  //Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
  
}
void temp(){
  char hours, minutes, seconds;
  //get a random server from the pool
  WiFi.hostByName(ntpServerName, timeServerIP); 

  sendNTPpacket(timeServerIP); // send an NTP packet to a time server
  // wait to see if a reply is available
   //delay(500);
  
  int cb = udp.parsePacket();
  if (!cb) {
   // Serial.println("no packet yet");
  }
  else {
    Serial.print("packet received, length=");
    Serial.println(cb);
    // We've received a packet, read the data from it
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    //Serial.print("Seconds since Jan 1 1900 = " );
    //Serial.println(secsSince1900);

    // now convert NTP time into everyday time:
    //Serial.print("Unix time = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = (secsSince1900 - seventyYears)+7200;
    // print Unix time:
    
    times=epoch;
    
  // wait ten seconds before asking for the time again
  delay(500);
}
}
void gett(){
   
      temp();
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
              id=id + String(UID[i],DEC);
             
            }
            Serial.println("");
            Serial.println(id);
            
            poste1=poste1+times+poste11;
            poste3=poste1+id+poste2;
            Serial.println("{\"timestamp\": 1527291678, \"tag_id\": \"253F4AEC3\", \"signature\": \"9234E84CaB42\"}");
            Serial.println(poste3);
            delay(500);
            
            
            
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
   
             } else {
              
              msg="initialization";
             
                  }
          }
           
          // delay(1000);
          envoie();
    }
    
    rfid.halt();
   
    digitalWrite(ledPin, LOW); 
    id="";
    poste3="";
    poste1 = "{\"timestamp\": ";
    delay(400);
}
