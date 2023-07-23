/*
 * pilot.cpp
 *
 *  Created on: Jul 5, 2023
 *      Author: Kudzai Samakande
 */

#include "pilot.h"
#include <iostream>

namespace halow
{

const double POLARITY[127] = {
             1, 1, 1, 1,-1,-1,-1, 1,-1,-1,-1,-1, 1, 1,-1, 1,
            -1,-1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1,
             1, 1,-1, 1, 1,-1,-1, 1, 1, 1,-1, 1,-1,-1,-1, 1,
            -1, 1,-1,-1, 1,-1,-1, 1, 1, 1, 1, 1,-1,-1, 1, 1,
            -1,-1, 1,-1, 1,-1, 1, 1,-1,-1,-1, 1, 1,-1,-1,-1,
            -1, 1,-1,-1, 1,-1, 1, 1, 1, 1,-1, 1,-1, 1,-1, 1,
            -1,-1,-1,-1,-1, 1,-1, 1, 1,-1, 1,-1, 1, 1, 1,-1,
            -1, 1,-1,-1,-1, 1, 1, 1,-1,-1,-1,-1,-1,-1,-1};

//basic pilot patterns Table 19.19
std::complex<double> p_values_11 [4] = {{1, 0},{1, 0},{1, 0},{-1, 0}};

const int pilotPosition_1 [2]={-7,7};
const int pilotPosition_2 [4]={-21,-7,7,21};
const int pilotPosition_4 [6]={-53,-25,-11,11,25,53};
const int pilotPosition_8 [8]={-103,-75,-39,-11,11,39,75,103};
const int pilotPosition_16 [16]={-231,-203,-167,-139,-117,-89,-53,-25,25,53,89,117,139,167,203,231};

std::vector<std::complex<double>> insertPilot(std::vector<std::complex<double>> &psdu, halow::MODPARAMS &params,  int n)
    {

        int psdu_length = psdu.size()/params.getNSD(); //PSDU length in terms of the OFDM symbols
        std::cout << "psdu_length " << psdu_length << std::endl;
        std::vector<std::complex<double> > data(params.getNSA() * psdu_length);
        std::vector<std::complex<double>>::iterator point = data.begin();
        std::complex<double> null_value = std::complex<double>(0, 0);

        switch (params.getCBW())
        {
            case(CBW2):
                    for(int s = 0; s < psdu_length; s++)
                    {
                       int pilot_index = 0;
                       int psdu_index =0;
                       for(int k = -32; k <= 31; k++)
                       {

                           if(k<-28 || k>28 || k == 0)
                           {
                               *point = null_value;
                               point++;
                           }

                           else if (k==pilotPosition_2[pilot_index])
                           {
                               *point =p_values_11[pilot_index++] * POLARITY[(s+n) % 127]; //n indicates if its a data symbol(n=1) or SIG symbol(n=0)
                               point++;
                           }

                           else
                           {
                               *point =psdu[(psdu_index++) + s*params.Nsd];
                               point++;
                           }
                       }

                    }
                    return data;

            default:
                   break;
        }
    }

} /* namespace halow */
