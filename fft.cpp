/*
 * fft.cpp
 *
 *  Created on: Jun 29, 2023
 *      Author: Kudzai Samakande
 */
#include <cstring>
#include "fft.h"

namespace halow
{
    void fft::inverseFFT(std::vector<std::complex<double>> & modulated_qam)
    {

        int N = modulated_qam.size();
        fft::inversefft_in =  (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);;
        fft::inversefft_out =  (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);;

        fft::inversePlan = fftw_plan_dft_1d(N, inversefft_in, inversefft_out, FFTW_BACKWARD, FFTW_ESTIMATE); //create plan before initialization INPUT just in case the plan creation tempers with the input aray

        memcpy(inversefft_in, &modulated_qam[0], N * sizeof(std::complex<double>)); //pass by value the input point now point to the time domain samples ready for transmission
        fftw_execute(inversePlan);

        memcpy(&modulated_qam[0],inversefft_out , N * sizeof(std::complex<double>));

        for(int x = 0; x < modulated_qam.size(); x++)
               {
            modulated_qam[x] /=N;
               }

        fftw_destroy_plan(inversePlan);
        fftw_free(inversefft_in); fftw_free(inversefft_out);

    }
}


