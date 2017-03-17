#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class analogDigitApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    void drawHorizontalLine(float x, float y, float height);
    void drawVerticalLine(float x, float y, float width);
};

void analogDigitApp::setup()
{
    setWindowSize(700.f, 700.f);
}

void analogDigitApp::mouseDown( MouseEvent event )
{
}

void analogDigitApp::update()
{
}

void analogDigitApp::draw()
{
    float a = 20.f; //the height or width of component
    float space = 5.f; // the space between tow components
    
	gl::clear( Color( 0, 0, 0 ) );
    
    
    // digit 4
    drawVerticalLine(100, 100, a);
    drawHorizontalLine(100 + a + space, 100 + 4 * a + space, a);
    drawVerticalLine(100 + 2 * space + 5 * a, 100, a);
    drawVerticalLine(100 + 2 * space + 5 * a, 100 + 2 * space + 5 * a, a);
    
    // digit 6
    drawVerticalLine(250, 100, a);
    drawHorizontalLine(250 + a + space, 100 - a - space, a);
    drawVerticalLine(250, 100 + 5 * a + 2 * space, a);
    drawHorizontalLine(250 + a + space, 100 + 4 * a + space, a);
    drawVerticalLine(250 + 5 * a + 2 * space, 100 + 5 * a + 2 * space, a);
    drawHorizontalLine(250 + a + space, 100 + 9 * a + 3 * space, a);
    
    
}

void analogDigitApp::drawHorizontalLine(float x, float y, float height){
    gl::drawSolidRect(Rectf(x, y, x + 4 * height, y + height));
    gl::drawSolidTriangle(vec2(x, y), vec2(x-height/2,y+height/2), vec2(x,y+height));
    gl::drawSolidTriangle(vec2(x+4*height,y), vec2(x+4.5*height,y+height/2), vec2(x+4*height,y+height));
}

void analogDigitApp::drawVerticalLine(float x, float y, float width){
    gl::drawSolidRect(Rectf(x, y, x + width, y+4*width));
    gl::drawSolidTriangle(vec2(x, y), vec2(x + width/2, y - width/2), vec2(x + width, y));
    gl::drawSolidTriangle(vec2(x, y + 4 * width), vec2(x + width/2, y + 4.5 * width), vec2(x + width, y + 4 * width));
}



CINDER_APP( analogDigitApp, RendererGl )
