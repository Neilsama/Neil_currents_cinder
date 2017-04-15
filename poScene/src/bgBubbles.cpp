//
//  bgBubble.cpp
//  poScene
//
//  Created by Neil on 4/4/17.
//
//

#include "bgBubbles.h"


using namespace ci;
using namespace ci::app;
using namespace std;

bgBubblesRef bgBubbles::create()
{
    bgBubblesRef ref = std::shared_ptr<bgBubbles>(new bgBubbles);
    ref->setup();
    return ref;
}

bgBubbles::bgBubbles()
:mIsActivate(false)
,mBgCircleSize(510.f)
,mBgCirclePosition1(glm::vec2(378/2,-188/2)), mBgCirclePosition2(glm::vec2(56/2, 1562/2)), mBgCirclePosition3(glm::vec2(612/2, 1380/2))
,mTime(0.f)
,mFrequency(1/200.f)

{
}

void bgBubbles::setup()
{
    mBgCircle1 = po::scene::Shape::createCircle(mBgCircleSize);
    mBgCircle2 = po::scene::Shape::createCircle(mBgCircleSize);
    mBgCircle3 = po::scene::Shape::createCircle(mBgCircleSize);
    
    mBgCircle1->setPosition(mBgCirclePosition1);
    mBgCircle2->setPosition(mBgCirclePosition2);
    mBgCircle3->setPosition(mBgCirclePosition3);
    
    ci::ColorA bubbleColor = ci::ColorA::hex(0x802d5a);
    mBgCircle1->setFillColor(255, 255, 255, 0.1);
    mBgCircle2->setFillColor(bubbleColor);
    mBgCircle3->setFillColor(bubbleColor);
    mBgCircle2->setAlpha(0.1f);
    mBgCircle3->setAlpha(0.1f);
    
    mBgCircle1->setAlignment(po::scene::Alignment::CENTER_CENTER);
    mBgCircle2->setAlignment(po::scene::Alignment::CENTER_CENTER);
    mBgCircle3->setAlignment(po::scene::Alignment::CENTER_CENTER);
    addChild(mBgCircle1);
    addChild(mBgCircle2);
    addChild(mBgCircle3);
    
//    getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&bgBubbles::onMouseEvent, this, std::placeholders::_1));
    
}

void bgBubbles::update()
{
    mTime += 4.f;
    
    vec3 norm1 = mPerlin.dfBm(vec3(mBgCirclePosition1.x,mBgCirclePosition1.y, mTime)*mFrequency)*200.f;
    mBgCirclePosition1 = mBgCirclePosition1+normalize(vec2(norm1.x, norm1.y));
    mBgCircle1->setPosition(mBgCirclePosition1);
    
    vec3 norm2 = mPerlin.dfBm(vec3(mBgCirclePosition2.x,mBgCirclePosition2.y, mTime)*mFrequency)*200.f;
    mBgCirclePosition2 = mBgCirclePosition2+normalize(vec2(norm2.x, norm2.y));
    mBgCircle2->setPosition(mBgCirclePosition2);
    
    vec3 norm3 = mPerlin.dfBm(vec3(mBgCirclePosition3.x,mBgCirclePosition3.y, mTime)*mFrequency)*200.f;
    mBgCirclePosition3 = mBgCirclePosition3+normalize(vec2(norm3.x, norm3.y));
    mBgCircle3->setPosition(mBgCirclePosition3);

}

//
//void bgBubbles::onMouseEvent(po::scene::MouseEvent &event)
//{
//    switch (event.getType()) {
//        case po::scene::MouseEvent::DOWN_INSIDE:
//            mIsActivate = !mIsActivate;
//            if (mIsActivate) {
//                mBgBubbleStateChangeSignal.emit(true);
//            }
//            else{
//                mBgBubbleStateChangeSignal.emit(false);
//            }
//            break;
//            
//        default:
//            break;
//    }
//}

void bgBubbles::reset()
{
    mIsActivate = false;
    mBgCirclePosition1 = glm::vec2(378/2,-188/2);
    mBgCirclePosition2 = glm::vec2(56/2, 1562/2);
    mBgCirclePosition3 = glm::vec2(612/2, 1380/2);
    mTime = 0.f;
}





