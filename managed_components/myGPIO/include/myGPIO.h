#ifndef MYGPIO_H
#define MYGPIO_H

void MyGPIO_setup_led(int pin);
void MyGPIO_setup_button(int pin);

int MyGPIO_lezen(int pin);
int MyGPIO_flank(int pin);

void MyGPIO_schrijven(int pin, int value);
void MyGPIO_toggle(int pin);



#endif
