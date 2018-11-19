#include "imageCaptureSubsystem.h"
#include "print_format.h"
#include "optfft.h"
#include "circularBuffer.h"
#include "globals.h"
#include <Arduino.h>

void imageCaptureFunction(void* data) {
    imageCaptureData* imageData = (imageCaptureData*) data;

    // don't do much in sampling to get sampling rate as high as possible
    for (int i = 0; i < FFT_BUFFER_SIZE; i++) {
        imageData -> fft_in[i] = analogRead(IMAGE_READ_PIN);
    }

    for (int i = 0; i < FFT_BUFFER_SIZE; i++) {
        // divide by 100 to prevent overflows
        imageData -> fft_in[i] = imageData -> fft_in[i] / SCALING_FACTOR - OFFSET_ADC / SCALING_FACTOR;
    }

    // zero out data
    for (int i = 0; i < FFT_BUFFER_SIZE; i++) {
        imageData -> fft_out[i] = 0;
    }

    int m_index = optfft(imageData -> fft_in, imageData -> fft_out); // run fft
    unsigned int frequency = (0.0 + m_index) / FFT_BUFFER_SIZE * SAMPLE_FREQUENCY;

    pushSample(imageData -> freq_buffer, frequency);
    *(imageData -> last_freq) = frequency;
}
