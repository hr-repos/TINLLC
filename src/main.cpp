#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/atomic.h>
#include "bmp.h"
#include "7-segment.h"
#include "interrupts.h"
// PB0=DI    PB1=DO     PB7=SCK
int counter;
void init() {
    cli(); // deactiveer interrupts
    PORTB = 0;
    USICR |= (1<<USIWM0)|(1<<USICS1);  // 3 wire mode
    DDRB |= (1<<PB1)|(1<<PB2)|(1<<PB3)|(1<<PB4); // D0 & SCK als pinmode ouput 
    while(!testBMP());
    writeDigit(11, 1);
    startTempBMP();
    getCalibrationDataTemperature();
    getTemperature();
    sei(); // deactiveer interrupts
    activateTimer1(1);
}

int main() {
    init();
    while (true){
        writeDigit(tempTien, 1);
        writeDigit(tempEnkel, 2);
        writeDigit(tempTiende, 3);
        writeDigit(tempHonderste, 4);
    }
    return 0;
}
