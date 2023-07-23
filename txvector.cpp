/*
 * txvector.cpp
 *
 *  Created on: Jul 16, 2023
 *      Author: Kudzai Samakande
 */

#include "txvector.h"
#include <cstdio>
#include <iostream>
#include <complex>

namespace halow
{

TXVECTOR::TXVECTOR(FORMAT format, PREAMBLE_TYPE preamble, AGGREGATION aggregation, int mcs, CH_BANDWIDTH cbw)
            :
                format(format),
                preamble(preamble),
                model(SU),
                ndp_indication(false),
                /*ndp_cmac_ppdu_body(),*/
                /*smoothing(false),*/
                aggregation(aggregation),
                /*sector_id(),*/
                ntx(1),
                /* expansion_mat,
                 * std::vector<int>  delta_snr,
                 */
                coding(BCC_CODING),
                stbc(false),
                guard(SHORT_GI),
                //txpwr_level,
                mcs(mcs),
                cbw(cbw),
                length(length),
                /*
                 * apep_length,
                 * psdu_length,
                 *             user_position,
                */
                nun_sts(1),
                /*
                 * group_id,
                 * partial_id,
                 */
                nun_users(1),
                beam_change(false),
                responce_indication(0),
                travelling_pilots(false),
                time_of_departure_requested(false),
                uplink_indication(false),
                color(0),
                params(mcs,  cbw, model, length)

