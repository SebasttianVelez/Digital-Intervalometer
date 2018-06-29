int PULSADOR = 2;
int LED = 4;
int i = 0;
int estado = LOW;

void setup(){

	pinMode(PULSADOR, INPUT); // Pulsador entrada in
  	pinMode(LED, OUTPUT);	  // Led salida
	
  	digitalWrite(LED, LOW);   //APAGAR EL LED
}

void loop(){
	while(digitalRead(PULSADOR)==LOW);
  	estado = digitalRead(LED);
	digitalWrite(LED, !estado);
  	while(digitalRead(PULSADOR)==HIGH);
	
}
