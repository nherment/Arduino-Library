/** Arduino library for drawing Histogram on a LCD
 * Represents a chart to display in a LCD screen
 *
 * Copyright 2011 Nicolas Herment
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef CHART_H
#define CHART_H

#include "WProgram.h"
#include "LCD.h"

class Chart {

    public:
        Chart(LCD* lcd, int x1, int y1, int x2, int y2);

		/** The actual values of the chart.
		 * Values should be in the range defined by #setVerticalScale() or
		 * #activateAutoScale() should be used.
		 */
        void setValues(double* values);

        /** Declare the number of values to process */
        void setNumValues(int numValues);

		/** this method redraw the whole graph.
		 * It should be called whenever a value or a parameter has changed.
		 */
		void fullUpdate();

        /** set the color of the graph.
         * @param color between 0 and 255.
         */
		void setColor(int color);

		/** Style of the graph.
		 * @param style one of GRPH_STYLE_* constants.
		 */
		void setStyle(int style);

		/** set the vertical scale of the values.
		 */
		void setVerticalScale(double min, double max);

        /** true base offset */
		void setOffset(double offset);

		/** Activate the automatic scale for displaying the values.
		 * AutoScale is activated by default and is disactivated when
		 * #setVerticalScale() is called.
		 * Use this method to re-activate the autoScale afetr you've used
		 * #setVerticalScale().
		 */
		void activateAutoScale();

        /** Bar-style chart where bars always start from the bottom of the chart */
		static const int STYLE_BAR = 0;
        /** Line-style chart */
		static const int STYLE_LINE = 1;
        /** Bar-style chart where bars always start from a reference */
		static const int STYLE_BAR_REL = 2;


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
        boolean _autoScale;

        void drawFullGraphLine();
        void drawFullGraphBar(boolean relativeToOffset);
        void preventLCDBufferOverflow();

        int valueToPixel(double value);

        void autoScale();

        void debug(String msg);
        void drawBar(int x, int value, int offset);
};

#endif
