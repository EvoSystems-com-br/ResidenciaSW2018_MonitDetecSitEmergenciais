#include "SIM808_methods.h"

//Telefone para enviar a mensagem
#define PHONE "+551197694****"

//Mensagem com latitude e longitude
char MESSAGE[300];
char lat[12];
char lon[12];

//Comunicacao serial com o SIM808
//PIN RX 16
//PIN TX 17
HardwareSerial Serial2(2);

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);

  //Iniciando comunicacao com o SIM808
  while(!sim808_AT()) {
    delay(1000);
    Serial.print("Sem comunicacao\r\n");
  }
  Serial.println("SIM808 conectado!");
  Serial.println("Ligando GPS...");

  //Ligando GPS
  while(!sim808_turnon_GPS()) {
    delay(1000);
    Serial.print("Problema ao ligar GPS...\r\n");
  }
  Serial.println("GPS ligado com sucesso!");
}

void loop() {
  
  //Ler dados GPS do SIM808
  if(sim808_gotGPS()) {
    Serial.print(sim808.GPSdata.year);
    Serial.print("/");
    Serial.print(sim808.GPSdata.month);
    Serial.print("/");
    Serial.print(sim808.GPSdata.day);
    Serial.print(" ");
    Serial.print(sim808.GPSdata.hour);
    Serial.print(":");
    Serial.print(sim808.GPSdata.minute);
    Serial.print(":");
    Serial.print(sim808.GPSdata.second);
    Serial.print(":");
    Serial.println(sim808.GPSdata.centisecond);
    Serial.print("latitude :");
    Serial.println(sim808.GPSdata.lat);
    Serial.print("longitude :");
    Serial.println(sim808.GPSdata.lon);
    Serial.print("speed_kph :");
    Serial.println(sim808.GPSdata.speed_kph);
    Serial.print("heading :");
    Serial.println(sim808.GPSdata.heading);
    Serial.println();
    
    Serial.println("Mandando mensagem para %s com conteudo:\n", PHONE);
    sprintf(MESSAGE, "Latitude : %s\nLongitude : %s\n", lat, lon);

    //Enviando mensagem
    sim808_sendSMS(PHONE,MESSAGE);

    //Desligando GPS
    while(!sim808_turnoff_GPS()) {
      delay(1000);
      Serial.print("Problema ao desligar GPS...\r\n");
    }
    Serial.println("GPS desligado com sucesso!");
  }
}
