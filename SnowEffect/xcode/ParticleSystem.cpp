//
//  ParticleSystem.cpp
//  SnowEffect
//
//  Created by Neil on 2/15/17.
//
//

#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(){
    mParticleNum = 800;
    
    for (int i = 0; i < mParticleNum; i++) {
        Particle singleParticle;
        mParticles.push_back(singleParticle);
    }
}

ParticleSystem::~ParticleSystem(){
}

void ParticleSystem::update(){
    for(auto& p: mParticles){
        p.update();
    }
}

void ParticleSystem::draw(){
    for(auto& p: mParticles){
        p.draw();
    }
}
