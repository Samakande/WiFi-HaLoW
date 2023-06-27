/*
 * QAM.H
 *
 *  Created on: Jun 24, 2023
 *      Author: Kudzai Samakande
 */

/*HEADER FILE FOR QAM TEMPLATE
 *THE FILE CONTAINS QAM CLASS WHICH CONTAINS THE FUNCTIONS FOR ENCODING AND DECODING QAM MODULATION
 */


#ifndef QAM_H_
#define QAM_H_

namespace halow
{
    class QAM
    {
        int numBits;
        int gain;

        public:
            //constructor
            QAM(int numBits, double power, int gain =0 );

            //member function definition
            void encode(const char *data, double *cPoint ); //calculate constellation point from the bit vector
            void decode(const char* IQ); //retrieves bits from the received constellation points
    };
}
#endif /* QAM_H_ */
