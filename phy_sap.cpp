/*
 * phy_sap.cpp
 *
 *  Created on: Jul 12, 2023
 *      Author: Kudzai Samakande
 */

#include "phy_sap.h"
#include "preamble.h"
#include "data.h"

namespace halow
{

    PHY_TXSTART::PHY_TXSTART(std::vector<unsigned char> &payload)
        :payload(payload)
    {

    }


    /*
     * this is a transmission initialization process issued by the MAC to the PHY to start transmitting.
     * the method will start the local state machine by generating the appropriate preambles, training
     * fields and plcp headers.
     */
    void PHY_TXSTART::request(TXVECTOR &txvector)
    {
        switch (txvector.getFORMAT())
        {
            case S1G:
                if (txvector.getPREAMBLE() == S1G_SHORT_PREAMBLE && !txvector.isNDP())
                {
                    /*
                     * 2 symbols of the STF field
                     */
                    std::vector<std::complex<double>> stf = generate_stf_field(txvector);

                    /*
                     * 2 symbols of the LTF1 field with a double guard interval
                     */
                    std::vector<std::complex<double>> ltf1 = generate_ltf1_field(txvector);

                    /*
                     * 2 symbols of the SIG field
                     */
                    std::vector<std::complex<double>> sig = generate_sig_field(txvector);


                }

                /*
                 * other conditions are yet to be implemented
                 */
                break;

            case S1G_DUP_2M:
                break;

            case S1G_DUP_1M:
                break;
        }

    }


    void PHY_DATA::request(std::vector<unsigned char> &payload, int user_index)
    {
        /*
         *generate the data field of variable length from the psdu and service bits.
         */
       // std::vector<std::complex<double>> data = generate_data_field(psdu, txvector)

    }


} /* namespace halow */
