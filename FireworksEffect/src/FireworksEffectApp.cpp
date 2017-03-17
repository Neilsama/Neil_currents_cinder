#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "Particle.hpp"
#include "cinder/Rand.h"
#include "cinder/Perlin.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class FireworksEffectApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    Particle mParticle; // launched particle;
    
    const float RANDOM_LIFESPAN = 4.f;
    const int   PARTICLE_NUM = 100;
    const float RANDOM_FORCE = 0.1f;
    const float RANDOM_VELECITY = 10.f;
    
    bool rising = false;
    bool explode = false;
    bool finish = true;

    Perlin mPerlin;
    
    float mTime;
    
    std::vector<ParticleRef> firework; // one firework's particle system
    
};

void FireworksEffectApp::setup()
{
    ci::app::setWindowSize(800, 640);
}

void FireworksEffectApp::mouseDown( MouseEvent event )
{
    
    mParticle.setup(glm::vec2(event.getPos()), ci::randFloat(3, 4),glm::vec2(0, ci::randFloat(-25.f,-15.f)));
    
    mParticle.applyForce(glm::vec2(0, 0.5f));
    rising = true;
}

void FireworksEffectApp::update()
{
    // if first particle is rising
    if(rising){
        mParticle.update();
    
        if (mParticle.getVelocity().y > 0.f)
        {
            for (int i = 0; i <PARTICLE_NUM; i++) {
                firework.push_back(Particle::create(mParticle.getPosition(), ci::randFloat(0, RANDOM_LIFESPAN),glm::vec2(ci::randFloat(-5, 5), ci::randFloat(-5,5))));
            }
            rising = false;
            explode = true;
            //cout<<"exploded"<<endl;
        }
    }
    
    if(explode)
        for(auto&p: firework){
            p->applyForce(glm::vec2(0, 0.5f));
            mTime = ci::app::getElapsedSeconds()*100.f;;
            explode = false;
            finish = false;
        }
    
    if(!finish){
        for(auto&p:firework)
        {
            p->update();
            cout<<"particle the velocity: "<<p->getVelocity()<<endl;
        }
    
        for(auto p = firework.begin(); p != firework.end();)
        {
            if((*p)->getTimeLeft() < 0)
                p = firework.erase(p);
            else
                ++p;
        }
        if(firework.size() == 0){
            finish = true;
            cout<<"finished"<<endl;
        }
    }


    

}

void FireworksEffectApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    //cout<<mParticle.getTimeLeft()/mParticle.getLifespan()<<endl;
    gl::begin(GL_POINTS);
    
    
    if (rising) {
        gl::color(1, 1,1, mParticle.getTimeLeft()/mParticle.getLifespan());
        gl::vertex(mParticle.getPosition());
    }
    if(!finish){
        for(auto&p: firework)
        {
            gl::color(1, 1, 1, p->getTimeLeft()/p->getLifespan());
            
            vec3 norm = mPerlin.dfBm(vec3(p->getPosition().x, p->getPosition().y, mTime))*0.01f;
            vec2 flowForce = normalize(vec2(norm.x, norm.y))*0.05f;
            p->applyForce(flowForce);
            gl::vertex(p->getPosition());
        }
    }
    
    gl::end();
    
}

CINDER_APP( FireworksEffectApp, RendererGl )
