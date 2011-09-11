
#include "WProgram.h"
#include "LCD.h"
#include "Chart.h"

Chart::Chart(LCD* lcd, int x1, int y1, int x2, int y2) {
    _lcd = lcd;
    _x1 = x1;
    _y1 = y1;
    _x2 = x2;
    _y2 = y2;
    _color = 255;
    _numValues = 0;
    _style = GRPH_STYLE_LINE;
    _verticalRatio = 100.; // assumes values will be percents
    _scaleMin = 0;
    _offset = 0;
    _autoRange = true;
}

void Chart::setVerticalScale(double scaleMin, double scaleMax) {
	_scaleMin = scaleMin;
	_scaleMax = scaleMax;
	double measureScale = _scaleMax - _scaleMin;
	int pixelScale = _y2 - _y1;

	_verticalRatio = (double) pixelScale / measureScale;
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
    //_lcd->drawText(180, 0, _numValues);
    if(_style == GRPH_STYLE_BAR) {
        //_lcd->drawText(180, 20, "BAR");
        drawFullGraphBar();
    } else if(_style == GRPH_STYLE_LINE) {
        //_lcd->drawText(180, 20, "LINE");
        drawFullGraphLine();
    }
}

void Chart::drawFullGraphLine() {
    boolean first = true;
    for( int i = 0 ; i < _numValues ; i++ ) {
    	int x = _x1+(i*_step);
    	_lcd->fillRect(0, x, _y1, x+_step, _y2);
        preventLCDBufferOverflow();
        //if(_values[i] > 0 ) {
    	    //int x = constrain(_x1+(i*_step), 0 , _x2);
    	    int value = constrain(_y2-valueToPixel(_values[i]), _y1, _y2);
    	    if(first) {

    	        first = false;
                _lcd->drawLine(_x1, value, x, value);

            } else {

                _lcd->continueLine(x+floor(_step/2), value);

            }

            preventLCDBufferOverflow();

        //}
    }
}

int Chart::valueToPixel(double value) {
	return (value + _offset) * _verticalRatio;
}

void Chart::drawFullGraphBar() {
    //int lastValue = 0;
    for( int i = 0 ; i < _numValues ; i++ ) {
        int x = _x1+(i*_step);
        int value = constrain(_y2-valueToPixel(_values[i]), _y1, _y2);
        //if(_values[i] > 0) {
    	    if(x > _x2) {
    	        break;
    	    }
            _lcd->fillRect(0, x, _y1, x+_step-1, value);
            _lcd->fillRect(_color, x, _y2, x+_step-1, value);

            preventLCDBufferOverflow();

        	//lastValue = valueToPixel(_values[i]);
        //}
    }
    //debug(lastValue);
}

void Chart::debug(String msg) {
	_lcd->drawText(180, 0, msg);
}

void Chart::preventLCDBufferOverflow() {
    delay(10);
}