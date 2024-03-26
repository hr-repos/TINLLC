void activateTimer1(int freq){
    cli();    // deactiveer interrupts
    TCCR1 |= (1<<CS10)|(1<<CS11)|(1<<CS12)|(1<<CS13); // instellen prescaler 
    TCCR1 |= (1<< CTC1);                              // Clear Timer/Counter on Compare Match (voor timer interrupt)
    OCR1A = F_CPU / 16384.0 / freq - 1;                  // interrupt tijd instellen
    OCR1C = OCR1A;  // Het OCR1A-register geeft aan wanneer de interrupt plaatsvindt, maar de timer wordt pas gereset als er
                    // een match is met het OCR1C-register. Dit zetten we op dezelfde waarde:
    TIMSK |= (1<<OCIE1A);                             // output compare register activeren
    sei();    // activeer interrupts
}


ISR(TIM1_COMPA_vect) {
    getTemperature();       // functie die moet worden uitgevoerd wanneer de interrupt wordt getriggerd
}