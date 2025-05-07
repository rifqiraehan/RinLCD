#include <Arduino.h>
#include <RinLCD.h>

RinLCD lcd(13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3);

unsigned char Character1[8] = {0x04, 0x1F, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x1F};
unsigned char Character2[8] = {0x01, 0x03, 0x07, 0x1F, 0x1F, 0x07, 0x03, 0x01};

void setup() {
    lcd.mulai(16, 2);
    lcd.bersihkan();
    lcd.buatKarakter(0, Character1);
    lcd.buatKarakter(1, Character2);
}

void loop() {
    lcd.aturKursor(0, 0);
    lcd.cetak("Hello World!");
    lcd.aturKursor(0, 1);
    lcd.tulis(byte(0));
    lcd.tulis(1);
}