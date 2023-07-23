/*
 * qam.cc
 * This is a helper class of the const_mapper class. It encodes the data bits into IQ samples
 * using grayscale coding
 *
 *  Created on: Jun 24, 2023
 *      Author: Kudzai Samakande
 */
#include "qam.h"
#include <iostream>
namespace halow
{
    //define the constructor
    QAM::QAM(int numBits, double power, int gain)
    {
        this->numBits = numBits;
        this->gain = gain;
    }

    //encode definition
    void QAM::encode(const unsigned char *bits, double &cPoint)
    {
        int pt = 0;
        int flip = 1;

        for (int i = 0; i < numBits/2; ++i)
        {
            int bit = *bits * 2 - 1; // +1 or -1
            pt = bit * flip + pt * 2;
            flip *= -bit;
            ++bits;
        }
        cPoint = pt;
    }

}
