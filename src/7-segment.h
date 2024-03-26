// data die naar het shift register gestuurd moet worden om de cijfers te tonen
static uint8_t segmentArray[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9
    0b00000000, // 10, niks/leeg
    0b01000000, // 11, streepje
    0b10000000, // 12, punt
    0b00001001  // 13, test
};
// data die naar het shift register moet worden gestuurd om te kiezen welk(e) digit(s) aan moet(en)
static uint8_t digitArray[] = {
    0b00000000, // uit
    0b00000001, // 1
    0b00000010, // 2
    0b00000100, // 3
    0b00001000, // 4
    0b00001111  // alle digits tegelijk
};

uint8_t transfer(uint8_t data) {
    USIDR = data;   // data die verstuurd moet worden
    for (int i=0; i<16; i++) {      // toggle 16x voor 8 bits data
        USICR |= (1<<USITC);        // toggle de clock pin
    }
    return USIDR;                       
}

void writeDigit(uint8_t segment, int digit){
    // om te debuggen: als er een getal hoger dan 9 wordt gestuurd wortd er een speciaal symbool gebruikt -> voor debugging
    if (segment > 9) {
        segment = 13;
    }
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
        PORTB &= ~(1<<PB3);          // latch laag
        transfer(digitArray[digit]);
        // stuur de juiste waardes naar het shift register, en zet er bij het 2e getal een punt bij
        if (digit != 2) {
            transfer(~(segmentArray[segment]));
        } else {
            transfer(~(segmentArray[segment] | segmentArray[12]));
        }
        PORTB |= (1<<PB3);          // latch hoog
    }
}

/*
#include <util/delay.h>     // deze library moet bij gebruik van deze functie toegevoegd worden
void testDisplays(){
    // deze functie geeft de getallen 0 t/m 10 weer bij alle digits
    for(int i=0; i<10; i++){
        writeDigit(i, 5);
        _delay_ms(500);
    }
}
*/