const int relay1 = 4;
int i = 0;
void setup() {
     // put your setup code here, to run once:
     pinMode(relay1, OUTPUT);
}

void loop() {
     // put your main code here, to run repeatedly:

     while(i < 12){
     digitalWrite(relay1, HIGH);
     delay(1000);
     digitalWrite(relay1, LOW);
     delay(1000);
     i += 1;
     }

}
