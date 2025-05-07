#include "RinLCD.h"
#include <Arduino.h>

#define WAKTU_EKSEKUSI 37

RinLCD::RinLCD(uint8_t rs, uint8_t rw, uint8_t enable,
               uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
               uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
    _pin_rs = rs;
    _pin_rw = rw;
    _pin_aktifkan = enable;
    _pin_data[0] = d0;
    _pin_data[1] = d1;
    _pin_data[2] = d2;
    _pin_data[3] = d3;
    _pin_data[4] = d4;
    _pin_data[5] = d5;
    _pin_data[6] = d6;
    _pin_data[7] = d7;

    for (int i = 0; i < 8; i++) {
        pinMode(_pin_data[i], OUTPUT);
    }
    pinMode(_pin_rs, OUTPUT);
    if (_pin_rw != 255) {
        pinMode(_pin_rw, OUTPUT);
    }
    pinMode(_pin_aktifkan, OUTPUT);

    _displayfunction = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;
}

void RinLCD::mulai(uint8_t cols, uint8_t rows) {
    begin(cols, rows);
}

void RinLCD::bersihkan() {
    clear();
}

void RinLCD::buatKarakter(uint8_t location, uint8_t charmap[]) {
    createChar(location, charmap);
}

void RinLCD::aturKursor(uint8_t col, uint8_t row) {
    setCursor(col, row);
}

size_t RinLCD::cetak(const char str[]) {
    return print(str);
}

void RinLCD::tulis(uint8_t value) {
    write(value);
}

void RinLCD::tulisBerjalan(const char* teksBaris0, const char* teksBaris1, uint16_t kecepatan, uint16_t iterasi) {
    int posisi0 = 0, posisi1 = 0;
    char tampilan0[17], tampilan1[17];
    uint16_t panjangTeks0 = strlen(teksBaris0);
    uint16_t panjangTeks1 = strlen(teksBaris1);
    uint32_t iterasiSaatIni = 0;
    uint32_t maksIterasi = max(panjangTeks0 ? panjangTeks0 : 1, panjangTeks1 ? panjangTeks1 : 1) * iterasi;

    while (iterasiSaatIni < maksIterasi) {
        for (int i = 0; i < 16; i++) {
            if (panjangTeks0) {
                int indeks0 = (posisi0 + i) % panjangTeks0;
                tampilan0[i] = teksBaris0[indeks0];
            } else {
                tampilan0[i] = ' ';
            }
            if (panjangTeks1) {
                int indeks1 = (posisi1 + i) % panjangTeks1;
                tampilan1[i] = teksBaris1[indeks1];
            } else {
                tampilan1[i] = ' ';
            }
        }
        tampilan0[16] = '\0';
        tampilan1[16] = '\0';

        aturKursor(0, 0);
        cetak(tampilan0);
        aturKursor(0, 1);
        cetak(tampilan1);

        posisi0 = (posisi0 + 1) % (panjangTeks0 ? panjangTeks0 : 1);
        posisi1 = (posisi1 + 1) % (panjangTeks1 ? panjangTeks1 : 1);
        iterasiSaatIni++;
        delay(kecepatan);
    }
}

void RinLCD::send(uint8_t value, uint8_t mode) {
    digitalWrite(_pin_rs, (mode == LCD_DATA));
    if (_pin_rw != 255) {
        digitalWrite(_pin_rw, LOW);
    }
    if (mode != FOUR_BITS) {
        if (_displayfunction & LCD_8BITMODE) {
            tulisNbit(value, 8);
        } else {
            tulisNbit(value >> 4, 4);
            tulisNbit(value, 4);
        }
    } else {
        tulisNbit(value, 4);
    }
    waitUsec(WAKTU_EKSEKUSI);
}

void RinLCD::tulisNbit(uint8_t value, uint8_t numBits) {
    for (uint8_t i = 0; i < numBits; i++) {
        digitalWrite(_pin_data[i], (value >> i) & 0x01);
    }
    pulsaAktifkan();
}

void RinLCD::pulsaAktifkan() {
    digitalWrite(_pin_aktifkan, HIGH);
    waitUsec(1);
    digitalWrite(_pin_aktifkan, LOW);
}