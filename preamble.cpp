/*
 * preamble.cpp
 *
 *  Created on: Jul 6, 2023
 *      Author: Kudzai Samakande
 */

#include "preamble.h"
#include "const_mapper.h"
#include "fft.h"
#include "pilot.h"
#include <bitset>
#include <string>
#include <algorithm>
#include <cstring>

namespace halow
{

    /*
     * generate short training field
     */
    std::vector<std::complex<double>> generate_stf_field(halow::TXVECTOR &txvector)
    {
        switch (txvector.getCBW())
        {

            case CBW2:
                //Sequence generation in the frequency domain over the bandwidth
                for (auto& e : STF_2M)
                {
                    e *= 1 / std::sqrt(24); /*The normalization factor is the QPSK normalization multiplied by sqr(1/Ntone) */
                }

                /* Phase rotation Y_k,2 =1*/

                /* PHTLTF matrix mapping: PHTLTF_1,1 = 1
                 * PHTLTF_2,1 = 1
                 * PHTLTF_3,1 = 1
                 * PHTLTF_4,1 = -1
                 */

                /*
                 * CSD, for single spatial stream (Nsts=1) Tcs = 0
                 */

                /*
                 * IDFT
                 */
                halow::MODPARAMS params(txvector.getMCS(),  txvector.getCBW(), txvector.getMDL(), 8/*length of the symbols in octects*/);
                halow::fft myFFT;
                myFFT.inverseFFT(STF_2M , params);

                //Insert GI and windowing
                std::vector<std::complex<double>> stf= myFFT.insertGI(STF_2M, params, 8);

                return stf;


            /*
             * case CBW4: case CBW8:case CBW16:
             */

            /*default:
                break;*/
        }
    }

    /*
     * generate long training field
     */
    std::vector<std::complex<double>> generate_ltf1_field(halow::TXVECTOR &txvector)
    {
        switch (txvector.getCBW())
        {

            case CBW2:
                //Sequence generation in the frequency domain over the bandwidth
                for (auto& e : LTF_2M)
                {
                    e *= 1 / std::sqrt(56); /*The normalization factor is sqr(1/Ntone) */
                }

                /* Phase rotation Y_k,2 =1*/

                /* PHTLTF matrix mapping: ALTF_1,1 = 1
                 * ALTF_2,1 = 1
                 * ALTF_3,1 = 1
                 * ALTF_4,1 = -1
                 */

                /*
                 * CSD, for single spatial stream (Nsts=1) Tcs = 0
                 */

                /*
                 * IDFT
                 */
                halow::MODPARAMS params(txvector.getMCS(),  txvector.getCBW(), txvector.getMDL(), 8/*length of the symbols in octects*/);
                halow::fft myFFT;
                myFFT.inverseFFT(LTF_2M , params);

                //Insert GI and windowing
                std::vector<std::complex<double>> ltf1= myFFT.insertGI(LTF_2M, params, 16/* micro seconds guard interval*/);
                ltf1.insert(ltf1.end(), LTF_2M.begin(), LTF_2M.end()); //create a two symbol lft1 field with a double guard interval
                return ltf1;

            /*
             * case CBW4: case CBW8:case CBW16:
             */

            /*default:
                break;*/
        }
    }


    /*
     * generate the SIG field of short preamble
     */
    std::vector<std::complex<double>> generate_sig_field(halow::TXVECTOR &txvector)
    {

        long sig_1 = 0b1 << 23 | txvector.isSTBC() << 22 | txvector.isUplink() << 21 | txvector.getCBW() << 19 | txvector.getNSTS() << 17 | txvector.getID() << 8 | txvector.getGUARDTYPE() << 7 | txvector.getCODING() << 6 | txvector.getLDPC_E() << 5 | txvector.getMCS() << 1 | txvector.isSMOOTHING();

        long sig_2 = txvector.isAGGREGATED() << 23 | txvector.getLENGTH() << 14 | txvector.getRESPONSE_IND() << 12 | txvector.isTP() << 11 | txvector.isNDP() << 10 | txvector.getCRC() << 6 ;

        std::string samples = std::bitset<24>(sig_1).to_string() + std::bitset<24>(sig_2).to_string();

        /*48 uncoded bits*/
        std::vector<unsigned char> sig(samples.begin(), samples.end());

        /*
        * BCC encoder
        * BCC interleaver
        */

        sig.insert(sig.end(), sig.begin(), sig.end());; /*to delete after implementing encoder and interleaver*/

        /*
         * mapping the 96 coded and interleaved bits
         */
        halow::MODPARAMS params(0,  halow::CBW2, txvector.getMDL(), 16/*length of the symbols in octects*/);

        halow::const_mapper mapper;

        std::vector<std::complex<double>> sig_symbols = mapper.map(params, sig.data());

        /* The insertPilot method works with 52 data subcarriers not 48 therefore perform the
        * appropriate zero padding per symbol
        */
        std::vector<std::complex<double>> sig_buffer(104);

        memcpy(&sig_buffer[2], &sig_symbols[0], 48 * sizeof(std::complex<double>));
        memcpy(&sig_buffer[54], &sig_symbols[48], 48 * sizeof(std::complex<double>));

        //pilot insertion
        std::vector<std::complex<double>> sig_field = halow::insertPilot(sig_buffer, params, 0);

        // PHTLTF matrix mapping:
        // CSD, for single spatial stream (Nsts=1) Tcs = 0
        // No spatial mapping

        /*duplication and phase rotation*/
        params.setCBW(txvector.getCBW());

        // IDFT
        halow::fft myFFT;
        myFFT.inverseFFT(sig_field, params);

        //Insert GI and windowing
        std::vector<std::complex<double>> sig_field_p= myFFT.insertGI(sig_buffer, params, 8);


        return sig_field_p;
    }


} //namespace halow
