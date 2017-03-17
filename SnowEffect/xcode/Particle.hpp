//
//  Particle.hpp
//  SnowEffect
//
//  Created by Neil on 2/14/17.
//
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>
class Particle{
public:
    Particle();
    ~Particle();
    void update();
    void draw();
    glm::vec2 getPosition();
    void bonceBoundary();
    
    
    
private:
    glm::vec2 mVelocity;
    glm::vec2 mAcceleration;
    glm::vec2 mPosition;
    float mSize;
    float mOpaticy;
    float mFiction; //air flow fiction
    
};

#endif /* Particle_hpp */
