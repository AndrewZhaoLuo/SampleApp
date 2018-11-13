// Displays str for  aprox. num_secs seconds to console. Max char* length of 20 characters.
void tempPrint(char* str, int num_secs, int tics_per_sec) {
    printf("\r%s                    ", str);
    fflush(stdout);
    volatile int i = 0;
    for (i = tics_per_sec * (num_secs); i > 0;) {
        i--;
    }
}
