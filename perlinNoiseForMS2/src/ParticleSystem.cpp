//
//  ParticleSystem.cpp
//  perlinNoiseForMS2
//
//  Created by Neil on 4/14/17.
//
//

#include "ParticleSystem.hpp"
#include "Particle.hpp"
#include "cinder/Rand.h"


using namespace ci;
using namespace ci::app;
using namespace std;

ParticleSystem::ParticleSystem(){}

ParticleSystem::~ParticleSystem(){}


void ParticleSystem::setup(glm::vec2 position)
{
    
    mPosition = position;
    particleNum = 40;
    forceRange = 2;
    velocityRange = 2;
    lifespanRange = 3;
    
    for (int i = 0 ; i < particleNum; i++) {
        mSystem.push_back(Particle::create(mPosition, randFloat(lifespanRange), glm::vec2(randFloat(-velocityRange, velocityRange), randFloat(-velocityRange, velocityRange))));
    }
}

void ParticleSystem::update(glm::vec2   position)
{
    
    for (auto &p:mSystem ) {
        p->update();
    }
    for (auto p = mSystem.begin();  p != mSystem.end();) {

        if ((*p)->getTimeLeft() < 0){
            mSystem.erase(p);
            mSystem.push_back(Particle::create(position, randFloat(lifespanRange), glm::vec2(randFloat(-velocityRange, velocityRange), randFloat(-velocityRange, velocityRange))));
        }
        else{
            ++p;
        }
    }
    mTime = ci::app::getElapsedSeconds()*100;
    
}


