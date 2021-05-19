#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>


int main()
{
    int fd =  wiringPiI2CSetup(7);
    int M;
    while(1){
        unsigned char a = wiringPiI2CRead(fd);

        short int c = (int)a;

        std::cout << c << std::endl;

        if(c == 5){
            M = 0;
        }
        if(c > 5){
            M = 1;
        }
//        if(c < 5){
//            M = 2;
//        }
        //std::cout << M << std::endl;
        wiringPiI2CWrite(fd, M);

        }
    return 0;
}
