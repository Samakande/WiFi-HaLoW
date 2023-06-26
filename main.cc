

/**
 * main.c
 */
#include "qam.h"
#include <complex>
#include <vector>
#include <cstring>
#include <iostream>

int main(void)
{
    const char* bitVector = "0000000100100011010001010110011110001001101010111100110111101111";
    int numSymbols = 16;
    int* mod_data_buffer = new int[numSymbols * 2];
    for(int i=0; i<numSymbols; i++)
    {
        halow::QAM qam16(2, 1);
        qam16.encode(&bitVector[i*4], &mod_data_buffer[i*2]); // I
        qam16.encode(&bitVector[i*4+2], &mod_data_buffer[i*2+1]); // Q
    }

    //rearrange mod_data_buffer into an array of complex numbers. Pass by reference to save time
    std::complex<int> modulatedData[numSymbols];
    std::memcpy(&modulatedData[0], &mod_data_buffer[0], numSymbols * sizeof(std::complex<int>));

    //print the constellation points
    for (int i = 0; i < numSymbols; i++)
    {
        std::cout << "Constellation Point " << i << ": " << modulatedData[i] << std::endl;
    }

    delete[] mod_data_buffer;
    return 0;
}
