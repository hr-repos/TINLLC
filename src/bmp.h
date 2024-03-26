uint16_t T1;
int16_t T2;
int16_t T3;
int32_t adc_T;
int32_t adc_P;
int tempTien;
int tempEnkel;
int tempTiende;
int tempHonderste;
int test;

uint8_t transferBMP(uint8_t data) {
    USIDR = data;   // data die verstuurd moet worden
    for (int i=0; i<16; i++) {      // toggle 16x voor 8 bits data
        USICR |= (1<<USITC);        // toggle de clock pin
    }
    return USIDR;
}

// dit maakt de 0 een 32 bit zodat er genoeg ruimte is om te bitshiften
int32_t spiRead ()
{
    return transferBMP(0);
}

void startTempBMP(){
    PORTB &= ~(1 << PB4);           // toggle chip select
    transferBMP(0x74);              // stuur de waarde 0x74 dat hoort bij het ctrl_meas register
    transferBMP(0b01000011);        // zet de sensor in de juiste modus
    PORTB |= (1 << PB4);
}

void getCalibrationDataTemperature(){
    PORTB &= ~(1 << PB4);   // toggle chip select
    transferBMP(0x88);      // vraag de clibartiedata voor de temperatuur
    T1 = spiRead();         // lage byte
    T1 |= spiRead() << 8;   // hoge byte (samengeoegd met het lage getal)
    T2 = spiRead();
    T2 |= spiRead() << 8;
    T3 = spiRead();
    T3 |= spiRead() << 8;
    PORTB |= (1 << PB4);
}

int testBMP(){
    PORTB &= ~(1 << PB4);           // toggle chip select
    transferBMP(0xD0);              // vraag het device id op
    uint8_t id = transferBMP(0);
    PORTB |= (1 << PB4);
    return(id == (0x58));           // geef een true als het verwachte id wordt ontvangen, anders false
}

void getTemperature(){
    PORTB &= ~(1 << PB4);  
    transferBMP(0xFA);
    // int32_t msb = transferBMP(0) << 12;
    // int32_t lsb = transferBMP(0) << 4;
    // int32_t xlsb = transferBMP(0) >> 4;
    adc_T = spiRead() << 12; // MSB (8-bit)
    adc_T |= spiRead() << 4; // LSB (8-bit)
    adc_T |= spiRead() >> 4; // XLSB (4-bit)
    PORTB |= (1 << PB4);
    // adc_T = msb | lsb | xlsb;

    // reken de temeratuur uit aan de hand van de ontvangen data
    long var1 = ((((adc_T >> 3) - ((long) T1 << 1))) * ((long) T2)) >> 11;
    long var2 = (((((adc_T >> 4) - ((long) T1)) * ((adc_T >> 4) - ((long)T1))) >> 12) * ((long)T3)) >> 14;
    float temp = ((var1 + var2) / 5120.0);
    
    // zet met de volgende berekeningen de juiste waardes op de plek van de 4 digits aan de hand van de omgerekende temperatuur hierboven
    float var3 = temp / 10;
    tempTien = (int) var3;
    int var4 = temp; 
    tempEnkel = var4 % 10;
    float var5 = temp * 10;
    int var6 = var5;
    tempTiende = (var6 % 10);
    float var7 = temp * 100;
    int var8 = var7;
    tempHonderste = (var8 % 10); 
}
