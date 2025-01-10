#include <SoftwareSerial.h>
int rele = 6;
int rele2 = 7;
int rele3 = 8;
SoftwareSerial HC12(4,5); // HC-12 TX Pin, HC-12 RX Pin
char a;
void setup() {
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(rele, 1);
  digitalWrite(rele2, 1);
  digitalWrite(rele3, 1);
  HC12.begin(9600);               // Serial port to HC12
}
void loop() {
  while(HC12.available()){
    a=HC12.read();
    switch (a) {

      case 'a':
        digitalWrite(rele, 1);
        HC12.println("Spento");
        break;

      case 'A':
        digitalWrite(rele, 0);
        HC12.println("Acceso");
        break;

      case 'b':
        digitalWrite(rele2, 1);
        HC12.println("Spento");
        break;

      case 'B':
        digitalWrite(rele2, 0);
        HC12.println("Acceso");
        break;

      case 'c':
        digitalWrite(rele3, 1);
        HC12.println("Spento");
        break;

      case 'C':
        digitalWrite(rele3, 0);
        HC12.println("Acceso");
        break;

      default:
        HC12.println("Comando non valido");
        break;
    }  
  }
}

