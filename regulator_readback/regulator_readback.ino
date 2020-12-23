#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int togglePin = 7;

int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int manReg = 0;
int shearReg = 0;
int annReg = 0;

int toggle = 0;
int lastToggle = 0;
int selection = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2); 


// the setup routine runs once when you press reset:
void setup() {

     pinMode(togglePin, INPUT_PULLUP);

     lcd.init();//Defining 16 columns and 2 rows of lcd display
     lcd.backlight();//To Power ON the back light
     // initialize serial communication at 9600 bits per second:
     Serial.begin(9600);
}



// the loop routine runs over and over again forever:
void loop() {
     sensorValue1 = analogRead(A0);
     manReg = map(sensorValue1, 0, 1023, 0, 5000);
     
     sensorValue2 = analogRead(A1);
     shearReg = map(sensorValue2, 0, 1023, 0, 5000);
     
     sensorValue3 = analogRead(A2);
     annReg = map(sensorValue3, 0, 1023, 0, 5000);

     toggle = digitalRead(togglePin);

     
     if (toggle == HIGH){
          selection++;
          }
     
     if (selection > 2){
          selection = 0;
     }
     switch (selection){
          case 0:               
               lcd.setCursor(0,0);
               lcd.print("Manifold Reg: ");
               lcd.setCursor(0,1);
               lcd.print(manReg);
               break;
          case 1:
               lcd.setCursor(0,0);
               lcd.print("Shear Reg: ");
               lcd.setCursor(0,1);
               lcd.print(shearReg);  
               break;
          case 2:
               lcd.setCursor(0,0);
               lcd.print("Annular Reg: ");
               lcd.setCursor(0,1);
               lcd.print(annReg);
               break;
     }

     Serial.print(manReg);
     Serial.print(",");
     Serial.print(shearReg);
     Serial.print(",");
     Serial.println(annReg);
    
     
     delay(100);        // delay in between reads for stability
  
}
