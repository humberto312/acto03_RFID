#ifndef MQTT_H
#define MQTT_H

#include "WiFi.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>

WiFiClient espClient;
PubSubClient client(espClient);

class mqttClass{
  public:
    char* mqtt_server = "test.mosquitto.org";
    int mqtt_port = 1883;
    char* mqtt_topic = "rgcvh/registro";

    void mqttSetup(void);
    void mqttMensaje(Integrante &integrante, String accion);
    void reconnect(void);
};

void mqttClass::mqttSetup(){
  WiFi.mode(WIFI_STA);
  WiFi.begin("Poco F7","pocoF7W!F!pa$word"); // Cambiar a la red que vamos a usar
  Serial.println("Comenzando Conexión");
  while(WiFi.status()!= WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado a WiFi, IP Asignada: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, mqtt_port);

  Serial.print("Conectado al servidor ");
  Serial.print(mqtt_server);
  Serial.print(":");
  Serial.println(mqtt_port);
  Serial.print("Topico: ");
  Serial.println(mqtt_topic);
  delay(1000);
}

void mqttClass::mqttMensaje(Integrantes &integrante, String accion){
  StaticJsonDocument<200> doc;

  Serial.println("");
  doc["nombreEquipo"] = "RGCVH";
  doc["nombreIntegrante"] = integrante.nombre;
  doc["id"] = integrante.uid;

  JsonObject evento = doc.createNestedObject("evento");
  evento["accion"] = accion;
  evento["fecha"] = tiempo.obtenerFecha();
  evento["hora"] = tiempo.obtenerHora();

  char jsonBuffer[200];
  serializeJson(doc, jsonBuffer);

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (client.publish(mqtt_topic, jsonBuffer)) {
    Serial.print("Publicando mensaje: ");
    Serial.println(jsonBuffer);
  } else {
    Serial.println("Fallo al publicar el mensaje.");
  }
}

void mqttClass::reconnect(){
  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT...");
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    if(client.connect(clientId.c_str())) {
      Serial.println("Conectado");
    } else {
      Serial.print("Fallo, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

#endif