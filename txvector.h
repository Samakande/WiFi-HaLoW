/*
 * txvector.h
 *
 *  Created on: Jul 16, 2023
 *      Author: Kudzai Samakande
 */

#ifndef TXVECTOR_H_
#define TXVECTOR_H_

#include <vector>

namespace halow
{

enum  FORMAT : int   // Determines the format of the PPDU.
   {
      S1G,
      S1G_DUP_1M,
      S1G_DUP_2M
   };

   enum  PREAMBLE_TYPE : int //Determine the type of preamble of the S1G PPDU
   {
              /*Conditon
               *FORMAT is S1G
               *and (CH_BANDWIDTH is CBW2 or CBW4 or CBW8 or CBW16)
               *FORMAT is S1G_DUP_2M
               *Otherwise not present
       */
      S1G_1M_PREAMBLE,
      S1G_SHORT_PREAMBLE,
      S1G_LONG_PREAMBLE
   };

   enum  MU_SU  : int //Determine whether MU or SU of the S1G PPDU
   {
      /*FORMAT is S1G and PREAMBLE_TYPE is
           *S1G_LONG_PREAMBLE and
               *(CH_BANDWIDTH is CBW2
               *or CBW4 or CBW8 or CBW16)
               */

      MU, // if NUM_USERS is 2 to 4
      SU //  if NUM_USERS is 1.
   };

   enum AGGREGATION : int
   {
              /* Indicates whether the PSDU contains an A-MPDU.
               */

      AGGREGATED, //indicates this packet has A-MPDU aggregation.
      NOT_AGGREGATED //indicates this packet does not have A-MPDU aggregation.
   };

   enum FEC_CODING : int
   {
            /* Indicates which FEC encoding is used.
              */

      BCC_CODING, //Indicates binary convolutional code
      LDPC_CODING //  indicates low-density parity check code
   };

   enum GI_TYPE : int
   {
      /*Indicates whether a short guard interval is used in the
               * transmission of the Data field of the PPDU.
          */
      LONG_GI,
      SHORT_GI
   };


   enum CH_BANDWIDTH : int
   {
      /* Indicates the channel width of the transmitted PPDU
      */
      CBW2, // 2 MHZ
      CBW4,  // 4 MHZ
      CBW8,  // 8 MHZ
      CBW16,  // 16 MHZ
      CBW1 // 1MHZ
   };


   /*
    * mapping and modulation parameters
    */
   struct MODPARAMS
   {

        CH_BANDWIDTH channelWidth;
        int mcs;
        int Nsa;                    //Total subcarriers
        int Nsd;                    //Number of data subcarriers per OFDM symbol
        int Nbpsc;                  //Number of Bits Per Subcarrier
        int Ncbps;                  //Number of Coded Bits Per OFDM Symbol = Nbpsc * Nsd
        double Kmod;                //QAM Normalization Factor
        int Nsym;                   //Number of symbols to be modulated
        MU_SU model;

        void setCBW(CH_BANDWIDTH cbw);

        MODPARAMS(int mcs,  CH_BANDWIDTH channelWidth, MU_SU model, int length);
        int getMCS();
        int getNSA();
        int getNSYM();
        int getNSD();
        CH_BANDWIDTH getCBW();

   };


/*
* TXVECTOR is a set of parameters defined in Table 23-1
*/
class TXVECTOR
{
private:
        FORMAT format;
        PREAMBLE_TYPE preamble;
        MU_SU model;
        bool ndp_indication;
        int ndp_cmac_ppdu_body;
        bool smoothing;
        AGGREGATION aggregation;
        unsigned char sector_id;
        int ntx;
        std::vector<int>  expansion_mat;
        std::vector<int>  delta_snr;
        std::vector<int>  snr;
        FEC_CODING coding;
        bool stbc;
        GI_TYPE guard;
        int txpwr_level;
        int mcs;
        CH_BANDWIDTH cbw;
        int length;
        int apep_length;
        int psdu_length;
        std::vector<int> user_position;
        int nun_sts;
        int group_id;
        int partial_id;
        int nun_users;
        bool beam_change;
        int responce_indication;
        bool travelling_pilots;
        bool time_of_departure_requested;
        bool uplink_indication;
        int color;


public:
        TXVECTOR(FORMAT format, PREAMBLE_TYPE preamble, AGGREGATION aggregation, int mcs, CH_BANDWIDTH cbw);
        MODPARAMS params;

        //GET METHODS
        int getMCS();
        FORMAT getFORMAT();
        PREAMBLE_TYPE getPREAMBLE();
        CH_BANDWIDTH getCBW();
        int getNTX();
        MU_SU getMDL();
        bool isNDP();
        bool isSTBC();
        bool isUplink();
        int getNSTS();
        int getID();
        GI_TYPE getGUARDTYPE();
        FEC_CODING getCODING();
        int getLDPC_E();
        bool isSMOOTHING();

        bool isTP();
        bool isAGGREGATED();
        int getLENGTH();
        int getRESPONSE_IND();
        int getCRC();
};


} /* namespace halow */

#endif /* TXVECTOR_H_ */
