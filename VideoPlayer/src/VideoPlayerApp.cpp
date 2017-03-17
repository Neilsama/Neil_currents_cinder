#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "MoviePlayer.hpp"
#include "ToolBar.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class VideoPlayerApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    MoviePlayerRef     mPlayer;
    ci::fs::path       mFilePath;
    
    ToolBar         mToolBar;
    ci::vec2        cursorPos;
    
};

void VideoPlayerApp::setup()
{
    ci::app::setWindowSize(1000, 800);
    mPlayer = MoviePlayer::creat();
    mFilePath = getOpenFilePath();
    if (! mFilePath.empty()) {
        mPlayer->loadVideo(mFilePath);
    }
    mPlayer->setWindow(ci::vec2(100.f, 80.f), 640, 480);
    
    mToolBar.setup(ci::vec2(100.f, 560.f), ci::vec2(640, 40));
    mToolBar.isPlaying = false;
    cursorPos = ci::vec2(205, 577);
}

void VideoPlayerApp::mouseDown( MouseEvent event )
{
    if (mToolBar.inPlayButton(ci::vec2(event.getPos())))
    {
        if (mPlayer->isPlaying) {
            mPlayer->stopMovie();
            mToolBar.isPlaying = true;
            cout <<"stopped" <<endl;
        }else{
            mPlayer->playMovie();
            mToolBar.isPlaying = false;
            cout <<"played" <<endl;
        }
        
    }
    if (mToolBar.inOpenFileButton(event.getPos())) {
        mFilePath = getOpenFilePath();
        if (! mFilePath.empty()) {
            mPlayer->loadVideo(mFilePath);
        }
    }
    
    if(mToolBar.inSeekBar(ci::vec2(event.getPos())))
    {
        float pos = event.getX() - 205;
        mPlayer->setVideoTimeTo(pos/520 * mPlayer->getDuration());
    }
    

}

void VideoPlayerApp::update()
{
    mPlayer->update();
    mToolBar.update(mPlayer->getCurrentTime());
    
}

void VideoPlayerApp::draw()
{
	gl::clear( Color(  0.917, 0.717, 0.109 ) );
    mPlayer->draw();
    mToolBar.draw();
    
}

CINDER_APP( VideoPlayerApp, RendererGl )
