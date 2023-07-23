/*
 * ppdu.cpp
 * The ppdu class is a container for a ppdu frame which is made up of the PHY Preamble(training fields),
 * PHY Header(SIG) and payload of bytes. The class has functions for assembling the ppdu fields.
 * The member methods computes and  return frame symbols in the time domain.
 *
 *  Created on: Jul 7, 2023
 *      Author: Kudzai Samakande
 */

#include "ppdu.h"
#include "psdu.h"
#include "preamble.h"
#include "sig.h"

namespace halow
{


    ppdu::ppdu(std::vector<unsigned char> payload, halow::MODPARAMS &params)
            :payload(payload)
             params(params){    }

    std::vector<std::complex<double> > ppdu::build_frame()
        {
        /*
         * build_psdu -> concatenates the the 8 bit service bits with the payload. Tail bits
         * and Pad bits are then appended to generate an integer number of OFDM symbols
         */
        halow::psdu generate_data_field;
        std::vector<std::complex<double>> data = generate_data_field.build_psdu(payload, params);

        /*
         * generate_stf_field method computes the short training field needed for packet detection and
         * AGC.
         * The methods generates a sequences in the frequency domain over the channel bandwidth specified
         * in the params ]'\;
         * struct.The sequence is mapped appropriately and the IDFT is computed.
         * A guard interval of 8 micro seconds is prepended and the symbol is duplicated to form two STF
         * symbols for S1G_SHORT and and S1G_LONG preambles.
         */
        std::vector<std::complex<double>> stf = halow::generate_stf_field(params);

        /*
         * generate_ltf1_field method computes the long training field needed for channel estimation
         * The method maps(the pilots are processed differently) a sequence of complex numbers generated
         * in the frequency domain over the channel bandwidth specified in the params struct.
         * The computed time samples are duplicated to form two OFDM LTF1 symbols and a double guard interval
         * of 16 micro seconds is prepended.
         */
        std::vector<std::complex<double>> ltf1 = halow::generate_ltf1_field(params);

        /*
         * The SIG field is constructed per user using parameters from the TXVECTOR such as CH_BANDWIDTH,
         * STBC, NUM_USERS, MCS, etcThe crc is calculated and appended to the list making a total of 48 uncoded bits.
         * The header is not scrambled. THe header uses BPSK mapping with 1/2 coding rate. The resulting 96 bits are
         * padded and pilots are inserted. This produces two OFDM symbols for the SIG field in both the
         * LONG and SHORT preamble.
         */
        std::vector<std::complex<double>> sig = halow::encode_header(params);

        // Reserve enough space in the samples vector to avoid unnecessary reallocations
        std::vector<std::complex<double>> samples;
        samples.reserve(stf.size() + ltf1.size() + sig.size() + data.size());

        samples.insert(samples.end(), stf.begin(), stf.end());
        samples.insert(samples.end(), ltf1.begin(), ltf1.end());
        samples.insert(samples.end(), sig.begin(), sig.end());
        samples.insert(samples.end(), data.begin(), data.end());

        //The returned samples can be passed to the transmitting block
        return samples;

    }

} /* namespace halow */
