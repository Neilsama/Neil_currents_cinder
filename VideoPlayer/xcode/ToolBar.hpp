//
//  ToolBar.hpp
//  VideoPlayer
//
//  Created by Neil on 3/7/17.
//
//

#ifndef ToolBar_hpp
#define ToolBar_hpp

#include <stdio.h>
#include "cinder/gl/Texture.h"
#include "cinder/Surface.h"
#include "cinder/gl/gl.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class ToolBar;

//typedef  std::shared_ptr<ToolBar> ToolBarRef;

class ToolBar{
public:
//    static ToolBarRef  creat(ci::vec2 startpoint, ci::vec2 toolBarSize);
    ToolBar();  
    void        setup(ci::vec2 startpoint, ci::vec2 toolBarSize);
    void        update(float time);
    void        draw();
    bool        inPlayButton(ci::vec2 mousePos);
    bool        inOpenFileButton(ci::vec2 mousePos);
    bool        inSeekBar(ci::vec2 mousePos);
    float       getHandlePos();
    
    bool        isPlaying;
    float       currentTime;

private:
    
    ci::vec2            mToolBarPos;
    
    ci::vec2            mToolBarSize;
    
    ci::vec2            mPlayButtonSize;
    ci::gl::TextureRef  playButtonTexture;
    ci::gl::TextureRef  stopButtonTexture;
    
    ci::vec2            mOpenFileSize;
    ci::gl::TextureRef  openFileTexture;
    
    
    


    
    
    
    
    

    
};

#endif /* ToolBar_hpp */
