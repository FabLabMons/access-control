#include <SPI.h>
#include <RFID.h>

#define SS_PIN 5
#define RST_PIN 22
int UID[5];
RFID rfid(SS_PIN, RST_PIN); 

// Setup variables:
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
  Serial.print(serNum0);
  Serial.println(serNum1);
  Serial.println(serNum2);
  Serial.println(serNum3);
  Serial.println(serNum4);
  
}

void loop()
{
    
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
              //lcd.print("l'objet bleu");
              for(int i=0;i<=4;i++)
              {
              Serial.print(UID[i],DEC);
              Serial.print("-");
              }
            }
             else if ((UID[0]==141)&&(UID[1]==111)&&(UID[2]==124)&&(UID[3]==35)&&(UID[4]==189)){
              
              Serial.print("Voila Monsieur MATHLOUTHI_Maher: " );
              //lcd.begin(16,2);
              //lcd.setCursor(0,0);
             // lcd.print("MATHLOUTHI_Maher");
              
              
              
              for(int i=0;i<=4;i++)
              {
              Serial.print(UID[i],DEC);
              Serial.print("-");
              }
             
            }
            
             else if ((UID[0]==240)&&(UID[1]==103)&&(UID[2]==18)&&(UID[3]==164)&&(UID[4]==33)){
              
              Serial.print("Voila l'objet blanc: " );
              //lcd.print("l'objet blanc");
              for(int i=0;i<=4;i++)
              {
              Serial.print(UID[i],DEC);
              Serial.print(".");
              }
            }
             } else {
              delay(10000);
              serNum0=0;
              serNum1=0;
              serNum2=0;
              serNum3=0;
              serNum4=0;
              
                   
               /* If we have the same ID, just write a dot. */
               //Serial.print(".");
             }
          }
    }
    
    rfid.halt();
    digitalWrite(ledPin, LOW); 
    delay(400);
}
