#include "SIM808_methods.h"

HardwareSerial *serialGPS = NULL;

char serial_data[100];
int pos = 0;

SIM808_methods::SIM808_methods(HardwareSerial *mySerial){
  serialGPS = mySerial;
}

bool SIM808_methods::init(void) {
  delay(500);
  serialGPS->println("AT\n");
  delay(500);
  if(!strcmp(read_buffer("AT", 2), "OK") == 0)
    return false;
  serialGPS->println("AT+CFUN=1\n"); //Phone Functionality (1 = Full)
  delay(500);
  if(!strcmp(read_buffer("AT+CFUN=1", 9), "OK") == 0)
    return false;  
  return true;
}

bool SIM808_methods::SIM_status(void) {
  delay(500);
  serialGPS->println("AT+CPIN?\n"); //Esperando resposta READY
  delay(500);
  if(!strcmp(read_buffer("AT+CPIN?", 8), "READYOK") == 0)
    return false;
  return true;
}

bool SIM808_methods::turnon_GPS(void) {
  delay(500);
  serialGPS->println("AT+CGPSPWR=1\n");
  delay(500);
  if(!strcmp(read_buffer("AT+CGPSPWR=1", 12), "OK") == 0)
    return false;
  return true;
}

bool SIM808_methods::turnoff_GPS(void) {
  delay(500);
  serialGPS->println("AT+CGPSPWR=0\n");
  delay(500);
  if(!strcmp(read_buffer("AT+CGPSPWR=0", 12), "OK") == 0)
    return false;
  return true;
}

bool SIM808_methods::GPS_status(void) {
  delay(500);
  serialGPS->println("AT+CGPSSTATUS?");
  delay(500);
  if(!strcmp(read_buffer("AT+CGPSSTATUS?", 14), "Location3DFixOK") == 0)
    return false;
  return true;
}

void SIM808_methods::read_GPS(void) {
  int comma = 0, aux = 0;
  delay(500);
  serialGPS->println("AT+CGPSINF=0");
  delay(500);
  Serial.println(read_buffer("AT+CGPSINF=0", 12));
  for(int i = 0; i < pos-2; i++) {
    if(serial_data[i] == ',') {
      comma++;
      aux = 0;
    }
    else {
      if(comma == 1)
        GPSdata.lon[aux++] = serial_data[i];
      if(comma == 2)
        GPSdata.lat[aux++] = serial_data[i];
      if(comma == 3)
        GPSdata.alt[aux++] = serial_data[i];
      if(comma == 4)
        GPSdata.utc[aux++] = serial_data[i];
      if(comma == 7)
        GPSdata.speed_knots[aux++] = serial_data[i];
      if(comma == 8)
        GPSdata.heading[aux++] = serial_data[i];
    }
  }
}

bool SIM808_methods::send_SMS(char *PHONE, char *MESSAGE) {

  delay(500);
  serialGPS->println("AT+CMGF=1\r\n");
  delay(500);
  if(!strcmp(read_buffer("AT+CMGF=1", 9), "OK") == 0)
    return false;
    
  delay(500);
  serialGPS->println("AT+CSCS=\"GSM\"\r\n");
  delay(500);
  if(!strcmp(read_buffer("AT+CSCS=\"GSM\"", 13), "OK") == 0)
    return false;
    
  serialGPS->write("AT+CMGS=\"");
  serialGPS->write(PHONE);
  serialGPS->write("\"\r\n");
  delay(1000);
  if(!wait_response('>'))
    return false;
  serialGPS->write(MESSAGE);
  serialGPS->write("\r\n");
  delay(500);
  serialGPS->write((char)26);
  serialGPS->write("\r\n");
  delay(5000);
  read_buffer("+", 1);
  if(serial_data[pos-2] == 'O') {
    if(serial_data[pos-1] == 'K')
      return true;
  }
  return false;
}

void SIM808_methods::reset_buffer(void) {
  memset(serial_data, 0, sizeof(serial_data));
  pos = 0;
}

char* SIM808_methods::read_buffer(char* msg_sent, int msg_size) {

  char c;

  reset_buffer();
  
  while (serialGPS->available()) {
    c = serialGPS->read();
    if ((c != '\n')&&(c != '\r')&&(c != ' ')) {
      serial_data[pos++] = c;
      if(c == ':')
        reset_buffer();
      if((pos == msg_size)&&(strcmp(serial_data, msg_sent) == 0))
        reset_buffer();
    }
  }
  
  return serial_data;
  
}

bool SIM808_methods::wait_response(char r) {

  char c;
  
  reset_buffer();
  
  while (serialGPS->available()) {
    c = serialGPS->read();
    if (c == r)
      return true;
  }
  return false;
}
