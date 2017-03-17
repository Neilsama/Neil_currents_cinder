#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/Timeline.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class animationPracticeApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

    
    ci::Anim<ci::vec2>      startPos;
    ci::Anim<float>         homeRadius;
    
    //ci::Anim<vector<shared_ptr<vec2>>>  mPos;
    ci::Anim<ci::vec2>  singlePos;
    std::shared_ptr<Anim<ci::vec2>> mPos;
    std::vector<shared_ptr<Anim<ci::vec2>>> mPositions;
    
    int                     circleNum;
    const float             RANDOM_DISTANCE_RANGE = 300.f;
    
};

void animationPracticeApp::setup()
{
    circleNum = 100;
}

void animationPracticeApp::mouseDown( MouseEvent event )
{
    startPos = glm::vec2(event.getPos());
    //generate other circles
    
    for (int i = 0; i < circleNum; i++) {
        
        singlePos = vec2(startPos.value() + vec2(randFloat(-RANDOM_DISTANCE_RANGE,RANDOM_DISTANCE_RANGE), randFloat(-RANDOM_DISTANCE_RANGE,RANDOM_DISTANCE_RANGE)));
        mPos = shared_ptr<Anim<ci::vec2>>(new Anim<ci::vec2>);
        *mPos = singlePos;
        mPositions.push_back(mPos);
    }
    
    for(auto &p : mPositions){
        timeline().apply(&(*p), vec2(startPos), ci::randFloat(1.8f, 2.8f), EaseOutExpo());
    }

}

void animationPracticeApp::update()
{
    for(auto p = mPositions.begin(); p != mPositions.end();){
        if ((*p)->value() == glm::vec2(startPos)){
            p = mPositions.erase(p);
        }
        else ++p;
    }
}

void animationPracticeApp::draw()
{
    gl::clear( Color(0.917,0.717, 0.109));
    
    cout<<"total: "<<mPositions.size()<<endl;
    
    gl::begin(GL_POINTS);
    gl::pointSize(2.f);
    for(auto & p: mPositions){
        gl::color(1, 1, 1, ci::randFloat(0.4f, 0.9f));
        gl::vertex(ci::vec2((*p).value()));
//        gl::color(1, 1, 1, 0.2);
//        gl::drawLine(startPos.value(), *p);
    }
    gl::end();
}

CINDER_APP( animationPracticeApp, RendererGl )
