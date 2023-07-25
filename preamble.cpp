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
    preamble::preamble():
    {
    }
   
    std::vector<std::complex<double>>  preamble::sequence_generation()
    {
	string preamble_type = TXVECTOR.PREAMBLE_TYPE;

		if (preamble_type == S1G_SHORT_PREAMBLE)
		{
			//Determine the CH_BANDWIDTH from the TXVECTOR
			string ch_bandwidth = TXVECTOR.CH_BANDWIDTH;
			string format = TXVECTOR.FORMAT; 
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

				preamble::stf_sequence = sequence;
	
				break;
				case "CBW4":
				break;
				case "CBW8":
				break;
				case "CBW16":
				break;
			}
			// generating LTF for  S1G_SHORT PPDU
			switch(format){
				case "S1G":
					if (ch_bandwidth == "CBW2"){
						
					const std::vector<std::complex<double>> sequence1 =
   					   {
						{0,0},{0,0},{0,0},{0,0}
						{1,0},{1,0},
       						{1,0}, {1,0}, {–1,0}, {–1,0},
						{ 1,0}, {1,0}, {–1,0}, {1,0},
						{ –1,0}, {1,0}, {1,0}, {1,0},
						{ 1,0}, {1,0}, {1,0}, {–1,0},
						{ –1,0}, {1,0}, {1,0}, {–1,0},
						{1,0}, {–1,0}, {1,0}, {1,0}, {1,0}, {1,0},
						{0,0}
						{1,0}, {–1,0}, {–1,0}, {1,0}, {1,0}, {–1,0},
						{ 1,0}, {–1,0}, {1,0}, {–1,0}, {–1,0}, {–1,0},
						 {–1,0}, {–1,0}, {1,0}, {1,0}, {-1,0}, {–1,0},
						 {1,0}, {–1,0}, {1,0}, {–1,0}, {1,0}, {1,0},
						{1,0}, {1,0},
						{-1,0}, {-1,0},
						{0,0}, {0,0},{0,0}
	
   					   };

					preamble::ltf_sequence = sequence1;
					}
					else if (ch_bandwidth == "CBW4"){
						
					}
					else if (ch_bandwidth == "CBW8"){
					}
					else{
					}
				break;
				case "S1G_DUP_1M":
				break;
				case "S1G_DUP_2M":
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
					preamble::phaserotated_stf = preamble::stf_sequence;
					preamble::phaserotated_ltf = preamble::ltf_sequence;
				break;
				case "CBW2":
					// For 2MHz channe; all the sequences are rotated by gamma = 1 
					preamble::phaserotated_stf = preamble::stf_sequence;
					preamble::phaserotated_stf = preamble::ltf_sequence;
				break;
				case "CBW4":
					//For a 4 MHz PPDU transmissions of S1G or S1G_DUP_2M frames
					// gamma is 1 for k < 0
					// gamma is j for k >= 0
					for ( int k = 0, k < 128, k++){
						if (k < 64){
							 preamble::phaserotated_stf[k] = preamble::stf_sequence[k];
							 preamble::phaserotated_ltf[k] = preamble::ltf_sequence[k];
						}
						else{
							preamble::phaserotated_stf[k] = preamble::stf_sequence[k]*std::complex<double> complex (0, 1);
							preamble::phaserotated_ltf[k] = preamble::ltf_sequence[k]*std::complex<double> complex (0, 1);
						}
					}
				break;
				case "CBW8":
					//For 8 MHz PPDU transmission of S1G or S1G_DUP_2M frame
					//  gamma = 1 for k < -64
					//  gamma = -1 for k > -64
					for ( int k = 0, k < 256, k++){
                                                if (k < 64){
                                                         preamble::phaserotated_stf[k] = preamble::stf_sequence[k];
							 preamble::phaserotated_ltf[k] = preamble::ltf_sequence[k];
                                                }
                                                else{
                                                        preamble::phaserotated_stf[k] = preamble::stf_sequence[k]*-1;
                                                        preamble::phaserotated_ltf[k] = preamble::ltf_sequence[k]*-1;                     
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
                                                         preamble::phaserotated_stf[k] = preamble::stf_sequence[k];
							 preamble::phaserotated_ltf[k] = preamble::ltf_sequence[k];
                                                }
						else if (k >= 192 && k < 256){
							 preamble::phaserotated_stf[k] = preamble::stf_sequence[k]*-1;
							 preamble::phaserotated_ltf[k] = preamble::ltf_sequence[k]*-1;
						}
						else if (k >= 256 && k < 320) {
							 preamble::phaserotated_stf[k] = preamble::stf_sequence[k]*1;
							 preamble::phaserotated_ltf[k] = preamble::ltf_sequence[k]*1;
						}
                                                else{
                                                        preamble::phaserotated_stf[k] = preamble::stf_sequence[k]*-1;
							preamble::phaserotated_ltf[k] = preamble::ltf_sequence[k]*-1;        
                                               }
					}
				break;
                         }

    		}

		std::vector<std::complex<double>>  preamble::phtltf_map(){
			// matrix mapping: Apply the mapping of the first column of the  PHTLTF matrix
			preamble::phtltf = preamble::phaserotated_stf;
			preamble::Altf = preamble::phaserotated_ltf; 			
		}

		std::vector<std::complex<double>>  preamble::csd_map(){
			//Apply CSD for each space-time stream and frequency segment
			
		}

		std::vector<std::complex<double>>  preamble::spatial_map(){
			//Spatial mapping: Apply the Q matrix
		}
}
