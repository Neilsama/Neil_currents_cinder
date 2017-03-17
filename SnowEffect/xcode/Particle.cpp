//
//  Particle.cpp
//  SnowEffect
//
//  Created by Neil on 2/14/17.
//
//

#include "Particle.hpp"
#include "cinder/Rand.h"

Particle::Particle(){
    mPosition = glm::vec2(ci::randFloat(0.f, ci::app::getWindowWidth()), ci::randFloat(0.f, ci::app::getWindowHeight()));
    mVelocity = glm::vec2(0.f, 0.f);
    mAcceleration = glm::vec2(0.f, 9.8f);
    mFiction = 0.1f;
    
    mSize = ci::randFloat(0.5f, 2.f);
    mOpaticy = mSize*0.1f+ 0.5f;
    
}

Particle::~Particle(){}

void Particle::update(){
    mVelocity += mAcceleration;
    mVelocity *= mFiction + mSize*0.05f;
    mPosition += mVelocity;
    bonceBoundary();
}

void Particle::draw(){
    ci::gl::color(255, 255, 255, mOpaticy);
    ci::gl::drawSolidCircle(getPosition(), mSize);
}

glm::vec2 Particle::getPosition(){
    return mPosition;
}

void Particle::bonceBoundary(){
    if (mPosition.y >= ci::app::getWindowHeight()){
        mPosition = glm::vec2(ci::randFloat(0.f, ci::app::getWindowWidth()), 0.f);
    }
}
//glm::vec2 Particle::getAcceleration(){
//    //force = gravity - airForce
//    // airForce = mFiction * mVelocity;
//    //when gravity = ariForce, particle fall down with mVelocity;
//}
