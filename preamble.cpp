/*
 * Dean Makoni
 * 07 July 2023
 */

#include "preamble.h"
#include "TXVECTOR.h"

namespace halow{

	/*!
     *  -Initializations
     */
    {
    }
   
    std::vector<std::complex<double>>  preamble::sequence_generation()
    {
	string preamble_type = TXVECTOR.PREAMBLE_TYPE;

		if (preamble_type == S1G_SHORT_PREAMBLE)
		{
			//Determine the CH_BANDWIDTH from the TXVECTOR
			string ch_bandwidth = TXVECTOR.CH_BANDWIDTH;
			switch (ch_bandwidth){

			// Generating the STF field in the frequency domain over the bandwidth indicated
				case "CBW2":
					    const std::vector<std::complex<double>> sequence =
   					   {
       						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
       					        { 0, 0},
						{ 1, 1},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ -1, -1},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 1, 1},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ -1, -1},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ -1, -1},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 1, 1},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ -1, -1},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ -1, -1},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
       					        { 1, 1},
      					        { 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 1, 1},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 1, 1},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 1, 1},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0},
						{ 0, 0}
	
   					   };

				preamble::generated_sequence = sequence;
	
				break;
				case "CBW4":
				break;
				case "CBW8":
				break;
				case "CBW16":
				break;
			}
                }
		else if (preamble_type ==  S1G_LONG_PREAMBLE)
		{
		}
		else
		{
		}
    }      

		/*!
                 *\ Method used to rotate the frequency domain symbols
                 */
		std::vector<std::complex<double>>  preamble::phase_rotate() {
		
		// Determine the bandwidth irst before rotation
			 string ch_bandwidth = TXVECTOR.CH_BANDWIDTH;
                         switch (ch_bandwidth){
				
				case "CBW1":
					// For 1MHz channel all the sequences are  rotated by a gamma = 1
					preamble::phaserotated_sequence = preamble::generated_sequence;
				break;
				case "CBW2":
					// For 2MHz channe; all the sequences are rotated by gamma = 1 
					preamble::phaserotated_sequence = preamble::generated_sequence;
				break;
				case "CBW4":
					//For a 4 MHz PPDU transmissions of S1G or S1G_DUP_2M frames
					// gamma is 1 for k < 0
					// gamma is j for k >= 0
					for ( int k = 0, k < 128, k++){
						if (k < 64){
							 preamble::phaserotated_sequence[k] = preamble::generated_sequence[k];
						}
						else{
							preamble::phaserotated_sequence[k] = preamble::generated_sequence[k]*std::complex<double> complex (0, 1);
						}
					}
				break;
				case "CBW8":
					//For 8 MHz PPDU transmission of S1G or S1G_DUP_2M frame
					//  gamma = 1 for k < -64
					//  gamma = -1 for k > -64
					for ( int k = 0, k < 256, k++){
                                                if (k < 64){
                                                         preamble::phaserotated_sequence[k] = preamble::generated_sequence[k];
                                                }
                                                else{
                                                        preamble::phaserotated_sequence[k] = preamble::generated_sequence[k]*-1;                                                       
                                        }
				}
				break;
				case "CBW16":
					// For 16 MHz PPDU transmissions of S1G or S1G_DUP_2M frames
					// gamma = 1 , k < -192
					// gamma = -1, -192 <= k < 0
					// gamma =  1, 0 <= k  < 64
					// gamma = -1, k > 64
					for ( int k = 0, k < 512, k++){
                                                if (k < 192){
                                                         preamble::phaserotated_sequence[k] = preamble::generated_sequence[k];
                                                }
						else if (k >= 192 && k < 256){
							 preamble::phaserotated_sequence[k] = preamble::generated_sequence[k]*-1;
						}
						else if (k >= 256 && k < 320) {
							 preamble::phaserotated_sequence[k] = preamble::generated_sequence[k]*1;
						}
                                                else{
                                                        preamble::phaserotated_sequence[k] = preamble::generated_sequence[k]*-1;        
                                               }
					}
				break;
                         }

    		}
}
