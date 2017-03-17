#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "ParticleSystem.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class SnowEffectApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    ParticleSystem mParticleSystem;
    
};

void SnowEffectApp::setup()
{
    ci::app::setFrameRate(60);
}

void SnowEffectApp::mouseDown( MouseEvent event )
{
}

void SnowEffectApp::update()
{
    mParticleSystem.update();
}

void SnowEffectApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    mParticleSystem.draw();
}

CINDER_APP( SnowEffectApp, RendererGl )
