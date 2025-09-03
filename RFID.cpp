#include "RFID.h"
#include <SPI.h>

SistemaRFID::SistemaRFID() : lectorRFID(PIN_SS, PIN_RST) {

  UIDAutorizados Integrantes [5] = {
    {"A1B2C3D4", "Noemi Galicia", "Morado", "20195268", false},
    {"E5F6G7H8", "José Raúl Herrera", "Azul", "20156348", false},
    {"I9J0K1L2", "José Alejandro Ramirez", "Verde", "20196833", false},
    {"I09EABL8", "Humberto Mateus", "Amarillo", "20196823", false},
    {"B7UIEBA2", "Juan Manuel Calvillo", "Rosa", "20196457", false}
  };

  // Inicializar estados
  for(int i = 0; i < 3; i++) {
    tarjetasRegistradas[i] = false;
    Integrantes[i].estadosAcceso = false; // Todas las tarjetas empiezan fuera
  }
  ultimoUIDEscaneado = "";
}

void SistemaRFID::iniciar() {
  SPI.begin();
  lectorRFID.PCD_Init();
  delay(4);
  lectorRFID.PCD_DumpVersionToSerial();
}

bool SistemaRFID::verificarTarjetaPresente() {
  // Verificar si hay una nueva tarjeta presente
  if (!lectorRFID.PICC_IsNewCardPresent()) {
    return false;
  }
  
  // Leer la tarjeta
  if (!lectorRFID.PICC_ReadCardSerial()) {
    return false;
  }
  
  return true;
}

//Originalmente un UID es {0x12, 0x34, 0xAB, 0xCD}
//Si se convierte a string es más fácil su comparación: "1234ABCD"
String SistemaRFID::convertirUIDaString(byte *buffer, byte bufferSize) {
  String uidString = "";
  for (byte i = 0; i < bufferSize; i++) {
    if (buffer[i] < 0x10) {
      uidString += "0";
    }
    uidString += String(buffer[i], HEX);
    uidString.toUpperCase();
  }
  return uidString;
}

String SistemaRFID::obtenerUIDTarjeta() {
  if (verificarTarjetaPresente()) {
    ultimoUIDEscaneado = convertirUIDaString(lectorRFID.uid.uidByte, lectorRFID.uid.size);
    lectorRFID.PICC_HaltA(); // Detener comunicación con tarjeta
    return ultimoUIDEscaneado;
  }
  return "";
}
//***********************************************
int SistemaRFID::validarTarjeta(String uid) {
  // Buscar el UID en la lista de autorizados
  for(int i = 0; i < 3; i++) {
    if(uid == Integrantes[i].uid) {
      tarjetasRegistradas[i] = true;
      return i; // Retorna el índice de la tarjeta autorizada
    }
  }
  return -1; // Tarjeta no autorizada
}

bool SistemaRFID::procesarAcceso(String uid) {
  int indiceTarjeta = validarTarjeta(uid);
  
  if(indiceTarjeta == -1) {
    return false; // Tarjeta no autorizada
  }
  
  // No se permiten dos entradas/salidas consecutivas
  if(Integrantes[indiceTarjeta].estadosAcceso) {
    // Tarjeta está dentro → intenta salir
    Integrantes[indiceTarjeta].estadosAcceso = false;
    return true;
  } else {
    // Tarjeta está fuera → intenta entrar
    Integrantes[indiceTarjeta].estadosAcceso = true;
    return true;
  }
}

bool SistemaRFID::tarjetaEstaDentro(String uid) {
  int indiceTarjeta = validarTarjeta(uid);
  if(indiceTarjeta != -1) {
    return Integrantes[indiceTarjeta].estadosAcceso;
  }
  return false;
}

String SistemaRFID::obtenerUltimoUID() {
  return ultimoUIDEscaneado;
}

void SistemaRFID::reiniciarSistema() {
  for(int i = 0; i < 3; i++) {
    Integrantes[i].estadosAcceso = false;
  }
  ultimoUIDEscaneado = "";
}

void SistemaRFID::mostrarEstadoActual(int index) {
  Serial.println("=== ESTADO DE LA TARJETA ===");
  Serial.println(Integrantes[index].uid);
  Serial.println(Integrantes[index].nombre);
  Serial.println(Integrantes[index].num_cuenta);
  Serial.println(Integrantes[index].color);
  Serial.println(Integrantes[index].estadosAcceso ? "DENTRO" : "FUERA");
  Serial.println("=================================");
}