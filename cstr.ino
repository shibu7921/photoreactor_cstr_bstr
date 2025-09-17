#include <HX711_ADC.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // LiquidCrystal_I2C library

HX711_ADC LoadCell(4, 5);  // dt pin, sck pin
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD HEX address 0x27

int taree = 6;
int a = 0;
float b = 0;
int inlet = 7;
int outlet = 8;

void setup() {
    pinMode(inlet, OUTPUT);
    pinMode(outlet, OUTPUT);
    pinMode(taree, INPUT_PULLUP);

    LoadCell.begin(); // start connection to HX711
    LoadCell.start(1000); // load cells get 1000ms of time to stabilize

    ///////////////////////////////////////////
    LoadCell.setCalFactor(375); // Calibrate your LOAD CELL with 100g weight,
                               // and change the value according to readings
    ///////////////////////////////////////////

    // initialize the LCD
    lcd.begin();      // begins connection to the LCD module
    lcd.backlight();  // turns on the backlight
    lcd.setCursor(1, 0); // set cursor to first row
    lcd.print("Digital Scale "); // print out to LCD
    lcd.setCursor(0, 1); // set cursor to first row
    lcd.print(" SHIBU NASKAR "); // print out to LCD
    delay(3000);
    lcd.clear();
}

void loop() {
    lcd.setCursor(1, 0); // set cursor to first row
    lcd.print("Digital Scale "); // print out to LCD

    LoadCell.update(); // retrieves data from the load cell
    float i = LoadCell.getData(); // get output value

    if (i < 0) {
        i = i * (-1);
        lcd.setCursor(0, 1);
        lcd.print(" ");
        lcd.setCursor(8, 1);
        lcd.print(" ");
    } else {
        lcd.setCursor(0, 1);
        lcd.print(" ");
        lcd.setCursor(8, 1);
        lcd.print(" ");

        lcd.setCursor(1, 1); // set cursor to second row
        lcd.print(i); // print out the retrieved value to the second row
        lcd.print("g ");
        float z = i / 28.3495;
        lcd.setCursor(9, 1);
        lcd.print(z, 2);
        lcd.print("oz ");

        if (i > 5000) {
            i = 0;
            lcd.setCursor(0, 0); // set cursor to second row
            lcd.print(" Over loaded ");
            delay(200);
        }

        if (i > 20.5) {
            digitalWrite(outlet, HIGH);
            delay(10);
            digitalWrite(inlet, LOW);
            delay(800);
        } else if (i < 18.5) {
            digitalWrite(inlet, HIGH);
            delay(10);
            digitalWrite(outlet, LOW);
            delay(800);
        } else if (i >= 18.5 && i <= 20.5) {
            digitalWrite(outlet, HIGH);
            digitalWrite(inlet, HIGH);
            delay(800);
        } else {
            digitalWrite(outlet, LOW);
            digitalWrite(inlet, LOW);
            delay(800);
        }
    }
}