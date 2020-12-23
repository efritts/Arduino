/*
 * Needed code: 
 *   - Temp / Humidity reading
 *        - Fan Control
 *        - Water bubbler
 *   - Soil moisture sensor         
 *        - Plant watering
 *   - RTC timer
 *        - Grow lights
 *        - Fertilizer reminder
 */

const int PUMP = 4; // D4 output
const int VALVE = 5; // D5 output
const int WATER_SENSOR = 0; // Analog 0 input


int waterSensorValue = 0;
int percentHydrated = 50; // set to 50% to start

 
void setup() {
  // put your setup code here, to run once:

  
  Serial.begin(9600);

}

// following code closes the relays to provide power to the pump and the solenoid
void pumpRun(){
     digitalWrite(VALVE, HIGH);
     delay(1000);
     digitalWrite(PUMP, HIGH);
     
}

// following code opens relays to pump and valve power
void pumpOff(){
     digitalWrite(PUMP, LOW);
     digitalWrite(VALVE, LOW);
}

// takes moisture sensor input and converts to moisture percentage
void measureSoilMoisture(){
     waterSensorValue = analogRead(WATER_SENSOR);
     //percentHydrated = map(waterSensorValue, 350, 720, 0, 100);
}

void loop() {
  // put your main code here, to run repeatedly:
  measureSoilMoisture();
  
  // test target of 35-65% soil moisture
  if(percentHydrated > 35 && percentHydrated < 65){
     Serial.println("Soil moisture is optimal.");
  }
  if(percentHydrated <= 35){
     Serial.println("Soil is dry.  Initiating hydration cycle...");
     pumpRun();
     delay(5000); // sends approx. 5 oz of water to the plant
     pumpOff();
  }
  if(percentHydrated >= 65){
     Serial.println("Soil is too wet, yo.");
  }
  // wait 1 minute for soil to absorb water and measure again
  delay(60000);

}
