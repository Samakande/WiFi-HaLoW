/** * main.c */
#include "qam.h"
#include "modulator.h"
#include "symbol_mapper.h"
#include <cstring>
#include <iostream>

int main(void)
{
    const char* bitVector = "0000000100100011010001010110011110001001101010111100110111101111000000010010001101000101011001111000100110101011110011011110111100000001001000110100010101100111100010011010101111001101111011110000000100100011010001010110011110001001101010111100110111101111000000010010001101000101011001111000100110101011110011011110111100000001001000110100010101100111100010011010101111001101111011110000000100100011010001010110011110001001101010111100110111101111000000010010001101000101011001111000100110101011110011011110111100000001001000110100010101100111100010011010101111001101111011110000000100100011010001010110011110001001101010111100110111101111000000010010001101000101011001111000100110101011110011011110111100000001001000110100010101100111100010011010101111001101111011110000000100100011010001010110011110001001101010111100110111101111";
    halow::modParams params;
    params = params.mcss(2,3,"SISO");

    halow::modulator modTest{};

    std::vector<std::complex<double>> modulatedData = modTest.modulate(&params, bitVector);

    //print the constellation points
    for (int i = 0; i < params.Nsd; i++)
    {
        std::cout << "Constellation Point " << i << ": " << modulatedData[i] << std::endl;
    }
    
    // instantiate the pilot object
   halow::symbol_mapper pilotTest{};
   std::vector<std::complex<double>> pilotInserted = pilotTest.map(modulatedData); // insert the pilots and the nulls

    // print the data with the  zeros and pilots inserted
    for (int i = 0; i < pilotInserted.size(); i++)
    {
        std::cout << "Mapped Point " << i << ": " << pilotInserted[i] << std::endl;
    }
    

    return 0;

}
