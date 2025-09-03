README. MFRC-522.

## Objetivo general. 

Generar sistema de registro de entradas y salidas con RFID.

## 

## Objetivos específicos.

1.  Almacenar y registrar los UIDs de los usuarios autorizados.

2.  Configurar el hardware necesario para la comunicación entre el
    ESP32, el lector MFRC-522 y el LED RGB.

3.  Detectar tarjetas RFID y clasificarlas en categorías: autorizadas,
    rechazadas o sin pase.

4.  Controlar el LED RGB para indicar visualmente el estado de la
    tarjeta y el ciclo de entrada/salida.

5.  Generar y publicar mensajes JSON con la información de los eventos
    en consola serial y en un broker MQTT.

## Competencias.

-   Manejo de comunicación SPI entre módulos electrónicos.

-   Uso de librerías de Arduino para procesamiento RFID.

-   Implementación de lógica de control para validación de accesos.

-   Construcción y transmisión de mensajes en formato JSON.

-   Publicación de eventos en un broker MQTT.

-   Trabajo colaborativo en la integración de hardware y software.

## Tabla de Contenidos.

[Objetivo General.](#objetivo-general.)

[Objetivos Específicos.](#objetivos-específicos.)

[Competencias.](#competencias.)

[Tabla de Contenidos.](#tabla-de-contenidos.)

[Descripción.](#descripción.)

[Requerimientos.](#requisitos.)

[Instalación y configuración.](#instalación-y-configuración.)

Conexiones de Hardware.

Parámetros Técnicos del MFRC-522.

Uso y ejemplos de Código.

Resultados de Prueba.

Consideraciones Éticas y de Seguridad.

Formato de Salida (JSON).

Solución de Problemas.

Contribuciones.

Referencias.

## Descripción.

La práctica consiste en desarrollar un entorno inteligente de validación
de entradas y salidas utilizando tecnología RFID, donde cada integrante
del equipo cuenta con una tarjeta pasiva para identificarse. El sistema
no solo controla el acceso mediante reglas lógicas (entrada/salidas
válidas, rechazo de tarjetas desconocidas), sino que también brinda
retroalimentación visual con un LED RGB y publica todos los eventos en
un bróker MQTT en formato JSON. Esta actividad resulta relevante en el
contexto de los entornos inteligentes porque combina identificación sin
contacto, automatización de procesos, comunicación en red y gestión de
datos, habilidades clave en sistemas de control de accesos modernos y
aplicaciones de IoT.

## Requisitos.

**Hardware.**

-   Led RGB.

-   ESP32

-   Protoboard.

-   Jumpers.

-   Lector de tarjetas y tarjetas RFID.

**Software y bibliotecas requeridas.**

-   Arduino IDE.

-   Bibliotecas: wifi_mqtt_setup.h, sensores.h, actuadores.h,
    lcd_display.h, sd_logger.h, mqtt_service.h, tareas.h, SPI.h, Wire.h,
    LiquidCrystal_I2C.h, SD.h, DHT.h, RTClib.h, WiFi.h, PubSubClient.h.

**Conocimientos previos imprescindibles.**

-   Programación en C++ para Arduino.

-   Uso de MQTT en IoT.

-   Principios básicos de RFID.

## Instalación y configuración.

**Credenciales de acceso:**

UIDAutorizados Integrantes \[5\] = {

{\"A1B2C3D4\", \"Noemi Galicia\", \"Morado\", \"20195268\", false},

{\"E5F6G7H8\", \"José Raúl Herrera\", \"Azul\", \"20156348\", false},

{\"I9J0K1L2\", \"José Alejandro Ramirez\", \"Verde\", \"20196833\",
false},

{\"I09EABL8\", \"Humberto Mateus\", \"Amarillo\", \"20196823\", false},

{\"B7UIEBA2\", \"Juan Manuel Calvillo\", \"Rosa\", \"20196457\", false}

};

**MQTT.**

const char\* mqtt_server = \"test.mosquitto.org\";

const int mqtt_port = 1883;

String jsonMQTT = \"{\";

  jsonMQTT += \"\\\"fecha\\\":\\\"\" + String(fecha) + \"\\\",\";

  jsonMQTT += \"\\\"hora\\\":\\\"\" + String(hora) + \"\\\",\";

  jsonMQTT += \"\\\"temperatura\\\":\" + String(temp, 1) + \",\";

  jsonMQTT += \"\\\"humedad\\\":\" + String(hum, 1) + \",\";

  jsonMQTT += \"\\\"humo\\\":\" + String(smokePPM) + \",\";

  jsonMQTT += \"\\\"luz_adc\\\":\" + String(lightLevel) + \",\";

  jsonMQTT += \"\\\"luz_estado\\\":\\\"\" + luzEstado + \"\\\",\";

  jsonMQTT += \"\\\"humedad_suelo\\\":\" + String(soilMoisturePercent) +
\",\";

  jsonMQTT += \"\\\"riego\\\":\\\"\" + riegoEstado + \"\\\",\";

  jsonMQTT += \"\\\"buzzer\\\":\\\"\" + String(buzzerActivo ?
\"ACTIVADO\" : \"DESACTIVADO\") + \"\\\"\";

  jsonMQTT += \"}\";

  client.publish(\"invernadero/datos\", jsonMQTT.c_str());

**Configuraciones para WiFi.**

const char\* ssid = \"zonadecoberturainalambrica\";

const char\* password = \"1234\";

WiFiClient espClient;

PubSubClient client(espClient);

**Conexiones de pines**

+----------------------+----------------------+------------------------+
| Señal del modulo     | Pinde placa          | Función                |
+======================+======================+========================+
| VCC                  | 3.3V                 | Alimentación del       |
|                      |                      | modulo rfid            |
+----------------------+----------------------+------------------------+
| GND                  | GND                  | Tierra común del       |
|                      |                      | circuito               |
+----------------------+----------------------+------------------------+
| RST                  | RESET                | Reinicia el modulo     |
|                      |                      | RFID                   |
+----------------------+----------------------+------------------------+
| IRQ                  | Interrupción         | Pin de interrupción    |
+----------------------+----------------------+------------------------+
| MISO/SCL/TX          | MISO                 | Salida de datos desde  |
|                      |                      | del RFID hacia el mcu  |
+----------------------+----------------------+------------------------+
| MOSI                 | MOSI                 | Entrada de datos desde |
|                      |                      | el mcu hacia el RFID   |
+----------------------+----------------------+------------------------+
| SCK                  | SCK                  | Reloj del bus spi.     |
|                      |                      | Sincroniza la          |
|                      |                      | comunicación           |
+----------------------+----------------------+------------------------+
| SDA / NSS/ CS        | SDA                  | En spi: Selección del  |
|                      |                      | chip                   |
|                      |                      |                        |
|                      |                      | En i2c: dirección del  |
|                      |                      | esclavo                |
+----------------------+----------------------+------------------------+

**parámetros técnicos del MFRC-522**

  -----------------------------------------------------------------------
  **parámetro**    **Valor típico** **Unidad**       **descripción**
  ---------------- ---------------- ---------------- --------------------
  VCC              3.3              Voltaje          Voltaje no mayor a
                                                     5V

  Corriente de     10-13            mA               Consumo en
  operación                                          funcionamiento
                                                     normal

  Corriente en     \<80             uA               Consumo en modo de
  standby                                            bajo consumo

  Frecuencia de    13.56            MHz              Frecuencia de la
  operación                                          señal de radio para
                                                     el rfid

  Frecuencia de    27.12            MHz              Reloj base interno
  reloj interno                                      del chip

  Interfaz de      SPI,I2C,UART     \-               Modos soportados
  comunicación                                       para comunicarse con
                                                     el MCu

  Velocidad de SPI Hasta 10         Mbps             Velocidad máxima de
                                                     transferencia en
                                                     modo SPI

  Velocidad i2c    100 / 400        Khz              Soporta modos
                                                     estándar y rápido de
                                                     i2c

  Distancia de     0-60             Mm               Depende del tipo de
  lectura típica                                     tarjeta

  Temperatura de   -20 a +85        C                Rango de temperatura
  operación                                          de trabajo
  -----------------------------------------------------------------------

**Uso y ejemplos de código**

**El archivo**

**Resultados de prueba**

**Lecturas de tarjetas RFID**

El RFID debe de detectar cada tarjeta ya registrada en el proyecto sus
salidas son los siguientes (entrada, salida, no autorizado).

**Mensajes enviados a través de MQTT.**

Se debe de verificar que el mensaje JSON con los datos del integrante y
la salida que tuvo en el lector RFID son publicados en el bróker del
MQTT.

**Salida por consola serial**

La consola debe mostrar mensajes desde el inicio y fin del proceso tales
como:

(inicialización, conexión a wifi, lectura de tarjeta, validación,
publicación en MQTT).

**Indicadores Fisicos.**

Señalar el comportamiento de los LEDS como evidencia de funcionamiento
por ejemplo (Verde permitir acceso, Rojo denegar, Luz en espera).

**Consideraciones Éticas y de Seguridad**

**Privacidad de datos**

Los datos de los integrantes deben transmitirse y guardarse de manera
segura

Solo debe de guardarse la información necesaria para el correcto
funcionamiento del sistema

**Posibles vulnerabilidades**

Las tarjetas RFID pueden ser clonadas fácilmente si no se utiliza otras
tecnologías externas

Los mensajes que viajan entre WIFI/MQTT pueden ser capturados si no
están cifrados

El bróker debe de tener diferentes contraseñas o diferente configuración
para evitar los hackers

Si el usuario pierde su tarjeta alguien mas puede usarla y no hay manera
de cancelarla

**Medidas de mitigación**

Configurar diferente el MQTT que a lo predeterminado y poniendo
contraseñas

Revocar permisos en caso de perdida de tarjetas

Cifrar los mensajes del mqtt y el wifi

**Formato de Salida (JSON)**

**usuario** (string): Nombre del integrante autorizado

**uid** (string): Identificador único de la tarjeta RFID detectada

**evento** (string): Tipo de acción registrada, como \"Entrada\",
\"Salida\" o \"Rechazado\".

**timestamp** (string): Fecha y hora del evento en formato ISO 8601

**ubicacion** (string): Punto de acceso o lugar donde ocurrió la lectura

**solución de problemas**

+---------------+---------------+---------------+----------------------+
| **Fallo       | **Sintomas**  | **            | **Solucion**         |
| comun**       |               | Diagnostico** |                      |
+===============+===============+===============+======================+
| Lector rfid   | No hay        | Verificar     | Revisar soldaduras   |
| no detecta    | lectura led   | alimentación  |                      |
| tarjetas      | no reacciona  |               | Probar con ejemplo   |
|               |               | Revisar       | básico               |
|               |               | conexiones    |                      |
|               |               |               | Cambiar modulo       |
+---------------+---------------+---------------+----------------------+
| **Conexión    | **No se       | **Verificar   | **Actualizar         |
| WIFI falla**  | conecta, mqtt | credenciales  | credenciales**       |
|               | no envia o    | wifi**        |                      |
|               | recibe        |               | **Acercar a router** |
|               | mensajes**    | **Probar con  |                      |
|               |               | red           |                      |
|               |               | diferente**   |                      |
+---------------+---------------+---------------+----------------------+
| **Conexión    | **Mensajes se | **Verificar   | **Usar bróker        |
| mqtt          | pierden**     | bróker**      | alternativo**        |
| i             |               |               |                      |
| ntermitente** |               |               | **Ajustar keepalive  |
|               |               |               | time**               |
+---------------+---------------+---------------+----------------------+

**Lista de materiales**

-LED RGB

-modulo rfid

-ESP32

-cables upon

-cable de datos

-Resistencias de 330 ohms

-5 tarjetas con rffid

**Referencias**

** NXP Semiconductors. (2016). *MFRC522 Standard performance MIFARE and
NTAG frontend (Rev. 3.9)* \[Data sheet\]. NXP.
https://www.nxp.com/docs/en/data-sheet/MFRC522.pdf**

** Random Nerd Tutorials. (s.f.). *ESP32 RFID Reader with RC522
Module*. Recuperado el 2 de septiembre de 2025, de
https://randomnerdtutorials.com/esp32-rfid-rc522/**

** LastMinuteEngineers. (s.f.). *Arduino RFID Reader/Writer MFRC522
Tutorial*. Recuperado el 2 de septiembre de 2025, de
https://lastminuteengineers.com/how-rfid-works-rc522-arduino-tutorial/**
