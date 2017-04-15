//
//  button.cpp
//  poScene
//
//  Created by Neil on 4/4/17.
//
//

#include "button.h"

buttonRef button::create(float length, float radius, ci::Color buttonColor, ci::Color buttonActiveColor, std::string buttonText, ci::Color textColor, ci::Color textActiveColor, float textSize, bool clickable)
{
    buttonRef ref = std::shared_ptr<button>(new button);
    ref->setup(length, radius, buttonColor, buttonActiveColor, buttonText, textColor, textActiveColor, textSize, clickable);
    return ref;
}

button::button()
:mRadius(0.f), mLength(0.f), mIsActivate(false)
{
}

void button::setup(float length, float radius, ci::Color buttonColor, ci::Color buttonActiveColor, std::string buttonText, ci::Color textColor, ci::Color textActiveColor, float textSize, bool clickable)
{
    mRadius = radius;
    mLength = length;
    
    mButtonColor = buttonColor;
    mButtonActivateColor = buttonActiveColor;
    mClickable = clickable;
    
    mTextColor = textColor;
    mTextActivateColor = textActiveColor;
    mTextSize = textSize;
    
    addShape();
    addText(buttonText);
    
    if (clickable) {
        getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&button::onMouseEvent, this, std::placeholders::_1));
    }
    
}

void button::addShape()
{
    mBgCircleLeft = po::scene::Shape::createCircle(mRadius * 2.f);
    mBgCircleRight = po::scene::Shape::createCircle(mRadius * 2.f);
    mBgRect = po::scene::Shape::createRect(mRadius * 2.f + mLength, mRadius * 2.f);
    
    mBgCircleLeft->setPosition(glm::vec2(0.f));
    mBgRect->setPosition(glm::vec2(mRadius, 0.f));
    mBgCircleRight->setPosition(glm::vec2(mRadius * 2.f + mLength, 0.f));
    
    mBgCircleRight->setFillColor(mButtonColor);
    mBgRect->setFillColor(mButtonColor);
    mBgCircleLeft->setFillColor(mButtonColor);
    
    addChild(mBgCircleLeft);
    addChild(mBgRect);
    addChild(mBgCircleRight);
}

void button::addText(std::string buttonText)
{
    ci::TextBox tempText = ci::TextBox();
    tempText.text(buttonText);
    tempText.size(ci::vec2(mRadius * 2.f + mLength, mRadius * 2.f));
    tempText.color(mTextColor);
    tempText.font(ci::Font("Arial", mTextSize));
    tempText.setAlignment(ci::TextBox::Alignment::CENTER);
    
    mButtonText = po::scene::TextBox::create(tempText);
    mButtonText->setAlignment(po::scene::Alignment::CENTER_CENTER);
    mButtonText->setPosition(ci::vec2(mLength, mRadius*1.5));
    
    addChild(mButtonText);
    
}

void button::setButtonActive()
{
    ci::app::timeline().apply(&mBgCircleLeft->getFillColorAnim(),mButtonActivateColor,0.5f, ci::EaseInAtan());
    ci::app::timeline().apply(&mBgCircleRight->getFillColorAnim(),mButtonActivateColor,0.5f, ci::EaseInAtan());
    ci::app::timeline().apply(&mBgRect->getFillColorAnim(),mButtonActivateColor,0.5f, ci::EaseInAtan());
}

void button::setButtonNormal()
{
    ci::app::timeline().apply(&mBgCircleLeft->getFillColorAnim(),mButtonColor,0.f);
    ci::app::timeline().apply(&mBgCircleRight->getFillColorAnim(),mButtonColor,0.f);
    ci::app::timeline().apply(&mBgRect->getFillColorAnim(),mButtonColor,0.f);
}


void button::onMouseEvent(po::scene::MouseEvent &event)
{
    switch (event.getType()) {
        case po::scene::MouseEvent::DOWN_INSIDE :
            mIsActivate = !mIsActivate;
            if (mIsActivate) {
                setButtonActive();
                mTextColor = mTextActivateColor;
                removeChild(mButtonText);
                addText("FOLLOWED");
                mButtonClickedSignal.emit(true);
                
            }
            else{
                setButtonNormal();
                removeChild(mButtonText);
                mTextColor = ci::Color::hex(0xc35c93);
                addText("FOLLOW");
                
                
                
                mButtonClickedSignal.emit(false);
            }
            
            break;
            
        default:
            break;
    }
}




