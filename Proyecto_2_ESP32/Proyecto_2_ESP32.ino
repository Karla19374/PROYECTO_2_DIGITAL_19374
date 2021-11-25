//********************************************************************************
//Universidad del Valle de Guatemala
//BE3015 Electrónica Digital 2
//Karla Melissa López
//Proyecto 2 - Sensor de presión y temperatura
//********************************************************************************

//*****************************************************************************
// Librerías
//*****************************************************************************
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_NeoPixel.h>

//*****************************************************************************
// Definición de pines
//*****************************************************************************
#define d4 14 //  Conectar LCD
#define d5 27
#define d6 26
#define d7 25
#define en 12
#define rs 13

#define PIN 23
#define MAX_BRIGHTNESS 255
//*****************************************************************************
// Prototipos de función
//*****************************************************************************
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 23, NEO_RGB + NEO_KHZ800);

//*****************************************************************************
// Variables Globales
//*****************************************************************************
LiquidCrystal LCD(rs, en, d4, d5, d6, d7); // Pantalla lcd
uint8_t DM, UM, C, D, U;                   // variables para datos

char inByte = 0;
String instruccion = ""; //  Indicar que la cadena inicia vacía

Adafruit_BMP085 MySensorBMP; //  Llmar a la librería para el sensor de presion

//*****************************************************************************
// Configuración
//*****************************************************************************
void setup()
{
  Serial.begin(115200);                                           //  comunicacion serial 1
  Serial2.begin(115200);                                          //  Comunicacion serial 2
  Serial.println("Proyecto 2 - Sensor de presión y temperatura"); //  Imprimir
  if (!MySensorBMP.begin())                                       //  Conocer si existe el sensor antes de iniciar
  {
    //  por si no se encuentra el sensor
    Serial.println("No fue posible encontrar un sensor BMP180, verifique las conexiones...!");
    while (1)
    {
    }
  }
  //  Parametros de inicio para la lcd
  LCD.begin(16, 2);
  LCD.clear();
}
//*****************************************************************************
// Loop Principal
//*****************************************************************************
void loop()
{
  int Temp = MySensorBMP.readTemperature(); //  Funcion para temperatura
  int PA = MySensorBMP.readPressure();      //  Funcion para presion
  Serial.println(PA);
  Serial2.println(PA);

  if (Serial2.available() > 0) //  Iniciar la comunicaion serial, UART
  {
    instruccion = Serial.readStringUntil('\n');
    Serial.print("Presion es de: ");
    Serial.println(instruccion.toInt());
    delay(500);
  }

  //  Imprimir los datos en la lcd de 16x2
  LCD.clear();
  LCD.setCursor(1, 0);
  LCD.print("Presión Atm:");
  LCD.setCursor(1, 1);
  LCD.print(PA);
  LCD.print(' ');
  LCD.print("Pa");
  delay(3000);
}
