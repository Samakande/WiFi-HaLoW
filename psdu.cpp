/*
 * psdu.cpp
 *
 *  Created on: Jul 5, 2023
 *      Author: Kudzai Samakande
 */

#include "psdu.h"

namespace halow
{

    psdu::psdu()
    {
        // TODO Auto-generated constructor stub

    }

    std::vector<std::complex<double>> psdu::build_psdu( const char* bitVector, halow::modParams params)
    {
        //PHY padding: Append the PHY pad bits to the PSDU

                //Scramble
                //BCC encoder
                //Stream Parse
                //Segment parser (if needed)
                //BCC interleaver

                halow::const_mapper data_field_symbol_gen;

                std::vector<std::complex<double>> symbols = data_field_symbol_gen.map(params, bitVector); //Constellation mapper

                //segment disparser
                //Apply STBC

                std::vector<std::complex<double>> symbols_pilots = insertPilot(symbols, params, 1); //Pilot insertion

                //CSD
                //Spatial mapping
                //Phase rotation

                //IDFT
                halow::fft myFFT;
                myFFT.inverseFFT(symbols_pilots , params);

                //Insert GI and windowing
                std::vector<std::complex<double>> payload = myFFT.insertGI(symbols_pilots, params, 8);

                return payload;
    }

} /* namespace halow */
