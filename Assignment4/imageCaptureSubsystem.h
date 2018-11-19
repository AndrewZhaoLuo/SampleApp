#ifndef IMAGECAPTURESUBSYSTEM_H_INCLUDED
#define IMAGECAPTURESUBSYSTEM_H_INCLUDED

#define OFFSET_ADC 512 // how much to offset to get true symmetric values
                       // 3V PP equals 3/5 of the adc range  or 614 bits. half of this is 312
#define SAMPLE_FREQUENCY 8929.0 // in hz, determined experimentally
#define FFT_BUFFER_SIZE 256
#define FREQUENCY_BUFFER 16

typedef struct imageCaptureSubsystemStruct {
    signed int* fft_in;
    signed int* fft_out;

    int* freq_buffer;

    int* last_freq;
} imageCaptureData;

void imageCaptureFunction(void* data);

#endif // IMAGECAPTURESUBSYSTEM_H_INCLUDED
