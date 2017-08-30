/*
THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
/*
 * Demonstrates single arrow button with value display.
 * For Adafruit 2.8" TFT LCD - capacitive.
 * Any of the four screen rotations may be used. 
 * Requires Arrows folder in libraries folder.
 * https://github.com/vsquared/Arrows
*/

#include "Adafruit_ILI9341.h"
#include "Adafruit_FT6206.h"
#include "Arrows.h"

// Default values for Adafruit shield v2.
#define TFT_DC 9
#define TFT_CS 10

// The FT6206 uses hardware I2C (SCL/SDA)
Adafruit_FT6206 ctp = Adafruit_FT6206();
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// Common 16-bit colors:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

const int rotation = 0; //(0->3)
// Rotations 0,2 = portrait  : 0->USB=right,upper : 2->USB=left,lower
// Rotations 1,3 = landscape : 1->USB=left,upper  : 3->USB=right,lower

Arrows arrw;
/* Arrow value may be accessed at
 * any time by using arrw.value.
 */

void displayValue() {
 //showValue(&tft,x,y,txtSize,txtColor,bkgrndColor)
 arrw.showArrowValue(&tft,120,60,3,WHITE,BLACK); 
}

void setup() {
 Serial.begin(9600);
 tft.begin();
 if (! ctp.begin()) {  // pass in 'sensitivity' coefficient
    Serial.println("Couldn't start FT6206 touchscreen controller");
    while (1);
   }
 tft.setRotation(rotation);
 tft.fillScreen(BLACK);
 //initArrows(value,min,max,step,wrap)
 arrw.initArrows(50,20,90,2,false);
 //drawArrows(&tft,x,y,w,h,frameColor,arrowColor)
 arrw.drawArrows(&tft, 30, 30, 60, 120, WHITE, GREEN);
 displayValue();
}

void loop() {
  uint16_t x, y;
 TS_Point p;

 if (! ctp.touched()) {  
    return;
 }
 
  p = ctp.getPoint();
 
 switch (rotation) {
  case 0:
   x = 240 - p.x;
   y = 320 - p.y;
  break;
  case 1:   // p.x, p.y reversed
   x = 320 - p.y;
   y = p.x;
  break;
  case 2:
   x = p.x;
   y = p.y;
  break;
  case 3:  // p.x, p.y reversed
   x = p.y;
   y = 240 - p.x;
  break; 
 }
 
  while (ctp.touched()) { 
    if(arrw.upArrowContains(x,y)) {arrw.upArrowHandler();delay(100);displayValue();}
    if(arrw.downArrowContains(x,y)) {arrw.downArrowHandler();delay(100);displayValue();}       
  }
}

