#include <Ultrasonic.h>
#include <ESP8266WiFi.h>

WiFiServer server(80);

//DEFININDO O ECHO E O TRIGGER DO SENSOR ULTRASSONICO
#define TRIGGER_PIN  D7
#define ECHO_PIN     D10

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

//SSD DA REDE
const char* ssid = "Vaval";
const char* password = "88172947";

String result; //VARIÁVEL QUE MOSTRA O RESULTADO
int temp; //VARIÁVEL QUE MOSTRA O TEMPO DE LEITURA
float dist; //VARIÁVEL QUE MOSTRA DISTÂNCIA
int PWMAC; //CONVERTE DISTÂNCIA PARA DUTY CICLE
float ERRO; //ERRO DA MALHA
float ERRO1; //ERRO DA MALHA
int SETP; //SETPOINT
float AC; //AÇÃO DE CONTROLE
float MV; //VARIÁVEL MANIPULADA
float KP; //CONSTANTE CONTROLE PROPORCIONAL
float KI; //CONSTANTE CONTROLE INTEGRAL
float KD; //CONSTANTE CONTROLE DERIVATIVO
float INTEGRAL; //INTEGRAL DO ERRO PARA O CONTROLE EM FUNÇÃO DO TEMPO
float DERIVADA; //DERIVADA DO ERRO PARA O CONTROLE EM FUNÇÃO DO TEMPO
long microsec;

