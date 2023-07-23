/*
 * qam.h
 * This is a helper class of the const_mapper class. It encodes the data bits into IQ samples
 * using grayscale coding
 *
 *  Created on: Jun 24, 2023
 *      Author: Kudzai Samakande
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
            void encode(const unsigned char *data, double &cPoint ); //calculate constellation point from the bit vector
            void decode(const char* IQ); //retrieves bits from the received constellation points
    };
}
#endif /* QAM_H_ */
