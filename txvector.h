/*
 * txvector.h
 *
 *  Created on: Jul 3, 2023
 *      Author: Kudzai Samakande
 */

#ifndef TXVECTOR_H_
#define TXVECTOR_H_

#include <vector>
#include <complex>
#include <iostream>
namespace halow
{

    enum FORMAT : int           //The S1G FORMAT is the currently supported
        {
            SIG,
            S1G_DUP_1M,
            S1G_DUP_2M
        };
    enum PREAMBLE_TYPE    //S1G_1M and S1G_SHORT_PREAMBLE are the preamble types implemented
            {
                S1G_1M,
                S1G_SHORT_PREAMBLE,
                S1G_LONG_PREAMBLE
            };
    enum GI_TYPE : int
               {
                    SHORT_GI,
                    LONG_GI
              };
    enum CH_BANDWIDTH: int
               {
                    CBW1=1,
                    CBW2=2,
                    CBW4=4,
                    CBW8=8,
                    CBW16=16
               };

    enum MU_SU : int
               {
                    SU,
                    MU
               };


    //define a structure data type that contains the transmission parameters

    struct modParams
    {
        int mcs;
        CH_BANDWIDTH channelWidth;
        MU_SU model;
        GI_TYPE guard;
        int Nsa;                    //Total subcarriers
        int Nst;                    //Total number of useful subcarriers per OFDM symbol
        int Nsd;                    //Number of data subcarriers per OFDM symbol
        int Nsp;                    //Pilot subcarriers per OFDM symbol
        int Nbpsc;                  //Number of Bits Per Subcarrier
        int Ncbps;                  //Number of Coded Bits Per OFDM Symbol = Nbpsc * Nsd
        int Ndbps;                  //Number of Data Bits Per Symbol = Ncbps * Rate
        double Kmod;                //Normalization Factor
        int length;                 //Indicates the packet duration in number of symbols in the data to be modulated

        //member function of the structure that returns modulation parameters based on the mcs, channelWidth and model;

