/*
 * mcs.h
 *
 *  Created on: Jun 26, 2023
 *      Author: Kudzai Samakande
 */
#include <cstring>
#include <string>
#include <iostream>
#ifndef MCS_H_
#define MCS_H_


namespace halow
{

    //define a structure data type that contains the modulation parameters
    struct modParams
    {
        int mcs;
        int channelWidth;
        std::string model;
        int Nsd;                    //Number of data subcarriers per OFDM symbol
        int Nsa;                    //Total subcarriers
        int Nsp;                    //pilot subcarriers per OFDM symbol
        int Nbpsc;                  //Number of Bits Per Subcarrier
        int Ncbps;                  //Number of Coded Bits Per OFDM Symbol = Nbpsc * Nsd
        int Ndbps;                   //Number of Data Bits Per Symbol = Ncbps * Rate
        double Kmod;                //Normalization Factor
        int pilots[16];

        //member function of the structure that returns modulation parameters based on the mcs, channelWidth and model;

        modParams mcss(int channelWidth, int param, const char* model)
        {
            modParams params; // Create a new instance of the modParams structure
            params.channelWidth = channelWidth;
            params.model = model;
            params.mcs = param;

            switch (channelWidth) 
            {                
                // channel width 1 MHz
                case 1:
                    Nsa = 32;
                    Nsd = 24;
                    Nsp = 2;
                    pilots[0] = -7;
                    pilots[1] = 7;

                    if (strcmp(model, "SISO") == 0) {
                        switch (param) { //cases for all 10 possible values of the modulation and coding scheme
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
                                printf("Unknown param %d\n", param);
                                break;
                        }
                    } else if (strcmp(model, "MIMO") == 0) {
                        switch (param) {
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
                                printf("Unknown param %d\n", param);
                                break;
                        }
                    } else {
                        printf("Unknown model %s\n", model);
                    }

                    break;

                // channel width 2 MHz
                case 2:
                    std::cout << "finding channel parameters and case 2 invoked" << std::endl;
                    params.Nsa = 64;
                    params.Nsd = 52;
                    params.Nsp = 4;                        //4 pilot subcarriers per OFDM symbol
                    params.pilots[0] = -21;
                    params.pilots[1] = -7;
                    params.pilots[2] = 7;
                    params.pilots[3] = 21;

                    if (strcmp(model, "SISO") == 0) {
                        switch (param) {
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
                                params.Nbpsc = 4;
                                params.Ncbps = 208;
                                params.Ndbps = 104;
                                params.Kmod = 1 / sqrt(10);
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
                                printf("Unknown param %d\n", param);
                                break;
                        }
                    } else if (strcmp(model, "MIMO") == 0) {
                        switch (param) {
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
                                printf("Unknown param %d\n", param);
                                break;
                        }
                    } else {
                        printf("Unknown model %s\n", model);
                    }

                    break;

                // channel width 4 MHz
                case 4:
                    Nsd = 108;
                    Nsa = 128;
                    Nsp = 6;                        //6 pilot subcarriers per OFDM symbol
                    pilots[0] = -53;
                    pilots[1] = -25;
                    pilots[2] = -11;
                    pilots[3] = 11;
                    pilots[4] = 25;
                    pilots[5] = 53;

                    if (strcmp(model, "SISO") == 0) {
                        switch (param) {
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
                                printf("Unknown param %d\n", param);
                                break;
                        }
                    } else if (strcmp(model, "MIMO") == 0) {
                        switch (param) {
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
                                printf("Unknown param %d\n", param);
                                break;
                        }
                    } else {
                        printf("Unknown model %s\n", model);
                    }

                    break;

                // channel width 8 MHz
                case 8:
                    Nsd = 243;
                    Nsa = 256;
                    Nsp = 8;                       //8 pilot subcarriers per OFDM symbol
                    pilots[0] = -103;
                    pilots[1] = -75;
                    pilots[2] = -39;
                    pilots[3] = -11;
                    pilots[4] = 11;
                    pilots[5] = 39;
                    pilots[6] = 75;
                    pilots[7] = 103;

                    if (strcmp(model, "SISO") == 0) {
                        switch (param) {
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
                                printf("Unknown param %d\n", param);
                                break;
                        }
                    } else if (strcmp(model, "MIMO") == 0) {
                        switch (param) {
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
                                printf("Unknown param %d\n", param);
                                break;
                        }
                    } else {
                        printf("Unknown model %s\n", model);
                    }

                    break;

                // channel width 16 MHz
                       case 16:
                           Nsd = 468;
                           Nsa = 512;
                           Nsp = 16;                        //16 pilot subcarriers per OFDM symbol
                           pilots[0] = -231;
                           pilots[1] = -203;
                           pilots[2] = -167;
                           pilots[3] = -139;
                           pilots[4] = -117;
                           pilots[5] = -89;
                           pilots[6] = -53;
                           pilots[7] = -25;
                           pilots[8] = 25;
                           pilots[9] = 53;
                           pilots[10] = 89;
                           pilots[11] = 117;
                           pilots[12] = 139;
                           pilots[13] = 167;
                           pilots[14] = 203;
                           pilots[15] = 231;

                           if (strcmp(model, "SISO") == 0) {
                               switch (param) {
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
                                       printf("Unknown param %d\n", param);
                                       break;
                               }
                           } else if (strcmp(model, "MIMO") == 0) {
                               switch (param) {
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
                                       printf("Unknown param %d\n", param);
                                       break;
                               }
                           } else {
                               printf("Unknown model %s\n", model);
                           }

                           break;

                default:
                    printf("Unknown channel width %d\n", channelWidth);
                    break;
            }

            return params;
        }

    };
};
    #endif /* MCS_H_ */
