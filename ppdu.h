/*
 * ppdu.h
 * The ppdu class is a container for a ppdu which is made up of the PHY Preamble(training fields),
 * PHY Header and payload of bytes. The class has functions for assembling the ppdu(encoding)
 * and decoding the header and payload based on the modulation parameters.
 *
 *  Created on: Jul 7, 2023
 *      Author: Kudzai Samakande
 */

#ifndef PPDU_H_
#define PPDU_H_

#include "txvector.h"

namespace halow
{

/*
 *
 */
class ppdu
{
private:
    std::vector<unsigned char> payload; //!< This PPDU's payload
    halow::modParams &params;

public:

    /*
     * constructor for a NULL DATA PPDU (NDP)
     */
    ppdu();

    /*
     * Constructor for ppdu with payload and modulation parameters known.
     * The payload is the MPDU to be transmitted
     * params is a struct of the modulation parameters for this frame
     */
    ppdu(std::vector<unsigned char> payload, halow::modParams &params);

    /*
     * build frame is a public interface for assembling the PPDU constituent
     * fields.
     * returns the time domain modulated data as a vector of complex numbers
     *
     */
    std::vector<std::complex<double> > build_frame();
};

} /* namespace halow */

#endif /* PPDU_H_ */
