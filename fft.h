/*
 * fft.h
 * this is a wrapper class for computing DFT and inverse DFT using
 * FFT algorithms implemented in ffttw3 library
 * The inverse DFT computes takes in a complex array of
 * QAM modulated samples and computes the time domain samples
 * The forward DFT computes the IQ samples from the time
 * sampled data in the receiver.
 *  Created on: Jun 29, 2023
 *      Author: Kudzai Samakande
 */

#ifndef FFT_H_
#define FFT_H_

#include <complex>
#include <fftw3.h>
#include <vector>

namespace halow
{
  class fft
  {
      fftw_complex * fowardfft_in;
      fftw_complex * fowardfft_out;

      fftw_complex * inversefft_in; //subcarrier scaling values for all subcarries e.g 64 for 2Mhz channel
      fftw_complex * inversefft_out;

      fftw_plan forwadPlan;
      fftw_plan inversePlan;
      /*the variables for the fft class contains pointers to input
       * and output arrays used in fourier transform
       */
      void inverseFFT(std::vector<std::complex<double>> & modulated_qam); //creates the ifft plan and executes it
  };
};

#endif /* FFT_H_ */
