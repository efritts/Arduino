#include <Stepper.h>


#include <IRremote.h>


const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);


void setup(){
  Serial.begin(9600);
  myStepper.setSpeed(rolePerMinute);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){
  if (irrecv.decode(&results)){

    switch(results.value){
      case 0xFF22DD: 
          Serial.println("FAST BACK");  
          fastBackward();  
          break;
      case 0xFFC23D: 
          Serial.println("FAST FORWARD");   
          fastForward();
          break;
      case 0xFFE01F: 
          Serial.println("STEP BACK");    
          stepBack();
          break;
      case 0xFF906F: 
          Serial.println("STEP FORWARD"); 
          stepForward();   
          break;
            
//        case 0xFFA25D: Serial.println("POWER"); break;
//        case 0xFFE21D: Serial.println("FUNC/STOP"); break;
//        case 0xFF629D: Serial.println("VOL+"); break;        
//        case 0xFF02FD: Serial.println("PAUSE");    break;         
//        case 0xFFA857: Serial.println("VOL-");    break;        
//        case 0xFF9867: Serial.println("EQ");    break;
//        case 0xFFB04F: Serial.println("ST/REPT");    break;
//        case 0xFF6897: Serial.println("0");    break;
//        case 0xFF30CF: Serial.println("1");    break;
//        case 0xFF18E7: Serial.println("2");    break;
//        case 0xFF7A85: Serial.println("3");    break;
//        case 0xFF10EF: Serial.println("4");    break;
//        case 0xFF38C7: Serial.println("5");    break;
//        case 0xFF5AA5: Serial.println("6");    break;
//        case 0xFF42BD: Serial.println("7");    break;
//        case 0xFF4AB5: Serial.println("8");    break;
//        case 0xFF52AD: Serial.println("9");    break;
//        //case 0xFFFFFFFF: Serial.println(" REPEAT");break; 
//        default: ; 
      
      } // End Case
        
        irrecv.resume();
  }
}

void fastForward(){
    myStepper.step(stepsPerRevolution);

}

void fastBackward(){
    myStepper.step(-stepsPerRevolution);

}

void stepForward(){
  myStepper.step(100);
}

void stepBack(){
  myStepper.step(-100);
}
  
