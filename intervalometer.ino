
#include <LiquidCrystal.h>
LiquidCrystal lcd (12,11,5,4,3,2);

int PhotoSensor = 0;
int sensorValue =0;
//int sensorPin = A0;
// CONeccion con el arduino fisico
 
int botones = A0;


//


int b1 = 10;
int b4 = 9;
int b2 = 7;
int b3 = 8;

const byte LED1 = 13;
const byte LED2 = 6;
int op = 0;
int lag = 200;
int quantity = 0, time = 0, exposition = 0;

const int pResistor = A1;
int sensorResistor = 0;
int estadoBotonAnterior;
const int tiempoAntirebote =10;
int outputValue=0;

void setup()
{
 pinMode(LED1, OUTPUT);
 pinMode(LED2, OUTPUT);
 pinMode(b1, INPUT);
 pinMode(b2, INPUT);
 pinMode(b3, INPUT);
 pinMode(b4, INPUT);
 Serial.begin(9600);
 pinMode(pResistor, INPUT);
 lcd.begin(16,2);
}



bool antirebote  (int pin ) {
  int  contador =0;
  int estado;            // guarda el estado del boton
  int estadoAnterior=0;    // guarda el ultimo estado del boton

  do {
    estado = analogRead (pin);
    outputValue = map(estado, 0, 1023, 0, 255);
    Serial.println (outputValue);
    Serial.println (" ");
    if (estado != estadoAnterior ){  // comparamos el estado actual
      contador = 0;                   // reiniciamos el contador
      estadoAnterior = estado;
    }
    else{
      contador = contador +1;       // aumentamos el contador en 1
    }
    delay (1);
  }
  while (contador < tiempoAntirebote);
  return estado;
  //Serial.clear();
}




void foto(){
  int aux1, aux2;
  aux1 = 1000*exposition;
  aux2 = 1000*time;
  for (int i=0;i<quantity;i++){
    digitalWrite(LED1, HIGH);
    delay(1000); // Valor propio
    digitalWrite(LED2, HIGH);
    delay(aux1);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    delay(aux2);
  }
  op = 0;
  quantity = 0;
  time = 0;
  exposition = 0;
}



int opcion(int dato){
  if (antirebote(b3) && dato == 0){
      dato=0;
    }
   
   
    if (antirebote(b3) && dato > 0){
      dato -= 1;
   
     }
  
    if (antirebote(b2) && dato < 5){
      dato += 1;
   
    }
    
    if (antirebote(b2) && dato == 5){
      dato = 5;
   
    }
   
    if (antirebote(b1)){
      if (op > 0)
      	op -= 1;
    }
   
  
    if (antirebote(b4)){
      op += 1;
     
    }
  return dato;
}



void loop(){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    if (op == 0){
      delay(lag);
      lcd.setCursor(0,0);
      lcd.print("Cantidad:");
      lcd.setCursor(0,1);
      lcd.print(quantity);
      lcd.print("              ");
      quantity = opcion(quantity);
    }
    if (op == 1){
      lcd.setCursor(0,0);
      lcd.print("Tiempo:    ");
      lcd.setCursor(0,1);
      lcd.print(time);
      lcd.print("s              ");

      time = opcion(time);

    }
    if (op == 2){
      lcd.setCursor(0,0);
      lcd.print("Exposicion:     ");
      lcd.setCursor(0,1);
      lcd.print(exposition);
      lcd.print("s             ");
       exposition = opcion(exposition);
    }

    if (op == 3){
      lcd.setCursor(0,0);
      lcd.print("Sensor: Activar");
      lcd.setCursor(0,1);
      lcd.print("Atras: No");
      if ((analogRead(pResistor))>500){
        lcd.setCursor(0,0);
        lcd.print("Tomando fotos:     ");
        lcd.setCursor(0,1);
        lcd.print(quantity);
        lcd.print(" f- ");
        lcd.print(time);
        lcd.print(" s- ");
        lcd.print(exposition);
        lcd.print(" e  ");
        foto();
      }
      if (antirebote(b1)){
        op = 2;
      }
    }
  }