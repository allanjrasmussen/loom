#include "maskinrum.h"

maskinrum::maskinrum(){}

void maskinrum::setup_io(){

   // qDebug() << "void maskinrum::setup_io()";


       /* open /dev/mem */
       if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
           qDebug() << "GPIO_BASE: " << QString::number(GPIO_BASE);
       }

       /* mmap GPIO */
       gpio_map = mmap(
          NULL,             //Any adddress in our space will do
          BLOCK_SIZE,       //Map length
          PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
          MAP_SHARED,       //Shared with other processes
          mem_fd,           //File to map
          GPIO_BASE         //Offset to GPIO peripheral
       );

       close(mem_fd); //No need to keep mem_fd open after mmap

       if (gpio_map == MAP_FAILED) {
           qDebug() << "gpio_map == MAP_FAILED ";
       }

       // Always use volatile pointer!
       gpio = (volatile unsigned *)gpio_map;


}

void maskinrum::setBen(){
    INP_GPIO(2); // ben 3  -
   // OUT_GPIO(2); //
    INP_GPIO(3); // ben 5  -
   // OUT_GPIO(3); //
    INP_GPIO(4); // ben 7  -
   // OUT_GPIO(4); //
    INP_GPIO(5); // ben 29 -
   // OUT_GPIO(5); //
    INP_GPIO(6); // ben 31 -
   // OUT_GPIO(6); //
    INP_GPIO(7); // ben 24 -
   // OUT_GPIO(7); //
    INP_GPIO(8); // ben 24 -
   // OUT_GPIO(8); //
    INP_GPIO(9); // ben 21 -
   // OUT_GPIO(9); //
    INP_GPIO(10); // ben 19 -
   // OUT_GPIO(10); //
    INP_GPIO(11); // ben 23 -
    OUT_GPIO(11); //
    INP_GPIO(12); // ben 32 -
    OUT_GPIO(12); //
    INP_GPIO(13); // ben 33 -
    OUT_GPIO(13); //
    INP_GPIO(14); // ben 8  -
    OUT_GPIO(14); //
    INP_GPIO(15); // ben 10 -
    OUT_GPIO(15); //
    INP_GPIO(16); // ben 36 -
    OUT_GPIO(16); //
    INP_GPIO(17); // ben 11 -
    OUT_GPIO(17); //
    INP_GPIO(18); // ben 12 -
    OUT_GPIO(18); //
    INP_GPIO(19); // ben 35 -
    OUT_GPIO(19); //
    INP_GPIO(20); // ben 38 -
    OUT_GPIO(20); //
    INP_GPIO(21); // ben 40 -
    OUT_GPIO(21); //
    INP_GPIO(22); // ben 15 -
    OUT_GPIO(22); //
    INP_GPIO(23); // ben 16 -
    OUT_GPIO(23); //
    INP_GPIO(24); // ben 18 -
    OUT_GPIO(24); //
    INP_GPIO(25); // ben 22 -
    OUT_GPIO(25); //
    INP_GPIO(26); // ben 37 -
    OUT_GPIO(26); //
    INP_GPIO(27); // ben 13 -
   // OUT_GPIO(27); //


}

void maskinrum::setOutput(int port, int high){
    if(high==1){
        GPIO_SET = 1 << port;
    }else{
        GPIO_CLR = 1 << port;
    }
}

int maskinrum::getInput(int pin){
    setup_io();
    INP_GPIO(pin); // ben 3  -
    int val=0;
    if(GET_GPIO(pin) > 0) val = 1;
 //   qDebug() << "input pin: " << pin << " = "<< QString::number(val);
    return val;
}

