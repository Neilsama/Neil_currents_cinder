//
//  ParticleSystem.hpp
//  SnowEffect
//
//  Created by Neil on 2/15/17.
//
//

#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp

#include <stdio.h>
#include "Particle.hpp"

class ParticleSystem{
    
public:
    
    ParticleSystem();
    ~ParticleSystem();
    void update();
    void draw();
    
private:
    int mParticleNum;
    std::vector<Particle> mParticles;
};
#endif /* ParticleSystem_hpp */
