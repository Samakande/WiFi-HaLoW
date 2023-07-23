/** * main.c */

#include "phy_sap.h"
#include <complex>
#include <string>

int main(void)
{
    std::string payload_str = "101011101010001111010101011111100000001010111010100011110101010111111000000010101110101000111101010101111110000000";
    std::vector<unsigned char> payload(payload_str.begin(), payload_str.end());

    //MAC constructs the txvector
    halow::TXVECTOR txvector(halow::S1G, halow::S1G_SHORT_PREAMBLE, halow::NOT_AGGREGATED, 3, halow::CBW2);


    //a transmit initialization process is initiated where the plcp preamble and header are constructed
    halow::PHY_TXSTART phytxstart(payload);
    phytxstart.request(txvector);

    //transfer the payload from MAC to phy using PHY-DATA.request primitive


    //following that service bits are prepended to the psdu to form the data field
    //using the mcs and other parameters specified in txvector the data field is scrambled, encoded, interleaved
    //the phy will map the data and generate time domain ofdm samples which are then transmitted.


    return 0;
}

