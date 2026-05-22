#include <MD_MAX72XX.h>
#include <SPI.h>

// ─── Configurazione hardware ───────────────────────────────────────────
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW  // tipo modulo comune
#define MAX_DEVICES   1                     // una sola matrice 8x8

// Pin ESP-12E (NodeMCU):
//   D5 = GPIO14 -> DIN
//   D4 = GPIO2  -> CS (Load)
//   D7 = GPIO13 -> CLK
#define PIN_DIN  D5
#define PIN_CS   D4
#define PIN_CLK  D7

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, PIN_DIN, PIN_CLK, PIN_CS, MAX_DEVICES);

// ─── Buffer matrice ────────────────────────────────────────────────────
// 8 byte, uno per riga: bit7 = colonna 0, bit0 = colonna 7
uint8_t matrixBuffer[8] = {0};

// ─── Ricezione seriale ─────────────────────────────────────────────────
String  inputBuffer = "";
uint8_t rowsReceived = 0;

// ─── Funzioni ──────────────────────────────────────────────────────────

// Applica il buffer alla matrice fisica
void updateMatrix() {
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);  // batch update
    for (uint8_t row = 0; row < 8; row++) {
        mx.setRow(0, row, matrixBuffer[row]);
    }
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

// Converte una stringa binaria "10110010" in un byte
// bit7 = primo carattere (colonna 0)
uint8_t parseBinaryRow(const String &s) {
    uint8_t val = 0;
    for (uint8_t i = 0; i < 8; i++) {
        if (s[i] == '1') {
            val |= (1 << (7 - i));
        }
    }
    return val;
}

void processRow(const String &line) {
    if (line.length() < 8) {
        Serial.println("Errore: riga troppo corta");
        rowsReceived = 0;
        return;
    }

    // Valida che contenga solo '0' e '1'
    for (uint8_t i = 0; i < 8; i++) {
        if (line[i] != '0' && line[i] != '1') {
            Serial.println("Errore: carattere non valido");
            rowsReceived = 0;
            return;
        }
    }

    matrixBuffer[rowsReceived] = parseBinaryRow(line);
    rowsReceived++;

    if (rowsReceived == 8) {
        updateMatrix();
        rowsReceived = 0;
        Serial.println("Matrice ricevuta OK");
    }
}

// ─── Setup & Loop ──────────────────────────────────────────────────────

void setup() {
    Serial.begin(115200);

    mx.begin();
    mx.control(MD_MAX72XX::INTENSITY, 8);  // luminosità 0-15
    mx.clear();

    Serial.println("Pronto");
}

void loop() {
    while (Serial.available()) {
        char c = (char)Serial.read();

        if (c == '\n') {
            inputBuffer.trim();
            if (inputBuffer.length() > 0) {
                processRow(inputBuffer);
            }
            inputBuffer = "";
        } else if (c != '\r') {
            inputBuffer += c;
        }
    }
}
