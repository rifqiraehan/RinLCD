#include <Arduino.h>
#include <RinLCD.h>

RinLCD lcd(13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3);

void setup() {
    lcd.mulai(16, 2);
    lcd.bersihkan();
}

void loop() {
    lcd.tulisBerjalan("Kelompok 2      ", "Praktikum APPL  ", 300, 2);

    lcd.bersihkan();
    lcd.aturKursor(0, 0);
    lcd.cetak("Nama Anggota");
    lcd.aturKursor(0, 1);
    lcd.cetak("Kelompok 2");
    delay(3000);

    lcd.bersihkan();
    lcd.aturKursor(0, 0);
    lcd.cetak("M. Irsyad Alkais");
    lcd.aturKursor(0, 1);
    lcd.cetak("(3223600001)");
    delay(3000);

    lcd.bersihkan();
    lcd.aturKursor(0, 0);
    lcd.cetak("Muh. Nabil F.M.");
    lcd.aturKursor(0, 1);
    lcd.cetak("(3223600002)");
    delay(3000);

    lcd.bersihkan();
    lcd.aturKursor(0, 0);
    lcd.cetak("Rifqi Raehan H.");
    lcd.aturKursor(0, 1);
    lcd.cetak("(3223600004)");
    delay(3000);

    lcd.bersihkan();
}