/*
 * const_mapper.h
 * Generates the frequency domain symbols by grouping the bits into complex values
 *
 *  Created on: Jul 4, 2023
 *      Author: Kudzai Samakande
 */

#ifndef CONST_MAPPER_H_
#define CONST_MAPPER_H_

#include "txvector.h"
#include <vector>
#include <complex>

namespace halow
{

    class const_mapper
    {
        public:
            const_mapper();
            //member method to map the interleaved data stream to complex constellation points
            std::vector<std::complex<double>> map(halow::MODPARAMS &params, const unsigned char *message);
            std::vector<std::complex<double>> demap();
    };

} /* namespace halow */

#endif /* CONST_MAPPER_H_ */
