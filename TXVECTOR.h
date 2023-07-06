/*
 * txvector.h
 *
 *  Created on:  July 6 2023
 *      Author:  Dean Makoni
 */
#ifndef TXVECTOR_H_
#define TXVECTOR_H_

#include <vector>
#include <complex>
#include <iostream>

namespace halow
{

	enum  FORMAT	// Determines the format of the PPDU.
	{
		S1G,
		S1G_DUP_1M,
		S1G_DUP_2M	
	};
	
	enum  PREAMBLE_TYPE  //Determine the type of preamble of the S1G PPDU
	{       
                /*Conditon
                 *FORMAT is S1G
                 *and (CH_BANDWIDTH is CBW2 or CBW4 or CBW8 or CBW16)
                 *FORMAT is S1G_DUP_2M
                 *Otherwise not present
		 */	
		S1G_SHORT_PREAMBLE,
		S1G_LONG_PREAMBLE
	};

	enum  MU_SU   //Determine whether MU or SU of the S1G PPDU
	{
		/*FORMAT is S1G and PREAMBLE_TYPE is
	       	 *S1G_LONG_PREAMBLE and
                 *(CH_BANDWIDTH is CBW2
                 *or CBW4 or CBW8 or CBW16)
                 */

		MU, // if NUM_USERS is 2 to 4 
		SU //  if NUM_USERS is 1.		
	};
	
	enum AGGREGATION
	{
                /* Indicates whether the PSDU contains an A-MPDU.
                 */

		AGGREGATED, //indicates this packet has A-MPDU aggregation.
		NOT_AGGREGATED //indicates this packet does not have A-MPDU aggregation.
	};

	enum FEC_CODING
	{
              /* Indicates which FEC encoding is used.
                */
		
		BCC_CODING, //Indicates binary convolutional code
		LDPC_CODING //  indicates low-density parity check code
	};

	enum GI_TYPE
	{
		/*Indicates whether a short guard interval is used in the
                 * transmission of the Data field of the PPDU.
	       	*/

		LONG_GI,
		SHORT_GI
	};

       /* The following structure  is the TXVECTOR 
        * for the IEEE802.11ah
        */

	struct {

                FORMAT;
		PREAMBLE_TYPE;
		MU_SU;
		int NDP_INDICATION; //Set to 1 if this packet is one of NDP CMAC PPDUs, 0 otherwise
  		int NDP_CMAC_PPDU_BODY; //Set to concatenated bit fields, which describe the NDP
                                        //CMAC PPDU body content in one of NDP CMAC PPDU 
 		int SMOOTHING; //Indicates whether frequency domain smoothing is recommended as part of channel estimation.
	        AGGREGATION;
                unsigned char SECTOR_ID;
		int N_TX; // Indicates the number of transmit chains.
		std::vector<int>  EXPANSION_MAT;
		std::vector<int>  CHAN_MAT;
		std::vector<int>  DELTA_SNR;
		std::vector<int>  SNR;
		FEC_CODING;
		int STBC; // Indicates whether or not STBC is used
	        GI_TYPE;
		int TXPWR_LEVEL;
			

		
                } TXVECTOR;
}

