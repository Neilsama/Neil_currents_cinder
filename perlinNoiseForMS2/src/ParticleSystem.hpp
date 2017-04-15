//
//  ParticleSystem.hpp
//  perlinNoiseForMS2
//
//  Created by Neil on 4/14/17.
//
//

#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp

#include <stdio.h>
#include "Particle.hpp"
#include "cinder/Perlin.h"


class ParticleSystem
{
public:

    ParticleSystem();
    void    setup(glm::vec2 position);
    void    update(glm::vec2   position);
    glm::vec2   getPosition(){return  mPosition;}
    std::vector<ParticleRef>    getParticles(){return mSystem;}

    
    ~ParticleSystem();
    
private:
    
    glm::vec2   mPosition;
    int         particleNum;
    float       forceRange;
    float       velocityRange;
    float       lifespanRange;
    float       mTime;
    
    std::vector<ParticleRef>    mSystem;
    
};

#endif /* ParticleSystem_hpp */
