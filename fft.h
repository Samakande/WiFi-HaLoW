/*
 * fft.h
 * This is a wrapper class for computing DFT and inverse DFT using
 * FFT algorithms implemented in fftw3 library.
 * The inverse DFT takes in a complex array of
 * QAM modulated samples and computes the time domain samples.
 * The forward DFT computes the IQ samples from the time
 * sampled data in the receiver.
 *  Created on: Jun 29, 2023
 *      Author: Kudzai Samakande
 */

#ifndef FFT_H_
#define FFT_H_

#include "txvector.h"
#include <complex>
#include <fftw3.h>
#include <vector>

namespace halow
{
  class fft
  {
      fftw_complex * forwardfft_in;
      fftw_complex * forwardfft_out;

      fftw_complex * inversefft_in; // Subcarrier scaling values for all subcarriers, e.g., 64 for 2MHz channel
      fftw_complex * inversefft_out;

      fftw_plan forwardPlan;
      fftw_plan inversePlan;

      // The variables for the fft class contain pointers to input
      // and output arrays used in Fourier transform

      public:
          void inverseFFT(std::vector<std::complex<double>> &symbols, halow::modParams &TxVector); // Creates the IFFT plan and executes it
          std::vector<std::complex<double>> insertGI(std::vector<std::complex<double>> &time_samples, halow::modParams &params, int duration);
  };
};

#endif /* FFT_H_ */
