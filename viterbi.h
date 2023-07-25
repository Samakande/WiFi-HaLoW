/*!
 *Dean Makoni
 * \ Convolution Coding and Viterbi decoding
 */
#define K 7              /* constraint length, possible tap points */
#ifndef VITERBI_H_
#define VITERBI_H_
namespace halow{

		class viterbi{

		private:
                 /* Describing the indudtry dtandard polynomial 
                  * G0 = 1011011 , G1 = 1111001
                  */

		//int g[2][K];

		public:
			/*! virtebi class instance*/
			viterbi();

                        /*!
			 * \ Method used to do the convolution encoding
			 * \ acoording to the IEE802.11a standard
			 * \param data The data to be coded.
                         * \param symbols The coded output symbols.
                         * \param data_bits The number of bits in the data input.
			 */
			void conv_encode(unsigned char *data,unsigned char *symbols,int input_len);

		};
}
#endif /* PREAMBLE_H_ */
