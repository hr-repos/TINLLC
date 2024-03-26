# TINLLC Low Level Computing jaar 1 periode 2 

De eindopdracht is een combinatie van alle voorgaande practicumopdrachten: Bouw een digitale thermometer
/ barometer op basis van een ATtiny85. De requirements zijn als volgt:
1. De software draait op een ATtiny85.
2. De ATtiny85 draait op 1 MHz.
3. De timing wordt gedaan met behulp van een timer-interrupt; niet met een wachtlus.
4. De temperatuur wordt iedere paar seconden gemeten met een BMP280 sensor die wordt aangestuurd
en uitgelezen via een SPI-verbinding.
5. De temperatuur wordt afgebeeld in graden Celsius op een display van minstens 1 cijfer, met een precisie
van 0,1°C of beter (de cijfers worden zonodig sequentieel afgebeeld).
6. Het display wordt aangestuurd via een SPI-verbinding, indien nodig met behulp van een shift register.

**Optionele requirements** Deze zijn niet vereist voor de basisopdracht, maar hier kun je extra punten mee
verdienen: 

7. De implementatie van de SPI-communicatie maakt gebruik van de counter en overflow flag in het USI
status register.
8. De klok van de ATtiny85 wordt met een externe oscillator aangedreven.
9. Behalve de temperatuur wordt ook de atmosferische druk gemeten en afgebeeld in Pascal.
10. Het display bestaat uit meerdere karakters, zodat de temperatuur in ´e ´en keer afgebeeld kan worden.
11. Het display is een dot-matrix-display en geeft ook het verloop van de temperatuur over de afgelopen
minuut grafisch weer.
12. Met een drukknop is de uitlezing om te schakelen naar graden Fahrenheit en weer terug.