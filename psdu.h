/*
 * psdu.h
 *
 *  Created on: Jul 5, 2023
 *      Author: Kudzai Samakande
 */

#ifndef PSDU_H_
#define PSDU_H_

#include "const_mapper.h"
#include "pilot.h"
#include "fft.h"
#include <cstring>
#include <iostream>

namespace halow
{

/*
 *
 */
class psdu
{
public:
    psdu();
    std::vector<std::complex<double>> build_psdu( const char* message, halow::modParams params);
};

} /* namespace halow */

#endif /* PSDU_H_ */
