#include "SIM808_methods.h"

//Telefone para enviar a mensagem
#define PHONE "+551197694****"

//Mensagem com latitude e longitude
char MESSAGE[300];
char lat[12];
char lon[12];
bool testeSMS = false;
bool teste = true;

//Comunicacao serial com o SIM808
//PIN RX 16
//PIN TX 17
HardwareSerial Serial2(2);

SIM808_methods class_sim808(&Serial2);

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);

  //Iniciando comunicacao com o SIM808
  while(!(class_sim808.init())) {
    delay(1000);
    Serial.print("\r\nSem comunicacao\r\n");
  }
  Serial.println("\r\nSIM808 conectado!");
  Serial.println("Ligando GPS...");

  //Ligando GPS
  while(!(class_sim808.turnon_GPS())) {
    delay(1000);
    Serial.print("Problema ao ligar GPS...\r\n");
  }
  Serial.println("GPS ligado com sucesso!");
}

void loop() {
  /*if (Serial2.available()) {
    Serial.write(Serial2.read());
  }
  if (Serial.available()) {
    while(Serial.available()) {
      Serial2.write(Serial.read());
    }
  }*/

  if(testeSMS) {
    if(class_sim808.send_SMS(PHONE,"teste"))
      Serial.println("Sucesso");

    //Desligando GPS
    delay(500);
    while(!(class_sim808.turnoff_GPS())) {
      delay(1000);
      Serial.print("Problema ao desligar GPS...\r\n");
    }
    Serial.println("GPS desligado com sucesso!");
    testeSMS = false;
  }
   
  //Ler dados GPS do SIM808
  if((class_sim808.GPS_status())&&(teste)) {

    class_sim808.read_GPS();

    Serial.print("\n utc :");
    Serial.println(class_sim808.GPSdata.utc);
    Serial.print("latitude :");
    Serial.println(class_sim808.GPSdata.lat);
    Serial.print("longitude :");
    Serial.println(class_sim808.GPSdata.lon);
    Serial.print("altitude :");
    Serial.println(class_sim808.GPSdata.alt);
    Serial.print("speed_knots :");
    Serial.println(class_sim808.GPSdata.speed_knots);
    Serial.print("heading :");
    Serial.println(class_sim808.GPSdata.heading);

    float la = atof(class_sim808.GPSdata.lat);
    Serial.println(la);
    dtostrf(la, 4, 6, lat); //put float value of la into char array of lat. 4 = number of digits before decimal sign. 6 = number of digits after the decimal sign.
    
    Serial.print("Mandando mensagem para ");
    Serial.print(PHONE);
    Serial.println(" com conteudo:\n");
    sprintf(MESSAGE, lat);

    //Enviando mensagem
    class_sim808.send_SMS(PHONE,MESSAGE);

    //Desligando GPS
    delay(500);
    while(!(class_sim808.turnoff_GPS())) {
      delay(1000);
      Serial.print("Problema ao desligar GPS...\r\n");
    }
    Serial.println("GPS desligado com sucesso!");
  }
  delay(1000);
}
