#include "RinLCD.h"
#include <Arduino.h>

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

void RinLCD::init() {
    digitalWrite(_pin_rs, LOW);
    digitalWrite(_pin_aktifkan, LOW);
    if (_pin_rw != 255) {
        digitalWrite(_pin_rw, LOW);
    }

    delayMicroseconds(50000);
    send(0x30, 0);
    delayMicroseconds(4500);
    send(0x30, 0);
    delayMicroseconds(150);
    send(0x30, 0);

    if (!(_displayfunction & LCD_8BITMODE)) {
        send(0x20, 0);
    }

    command(LCD_FUNCTIONSET | _displayfunction);
    delayMicroseconds(50);

    _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
    delayMicroseconds(50);

    bersihkan();

    _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    command(LCD_ENTRYMODESET | _displaymode);
    delayMicroseconds(50);
}

void RinLCD::mulai(uint8_t cols, uint8_t rows) {
    _cols = cols;
    _numlines = rows;

    if (rows > 1) {
        _displayfunction |= LCD_2LINE;
    }
    init();
}

void RinLCD::bersihkan() {
    command(LCD_CLEARDISPLAY);
    delayMicroseconds(2000);
}

void RinLCD::buatKarakter(uint8_t location, uint8_t charmap[]) {
    location &= 0x7;
    command(LCD_SETCGRAMADDR | (location << 3));
    for (int i = 0; i < 8; i++) {
        send(charmap[i], 1);
    }
}

void RinLCD::aturKursor(uint8_t col, uint8_t row) {
    int row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    if (row >= _numlines) {
        row = _numlines - 1;
    }
    command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

size_t RinLCD::cetak(const char str[]) {
    size_t n = 0;
    while (*str) {
        tulis(*str++);
        n++;
    }
    return n;
}

void RinLCD::tulis(uint8_t value) {
    send(value, 1);
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
    digitalWrite(_pin_rs, mode);
    if (_pin_rw != 255) {
        digitalWrite(_pin_rw, LOW);
    }
    if (_displayfunction & LCD_8BITMODE) {
        tulisNbit(value, 8);
    } else {
        tulisNbit(value >> 4, 4);
        tulisNbit(value, 4);
    }
    delayMicroseconds(WAKTU_EKSEKUSI);
}

void RinLCD::command(uint8_t value) {
    send(value, 0);
}

void RinLCD::tulisNbit(uint8_t value, uint8_t numBits) {
    for (uint8_t i = 0; i < numBits; i++) {
        digitalWrite(_pin_data[i], (value >> i) & 0x01);
    }
    pulsaAktifkan();
}

void RinLCD::pulsaAktifkan() {
    digitalWrite(_pin_aktifkan, HIGH);
    delayMicroseconds(1);
    digitalWrite(_pin_aktifkan, LOW);
}