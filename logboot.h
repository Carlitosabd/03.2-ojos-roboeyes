// logboot.h
// ============================================
// RESPONSABILIDAD: Dibujar el logo de arranque y hacer el POST de pantalla.
// No sabe nada de: ojos, bus I2C ni comandos del Monitor Serie.
// ============================================

#ifndef LOGBOOT_H
#define LOGBOOT_H

#include <Arduino.h>
#include "display.h"
#include "logo.h"

// TODO 2.2: Pinta el marco del logo desde logo_bitmap y preséntalo en el panel.
// Pregunta Guía: ¿Qué debe verse en el panel durante la ventana de arranque?
inline void showLogo() {
    display.clearDisplay();
    // Dibuja el mapa de bits almacenado en logo.h centrado en el panel usando las dimensiones globales
    display.drawBitmap(
        (OLED_WIDTH - LOGO_WIDTH) / 2, 
        (OLED_HEIGHT - LOGO_HEIGHT) / 2, 
        logo_bitmap, 
        LOGO_WIDTH, 
        LOGO_HEIGHT, 
        SSD1306_WHITE
    );
    display.display();
}

// TODO 2.3: Dibuja el cuadrado de autoprueba centrado e informa sus coordenadas.
// Pregunta Guía: ¿Cómo compruebas que el cuadrado quedó centrado sin medir a ojo?
inline void testDisplay() {
    display.clearDisplay();
    
    // Definimos el tamaño del cuadrado de autoprueba (ej. 20x20 píxeles)
    int side = 20;
    int x = (OLED_WIDTH - side) / 2;
    int y = (OLED_HEIGHT - side) / 2;

    // Dibuja un rectángulo relleno o un contorno centrado geométricamente
    display.fillRect(x, y, side, side, SSD1306_WHITE);
    display.display();

    // Informa las coordenadas calculadas a través del Monitor Serie
    Serial.print(F("[POST] Cuadrado de autoprueba centrado en X: "));
    Serial.print(x);
    Serial.print(F(", Y: "));
    Serial.println(y);
}

#endif