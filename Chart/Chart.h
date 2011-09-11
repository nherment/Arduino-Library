/** Arduino library for drawing Histogram on a LCD
 *
 * @author Nicolas Herment
 * nherment@gmail.com
 */
#ifndef CHART_H
#define CHART_H

#include "WProgram.h"
#include "LCD.h"


const int GRPH_STYLE_BAR = 0;
const int GRPH_STYLE_LINE = 1;

class Chart {
    private:
        LCD* _lcd;
        int _x1;
        int _y1;
        int _x2;
        int _y2;
        double* _values;
        int _color;
        int _numValues;
        int _step;
        int _style;
        double _scaleMin;
        double _scaleMax;
        double _verticalRatio;
        double _offset;
        boolean _autoRange;

        void drawFullGraphLine();
        void drawFullGraphBar();
        void preventLCDBufferOverflow();

        int valueToPixel(double value);

        void debug(String msg);

    public:
        Chart(LCD* lcd, int x1, int y1, int x2, int y2);

        void setValues(double* values);
        void setNumValues(int numValues);

		void fullUpdate();

		void setColor(int color);

		/** Style of the graph.
		 * @param style one of GRPH_STYLE_* constants.
		 */
		void setStyle(int style);

		void setVerticalScale(double min, double max);

        /** true base offset */
		void setOffset(double offset);
};

#endif
