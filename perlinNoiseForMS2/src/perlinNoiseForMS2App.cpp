#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Perlin.h"
#include "cinder/Rand.h"
//#include "cinder/PolyLine.h"
#include "Particle.hpp"
#include "ParticleSystem.hpp"
#include "Math.h"
#include "cinder/Serial.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#define BUFSIZE 80
#define READ_INTERVAL 0.1

class perlinNoiseForMS2App : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    ~perlinNoiseForMS2App();

    std::vector<ParticleSystem>     mEmiters;
    cinder::Perlin                  mPerlin;
    float                           mTime;
    float                           mRadius;
    
    SerialRef	mSerial;
    string		mLastString;
    
    const float                     INPUT_MAX = 110;
    const float                     INPUT_MIN = 100;
    const float                     OUTPUT_MAX = 190;
    const float                     OUTPUT_MIN = 150;
};

void perlinNoiseForMS2App::setup()
{
    ci::app::setFullScreen();
    //set up bluetooth devices;
    Serial::Device dev = Serial::findDeviceByNameContains( "cu.HC-05-DevB" );
    mSerial = Serial::create( dev, 9600 );
    
    
    mRadius = 100;
    //set up all emiters position
    for (float i = 0; i < 2*M_PI; i += 0.02) {

        ParticleSystem p;
        p.setup(ci::app::getWindowCenter() + glm::vec2(mRadius*sin(i), mRadius*cos(i)));
        mEmiters.push_back(p);
    }
    
    //set up timer
    mTime = 0;

}

void perlinNoiseForMS2App::mouseDown( MouseEvent event )
{
}

void perlinNoiseForMS2App::update()
{
    //if recived data
    
    while (mSerial->getNumBytesAvailable()>0) {
        mLastString = mSerial->readStringUntil('\n',BUFSIZE);
        //cout<<"mLaststring is : "<< mLastString;
        mRadius = stoi(mLastString);
        mRadius = OUTPUT_MIN + (OUTPUT_MAX - OUTPUT_MIN) * ((mRadius - INPUT_MIN) / (INPUT_MAX - INPUT_MIN));
    }
    //update radius and emiters
    
    cout<<"mRadius: "<<mRadius<<endl;
    for (int i = 0; i < mEmiters.size(); i++) {
        mEmiters[i].update(ci::app::getWindowCenter() + glm::vec2(mRadius*sin(i), mRadius*cos(i)));
    }
    
    mTime = ci::app::getElapsedSeconds()*100;
    
}

void perlinNoiseForMS2App::draw()
{
    
	gl::clear( Color( 0, 0, 0 ) );
    gl::begin(GL_POINTS);
    gl::pointSize(0.5);

    for(int i = 0; i < mEmiters.size(); i++){
        for(auto &p:mEmiters[i].getParticles())
        {
            gl::color(1, 1, 1, p->getTimeLeft()/p->getLifespan());
            vec3 norm = mPerlin.dfBm(vec3(p->getPosition().x, p->getPosition().y, mTime))*0.001f;
            vec2 flowForce = normalize(vec2(norm.x, norm.y))*0.005f;
            p->applyForce(flowForce);
            gl::vertex(p->getPosition());
        }
    }
    gl::end();

}

perlinNoiseForMS2App::~perlinNoiseForMS2App(){}

CINDER_APP( perlinNoiseForMS2App, RendererGl )
