
//  Arrows.h

#ifndef Arrows_h
#define Arrows_h

#include "Arduino.h"
#include "Adafruit_GFX.h"


class Arrows {
    
public:
    Arrows(void);
    
    int16_t value;
    int16_t min;
    int16_t max;
    int16_t step;
    bool wrap;

    void initArrows(int16_t _value, int16_t _min, int16_t _max, int16_t _step, boolean _wrap);
    void drawArrows( Adafruit_GFX *gfx,
                    int16_t x, int16_t y,
                    uint16_t w, uint16_t h,
                    uint16_t arrowsframeColor, uint16_t arrowsfillColor);
    bool upArrowContains(int16_t x, int16_t y);
    bool downArrowContains(int16_t x, int16_t y);
    void upArrowHandler();
    void downArrowHandler();
    void showArrowValue(Adafruit_GFX *gfx, int16_t x, int16_t y, uint8_t textSize, uint16_t textColor, uint16_t bkgrndColor );
    
private:
    Adafruit_GFX *_gfx;
    int16_t _x, _y;
    uint16_t _w, _h;
    uint16_t _arrowsframeColor, _arrowsfillColor;
    int16_t _displayX, _displayY;
    uint8_t _textSize;
    uint16_t _textColor, _bkgrndColor;
    char arrwValueStr[5];
protected:
    
    };


#endif /* Arrows_h */
