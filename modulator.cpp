/*
 * modulator.cpp
 *
 *  Created on: Jun 26, 2023
 *      Author: Kudzai Samakande
 */

#include "modulator.h"
#include <iostream>
#include "qam.h"
#include <cstring>
#include <vector>
namespace halow
{

    modulator::modulator()
    {
        // TODO Auto-generated constructor stub

    }



    std::vector<std::complex<double>> modulator::modulate(halow::modParams* params, const char* message)
    {
        double mod_data_buffer [params->Nsd*2];
        switch (params->mcs)
        {
            case 0: case 10:
                for(int i=0; i<params->Nsd; i++)
                {
                    halow::QAM bpsk(params->Nbpsc,1);
                    bpsk.encode(&message[i], &mod_data_buffer[i*2]);
                }
                break;

            case 1: case 2:
                for(int i=0; i<params->Nsd; i++)
                {
                    halow::QAM qpsk(params->Nbpsc,1);
                    qpsk.encode(&message[i*2], &mod_data_buffer[i*2]);
                    qpsk.encode(&message[i*2+1], &mod_data_buffer[i*2+1]);
                }
                break;


            case 3: case 4:
                for(int i=0; i<params->Nsd; i++)
                {
                    halow::QAM qam_16(params->Nbpsc,1);
                    qam_16.encode(&message[i*4], &mod_data_buffer[i*2]);
                    qam_16.encode(&message[i*4+2], &mod_data_buffer[i*2+1]);
                }
                break;



            case 5: case 6: case 7:
                for(int i=0; i<params->Nbpsc; i++)
                {
                    halow::QAM qam_64(params->Nbpsc,1);
                    qam_64.encode(&message[i*6], &mod_data_buffer[i*2]);
                    qam_64.encode(&message[i*6+3], &mod_data_buffer[i*2+1]);
                }
                break;

            case 8: case 9:
                for(int i=0; i<params->Nsd; i++)
                {
                    halow::QAM qam_256(params->Nbpsc,1);
                    qam_256.encode(&message[i*8], &mod_data_buffer[i*2]);
                    qam_256.encode(&message[i*8+4], &mod_data_buffer[i*2+1]);
                }
                break;
        }

        //rearrange the modulated data buffer into an array of IQ complex numbers
        std::vector<std::complex<double>> modulatedData(params->Nsd);
        std::memcpy(&modulatedData[0], &mod_data_buffer[0], params->Nsd * sizeof(std::complex<double>));
        return modulatedData;
    }


} /* namespace halow */
