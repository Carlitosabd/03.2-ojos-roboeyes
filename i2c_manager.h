// i2c_manager.h
// ============================================
// RESPONSABILIDAD: Hablar con el bus I2C (pines, velocidad, escaneo y verificacion).
// No sabe nada de: OLED, logos, ojos ni comandos del Monitor Serie.
// ============================================

#ifndef I2C_MANAGER_H
#define I2C_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include "config.h"

// TODO 1.1: Levanta el bus I2C compartido con los pines y la velocidad declarados en config.h.
// Pregunta Guía: ¿Qué dos pines y qué velocidad necesita el bus antes de buscar el panel?
// Pista: Los valores viven en config.h; el resultado esperado se describe en la guía §05.
inline void initI2C() {
    // Inicializa el bus I2C con los pines SDA, SCL personalizados y la velocidad (clock frequency) de config.h
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    Wire.setClock(I2C_FREQ_HZ);
}

// TODO 1.2: Barre el rango completo de direcciones e informa cada dispositivo hallado y el conteo final.
// Pregunta Guía: ¿Cómo sabes que el barrido cubrió todo el rango si el monitor solo muestra un conteo?
// Pista: La guía §05 muestra el barrido esperado línea por línea.
inline void scanI2C() {
    byte error, address;
    int deviceCount = 0;

    Serial.println(F("[I2C] Iniciando barrido del bus I2C (direcciones 0x01 a 0x7F)..."));

    // Barrido estándar desde la dirección 1 hasta la 127 (0x7F)
    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            Serial.print(F("[I2C] Dispositivo encontrado en la direccion 0x"));
            if (address < 16) {
                Serial.print("0");
            }
            Serial.print(address, HEX);
            Serial.println();
            deviceCount++;
        } else if (error == 4) {
            Serial.print(F("[I2C] Error desconocido en la direccion 0x"));
            if (address < 16) {
                Serial.print("0");
            }
            Serial.print(address, HEX);
            Serial.println();
        }
    }

    if (deviceCount == 0) {
        Serial.println(F("[I2C] No se encontraron dispositivos I2C conectados."));
    } else {
        Serial.print(F("[I2C] Barrido completado. Total de dispositivos encontrados: "));
        Serial.println(deviceCount);
    }
}

// TODO 1.3: Sondea la dirección del panel e informa si responde o si el arranque debe detenerse.
// Pregunta Guía: ¿Qué debe imprimir el arranque cuando el panel no responde?
// Pista: Hay dos caminos, uno de éxito y uno fatal; la guía §05 los muestra.
inline void testI2CDevice() {
    Serial.print(F("[I2C] Verificando panel OLED en la direccion 0x"));
    Serial.print(OLED_I2C_ADDRESS, HEX);
    Serial.println(F("..."));

    Wire.beginTransmission(OLED_I2C_ADDRESS);
    byte error = Wire.endTransmission();

    if (error == 0) {
        Serial.println(F("[I2C] ¡Exito! Dispositivo OLED responde correctamente en la direccion configurada."));
    } else {
        Serial.println(F("[FATAL] Error critico: El panel OLED no responde en la direccion I2C. Verifique el cableado."));
        // Detiene el flujo de arranque de forma segura ante un fallo de hardware indispensable
        while (true) {
            delay(1000);
        }
    }
}

#endif