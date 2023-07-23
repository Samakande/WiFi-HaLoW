
/*
 * fft.cpp
 * This is a wrapper class for computing DFT and inverse DFT using
 * FFT algorithms implemented in fftw3 library.
 * The inverse DFT takes in a complex array of
 * QAM modulated samples and computes the time domain samples.
 * The forward DFT computes the IQ samples from the time
 * sampled data in the receiver.
 *
 *  Created on: Jun 29, 2023
 *      Author: Kudzai Samakande
 */
#include "fft.h"
#include <cstring>
#include <iostream>

namespace halow
{
    void fft::inverseFFT(std::vector<std::complex<double>> & symbols, halow::MODPARAMS &params)
    {
        int N = params.getNSA();
        fft::inversefft_in =  (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
        fft::inversefft_out =  (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
        fft::inversePlan = fftw_plan_dft_1d(N, inversefft_in, inversefft_out, FFTW_BACKWARD, FFTW_ESTIMATE); //create plan before initialization INPUT just in case the plan creation tempers with the input array

        for (int s = 0; s < params.getNSYM(); s++)
        {
            memcpy(inversefft_in, &symbols[s*N], N* sizeof(std::complex<double>));

            fftw_execute(inversePlan);

            memcpy(&symbols[s*N],inversefft_out , N * sizeof(std::complex<double>));

            for(int x = 0; x < N; x++)
            {
                //std::cout << "Symbols " << x << ": " <<  symbols[x] << std::endl;
                symbols[s*N+x] /=N;
            }


        }

        fftw_destroy_plan(inversePlan);
        fftw_free(inversefft_in); fftw_free(inversefft_out);
    }

    std::vector<std::complex<double>> fft::insertGI(std::vector<std::complex<double>> &time_samples, halow::MODPARAMS &params, int duration)
    {
        int N = params.getNSA();;
        int samples = duration * pow(2, params.getCBW())*2;;
        std::vector<std::complex<double>> prefixed((params.getNSYM())*(samples+N));

        for(int s = 0; s < params.getNSYM(); s++)
        {
           memcpy(&prefixed[s*(samples+N)], &time_samples[N*(s+1)-samples], samples*sizeof(std::complex<double>));
           memcpy(&prefixed[s*(samples+N)+samples], &time_samples[s*N], N*sizeof(std::complex<double>));
        }

        return prefixed;
    }
}


