/*
 * sig.h
 *
 *  Created on: Jul 6, 2023
 *      Author: Kudzai Samakande
 */

#ifndef SIG_H_
#define SIG_H_

#include "txvector.h"
#include "pilot.h"


namespace halow
{
    std::vector<std::complex<double>> encode_header(halow::modParams params)
    {
        //Obtain the following:
        /*
        CH_BANDWIDTH
        STBC
        PARTIAL_AID
        NUM_STS
        GI_TYPE
        FEC_CODING
        MCS
        SMOOTHING
        NUM_USERS
        LENGTH
        AGGREGATION
        RESPONSE_INDICATION
        NDP_INDICATION
        TRAVELLING_PILOTS
        UPLINK_INDICATION
        COLOR
        */

        //Add the reserved bits
        //Append the calculated 4bit CRC
        //Append N_tail tail bits

        //48 uncoded bits
        /*
         * BCC encoder
         * BCC interleaver
         * BPSK Constellation mapper (96 IQ samples) std::vector<std::complex<double>> sig_symbols (96)
         * The insertPilot method works with 52 data subcarriers not 48 therefore perform the
         * appropriate zero padding per symbol
         */

         std::vector<std::complex<double>> sig_buffer(104);
         for (int i =0; i<2; i++)
         {
            sig_buffer.insert(sig_buffer.begin()+2+52*(i+1), sig_symbols.begin()+48*i, sig_symbols.begin+48*(i+1));

         }



         //pilot insertion
         std::vector<std::complex<double>> sig_field = insertPilot(sig_buffer, params, 0);

         // PHTLTF matrix mapping:
         // CSD, for single spatial stream (Nsts=1) Tcs = 0
         // No spatial mapping

         // IDFT
         halow::fft myFFT;
         myFFT.inverseFFT(sig_buffer, params);
         //divide by 1/(Ntone)^0.5 sqr(1/12)

         //Insert GI and windowing
         std::vector<std::complex<double>> sig_field= myFFT.insertGI(sig_buffer, params, 8);


         return sig_field;

    }
}



#endif /* SIG_H_ */
