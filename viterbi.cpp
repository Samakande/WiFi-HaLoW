/*
 * Dean Makoni
 * 12 July 2023
 *
 */

#include "viterbi.h"
#include <memory>
#include <stdio.h>
#include <stdlib.h>

namespace halow {

   /*!
     *  -Initializations
     *  initialising the generator polynomial
     */

    viterbi::viterbi()
    {
     };
    int g[2][K] = {
		{1, 0, 1, 1, 0, 1, 1},
		{1, 1, 1, 1, 0, 0, 1}
		};

   /*!
    *\ Defination of the conv_encode method of virtebi class that does the convolution
    */
  void  halow::viterbi::conv_encode(unsigned char * data, unsigned char * symbols, int input_len){
		int m;                     /* K - 1 */
    long t, tt;                /* bit time, symbol time */
    int j, k;                  /* loop variables */
    int *unencoded_data;       /* pointer to data array */
    int shift_reg[K];          /* the encoder shift register */
    int sr_head;               /* index to the first elt in the sr */
    int p, q;                  /* the upper and lower xor gate outputs */

    m = K - 1; /*m is the maximum number of stages (memory size) in any shift register*/

    /* allocate space for the zero-padded input data array */
    unencoded_data = new  int[(input_len + m) * sizeof(int)] ;

    /* read in the data and store it in the array */
    for (t = 0; t < input_len; t++)
        *(unencoded_data + t) = *(data + t);

    /* zero-pad the end of the data */
    /* so that the encoder remains initialised*/
    for (t = 0; t < m; t++) {
        *(unencoded_data + input_len + t) = 0;
    }
 
    /* Initialize the shift register */
    /* to increase perfomance try to use memset to initialise shift register*/
    for (j = 0; j < K; j++) {
        shift_reg[j] = 0;
    }
 
    /* To try to speed things up a little, the shift register will be operated
       as a circular buffer, so it needs at least a head pointer. It doesn't
       need a tail pointer, though, since we won't be taking anything out of
       it--we'll just be overwriting the oldest entry with the new data. */
    sr_head = 0;

    /* initialize the channel symbol output index */
    tt = 0;

    /* Now start the encoding process */
    /* compute the upper and lower mod-two adder outputs, one bit at a time */
    for (t = 0; t < input_len + m; t++) {
        shift_reg[sr_head] = *( unencoded_data + t );
        p = 0;
        q = 0;

        for (j = 0; j < K; j++) {
            k = (j + sr_head) % K;
            p ^= shift_reg[k] & g[0][j];
            q ^= shift_reg[k] & g[1][j];
        }

        /* write the upper and lower xor gate outputs as channel symbols */
        *(symbols + tt) = p;
        tt = tt + 1;
        *(symbols + tt) = q;
        tt = tt + 1;
       

        sr_head -= 1;    /* equivalent to shifting everything right one place */
        if (sr_head < 0) /* but make sure we adjust pointer modulo K */
            sr_head = m;
   }    
  }
}



