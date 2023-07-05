/*
 * pilot.h
 *
 *  Created on: Jul 5, 2023
 *      Author: Kudzai Samakande
 */

#ifndef PILOT_H_
#define PILOT_H_

#include "txvector.h"
#include <complex>
#include <vector>

namespace halow
{



    std::vector<std::complex<double>> insertPilot(std::vector<std::complex<double>> &psdu, modParams& TxVector,  int n);

} /* namespace halow */

#endif /* PILOT_H_ */
