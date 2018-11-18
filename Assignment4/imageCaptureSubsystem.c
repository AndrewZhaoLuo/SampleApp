#include "imageCaptureSubsystem.h"
#include "print_format.h"
#include "optfft.h"
#include "circularBuffer.h"
#include <Arduino.h>

void imageCaptureFunction(void* data) {
    imageCaptureData* imageData = (imageCaptureData*) data;

    // don't do much in sampling to get sampling rate as high as possible
    for (int i = 0; i < FFT_BUFFER_SIZE; i++) {
        // divide by 10 to prevent overflows
        imageData -> fft_in[i] = analogRead(IMAGE_READ_PIN);
    }

    for (int i = 0; i < FFT_BUFFER_SIZE; i++) {
        // divide by 10 to prevent overflows
        imageData -> fft_in[i] = imageData -> fft_in[i] / 100.0 - OFFSET_ADC / 100.0;
    }

    for (int i = 0; i < FFT_BUFFER_SIZE; i++) {
        imageData -> fft_out[i] = 0;
    }

    int m_index = optfft(imageData -> fft_in, imageData -> fft_out); // run fft
    unsigned int frequency = (0.0 + m_index) / FFT_BUFFER_SIZE * SAMPLE_FREQUENCY;

    pushSample(imageData -> freq_buffer, frequency);
    //print_format("COOL FREQUENCY: %d", frequency);
}
