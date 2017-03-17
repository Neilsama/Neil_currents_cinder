#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ImageManipulationApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    ci::Surface8u mSurface; // normal surface;
    ci::Surface8u mSurfaceInvert; // invert surface;
    ci::Surface8u mSurfaceTwirl; // twirled surface;
    
    gl::TextureRef mTexture; //normal texture from image;
    gl::TextureRef mTexInvertFromSurface; // texture from invert color image;
    gl::TextureRef mTexTwirlFromSurface; // texture from twirled image;
    
    float maxAngle; // the max angle that twirled;
    
    float mWidth;
    float mHeight;
    
    
    void twirlSurface(Surface8u *surface, Area area, float maxAngle);
    Rectf getRectf(vec2 startPoint,vec2 size, vec2 scale);
    
};

//--------------------------------------------------
void ImageManipulationApp::setup()
{
    ci::app::setWindowSize(1000.f, 800.f);
    
    mWidth = 800.f;
    mHeight = 530.f;
    

    
    try{
        
        mSurface = loadImage(ci::app::loadAsset("2.jpg"));
        mSurfaceInvert = mSurface.clone();
        mSurfaceTwirl = mSurface.clone();

        mTexture = gl::Texture::create(mSurface);
        mTexInvertFromSurface = mTexture;
        mTexTwirlFromSurface = mTexture;
        
    } catch (exception & e){
        ci::app::console() << e.what() << endl;
    }
}

//--------------------------------------------------
void ImageManipulationApp::update()
{
    mTexture = gl::Texture::create(mSurface);
    mTexInvertFromSurface = gl::Texture::create(mSurfaceInvert);
    mTexTwirlFromSurface = gl::Texture::create(mSurfaceTwirl);
    
    
}

//--------------------------------------------------
void ImageManipulationApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    //draw the normal image;
    gl::draw(mTexture, getRectf(vec2(10.f, 10.f), vec2(mWidth/2, mHeight/2), vec2(1.f, 1.f)));
    
    //draw the invert image;
    gl::draw(mTexInvertFromSurface, getRectf(vec2(20.f + mWidth/2, 10.f), vec2(mWidth/2, mHeight/2), vec2(1.f, 1.f)));
    
    //draw the twirled image;

    
    
    gl::draw(mTexTwirlFromSurface, getRectf(vec2(10.f, 20.f + mHeight/2), vec2(mWidth/2, mHeight/2), vec2(1.f,1.f)));

}

//----------------------------------------------------------
Rectf ImageManipulationApp::getRectf(vec2 startPoint, vec2 size, vec2 scale)
{
     return Rectf(startPoint.x, startPoint.y, (size.x + startPoint.x) * scale.x, (size.y + startPoint.y) * scale.y);
}

//----------------------------------------------------------

void ImageManipulationApp::twirlSurface(Surface8u *surface, Area area, float maxAngle)
{
    ci::Surface8u inputSurface = surface->clone();
    
    ci::Surface8u::Iter inputIter(inputSurface.getIter());
    ci::Surface8u::Iter outputIter(surface->getIter());

    float maxDistance = ci::length((glm::vec2)area.getSize());
    glm::vec2 mid = (area.getUL()+area.getLR())/2;
    
    while (inputIter.line() && outputIter.line()) {
        while (inputIter.pixel() && outputIter.pixel()) {
            glm::vec2 current = (glm::vec2)inputIter.getPos() - mid;
            float r = length(current);
            
            float twirlAngle = r/maxDistance*maxAngle;
            float angle = atan2(current.x, current.y);
            
            glm::vec2 outSample(r*cos(angle + twirlAngle), r * sin(angle + twirlAngle));
            glm::vec2 out = outSample - current;
            
            outputIter.r() = inputIter.rClamped(out.x, out.y);
            outputIter.g() = inputIter.gClamped(out.x, out.y);
            outputIter.b() = inputIter.bClamped(out.x, out.y);
        }
    }
    
    
}

//--------------------------------------------------
void ImageManipulationApp::mouseDown( MouseEvent event )
{
    if(event.isRight())
    {
        console()<<"mouse pressed" << std::endl;
        ci::Surface::Iter iter = mSurfaceInvert.getIter();
        while (iter.line()) {
            while (iter.pixel()) {
                iter.r() = 255.f - iter.r();
                iter.g() = 255.f - iter.g();
                iter.b() = 255.f - iter.b();
            }
        }
    }
    
    maxAngle = event.getX()%360;
    mSurfaceTwirl = mSurface.clone();
    twirlSurface(&mSurfaceTwirl, mSurfaceTwirl.getBounds(), maxAngle);
    console()<< maxAngle <<std::endl;
    
    

    
    
}
//--------------------------------------------------

CINDER_APP( ImageManipulationApp, RendererGl )
