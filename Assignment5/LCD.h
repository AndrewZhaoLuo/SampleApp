#ifndef LCD_H
#define LCD_H

// get dimensions in pixels of the screen
int tft_get_height();
int tft_get_width();

// clear the top/bottom, or an arbitrary rectangle's screen with a color
void tft_clear_top(int color);
void tft_clear_bottom(int color);

// note, upper left corner -> lower right corner, going right is increasing x, going DOWN is increasing y!
void tft_fill_rect(int upper_left_x, int upper_left_y, int lower_right_x, int lower_right_y, int color);

// set cursor fontsize and color for printing
void tft_set_fontsize(int size);
void tft_set_color(int color);

// print to the top or bottom half of display with cursor, offset appropriately
void tft_display_top(const char* str, int cursorX, int cursorY);
void tft_display_bottom(const char* str, int cursorX, int cursorY);

void draw_buttons();
int inc_button_pressed();
int dec_button_pressed();
#endif // LCD_H
