#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "myADC.h"
#include "myGPIO.h"

#define LED 23
#define BUTTON 17
int locked = 0;
int pos = 0;

void code_slot_setup(void);
void code_slot1(void);
void code_slot2(void);
int code_test(void);

int mycode[4];
int mycode2[4];

void app_main(void)
{
    code_slot_setup();
    while (1)
    {
        vTaskDelay(1);
        if(locked == 0)
        {
            code_slot1();
            if(pos == 4)
            {
                MyGPIO_schrijven(LED, 1);
                pos = 0;
                locked = 1;

            }
        }
        else
        {
           printf("We zijn gesloten\n");
           code_slot2();
            if(pos == 4)
            {
                if(code_test ())
                {
                MyGPIO_schrijven(LED, 0);
                pos = 0;
                locked = 0;
                }
                else
                {
                    pos = 0;
                }

            }
            
        }
        
    }
    
}

void code_slot_setup(void)
{
    //LED
    MyGPIO_setup_led(LED);
    //KNOP
    MyGPIO_setup_button(BUTTON);
    //POT
    myADC_setup();
}
    
void code_slot1(void)
{
    int getal = myADC_waarde() * 10 / 4096;
    printf("ADC waarde: %d, positie: %d\n", getal, pos);
    if(MyGPIO_flank(BUTTON))
    {
        printf("WIEEEE flank\n");
        mycode[pos] = getal;
        pos++;
    }
}

void code_slot2(void)
{
    int getal = myADC_waarde() * 10 / 4096;
    printf("ADC waarde: %d, positie: %d\n", getal, pos);
    if(MyGPIO_flank(BUTTON))
    {
        printf("WIEEEE flank\n");
        mycode2[pos] = getal;
        pos++;
    }
}
    
int code_test(void)
{
    for(int i = 0; i<4; i++)
    {
        if(mycode[i] != mycode2[i])return 0;
      

    }
    return 1;
}
   
    
    
    /*MyGPIO_schrijven(LED, 1);
    vTaskDelay(500);
    for(int i = 0; i < 100; i++)
    {    
        MyGPIO_schrijven(LED, MyGPIO_lezen(BUTTON));
        vTaskDelay(10);
    }
        for(int i = 0; i < 10; i++)
    {
        printf("adc: %d\n", myADC_waarde());
        vTaskDelay(100);
    }*/















