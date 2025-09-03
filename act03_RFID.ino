#include "TIEMPO.h"
tiempoClass tiempo;
#include "MQTT.h"
mqttClass mqtt;

#include "RFID.h"
SistemaRFID sistemaRFID;

const int pinLEDVerde = 2;
const int pinLEDRojo = 3;
const int pinLEDAzul = 5;

void setup() {
  Serial.begin(115200);
  mqtt.mqttSetup();
  tiempo.configTiempo();

  Serial.println("Sistema de Control de Acceso RFID - Iniciando...");
  
  pinMode(pinLEDVerde, OUTPUT);
  pinMode(pinLEDRojo, OUTPUT);
  pinMode(pinLEDAzul, OUTPUT);

  sistemaRFID.iniciar();

  digitalWrite(pinLEDVerde, LOW);
  digitalWrite(pinLEDRojo, LOW);
  digitalWrite(pinLEDAzul, LOW);
  
  Serial.println("Sistema listo. Acerque una tarjeta RFID...");
}

void loop() {
  String uid = sistemaRFID.obtenerUIDTarjeta();
  
  if(uid != "") {
    Serial.print("UID detectado: ");
    Serial.println(uid);
    
    int resultado = sistemaRFID.validarTarjeta(uid);
    
    if(resultado != -1) {
      Serial.println("Tarjeta AUTORIZADA detectada");
      
      bool estadoAnterior = sistemaRFID.tarjetaEstaDentro(uid);
      bool accesoProcesado = sistemaRFID.procesarAcceso(uid);
      bool estadoActual = sistemaRFID.tarjetaEstaDentro(uid);
      
      if(accesoProcesado) {
        if(estadoAnterior != estadoActual) {
          if(estadoActual) {
            sistemaRFID.mostrarEstadoActual(resultado);
            Serial.println("ACCESO PERMITIDO - ENTRADA");
            mqtt.mqttMensaje(sistemaRFID.Integrantes[resultado], "Entrada");
          } else {
            sistemaRFID.mostrarEstadoActual(resultado);
            Serial.println("ACCESO PERMITIDO - SALIDA");
            mqtt.mqttMensaje(sistemaRFID.Integrantes[resultado], "Salida");
            mqtt.mqttMensaje(sistemaRFID.Integrantes[-1], "Salida");
          }
        } else {
          // Intento de entrada/salida consecutivo
          sistemaRFID.mostrarEstadoActual(resultado);
          Serial.println("ERROR: Debe completar el ciclo anterior primero");
          mqtt.mqttMensaje(sistemaRFID.Integrantes[resultado], "Tarjeta Rechazada, completar el ciclo anterior primero");
        }
      }
    } else {
      Serial.println("TARJETA NO AUTORIZADA - ACCESO DENEGADO");
      mqtt.mqttMensaje(sistemaRFID.Integrantes[resultado], "Tarjeta Rechazada");
    }
    delay(2000); 
  }
  
  delay(100);
}