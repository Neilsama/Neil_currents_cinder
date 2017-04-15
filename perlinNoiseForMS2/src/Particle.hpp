//
//  Particle.hpp
//  FireworksEffect
//
//  Created by Neil on 2/21/17.
//
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>

class Particle;

typedef std::shared_ptr<Particle> ParticleRef; // one particle's reference

class Particle{

public:
    Particle();
    ~Particle();
    
    // create reference of one parcicle information: position is where first step particle's position, velocity is random vec2, lifespan is same, apply same force
    
    static ParticleRef create(glm::vec2 position, float lifespan, glm::vec2 velocity);
    void        setup(glm::vec2 position, float lifespan, glm::vec2 velocity);
    
    void        update();
    void        applyForce(glm::vec2 force);
    void        applyFriction(float friction);
    glm::vec2   getPosition(){return mPosition;}
    glm::vec2   getVelocity(){return mVelocity;}
    float       getTimeLeft();
    float       getLifespan(){return mLifespan;}
    

private:
    
    glm::vec2   mPosition;
    glm::vec2   mVelocity;
    glm::vec2   mAcceleration;
    float       mLifespan;
    
    ci::Timer   mTimer;
    
};

#endif /* Particle_hpp */
