/*
This sketch will test the carrier board
Unless the touch pads
*/

#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier; // Constructor of the carrier maybe we can include it on the library itself

struct Color
{
  uint32_t led;
  uint32_t display;
};

Color red = {carrier.leds.Color(0, 255, 0), ST7735_RED};
Color green = {carrier.leds.Color(255, 0, 0), ST7735_GREEN};
Color blue = {carrier.leds.Color(0, 0, 255), ST7735_BLUE};

struct RuneDrawing
{
  uint8_t x;
  uint8_t y;
  uint8_t radius;
  uint32_t color;
};

class Rune
{
private:
  bool isRuneActive;
  bool runeChangedStatus;
  void updateButton();
  void setLedColor();
  void drawRune();
  RuneDrawing drawing;

public:
  uint32_t color;
  touchButtons button;
  Rune(touchButtons button, uint32_t color, RuneDrawing drawing);
  void update();
};
Rune::Rune(touchButtons button, uint32_t color, RuneDrawing drawing)
{
  this->button = button;
  this->color = color;
  this->isRuneActive = false;
  this->runeChangedStatus = false;
  this->drawing = drawing;
}
void Rune::updateButton()
{
  carrier.Buttons.update();
  // touch -> rune gets active/inactive
  if (carrier.Buttons.onTouchUp(this->button))
  {
    this->isRuneActive = !this->isRuneActive;
    this->runeChangedStatus = true;
  }
}
void Rune::setLedColor()
{
  if (this->isRuneActive)
  {
    carrier.leds.setPixelColor(this->button, this->color);
  }
  else
  {
    carrier.leds.setPixelColor(this->button, 0);
  }
}
void Rune::drawRune()
{
  if (this->runeChangedStatus)
  {
    carrier.display.fillCircle(drawing.x, drawing.y, drawing.radius, ST7735_BLACK);
    if (this->isRuneActive)
    {
      carrier.display.fillCircle(drawing.x, drawing.y, drawing.radius, drawing.color);
    }
    else
    {
      carrier.display.drawCircle(drawing.x, drawing.y, drawing.radius, drawing.color);
    }
  }
}
void Rune::update()
{
  this->updateButton();
  this->setLedColor();
  this->drawRune();
  this->runeChangedStatus = false;
}

RuneDrawing drawing_0 = {200, 80, 10, red.display};
RuneDrawing drawing_2 = {140, 200, 10, green.display};
RuneDrawing drawing_4 = {80, 80, 10, blue.display};

// Rune rune(TOUCH0, ST77XX_RED, drawing);

Rune runes[3] = {
    Rune(TOUCH0, red.led, drawing_0),
    Rune(TOUCH2, green.led, drawing_2),
    Rune(TOUCH4, blue.led, drawing_4),
};

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;
  carrier.begin();
  carrier.leds.setBrightness(1);
}

void loop()
{
  // carrier.leds.clear();
  for (uint8_t i = 0; i < 3; ++i)
  {
    runes[i].update();
  }
  carrier.leds.show();
}
