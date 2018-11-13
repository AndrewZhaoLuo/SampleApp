// Displays str for  aprox. num_secs seconds to console. Max char* length of 20 characters.
void tempPrintArduino(char* str, int num_secs, int tics_per_sec) {
    tft.setCursor(0, 0);
    tft.print(str);
    volatile long i = 0;
    for (i = tics_per_sec * num_secs; i > 0;) {
        i--;
    }
    tft.fillScreen(BLACK);    
}