        modParams(int mcs,  CH_BANDWIDTH channelWidth, MU_SU model, GI_TYPE guard, int length)
            : mcs(mcs),
            channelWidth(channelWidth),
            model(model),
            length(length)
        {


            switch (channelWidth)
            {
                // channel width 1 MHz
                case CBW1:
                    Nsa = 32;
                    Nsd = 24;
                    Nsp = 2;

                    if (model == SU)
                    {
                        switch (mcs)
                        { //cases for all 10 possible values of the modulation and coding scheme
                            case 0:                 //BPSK Rate = 1/2
                                Nbpsc = 1;
                                Ncbps = 24;
                                Ndbps = 12;
                                Kmod = 1;
                                break;
                            case 1:                 //QPSK 1/2
                                Nbpsc = 2;
                                Ncbps = 48;
                                Ndbps = 24;
                                Kmod = 1 / sqrt(2);
                                break;
                            case 2:                 //QPSK 3/4
                                Nbpsc = 2;
                                Ncbps = 48;
                                Ndbps = 36;
                                Kmod = 1 / sqrt(2);
                                break;
                            case 3:                 //16-QAM 1/2
                                Nbpsc = 4;
                                Ncbps = 96;
                                Ndbps = 48;
                                Kmod = 1 / sqrt(10);
                                break;
                            case 4:                 //16-QAM 3/4
                                Nbpsc = 4;
                                Ncbps = 96;
                                Ndbps = 72;
                                Kmod = 1 / sqrt(10);
                                break;
                            case 5:                 //64-QAM 2/3
                                Nbpsc = 6;
                                Ncbps = 144;
                                Ndbps = 96;
                                Kmod = 1 / sqrt(42);
                                break;
                            case 6:                 //64-QAM 3/4
                                Nbpsc = 6;
                                Ncbps = 144;
                                Ndbps = 108;
                                Kmod = 1 / sqrt(42);
                                break;
                            case 7:                 //64-QAM 5/6
                                Nbpsc = 6;
                                Ncbps = 144;
                                Ndbps = 120;
                                Kmod = 1 / sqrt(42);
                                break;
                            case 8:                 //256-QAM 3/4
                                Nbpsc = 8;
                                Ncbps = 192;
                                Ndbps = 144;
                                Kmod = 1 / sqrt(170);
                                break;
                            case 9:                 //256-QAM 5/6
                                Nbpsc = 8;
                                Ncbps = 192;
                                Ndbps = 160;
                                Kmod = 1 / sqrt(170);
                                break;
                            case 10:                //BPSK 1/2 with 2repetition
                                Nbpsc = 1;
                                Ncbps = 24;
                                Ndbps = 6;
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
                                Ndbps = 12;
                                Kmod = 1;
                                break;
                            case 1:
                                Nbpsc = 2;
                                Ncbps = 48;
                                Ndbps = 24;
                                Kmod = 1 / sqrt(2);
                                break;
                            case 2:
                                Nbpsc = 2;
                                Ncbps = 48;
                                Ndbps = 36;
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
                    Nsp = 4;                        //4 pilot subcarriers per OFDM symbol

                    if (model == SU)
                    {
                        switch (mcs)
                        {
                            case 0:
                                Nbpsc = 1;
                                Ncbps = 52;                     //Number of Coded Bits Per OFDM Symbol = Nbpsc * Nsd
                                Ndbps = 26;
                                Kmod = 1;
                                break;
                            case 1:
                                Nbpsc = 2;
                                Ncbps = 104;
                                Ndbps = 52;
                                Kmod = 1 / sqrt(2);
                                break;
                            case 2:
                                Nbpsc = 2;
                                Ncbps = 104;
                                Ndbps = 78;
                                Kmod = 1 / sqrt(2);
                                break;
                            case 3:
                                std::cout << "finding channel parameters and qam16 ready" << std::endl;
                                Nbpsc = 4;
                                Ncbps = 208;
                                Ndbps = 104;
                                Kmod = 1 / sqrt(10);
                                break;
                            case 4:
                                Nbpsc = 4;
                                Ncbps = 208;
                                Ndbps = 156;
                                Kmod = 1 / sqrt(10);
                                break;
                            case 5:
                                Nbpsc = 6;
                                Ncbps = 312;
                                Ndbps = 208;
                                Kmod = 1 / sqrt(42);
                                break;
                            case 6:
                                Nbpsc = 6;
                                Ncbps = 312;
                                Ndbps = 234;
                                Kmod = 1 / sqrt(42);
                                break;
                            case 7:
                                Nbpsc = 6;
                                Ncbps = 312;
                                Ndbps = 260;
                                Kmod = 1 / sqrt(42);
                                break;
                            case 8:
                                Nbpsc = 8;
                                Ncbps = 416;
                                Ndbps = 312;
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
                                Ndbps = 26;
                                Kmod = 1;
                                break;
                            case 1:
                                Nbpsc = 2;
                                Ncbps = 104;
                                Ndbps = 52;
                                Kmod = 1 / sqrt(2);
                                break;
                            case 2:
                                Nbpsc = 2;
                                Ncbps = 104;
                                Ndbps = 78;
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
                    Nsp = 6;                        //6 pilot subcarriers per OFDM symbol

                    if (model == SU)
                    {
                        switch (mcs)
                        {
                            case 0:
                                Nbpsc = 1;
                                Ncbps = 108;
                                Ndbps = 54;
                                Kmod = 1;
                                break;
                            case 1:
                                Nbpsc = 2;
                                Ncbps = 216;
                                Ndbps = 108;
                                Kmod = 1 / sqrt(2);
                                break;
                            case 2:
                                Nbpsc = 2;
                                Ncbps = 216;
                                Ndbps = 162;
                                Kmod = 1 / sqrt(2);
                                break;
                            case 3:
                                Nbpsc = 4;
                                Ncbps = 432;
                                Ndbps = 216;
                                Kmod = 1 / sqrt(10);
                                break;
                            case 4:
                                Nbpsc = 4;
                                Ncbps = 432;
                                Ndbps = 324;
                                Kmod = 1 / sqrt(10);
                                break;
                            case 5:
                                Nbpsc = 6;
                                Ncbps = 648;
                                Ndbps = 432;
                                Kmod = 1 / sqrt(42);
                                break;
                            case 6:
                                Nbpsc = 6;
                                Ncbps = 648;
                                Ndbps = 486;
                                Kmod = 1 / sqrt(42);
                                break;
                            case 7:
                                Nbpsc = 6;
                                Ncbps = 648;
                                Ndbps = 540;
                                Kmod = 1 / sqrt(42);
                                break;
                            case 8:
                                Nbpsc = 8;
                                Ncbps = 864;
                                Ndbps = 648;
                                Kmod = 1 / sqrt(170);
                                break;
                            case 9:
                                Nbpsc = 8;
                                Ncbps = 846;
                                Ndbps = 720;
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
                                Ndbps = 54;
                                Kmod = 1;
                                break;
                            case 1:
                                Nbpsc = 2;
                                Ncbps = 216;
                                Ndbps = 108;
                                Kmod = 1 / sqrt(2);
                                break;
                            case 2:
                                Nbpsc = 2;
                                Ncbps = 216;
                                Ndbps = 162;
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
                    Nsd = 243;
                    Nsa = 256;
                    Nsp = 8;                       //8 pilot subcarriers per OFDM symbol

                    if (model == SU)
                    {
                        switch (mcs)
                        {
                            case 0:
                                Nbpsc = 1;
                                Ncbps = 234;
                                Ndbps = 117;
                                Kmod = 1;
                                break;
                            case 1:
                                Nbpsc = 2;
                                Ncbps = 468;
                                Ndbps = 234;
                                Kmod = 1 / sqrt(2);
                                break;
                            case 2:
                                Nbpsc = 2;
                                Ncbps = 468;
                                Ndbps = 354;
                                Kmod = 1 / sqrt(2);
                                break;
                            case 3:
                                Nbpsc = 4;
                                Ncbps = 936;
                                Ndbps = 468;
                                Kmod = 1 / sqrt(10);
                                break;
                            case 4:
                                Nbpsc = 4;
                                Ncbps = 936;
                                Ndbps = 702;
                                Kmod = 1 / sqrt(10);
                                break;
                            case 5:
                                Nbpsc = 6;
                                Ncbps = 1404;
                                Ndbps = 936;
                                Kmod = 1 / sqrt(42);
                                break;
                            case 6:
                                Nbpsc = 6;
                                Ncbps = 1404;
                                Ndbps = 1053;
                                Kmod = 1 / sqrt(42);
                                break;
                            case 7:
                                Nbpsc = 6;
                                Ncbps = 1404;
                                Ndbps = 1170;
                                Kmod = 1 / sqrt(42);
                                break;
                            case 8:
                                Nbpsc = 8;
                                Ncbps = 1872;
                                Ndbps = 1404;
                                Kmod = 1 / sqrt(170);
                                break;
                            case 9:
                                Nbpsc = 8;
                                Ncbps = 872;
                                Ndbps = 1560;
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
                                Ndbps = 117;
                                Kmod = 1;
                                break;
                            case 1:
                                Nbpsc = 2;
                                Ncbps = 468;
                                Ndbps = 234;
                                Kmod = 1 / sqrt(2);
                                break;
                            case 2:
                                Nbpsc = 2;
                                Ncbps = 468;
                                Ndbps = 351;
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
                    Nsp = 16;                        //16 pilot subcarriers per OFDM symbol

                    if (model == SU)
                    {
                        switch (mcs)
                        {
                            case 0:
                                Nbpsc = 1;
                                Ncbps = 468;
                                Ndbps = 243;
                                Kmod = 1;
                                break;
                            case 1:
                                Nbpsc = 2;
                                Ncbps = 936;
                                Ndbps = 468;
                                Kmod = 1 / sqrt(2);
                                break;
                            case 2:
                                Nbpsc = 2;
                                Ncbps = 936;
                                Ndbps = 702;
                                Kmod = 1 / sqrt(2);
                                break;
                            case 3:
                                Nbpsc = 4;
                                Ncbps = 1872;
                                Ndbps = 936;
                                Kmod = 1 / sqrt(10);
                                break;
                            case 4:
                                Nbpsc = 4;
                                Ncbps = 1872;
                                Ndbps = 1404;
                                Kmod = 1 / sqrt(10);
                                break;
                            case 5:
                                Nbpsc = 6;
                                Ncbps = 2804;
                                Ndbps = 1872;
                                Kmod = 1 / sqrt(42);
                                break;
                            case 6:
                                Nbpsc = 6;
                                Ncbps = 2808;
                                Ndbps = 2106;
                                Kmod = 1 / sqrt(42);
                                break;
                            case 7:
                                Nbpsc = 6;
                                Ncbps = 2808;
                                Ndbps = 2340;
                                Kmod = 1 / sqrt(42);
                                break;
                            case 8:
                                Nbpsc = 8;
                                Ncbps = 3744;
                                Ndbps = 2808;
                                Kmod = 1 / sqrt(170);
                                break;
                            case 9:
                                Nbpsc = 8;
                                Ncbps = 3744;
                                Ndbps = 3120;
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
                                Ndbps = 234;
                                Kmod = 1;
                                break;
                            case 1:
                                Nbpsc = 2;
                                Ncbps = 936;
                                Ndbps = 468;
                                Kmod = 1 / sqrt(2);
                                break;
                            case 2:
                                Nbpsc = 2;
                                Ncbps = 936;
                                Ndbps = 702;
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


        }

    };
}


#endif /* TXVECTOR_H_ */
