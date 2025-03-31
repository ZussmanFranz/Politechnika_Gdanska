#include <LiquidCrystal.h>
#include <i2c_BMP280.h>

#define UPDATE_FREQUENCY 1000;
#define CRITICAL_TEMPERATURE_HIGH 26.3
#define CRITICAL_TEMPERATURE_LOW 26.2

LiquidCrystal LCD(12, 11, 5, 4, 3, 2);
BMP280 bmp280;

void critical_notification(char symbol) {

    LCD.setCursor(15, 1);
    LCD.print(symbol);
    delay(500);
    LCD.setCursor(15, 1);
    LCD.print("*");

}

void update_measurements() {

    bmp280.awaitMeasurements();

    float pressure;
    float temperature;
    
    bmp280.getPressure(pressure);
    bmp280.getTemperature(temperature);

    LCD.print("Pres: ");
    LCD.print(pressure / 100.0, 2);
    LCD.print(" hPa");

    LCD.setCursor(0, 1);

    LCD.print("Temp: ");
    LCD.print(temperature, 2);
    LCD.print((char)223);           // degree symbol
    LCD.print("C");

    LCD.setCursor(0, 0);

    // If the temperature is too high/low - show a blinking notification in
    // the bottom right corner of the LCD screen
    if (temperature > CRITICAL_TEMPERATURE_HIGH) critical_notification('H');
    else if (temperature < CRITICAL_TEMPERATURE_LOW) critical_notification('L');
    else {
        LCD.setCursor(15, 1);
        LCD.print(" ");
    }

}

void setup() {

    bmp280.initialize();
    LCD.begin(16, 2);
    LCD.clear();
    LCD.setCursor(0, 0);

}

void loop() {
    delay(UPDATE_FREQUENCY);
    update_measurements();
}