/*
 * data.h
 *
 *  Created on: Jul 19, 2023
 *      Author: Kudzai Samakande
 */

#ifndef DATA_H_
#define DATA_H_

#include "const_mapper.h"
#include "pilot.h"
#include "fft.h"
#include <cstring>
#include <iostream>

namespace halow
{

/*
 *
 */
std::vector<std::complex<double>> generate_data_field( std::vector<unsigned char> &psdu, halow::TXVECTOR &txvector)
{
    // Concatenate the service and psdu //data = psdu.apppend(service)
    /*
     *PHY padding: Append the PHY pad bits to the PSDU
     *Zero to seven PHY padding bits are appended to the PSDU to make the number of bits in the coded
     *PSDU an integer multiple of the number of coded bits per OFDM symbol.
     */

    //Scramble
    //BCC encoder
    //Stream Parse
    //Segment parser (if needed)
    //BCC interleaver

    halow::const_mapper map;

    std::vector<std::complex<double>> payload = map.map(txvector.params, psdu.data()); //Constellation mapper

    //segment disparser
    //Apply STBC

    //Pilot insertion
    std::vector<std::complex<double>> symbols = insertPilot(payload, txvector.params, 1);

    //CSD
    //Spatial mapping
    //Phase rotation

    //IDFT
    halow::fft myFFT;
    myFFT.inverseFFT(symbols , txvector.params);

    //Insert GI and windowing
    std::vector<std::complex<double>> data = myFFT.insertGI(symbols, txvector.params, 8);

    return data;
}

} /* namespace halow */

#endif /* DATA_H_ */