void setup() {
  Serial.begin(9600);
  //ZERANDO AS VARIAVEIS NO INICIO
  SETP=0;
  AC=0;
  MV=0;
  ERRO=0;
  INTEGRAL=0;
  DERIVADA=0;
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");
  
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
    // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  while (!client.available()) {
    delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');

  // Match the request
  if (request.indexOf("SETP=0") != -1) {
    SETP = 0;
  }
  if (request.indexOf("SETP=10") != -1) {
    SETP = 10;
  }
  if (request.indexOf("SETP=20") != -1) {
    SETP = 20;
  }
  if (request.indexOf("SETP=30") != -1) {
    SETP = 30;
  }
  if (request.indexOf("SETP=40") != -1) {
    SETP = 40;
  }
  if (request.indexOf("SETP=50") != -1) {
    SETP = 50;
  }
  if (request.indexOf("SETP=60") != -1) {
    SETP = 60;
  }
  if (request.indexOf("SETP=70") != -1) {
    SETP = 70;
  }
  if (request.indexOf("SETP=80") != -1) {
    SETP = 80;
  }
  if (request.indexOf("SETP=90") != -1) {
    SETP = 90;
  }
  if (request.indexOf("SETP=100") != -1) {
    SETP = 100;
  }

  //LENDO A DISTANCIA DADA PELO SENSOR ULTRASSONICO
  microsec = ultrasonic.timing();
  dist = ultrasonic.convert(microsec, Ultrasonic::CM);
  delay(50);
  

  MV=140.82-(8.02*dist); //TRANSFORMANDO A DISTANCIA DADA DE 0 A 100%
  if(MV>100) {
    MV=100; //CASO A RESPOSTA DO CALCULO DO MV SEJA MAIOR QUE 255 FORÇA O RESULTADO COMO 255
  }
  else if (MV<0) {
    MV=0; //CASO A RESPOSTA DO CALCULO DO MV SEJA MENOR QUE 0 FORÇA O RESULTADO COMO 0
  }
  else {
    MV=MV; //CASO A RESPOSTA DO CALCULO DO MV ESTEJA ENTRE O E 255 CONTINUA COM O VALOR CALCULADO
  }
  //DEFININDO OS ERROS PARA O  CONTROLE DERIVATIVO
  ERRO1=ERRO;
  ERRO=SETP-MV;

  //DEFINIR AS CONSTANTES
  KP=2;
  KI=0.25;
  KD=1;

  //CALCULAR A INTEGRAL E A DERIVADA
  INTEGRAL=INTEGRAL+ERRO*1.15;
  DERIVADA=(ERRO1-ERRO)/1.15;

  //ACAO DE CONTROLE
  AC=KP*ERRO+KI*INTEGRAL+KD*DERIVADA;

  if(AC>100) {
    AC=100; //CASO A RESPOSTA DO CALCULO DO DUTY CICLE SEJA MAIOR QUE 255 FORÇA O RESULTADO COMO 255
  }
  else if (AC<0) {
    AC=0; //CASO A RESPOSTA DO CALCULO DO DUTY CICLE SEJA MENOR QUE 0 FORÇA O RESULTADO COMO 0
  }
  else {
    AC=AC; //CASO A RESPOSTA DO CALCULO DO DUTY CICLE ESTEJA ENTRE O E 255 CONTINUA COM O VALOR CALCULADO
  }

  PWMAC = map(AC,0,100,0,1023); //CONVERTE A ACAO DE CONTROLE PARA DUTY CICLE
  analogWrite(D4, PWMAC); //IMPRIME O VALOR DA AÇÃO DE CONTROLE NA PORTA PWM 4

  Serial.print("SetPoint= "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(SETP); //IMPRIME NO MONITOR SERIAL A DISTÂNCIA MEDIDA
  Serial.print("%  "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print("MV= "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(MV); //IMPRIME NO MONITOR SERIAL A DISTÂNCIA MEDIDA
  Serial.print("%  "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print("Erro= "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(ERRO); //IMPRIME NO MONITOR SERIAL A DISTÂNCIA MEDIDA
  Serial.print("%  "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print("Integral= "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(INTEGRAL); //IMPRIME NO MONITOR SERIAL A DISTÂNCIA MEDIDA
  Serial.print(" "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print("Derivada= "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(DERIVADA); //IMPRIME NO MONITOR SERIAL A DISTÂNCIA MEDIDA
  Serial.print(" "); //IMPRIME O TEXTO NO 
  Serial.print("AC= "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(AC); //IMPRIME O TEXTO NO MONITOR SERIALTÂNCIA MEDIDA
  Serial.print("%  "); //IMPRIME O TEXTO NO 
  Serial.print("dist= "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(dist); //IMPRIME O TEXTO NO MONITOR SERIALTÂNCIA MEDIDA
  Serial.print("cm  "); //IMPRIME O TEXTO NO 
  Serial.print("PWMAC= "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.println(PWMAC); //IMPRIME O TEXTO NO MONITOR SERIALTÂNCIA MEDIDA

  //MONTAGEM DA INTERFACE WEB
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); // do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta charset ='utf-8'/>");
  client.println("<meta http-equiv='refresh' content='2'/>");
  client.println("<meta name = 'viewport' content = 'width=device-width, initial-scale=1'>");
  client.println("</head>");
  client.println(F("<link href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.1/css/bootstrap.min.css' rel='stylesheet'></link>"));
  client.println("<div class='jumbotron'>");
  client.println("<h1 class='text-center'>Controle de Nivel, com PID, e Interface IHM</h1>");
  client.println("<h2 class='text-center'>ESP8266</h2>");
  client.println("</div>");
  client.println("<div class='col-md-6'>");
  client.println("<div class='alert alert-info text-center' role='alert'>VARIAVEIS GLOBAIS");
  client.println("<br>");
  client.println("MV= ");
  client.println(MV);
  client.println("%");
  client.println("<br>");
  client.println("SP= ");
  client.println(SETP);
  client.println("%");
  client.println("<br>");
  client.println("ERRO= ");
  client.println(ERRO);
  client.println("%");
  client.println("<br>");
  client.println("AC= ");
  client.println(AC);
  client.println("%");
  client.println("</div>");
  client.println("<div class='alert alert-info text-center' role='alert'>SET POINT</div>");
  client.println("<a class='btn btn-success btn-lg center-block' href=\"/SETP=0\"> 0% </a>");
  client.println("<br>");
  client.println("<a class='btn btn-success btn-lg center-block' href=\"/SETP=10\"> 10% </a>");
  client.println("<br>");
  client.println("<a class='btn btn-success btn-lg center-block' href=\"/SETP=20\"> 20% </a>");
  client.println("<br>");
  client.println("<a class='btn btn-success btn-lg center-block' href=\"/SETP=30\"> 30% </a>");
  client.println("<br>");
  client.println("<a class='btn btn-success btn-lg center-block' href=\"/SETP=40\"> 40% </a>");
  client.println("<br>");
  client.println("<a class='btn btn-success btn-lg center-block' href=\"/SETP=50\"> 50% </a>");
  client.println("<br>");
  client.println("<a class='btn btn-success btn-lg center-block' href=\"/SETP=60\"> 60% </a>");
  client.println("<br>");
  client.println("<a class='btn btn-success btn-lg center-block' href=\"/SETP=70\"> 70% </a>");
  client.println("<br>");
  client.println("<a class='btn btn-success btn-lg center-block' href=\"/SETP=80\"> 80% </a>");
  client.println("<br>");
  client.println("<a class='btn btn-success btn-lg center-block' href=\"/SETP=90\"> 90% </a>");
  client.println("<br>");
  client.println("<a class='btn btn-success btn-lg center-block' href=\"/SETP=100\"> 100% </a>");
  client.println("<br>");
  client.println("</div>");
  client.println("</html>");
}
