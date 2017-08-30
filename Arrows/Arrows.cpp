
//  Arrows.cpp

#include "Arrows.h"
#include "Arduino.h"
#include "Adafruit_GFX.h"

Arrows::Arrows(void){
    _gfx = 0;
}

void Arrows::drawArrows(Adafruit_GFX *gfx,
                        int16_t x, int16_t y,
                        uint16_t w, uint16_t h,
                        uint16_t arrowsframeColor, uint16_t arrowsfillColor) {
    _x = x;
    _y = y;
    _w = w;
    _h = h;
    _arrowsframeColor = arrowsframeColor;
    _arrowsfillColor = arrowsfillColor;
    _gfx = gfx;
    //frameRect
    _gfx->drawRect(_x, _y, _w, _h, _arrowsframeColor);
    //dividerLine
    _gfx->drawLine(_x,_y+_h/2,_x+_w,_y+_h/2,_arrowsframeColor);
    //upArrow
    _gfx->fillTriangle(_x+_w/2,_y+5,_x+5,_y+_h/2-5,_x+_w-5,_y+_h/2-5,_arrowsfillColor);
    //downArrow
    _gfx->fillTriangle(_x+_w/2,_y+_h-5,_x+5,_y+_h/2+5, _x+_w-5,_y+_h/2+5,_arrowsfillColor);
}

void Arrows::initArrows(int16_t _value, int16_t _min, int16_t _max, int16_t _step, boolean _wrap){
    value = _value;
    min = _min;
    max = _max;
    step = _step;
    wrap = _wrap;
}

bool Arrows::upArrowContains(int16_t x, int16_t y) {
    if ((x < _x) || (x > (_x + _w))) return false;
    if ((y < _y) || (y > (_y + _h/2))) return false;
    return true;
}

bool Arrows::downArrowContains(int16_t x, int16_t y) {
    if ((x < _x) || (x > (_x + _w))) return false;
    if ((y < _y + _h/2) || (y > (_y + _h))) return false;
    return true;
}

void Arrows::upArrowHandler(){
    value = value + step;
    if(value > max) {
        if(wrap == true) {
            value = min;
        } else {
            value = max;
        }
    }
}

void Arrows::downArrowHandler(){
    value = value - step;
    if(value < min) {
        if(wrap == true) {
            value = max;
        } else {
            value = min;
        }
    }
}

void Arrows:: showArrowValue(Adafruit_GFX *gfx, int16_t x, int16_t y,
                        uint8_t textSize, uint16_t textColor, uint16_t bkgrndColor) {
    _gfx = gfx;
    _displayX = x;
    _displayY = y;
    _textSize = textSize;
    _textColor = textColor;
    _bkgrndColor = bkgrndColor;
    
    sprintf(arrwValueStr,"%03d",value);
    _gfx->setCursor(_displayX,_displayY);
    _gfx->setTextSize(_textSize);
    _gfx->setTextColor(_textColor, _bkgrndColor);
    _gfx->print(arrwValueStr);
}


