/** Arduino library for LCD screen Matrix Orbital GLK24064-25
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
#include "Wire.h"
#include "LCD.h"

LCD::LCD(int i2cAddress) {
	_i2cAddress = i2cAddress;
}

void LCD::setBacklight(boolean on, int minutesOn) {
    Wire.beginTransmission(_i2cAddress);
    Wire.send(254);
    if(on) {
      Wire.send(66);
      Wire.send(minutesOn);
    } else {
      Wire.send(70);
    }
    Wire.endTransmission();
}

void LCD::setBrightness(int brightness) {
    Wire.beginTransmission(_i2cAddress);
    Wire.send(254);
    Wire.send(152);
    Wire.send(brightness);
    Wire.endTransmission();
}

void LCD::clearScreen() {
    Wire.beginTransmission(_i2cAddress);
    Wire.send(254);
    Wire.send(88);
    Wire.endTransmission();
}

void LCD::drawPixel(int x, int y) {
    Wire.beginTransmission(_i2cAddress);
    Wire.send(254);
    Wire.send(112);
    Wire.send(x);
    Wire.send(y);
    Wire.endTransmission();
}

void LCD::drawRect(int color, int x1, int y1, int x2, int y2) {
    Wire.beginTransmission(_i2cAddress);
    Wire.send(254);
    Wire.send(114);
    Wire.send(color);
    Wire.send(x1);
    Wire.send(y1);
    Wire.send(x2);
    Wire.send(y2);
    Wire.endTransmission();
}

void LCD::fillRect(int color, int x1, int y1, int x2, int y2) {
    Wire.beginTransmission(_i2cAddress);
    Wire.send(254);
    Wire.send(120);
    Wire.send(color);
    Wire.send(x1);
    Wire.send(y1);
    Wire.send(x2);
    Wire.send(y2);
    Wire.endTransmission();
}

void LCD::drawLine(int x1, int y1, int x2, int y2) {
    Wire.beginTransmission(_i2cAddress);
    Wire.send(254);
    Wire.send(108);
    Wire.send(x1);
    Wire.send(y1);
    Wire.send(x2);
    Wire.send(y2);
    Wire.endTransmission();
}

void LCD::continueLine(int x, int y) {
    Wire.beginTransmission(_i2cAddress);
    Wire.send(254);
    Wire.send(101);
    Wire.send(x);
    Wire.send(y);
    Wire.endTransmission();
}

void LCD::drawText(int x, int y, String text) {
  char charArray[20];
  text.toCharArray(charArray, 20);

  //lcd_cursorHome();
  setCursor(x, y);

  Wire.beginTransmission(_i2cAddress);
  Wire.send(charArray);
  Wire.endTransmission();
}

void LCD::resetCursor() {
    Wire.beginTransmission(_i2cAddress);
    Wire.send(254);
    Wire.send(72);
    Wire.endTransmission();
}

void LCD::setCursor(int x, int y) {
    Wire.beginTransmission(_i2cAddress);
    Wire.send(254);
    Wire.send(121);
    Wire.send(x);
    Wire.send(y);
    Wire.endTransmission();
}

void LCD::selectFont(int fontId) {
    Wire.beginTransmission(_i2cAddress);
    Wire.send(254);
    Wire.send(49);
    Wire.send(fontId);
    Wire.endTransmission();

    // the default font with id #2 is too cramped.
    // Increasing the char spacing here.
    // This is a hack since default values won't be reset
    // for the font #1.
    if(fontId == 2) {
        Wire.beginTransmission(_i2cAddress);
        Wire.send(254);
        Wire.send(50);
        Wire.send(0); // left margin
        Wire.send(0); // top margin
        Wire.send(1); // char spacing
        Wire.send(1); // line spacing
        Wire.send(0); // scroll row
        Wire.endTransmission();
    }
}

void LCD::setColor(int color) {
    Wire.beginTransmission(_i2cAddress);
    Wire.send(254);
    Wire.send(99);
    Wire.send(color);
    Wire.endTransmission();
}
