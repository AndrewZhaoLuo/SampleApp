#ifndef IMAGECAPTURESUBSYSTEM_H_INCLUDED
#define IMAGECAPTURESUBSYSTEM_H_INCLUDED

#define SAMPLING_PERIOD 1
#define FFT_BUFFER_SIZE 256
#define FREQUENCY_BUFFER 16

typedef struct imageCaptureSubsystemStruct {
    signed int* fft_in;
    signed int* fft_out;

    int* freq_buffer;
} imageCaptureData;

void imageCaptureFunction(void* data);

#endif // IMAGECAPTURESUBSYSTEM_H_INCLUDED
