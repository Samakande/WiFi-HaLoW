/*
 * pilot.h
 *
 *  Created on: Jun 28, 2023
 *      Author: Kudzai Samakande
 */

/* set of functions that insert the pilot tones onto dedicated subcarriers
 * the pilot position is derived from the RATE specified in the TXVECTOR
 * the size of the mapped symbols = Ndbsc
 * the polarity of the pilot subcarriers is controlled by the sequence p_n (IEEE802.11, eq:17-25)
 * n the symbol number =  0, ... NSYM – 1
 * If the value of 'n' is greater than 126, the sequence 'p_n' can be extended cyclically.
 *
*/
#include "mcs.h"

#ifndef PILOT_H_
#define PILOT_H_

namespace halow
{
    const int POLARITY[127] = {
                 1, 1, 1, 1,-1,-1,-1, 1,-1,-1,-1,-1, 1, 1,-1, 1,
                -1,-1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1,
                 1, 1,-1, 1, 1,-1,-1, 1, 1, 1,-1, 1,-1,-1,-1, 1,
                -1, 1,-1,-1, 1,-1,-1, 1, 1, 1, 1, 1,-1,-1, 1, 1,
                -1,-1, 1,-1, 1,-1, 1, 1,-1,-1,-1, 1, 1,-1,-1,-1,
                -1, 1,-1,-1, 1,-1, 1, 1, 1, 1,-1, 1,-1, 1,-1, 1,
                -1,-1,-1,-1,-1, 1,-1, 1, 1,-1, 1,-1, 1, 1, 1,-1,
                -1, 1,-1,-1,-1, 1, 1, 1,-1,-1,-1,-1,-1,-1,-1
        };

    std::vector<std::complex<double>> insertPilot(std::vector<std::complex<double>>& modulated, int n, modParams& TxVector)
    {
        /* Get pilot positions
        int* pilotPos = TxVector.pilots;
        int Nusc = TxVector.Nsd + TxVector.Nsp;

        for (int i = 0; i < TxVector.Nsp; ++i)
        {
            pilotPos[i] += Nusc / 2;
        }
        */

        // Get pilot vector and change polarity
        int Nusc = TxVector.Nsd + TxVector.Nsp;
        int P[4] = {1, 1, 1, -1};

        for (int& num : P)
        {
            num *= POLARITY[n + 1];
        }

        // Get the template
        std::vector<int>& myTemplate = TxVector.OFDM_freqTemplate;

        // Create a vector of complex numbers
        std::vector<std::complex<double>> complexVector;
        complexVector.reserve(Nusc + 1);
        int k=0;
        int j =0;
        for (size_t i = 0; i < myTemplate.size(); ++i)
        {
            if(i == myTemplate.size() / 2 ) //the dc carrier is left with a null value
            {
                continue;
            }
            // Insert pilots into their position
            else if (myTemplate[i] == 0 ) // Insert data
            {
                complexVector[i]=modulated[k];
                ++k;
                //std::cout << i<< std::endl;
            }
            else
            {
                complexVector[i]=std::complex<double>(static_cast<double>(P[j]), 0.0);;
                ++j;
            }
        }

        return complexVector;

    }

}

#endif /* PILOT_H_ */
