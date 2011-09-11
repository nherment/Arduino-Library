/** Arduino library for LCD screen Matrix Orbital GLK24064-25
 *
 * @author Nicolas Herment
 * nherment@gmail.com
 */
#ifndef LCD_h
#define LCD_h

#include "WProgram.h"

class LCD {
    public:
        LCD(int i2cAddress);
        void setBacklight(boolean on, int minutesOn);
        void setBrightness(int brightness);
        void clearScreen();
        void drawPixel(int x, int y);
        void drawRect(int color, int x1, int y1, int x2, int y2);
        void fillRect(int color, int x1, int y1, int x2, int y2);
        void drawLine(int x1, int y1, int x2, int y2);
        void continueLine(int x, int y);
        void drawText(int x, int y, String text);
        void resetCursor();
        void setCursor(int x, int y);
        void selectFont(int fontId);
        void setColor(int color);
    private:
        int _i2cAddress;
};

#endif
