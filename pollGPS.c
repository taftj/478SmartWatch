#include "mainStuff.h"
#include "tomOLED.h"
#include <string.h>

void poll_GPS(ui_data* commander) {

    char* GPSmsg = (char*)AHT_uart_gets_GPS();
    if(strstr(GPSmsg, "G")) {
        rawFillRect(10,78,90,12,0);
         AHTStringDraw(10,80,GPSmsg,SELECTOR,SELECTOR,1);
    } else {
     AHTStringDraw(10,95,GPSmsg,SELECTOR,SELECTOR,1);
    }
        while (PORTBbits.RB4);
        rawFillRect(10,93,115,12,0); //clear 'set clock' msg

    return;

}

uint8_t* AHT_uart_gets_GPS(){
   static uint8_t buffer[16];
   int i;
   //static uint8_t holder[16] = "Waiting for GPS\0";
    for (i=0;i<15;i++) buffer[i] = 0;
   buffer[15] = '\0';
   i=0;

    //wait for reciever shift register to finish shifting in the other buffer
    //LATAbits.LATA0 = 1;



    while(!U1STAbits.TRMT);
    //LATAbits.LATA0 = 1;
    while(!U1STAbits.RIDLE);
    //while we have things to read from the buffer

    
    while (U1STAbits.URXDA && i < 15){
         buffer[i] = U1RXREG;
        i++;

    }    

   
    U1STAbits.OERR = 0;
    return buffer;
}

