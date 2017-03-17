//
//  ToolBar.cpp
//  VideoPlayer
//
//  Created by Neil on 3/7/17.
//
//

#include "ToolBar.hpp"


ToolBar::ToolBar()
{
    mToolBarPos = ci::vec2(100, 560);
    mToolBarSize = ci::vec2(640, 40);
}

void ToolBar::setup(ci::vec2 startpoint, ci::vec2 toolBarSize)
{
    try {
        playButtonTexture = ci::gl::Texture::create(loadImage(ci::app::loadAsset("playButton.png")));
        cout<<playButtonTexture<<endl;
        stopButtonTexture = ci::gl::Texture::create(loadImage(ci::app::loadAsset("stopButton.png")));
        openFileTexture = ci::gl::Texture::create(loadImage(ci::app::loadAsset("openfileButton.png")));
        
    } catch (std::exception &e) {
        cout<<e.what()<<endl;
    }
    
   
    mPlayButtonSize = mOpenFileSize = ci::vec2(toolBarSize.y);
    
    isPlaying = true;

}

void ToolBar::update(float time)
{
    currentTime = time;
}

void ToolBar::draw()
{

    {gl::ScopedColor newColor2(1, 1, 1, 0.5);
    
    ci::gl::drawSolidRect(Rectf(100, 560, 740, 600));
    }
    
    if (playButtonTexture && isPlaying) {
        gl::draw(playButtonTexture, Rectf(155, 560, 155+mPlayButtonSize.x, 560+mPlayButtonSize.y));
    }
    if (stopButtonTexture && !isPlaying) {
        gl::draw(stopButtonTexture, Rectf(155, 560, 155+mPlayButtonSize.x, 560+mPlayButtonSize.y));
    }
    
    if (openFileTexture) {
        gl::draw(openFileTexture, Rectf(110, 560, 110+mPlayButtonSize.x, 560+mPlayButtonSize.y));
    }
    
    gl::drawSolidRect(Rectf(205,575, 725, 582));
    //draw seekbar
    {
    gl::ScopedColor newColor1( 0.917, 0.717, 0.109);
    gl::drawSolidRect(Rectf(205, 580, currentTime+205, 577));
    }
}

bool ToolBar::inPlayButton(ci::vec2 mousePos)
{
    if(mousePos.x <= 195 && mousePos.x >= 155 && mousePos.y <= 600 && mousePos.y >= 560)
        return true;
    else
        return false;
}

bool ToolBar::inOpenFileButton(ci::vec2 mousePos)
{
    if(mousePos.x <= 150 && mousePos.x >= 110 && mousePos.y <= 600 && mousePos.y >= 560)
        return true;
    else
        return false;
}

bool ToolBar::inSeekBar(ci::vec2 mousePos)
{
    if (mousePos.x <= 725 && mousePos.x >= 205 & mousePos.y <=580 && mousePos.y >=577)
    {
        return true;
    }
    else
        return false;
}


