//
//  Particle.cpp
//  FireworksEffect
//
//  Created by Neil on 2/21/17.
//
//

#include "Particle.hpp"
#include "cinder/Rand.h"

using namespace std;

Particle::Particle(){}

Particle::~Particle(){}

ParticleRef Particle::create(glm::vec2 position, float lifespan, glm::vec2 velocity)
{
    // parameter position is where first particle exploded
    ParticleRef ref = shared_ptr<Particle>(new Particle());
    ref->setup(position, lifespan, velocity);
    return ref;
}

void Particle::setup(glm::vec2 position, float lifespan, glm::vec2 velocity)
{
    mPosition = position;
    mLifespan = lifespan;
    mVelocity = velocity;
    mAcceleration = glm::vec2(0);
    mTimer.start();
}

void Particle::update()
{
    mVelocity += mAcceleration;
    mPosition += mVelocity;
}

void Particle::applyForce(glm::vec2 force)
{
    mAcceleration += force;
}

float Particle::getTimeLeft(){
    
    return mLifespan - mTimer.getSeconds()*5;
}

void Particle::applyFriction(float friction)
{
    mVelocity *= friction;
}


