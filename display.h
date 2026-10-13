// TODO 1.4: Inicializa el panel con el modo de alimentación interna y la dirección de config.h; si falla, informa y no continúes.
// Pregunta Guía: ¿Qué dos argumentos necesita el panel para inicializarse y qué haces si falla?
// Pista: La línea de éxito esperada está en la guía §05.
inline void initDisplay() {
    // Se inicializa con SSD1306_SWITCHCAPVCC (generador de voltaje interno) y la dirección I2C definida en config.h (ej. 0x3C)
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
        Serial.println(F("[ERROR] Fallo al inicializar la pantalla OLED SSD1306. Verifique las conexiones I2C."));
        while (true) {
            // Detiene la ejecución en un bucle infinito si la pantalla no responde
            delay(1000);
        }
    }
    
    // Limpieza inicial del búfer y de la pantalla
    display.clearDisplay();
    display.display();
}
