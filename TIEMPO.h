#ifndef TIEMPO_H
#define TIEMPO_H

#include "time.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -21600;
const int   daylightOffset_sec = 0;

class tiempoClass{ 
  public:
    void configTiempo(void);
    String obtenerFecha();
    String obtenerHora();
};

void tiempoClass::configTiempo(){
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

String tiempoClass::obtenerFecha(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return "";
  }
  char fechaBuffer[11]; // "DD/MM/YYYY"
  strftime(fechaBuffer, sizeof(fechaBuffer), "%d/%m/%Y", &timeinfo);
  return String(fechaBuffer);
}

String tiempoClass::obtenerHora(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return "";
  }
  char horaBuffer[9]; // "HH:MM:SS"
  strftime(horaBuffer, sizeof(horaBuffer), "%H:%M:%S", &timeinfo);
  return String(horaBuffer);
}

#endif