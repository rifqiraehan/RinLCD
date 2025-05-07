#ifndef RinLCD_h
#define RinLCD_h

#include <inttypes.h>
#include "LCD.h"

class RinLCD : public LCD {
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

    virtual void send(uint8_t value, uint8_t mode) override;

private:
    void tulisNbit(uint8_t value, uint8_t numBits);
    void pulsaAktifkan();

    uint8_t _pin_rs;
    uint8_t _pin_rw;
    uint8_t _pin_aktifkan;
    uint8_t _pin_data[8];
};

#endif