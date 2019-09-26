#include <Ultrasonic.h>
const int echoPin = 7; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin = 8; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
 
Ultrasonic ultrasonic(trigPin,echoPin); //INICIALIZANDO OS PINOS DO ARDUINO
 
float distancia; //VARIÁVEL DO TIPO INTEIRO
String result; //VARIÁVEL DO TIPO STRING 
float dist;
int i;
int conver;
void setup(){
  Serial.begin(9600);
}
void loop(){
  dist = 0;
  for(i=0;i<=1000;i++){
  hcsr04(); // FAZ A CHAMADA DO MÉTODO "hcsr04()"
  dist=dist+distancia;
  delayMicroseconds(100);
  }
  dist=dist/1000;
  conver = (19.22*dist)-75.72;
  if(conver>255) {
    conver=255;
  }
  else if (conver<0) {
    conver = 0;
  }
  else {
    conver = conver;
  }
  analogWrite(3, conver);
  Serial.print("Distancia= "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(dist); ////IMPRIME NO MONITOR SERIAL A DISTÂNCIA MEDIDA
  Serial.print("cm  "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print("PWM= ");
  Serial.println(conver);
 
}
//MÉTODO RESPONSÁVEL POR CALCULAR A DISTÂNCIA
void hcsr04(){
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
    delayMicroseconds(2); //INTERVALO DE 2 MICROSSEGUNDOS
    digitalWrite(trigPin, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
    delayMicroseconds(10); //INTERVALO DE 10 MICROSSEGUNDOS
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
    //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
    //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
    //NA VARIAVEL "distancia"
    distancia = (ultrasonic.Ranging(CM)); //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
    result = String(distancia); //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
    delayMicroseconds(100); //INTERVALO DE 500 MILISSEGUNDOS
 }
