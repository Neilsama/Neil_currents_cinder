//
//  MoviePlayer.hpp
//  VideoPlayer
//
//  Created by Neil on 3/7/17.
//
//

#ifndef MoviePlayer_hpp
#define MoviePlayer_hpp

#include <stdio.h>
#include "cinder/qtime/QuickTimeGL.h"
#include "cinder/gl/Texture.h"
#include "cinder/Surface.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class MoviePlayer;

typedef std::shared_ptr<MoviePlayer> MoviePlayerRef;

class MoviePlayer{
public:
    static MoviePlayerRef creat();
    void loadVideo(const fs::path videoPath);
    
    void setWindow(ci::vec2 startPoint , float width, float height);
    ci::vec2 getWindowPos(){return mWindowPos;};

    void update();
    void draw();
    void stopMovie(){mMovie->stop(); isPlaying = false;};
    void playMovie(){mMovie->play(); isPlaying = true;};
    
    bool isPlaying;
    float       getCurrentTime();
    float       getDuration(){return mMovie->getDuration();}
    
    void   setVideoTimeTo(float newTime);

    
 
private:
    MoviePlayer();
    void setup();
    
    ci::gl::TextureRef      mFrameTexture;
    ci::qtime::MovieGlRef   mMovie;
    ci::fs::path            mMoviePath;
    ci::vec2                mWindowPos;
    ci::vec2                mWindowSize;
    Rectf                   mWindowRect;

};

#endif /* MoviePlayer_hpp */
