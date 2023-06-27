/*
 * modulator.h
 *
 *  Created on: Jun 26, 2023
 *      Author: Kudzai Samakande
 */

/*The modulator is responsible for modulating the bit stream into constellation points(IQ samples) and pilot insertion.
 *It creates the appropriate QAM class based on the MCS value passed to it
 *Class and method prototype
 *
 */
#include <complex>
#include <vector>
#include "mcs.h"

#ifndef MODULATOR_H_
#define MODULATOR_H_

namespace halow
{

/*
 *
 */
    class modulator
    {
        public:
            modulator();
            //modulator function takes the MCS value and creates the appropriate mapper class(QAM)
            std::vector<std::complex<double>> modulate(halow::modParams* params, const char* message);
    };

} /* namespace halow */
#endif /* MODULATOR_H_ */

