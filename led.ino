int PULSADOR = 8;
int LED = 4;     
int estado = LOW;
void setup() {
	pinMode(PULSADOR, INPUT); // El pulsador va a ser entrada
  	pinMode(LED, OUTPUT);     // El led va a ser salida
  	digitalWrite(LED,LOW);    //Apagar el led (por si acaso)
  	
}


void loop() {
	while(digitalRead(PULSADOR)==LOW); //Mientras el pulsador no tenganvoltaje (no se oprima)
  	//NO HAGA NADA, ES DECIR ESPERAR QUE SE OPRIMA
  	estado = digitalRead(LED);  //SI SE OPRIME, Leer el estado del led
  	digitalWrite(LED,!estado);  // Cambiar el estado del led con respecto al que tenia
  	while(digitalRead(PULSADOR)==HIGH); // Sistema antirebote
}