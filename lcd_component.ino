#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int pinSubir = 4;
const int pinBajar = 3;
const int pinValidar = A1;
const int pinIniciar = 9;
const int pinModificar = 2;
const int pinEnfoque = 6;
const int pinDisparo = 5;


int intervalo = 3;
int exposicion = 200;
int numFotos = 10;
int bulb = 0;
int presionado = 0;
int op = 0;
int modificando = 0;



void setup()  {
  lcd.begin(16, 2); 
  pinMode(pinSubir, INPUT);
  pinMode(pinBajar, INPUT);
  pinMode(pinValidar, INPUT);
  pinMode(pinEnfoque, OUTPUT);
  pinMode(pinIniciar, INPUT);
  pinMode(pinDisparo, OUTPUT);
  pinMode(pinModificar, INPUT);
  imprimir("Intervalo");
}
  
  int valor() {
    if (op == 0)
    	return intervalo;
    else if (op == 1)
      return numFotos;
    else if (op == 2)
      return exposicion;
    else
     return bulb;
  }


void disparo_enfoque(int pin, int tiempo){
  digitalWrite(pin, HIGH);
  delay(tiempo);
  digitalWrite(pin, LOW);
  delay(tiempo);
}

void rafaga() {
  for(int i = 0; i < numFotos; i++) {
    lcd.clear();
    lcd.print("Tomando fotos: ");
    lcd.setCursor(2, 6);
    lcd.print(i+1);
    lcd.print("/");
    lcd.print(numFotos);
    disparo_enfoque(pinDisparo, exposicion);
    delay(intervalo*1000);
  }
  subir();
  bajar();
  
}

void modoBulb() {
if (presionado)
  digitalWrite(pinDisparo, HIGH);
else
  digitalWrite(pinDisparo, LOW);
}

void imprimir(char *m) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(m);
  lcd.print(":");
  lcd.print("   ");
  lcd.setCursor(5,1);
  lcd.print(valor());
   lcd.print("   ");
}

void subir() {
  if (op == 0) {
    op = 1;
    imprimir("Cantidad");
  } else if (op == 1) {
    op = 2;
    imprimir("Exposicion");
  } else if (op == 2) {
    op = 3;
    imprimir("Bulb");
  } else {
    op = 0;
    imprimir("Intervalo");
  }
}

void bajar() {
  if (op == 0) {
    op = 3;
    imprimir("Bulb");
  } else if (op == 1) {
    op = 0;
    imprimir("Intervalo");
  } else if (op == 2){
    op = 1;
    imprimir("Cantidad");
  } else {
    op = 2;
    imprimir("Exposicion");
  }
  
}

void subirModificando() {
  if (op == 0) {
    intervalo += 1;
    imprimir("Intervalo");
  } else if (op == 1) {
    numFotos += 1;
    imprimir("Cantidad");
  } else if (op == 2) {
    exposicion += 50;
    imprimir("Exposicion");
  } else if (op == 3) {
    if (bulb == 0)
      bulb = 1;
    else
      bulb = 0;
    imprimir("Bulb");
  }
}

void bajarModificando() {
  if (op == 0) {
    intervalo -= 1;
    imprimir("Intervalo");
  } else if (op == 1) {
    numFotos -= 1;
    imprimir("Cantidad");
  } else if (op == 2) {
    exposicion -= 50;
    imprimir("Exposicion");
  } else if (op == 3) {
    if (bulb == 0)
      bulb = 1;
    else
      bulb = 0;
    imprimir("Bulb");
  }
}

void validar() {
 
}


void loop() {
  if (digitalRead(pinModificar)) {
    if (modificando == 0) {
      modificando = 1;
      lcd.blink();
    } else {
      modificando = 0;
      lcd.noBlink();
    }
   delay(200);
  }
  
  if (digitalRead(pinSubir)) {
    if (modificando == 0) 
      subir();
    else
      subirModificando();
    delay(200);
  }
  
if (digitalRead(pinBajar)) {
    if (modificando == 0) 
      bajar();
    else
      bajarModificando();
    delay(200);
  }
  
  if (digitalRead(pinIniciar)) {
    if (bulb == 0) {
    	disparo_enfoque(pinEnfoque, 200);
    	rafaga();
    } else {
      disparo_enfoque(pinEnfoque, 200);
      presionado = 1 - presionado;
      modoBulb();
    }
  }
}