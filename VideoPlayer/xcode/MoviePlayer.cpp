//
//  MoviePlayer.cpp
//  VideoPlayer
//
//  Created by Neil on 3/7/17.
//
//

#include "MoviePlayer.hpp"
#include "ToolBar.hpp"

MoviePlayerRef MoviePlayer::creat()
{
    MoviePlayerRef ref = std::shared_ptr<MoviePlayer>(new MoviePlayer());
    ref->setup();
    return ref;
}
void MoviePlayer::loadVideo(const fs::path videoPath)
{
    try {
        mMovie = ci::qtime::MovieGl::create(videoPath);
        mMovie->play();
        mMovie->setLoop();
        isPlaying = true;
    } catch (std::exception &e) {
        cout<<e.what()<<endl;
    }
}

void MoviePlayer::setWindow(ci::vec2 startPoint, float width, float height)
{
    mWindowSize = ci::vec2 (width, height);
    mWindowRect = Rectf(startPoint.x, startPoint.y, startPoint.x + width, startPoint.y + height);
    mWindowPos = startPoint;
}

void MoviePlayer::update()
{
    if(mMovie)
        mFrameTexture = mMovie->getTexture();
}

float MoviePlayer::getCurrentTime()
{
    float time = mMovie->getCurrentTime()/mMovie->getDuration() * 520.f;
    return time;
}

void MoviePlayer::setVideoTimeTo(float newTime)
{
    mMovie->seekToTime(newTime);
}

void MoviePlayer::draw()
{
    if (mFrameTexture) {
        ci::gl::draw(mFrameTexture, mWindowRect);
    }
}


MoviePlayer::MoviePlayer(){}

void MoviePlayer::setup()
{
    
}
