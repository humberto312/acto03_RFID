#ifndef RFID_H
#define RFID_H

#include <SPI.h>
#include <MFRC522.h>

#define PIN_SS 10
#define PIN_RST 9

class SistemaRFID {
private:
  MFRC522 lectorRFID;
  bool tarjetasRegistradas[5];  // Estado de registro de cada tarjeta
  String ultimoUIDEscaneado;
  String convertirUIDaString(byte *buffer, byte bufferSize);
  
public:
  struct UIDAutorizados{
    String uid;
    String nombre;
    String color;
    String num_cuenta;
    bool estadosAcceso; //Afuera = false, adentro = true
  };
  UIDAutorizados Integrantes[5];
  SistemaRFID();
  void iniciar();
  bool verificarTarjetaPresente();
  String obtenerUIDTarjeta();
  int validarTarjeta(String uid);
  bool procesarAcceso(String uid);
  void reiniciarSistema();
  String obtenerUltimoUID();
  bool tarjetaEstaDentro(String uid);
  void mostrarEstadoActual(int);
};

#endif