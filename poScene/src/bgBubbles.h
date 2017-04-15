//
//  bgBubble.h
//  poScene
//
//  Created by Neil on 4/4/17.
//
//

#ifndef bgBubble_h
#define bgBubble_h

#include <stdio.h>
#include "poNodeContainer.h"
#include "poShape.h"
#include "cinder/Signals.h"
#include "cinder/Perlin.h"

using namespace ci;
using namespace ci::app;
using namespace std;

//  create a shared pointer type for background bubble class
class bgBubbles;
typedef std::shared_ptr<bgBubbles> bgBubblesRef;

//  add signal to move bubbles
typedef ci::signals::Signal<void(bool state)> BgBubblesStateChangeSignal;


//  define the class
class bgBubbles
: public po::scene::NodeContainer
{
public:
    static bgBubblesRef create();
    //BgBubblesStateChangeSignal& getBgBubblesStateChangeSignal(){return mBgBubbleStateChangeSignal;};
    
    void reset();
    
private:
    bgBubbles();
    void setup();
    void update();
    //void onMouseEvent(po::scene::MouseEvent &event);

    //  three bubbles in background
    po::scene::ShapeRef     mBgCircle1;
    po::scene::ShapeRef     mBgCircle2;
    po::scene::ShapeRef     mBgCircle3;
    
    float           mBgCircleSize;
    
    glm::vec2       mBgCirclePosition1;
    glm::vec2       mBgCirclePosition2;
    glm::vec2       mBgCirclePosition3;
    
    //  Signal
    //BgBubblesStateChangeSignal  mBgBubbleStateChangeSignal;
    
    //  state bool
    bool    mIsActivate;
    
    cinder::Perlin  mPerlin;
    float           mTime;
    float           mFrequency;
};


#endif /* bgBubble_h */