    {
    } /*TEXVECTOR constructor*/

//get methods
int TXVECTOR::getMCS(){return mcs;}
FORMAT TXVECTOR::getFORMAT() {return format;}
PREAMBLE_TYPE TXVECTOR::getPREAMBLE(){return preamble;}
CH_BANDWIDTH TXVECTOR::getCBW(){return cbw;}
int TXVECTOR::getNTX(){return ntx;}
MU_SU TXVECTOR::getMDL(){return model;}
bool TXVECTOR::isNDP(){return ndp_indication;}
bool TXVECTOR::isSTBC(){return stbc;}
bool TXVECTOR::isUplink(){return uplink_indication;}
int TXVECTOR::getNSTS(){return nun_sts;}
int TXVECTOR::getID(){return group_id;}
GI_TYPE TXVECTOR::getGUARDTYPE(){return guard;}
FEC_CODING TXVECTOR::getCODING(){return coding;}
int TXVECTOR::getLDPC_E(){return 0;}
bool TXVECTOR::isSMOOTHING(){return smoothing;}

bool TXVECTOR::isTP(){return travelling_pilots;}
bool TXVECTOR::isAGGREGATED(){return aggregation;}
int TXVECTOR::getLENGTH(){return length;}
int TXVECTOR::getRESPONSE_IND(){return responce_indication;}
int TXVECTOR::getCRC(){return 2;}

MODPARAMS::MODPARAMS(int mcs,  CH_BANDWIDTH channelWidth, MU_SU model, int length)
        :mcs(mcs),
         channelWidth(channelWidth),
         model(model)
   {
       switch (channelWidth)
       {
           // channel width 1 MHz
           case CBW1:
               Nsa = 32;
               Nsd = 24;
               Nsym = length*8 / Nsa;

               if (model == SU)
               {
                   switch (mcs)
                   { //cases for all 10 possible values of the modulation and coding scheme
                       case 0:                 //BPSK Rate = 1/2
                           Nbpsc = 1;
                           Ncbps = 24;
                           Kmod = 1;
                           break;
                       case 1:                 //QPSK 1/2
                           Nbpsc = 2;
                           Ncbps = 48;
                           Kmod = 1 / sqrt(2);
                           break;
                       case 2:                 //QPSK 3/4
                           Nbpsc = 2;
                           Ncbps = 48;
                           Kmod = 1 / sqrt(2);
                           break;
                       case 3:                 //16-QAM 1/2
                           Nbpsc = 4;
                           Ncbps = 96;
                           Kmod = 1 / sqrt(10);
                           break;
                       case 4:                 //16-QAM 3/4
                           Nbpsc = 4;
                           Ncbps = 96;
                           Kmod = 1 / sqrt(10);
                           break;
                       case 5:                 //64-QAM 2/3
                           Nbpsc = 6;
                           Ncbps = 144;;
                           Kmod = 1 / sqrt(42);
                           break;
                       case 6:                 //64-QAM 3/4
                           Nbpsc = 6;
                           Ncbps = 144;
                           Kmod = 1 / sqrt(42);
                           break;
                       case 7:                 //64-QAM 5/6
                           Nbpsc = 6;
                           Ncbps = 144;
                           Kmod = 1 / sqrt(42);
                           break;
                       case 8:                 //256-QAM 3/4
                           Nbpsc = 8;
                           Ncbps = 192;
                           Kmod = 1 / sqrt(170);
                           break;
                       case 9:                 //256-QAM 5/6
                           Nbpsc = 8;
                           Ncbps = 192;
                           Kmod = 1 / sqrt(170);
                           break;
                       case 10:                //BPSK 1/2 with 2repetition
                           Nbpsc = 1;
                           Ncbps = 24;
                           Kmod = 1;
                           break;
                       default:
                           printf("Unknown param %d\n", mcs);
                           break;
                   }
               }
               else if (model == MU)
               {
                   switch (mcs)
                   {
                       case 0:
                           Nbpsc = 1;
                           Ncbps = 24;
                           Kmod = 1;
                           break;
                       case 1:
                           Nbpsc = 2;
                           Ncbps = 48;
                           Kmod = 1 / sqrt(2);
                           break;
                       case 2:
                           Nbpsc = 2;
                           Ncbps = 48;
                           Kmod = 1 / sqrt(2);
                           break;
                       default:
                           printf("Unknown param %d\n", mcs);
                           break;
                   }
               }
               else
               {
                   printf("Unknown model %d\n", model);
               }

               break;

           // channel width 2 MHz
           case CBW2:
               std::cout << "finding channel parameters and case 2 invoked" << std::endl;
               Nsa = 64;
               Nsd = 52;
               Nsym = length*8 / Nsa;

               if (model == SU)
               {
                   switch (mcs)
                   {
                       case 0:
                           Nbpsc = 1;
                           Ncbps = 52;                     //Number of Coded Bits Per OFDM Symbol = Nbpsc * Nsd
                           Kmod = 1;
                           break;
                       case 1:
                           Nbpsc = 2;
                           Ncbps = 104;
                           Kmod = 1 / sqrt(2);
                           break;
                       case 2:
                           Nbpsc = 2;
                           Ncbps = 104;
                           Kmod = 1 / sqrt(2);
                           break;
                       case 3:
                           Nbpsc = 4;
                           Ncbps = 208;
                           Kmod = 1 / sqrt(10);
                           break;
                       case 4:
                           Nbpsc = 4;
                           Ncbps = 208;
                           Kmod = 1 / sqrt(10);
                           break;
                       case 5:
                           Nbpsc = 6;
                           Ncbps = 312;
                           Kmod = 1 / sqrt(42);
                           break;
                       case 6:
                           Nbpsc = 6;
                           Ncbps = 312;
                           Kmod = 1 / sqrt(42);
                           break;
                       case 7:
                           Nbpsc = 6;
                           Ncbps = 312;
                           Kmod = 1 / sqrt(42);
                           break;
                       case 8:
                           Nbpsc = 8;
                           Ncbps = 416;
                           Kmod = 1 / sqrt(170);
                           break;
                       default:
                           printf("Unknown param %d\n", mcs);
                           break;
                   }
               }
               else if (model == MU)
               {
                   switch (mcs)
                   {
                       case 0:
                           Nbpsc = 1;
                           Ncbps = 52;
                           Kmod = 1;
                           break;
                       case 1:
                           Nbpsc = 2;
                           Ncbps = 104;
                           Kmod = 1 / sqrt(2);
                           break;
                       case 2:
                           Nbpsc = 2;
                           Ncbps = 104;
                           Kmod = 1 / sqrt(2);
                           break;
                       default:
                           printf("Unknown param %d\n", mcs);
                           break;
                   }
               }
               else
               {
                   printf("Unknown model %d\n", model);
               }

               break;

           // channel width 4 MHz
           case CBW4:
               Nsa = 128;
               Nsd = 108;
               Nsym = length*8 / Nsa;

               if (model == SU)
               {
                   switch (mcs)
                   {
                       case 0:
                           Nbpsc = 1;
                           Ncbps = 108;
                           Kmod = 1;
                           break;
                       case 1:
                           Nbpsc = 2;
                           Ncbps = 216;
                           Kmod = 1 / sqrt(2);
                           break;
                       case 2:
                           Nbpsc = 2;
                           Ncbps = 216;
                           Kmod = 1 / sqrt(2);
                           break;
                       case 3:
                           Nbpsc = 4;
                           Ncbps = 432;
                           Kmod = 1 / sqrt(10);
                           break;
                       case 4:
                           Nbpsc = 4;
                           Ncbps = 432;
                           Kmod = 1 / sqrt(10);
                           break;
                       case 5:
                           Nbpsc = 6;
                           Ncbps = 648;
                           Kmod = 1 / sqrt(42);
                           break;
                       case 6:
                           Nbpsc = 6;
                           Ncbps = 648;
                           Kmod = 1 / sqrt(42);
                           break;
                       case 7:
                           Nbpsc = 6;
                           Ncbps = 648;
                           Kmod = 1 / sqrt(42);
                           break;
                       case 8:
                           Nbpsc = 8;
                           Ncbps = 864;
                           Kmod = 1 / sqrt(170);
                           break;
                       case 9:
                           Nbpsc = 8;
                           Ncbps = 846;
                           Kmod = 1 / sqrt(170);
                           break;
                       default:
                           printf("Unknown param %d\n", mcs);
                           break;
                   }
               }
               else if (model == MU)
               {
                   switch (mcs)
                   {
                       case 0:
                           Nbpsc = 1;
                           Ncbps = 108;
                           Kmod = 1;
                           break;
                       case 1:
                           Nbpsc = 2;
                           Ncbps = 216;
                           Kmod = 1 / sqrt(2);
                           break;
                       case 2:
                           Nbpsc = 2;
                           Ncbps = 216;
                           Kmod = 1 / sqrt(2);
                           break;
                       default:
                           printf("Unknown param %d\n", mcs);
                           break;
                   }
               }
               else
               {
                   printf("Unknown model %d\n", model);
               }

               break;

           // channel width 8 MHz
           case CBW8:
               Nsd = 234;
               Nsa = 256;
               Nsym = length*8 / Nsa;

               if (model == SU)
               {
                   switch (mcs)
                   {
                       case 0:
                           Nbpsc = 1;
                           Ncbps = 234;
                           Kmod = 1;
                           break;
                       case 1:
                           Nbpsc = 2;
                           Ncbps = 468;
                           Kmod = 1 / sqrt(2);
                           break;
                       case 2:
                           Nbpsc = 2;
                           Ncbps = 468;
                           Kmod = 1 / sqrt(2);
                           break;
                       case 3:
                           Nbpsc = 4;
                           Ncbps = 936;
                           Kmod = 1 / sqrt(10);
                           break;
                       case 4:
                           Nbpsc = 4;
                           Ncbps = 936;
                           Kmod = 1 / sqrt(10);
                           break;
                       case 5:
                           Nbpsc = 6;
                           Ncbps = 1404;
                           Kmod = 1 / sqrt(42);
                           break;
                       case 6:
                           Nbpsc = 6;
                           Ncbps = 1404;
                           Kmod = 1 / sqrt(42);
                           break;
                       case 7:
                           Nbpsc = 6;
                           Ncbps = 1404;
                           Kmod = 1 / sqrt(42);
                           break;
                       case 8:
                           Nbpsc = 8;
                           Ncbps = 1872;
                           Kmod = 1 / sqrt(170);
                           break;
                       case 9:
                           Nbpsc = 8;
                           Ncbps = 872;
                           Kmod = 1 / sqrt(170);
                           break;
                       default:
                           printf("Unknown param %d\n", mcs);
                           break;
                   }
               }
               else if (model == MU)
               {
                   switch (mcs)
                   {
                       case 0:
                           Nbpsc = 1;
                           Ncbps = 234;
                           Kmod = 1;
                           break;
                       case 1:
                           Nbpsc = 2;
                           Ncbps = 468;
                           Kmod = 1 / sqrt(2);
                           break;
                       case 2:
                           Nbpsc = 2;
                           Ncbps = 468;
                           Kmod = 1 / sqrt(2);
                           break;
                       default:
                           printf("Unknown param %d\n", mcs);
                           break;
                   }
               }
               else
               {
                   printf("Unknown model %d\n", model);
               }

               break;

           // channel width 16 MHz
           case CBW16:
               Nsd = 468;
               Nsa = 512;
               Nsym = length*8 / Nsa;

               if (model == SU)
               {
                   switch (mcs)
                   {
                       case 0:
                           Nbpsc = 1;
                           Ncbps = 468;
                           Kmod = 1;
                           break;
                       case 1:
                           Nbpsc = 2;
                           Ncbps = 936;
                           Kmod = 1 / sqrt(2);
                           break;
                       case 2:
                           Nbpsc = 2;
                           Ncbps = 936;
                           Kmod = 1 / sqrt(2);
                           break;
                       case 3:
                           Nbpsc = 4;
                           Ncbps = 1872;
                           Kmod = 1 / sqrt(10);
                           break;
                       case 4:
                           Nbpsc = 4;
                           Ncbps = 1872;
                           Kmod = 1 / sqrt(10);
                           break;
                       case 5:
                           Nbpsc = 6;
                           Ncbps = 2804;
                           Kmod = 1 / sqrt(42);
                           break;
                       case 6:
                           Nbpsc = 6;
                           Ncbps = 2808;
                           Kmod = 1 / sqrt(42);
                           break;
                       case 7:
                           Nbpsc = 6;
                           Ncbps = 2808;
                           Kmod = 1 / sqrt(42);
                           break;
                       case 8:
                           Nbpsc = 8;
                           Ncbps = 3744;
                           Kmod = 1 / sqrt(170);
                           break;
                       case 9:
                           Nbpsc = 8;
                           Ncbps = 3744;
                           Kmod = 1 / sqrt(170);
                           break;
                       default:
                           printf("Unknown param %d\n", mcs);
                           break;
                   }
               }
               else if (model  == MU)
               {
                   switch (mcs)
                   {
                       case 0:
                           Nbpsc = 1;
                           Ncbps = 468;
                           Kmod = 1;
                           break;
                       case 1:
                           Nbpsc = 2;
                           Ncbps = 936;
                           Kmod = 1 / sqrt(2);
                           break;
                       case 2:
                           Nbpsc = 2;
                           Ncbps = 936;
                           Kmod = 1 / sqrt(2);
                           break;
                       default:
                           printf("Unknown param %d\n", mcs);
                           break;
                   }
               }
               else
               {
                   printf("Unknown model %d\n", model);
               }

               break;

               default:
                   printf("Unknown channel width %d\n", channelWidth);
                   break;
       }


   } /*modParams constructor*/

    //set methods
    void MODPARAMS::setCBW(CH_BANDWIDTH cbw){this->channelWidth = cbw;}

    //get methods
    int MODPARAMS::getMCS(){return mcs;}
    int MODPARAMS::getNSA(){return Nsa;}
    int MODPARAMS::getNSYM(){return Nsym;}
    int MODPARAMS::getNSD(){return Nsd;}
    CH_BANDWIDTH MODPARAMS::getCBW(){return channelWidth;}

} /* namespace halow */
