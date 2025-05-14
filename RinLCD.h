#ifndef RinLCD_h
#define RinLCD_h

#include <inttypes.h>
#include <stddef.h>

#define WAKTU_EKSEKUSI 37
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

class RinLCD {
public:
    RinLCD(uint8_t rs, uint8_t rw, uint8_t enable,
           uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
           uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

    void mulai(uint8_t cols, uint8_t rows);
    void bersihkan();
    void buatKarakter(uint8_t location, uint8_t charmap[]);
    void aturKursor(uint8_t col, uint8_t row);
    size_t cetak(const char str[]);
    void tulis(uint8_t value);
    void tulisBerjalan(const char* teksBaris0 = "", const char* teksBaris1 = "", uint16_t kecepatan = 100, uint16_t iterasi = 2);
    void send(uint8_t value, uint8_t mode);

private:
    void tulisNbit(uint8_t value, uint8_t numBits);
    void pulsaAktifkan();
    void init();
    void command(uint8_t value);

    uint8_t _pin_rs;
    uint8_t _pin_rw;
    uint8_t _pin_aktifkan;
    uint8_t _pin_data[8];
    uint8_t _displayfunction;
    uint8_t _displaycontrol;
    uint8_t _displaymode;
    uint8_t _numlines;
    uint8_t _cols;
};

#endif