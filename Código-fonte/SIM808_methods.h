#ifndef SIM808_H
#define SIM808_H

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class SIM808_methods {
  public:
    SIM808_methods(HardwareSerial *mySerial);
    bool init(void);
    bool SIM_status(void);
    bool turnon_GPS(void);
    bool turnoff_GPS(void);
    bool GPS_status(void);
    void read_GPS(void);
    bool send_SMS(char* PHONE, char* MESSAGE);

    struct gspdata{
      char utc[24];
      char lat[16];
      char lon[16];
      char alt[16];
      char speed_knots[16];
      char heading[16];      
    }GPSdata;

  private:
    void reset_buffer(void);
    char* read_buffer(char* msg_sent, int msg_size);
    bool wait_response(char r);
};


#endif
