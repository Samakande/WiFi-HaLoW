\/*
 * preamble.h
 *header file used  to generate preamble for the S1G_SHORT, S1G_LONG and S1G_1MHZ
 * 07 July 2023
 * Dean Makaoni
 * 
 */
#ifndef PREAMBLE_H_
#define PREAMBLE_H_

#include "const_mapper.h"
#include "pilot.h"
#include "fft.h"
#include "TXVECTOR.h"
#include <cstring>
#include <iostream>

namespace halow
{

/*
 *
 */
class preamble
{
	public:
		/*!
                 *\Constructor for the preamble
                 */

   		 preamble();

                /*!
		 * \Method used for sequence generation of the STF and LFT
                 * \ Arguments of the method depends on the TXVECTOR parameter
		 * \ Return a complex vector of the sequence
                 */

  		 std::vector<std::complex<double>> sequence_genaration();

		/*!
		 *\Method used for phase rotation of the generated sequence
		 *\ Return a complex vector of the sequence after phase rotating
		 */

		 std::vector<std::complex<double>> phase_rotate();

		/*!
		 *\ Method used for PHTLTF matrix mapping
		 * \ Return a complex vector after multiplying by the  PHTLTF matrix
		 */

		std::vector<std::complex<double> > phtltf_map();

		/*!
		 *\ Method used for CSD mapping
		 * \ returns a complex vector
		 */

                std::vector<std::complex<double> > csd_map(std::vector<std::complex<double> > sequence);

		/*!
		 *\ Method used for spatial mapping
		 *\ Returns a complex vector
		 */

		std::vector<std::complex<double> > spatial_map(std::vector<std::complex<double>> sequence);

		private:
			const std::vector<std::complex<double>> stf_sequence;
			const std::vector<std::complex<double>> ltf_sequence;
			const std::vector<std::complex<double>> stf_sequence;
			const std::vector<std::complex<double>> ltf_sequence;
			const std::vector<std::complex<double>> phtltf_sequence;
			const std::vector<std::complex<double>> Altf_sequence;
};

} /* namespace halow */

#endif /* PREAMBLE_H_ */
