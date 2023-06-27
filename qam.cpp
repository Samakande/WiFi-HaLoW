/*
 * qam.cc
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
    void QAM::encode(const char *bits, double *cPoint)
    {
        int pt = 0;
        int flip = 1;

        for (int i = 0; i < numBits/2; ++i)
        {
            int bit = (*bits-'0') * 2 - 1; // +1 or -1
            pt = bit * flip + pt * 2;
            flip *= -bit;
            ++bits;
        }
        //std::cout << "encoder called " << pt<< std::endl;
        *cPoint = pt;
    }

}
