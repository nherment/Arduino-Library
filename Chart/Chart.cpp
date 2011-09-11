/** Arduino library for displaying Charts on a LCD
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
#include "WProgram.h"
#include "LCD.h"
#include "Chart.h"
#include "Number.h"

/**
 *
 * @param lcd A reference to the LCD which displays the graph
 * @param x1 West boundary in pixels
 * @param y1 North bounday in pixels
 * @param x2 East boundary in pixels
 * @param y2 South boundary in pixels
 */
Chart::Chart(LCD* lcd, int x1, int y1, int x2, int y2) {
    _lcd = lcd;
    _x1 = x1;
    _y1 = y1;
    _x2 = x2;
    _y2 = y2;

    // setting default values
    _color = 255;
    _numValues = 0;
    _style = STYLE_BAR;
    _verticalRatio = 100.; // assumes values will be percents
    _scaleMin = 0;
    _offset = 0;
    _autoScale = true;
}

void Chart::setVerticalScale(double scaleMin, double scaleMax) {
    _autoScale = false;

	_scaleMin = scaleMin;
	_scaleMax = scaleMax;
	double measureScale = _scaleMax - _scaleMin;
	int pixelScale = _y2 - _y1;

	_verticalRatio = (double) pixelScale / measureScale;
}

void Chart::activateAutoScale() {
	_autoScale = true;
}

void Chart::autoScale() {
	if(_autoScale) {
		Number::minValue(_values, _numValues, &_scaleMin);
		Number::maxValue(_values, _numValues, &_scaleMax);

		double measureScale = _scaleMax - _scaleMin;
		int pixelScale = _y2 - _y1;

		_verticalRatio = (double) pixelScale / measureScale;

		if(_scaleMin < 0) {
			_offset = -_scaleMin;
		}
	}
}

void Chart::setValues(double* values) {
    _values = values;
}

void Chart::setColor(int color) {
    _color = color;
}

void Chart::setStyle(int style) {
	_style = style;
}

void Chart::setOffset(double offset) {
	_offset = offset;
}

void Chart::setNumValues(int numValues) {
    _numValues = numValues;
    _step = floor( ( _x2 - _x1 ) / _numValues );
}

void Chart::fullUpdate() {
	autoScale();

    if(_style == STYLE_BAR) {
        drawFullGraphBar(false);
    } else if(_style == STYLE_LINE) {
        drawFullGraphLine();
    } else if(_style == STYLE_BAR_REL) {
        drawFullGraphBar(true);
    }
}

void Chart::drawFullGraphLine() {
    boolean first = true;
    for( int i = 0 ; i < _numValues ; i++ ) {
    	int x = _x1+(i*_step);

    	_lcd->fillRect(0, x, _y1, x+_step, _y2);

        preventLCDBufferOverflow();

	    int value = constrain(  _y2-valueToPixel(_values[i]),
	    						_y1,
	    						_y2 );

    	if(x > _x2) {
            break;
	    }

        if(first) {

    	   first = false;
    	    _lcd->drawLine(_x1, value, x, value);

        } else {

            _lcd->continueLine(x+floor(_step/2), value);

        }

        preventLCDBufferOverflow();

    }
}

int Chart::valueToPixel(double value) {
	return (value + _offset) * _verticalRatio;
}

void Chart::drawFullGraphBar(boolean relativeToOffset) {
    for( int i = 0 ; i < _numValues ; i++ ) {

        int x = _x1+(i*_step);


        int offsetPx = _y2;
		if(relativeToOffset) {
			offsetPx = _y2 - abs(_offset * _verticalRatio);
		}



        int value = constrain(  _y2-valueToPixel(_values[i]),
        						_y1,
        						_y2 );

	    drawBar(x, value, offsetPx);

        preventLCDBufferOverflow();
    }
}

void Chart::drawBar(int x, int value, int reference) {
	if(value > reference) { // actually means true value is below reference
	    _lcd->fillRect(0, x, _y1, x + _step-1, _y2);
        preventLCDBufferOverflow();
	    //_lcd->fillRect(0, x, _y2, x + _step-1, _y2-offset);
        //preventLCDBufferOverflow();
        _lcd->fillRect(_color, x, reference, x + _step-1, value);
    } else {
	    _lcd->fillRect(0, x, _y1, x + _step-1, _y2);
        preventLCDBufferOverflow();
	    //_lcd->fillRect(0, x, value, x + _step-1, _y2);
        //preventLCDBufferOverflow();
        _lcd->fillRect(_color, x, reference, x + _step-1, value);
    }
}

void Chart::debug(String msg) {
	_lcd->drawText(180, 0, msg);
}

void Chart::preventLCDBufferOverflow() {
	// Since I'm not using Flow control, need to make sure
	// that the LCD's buffer does not overflow.
	// Refer to documentation to implement buffer overflow.
    delay(10);
}