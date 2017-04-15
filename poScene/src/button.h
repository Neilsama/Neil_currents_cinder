//
//  button.hpp
//  poScene
//
//  Created by Neil on 4/4/17.
//
//

#ifndef button_hpp
#define button_hpp

#include <stdio.h>
#include "poNodeContainer.h"
#include "poShape.h"
#include "poTextBox.h"

class button;
typedef std::shared_ptr<button> buttonRef;
typedef ci::signals::Signal<void(bool state)> ButtonClickedSignal;

class button
:public po::scene::NodeContainer
{
public:
    static buttonRef create(float length, float radius, ci::Color buttonColor, ci::Color buttonActiveColor, std::string buttonText, ci::Color textColor, ci::Color textActiveColor, float textSize, bool clickable);
    
    void setButtonActive();
    void setButtonNormal();
    
    ButtonClickedSignal& getButtonClickedSignal(){return mButtonClickedSignal;}
    
    
private:
    button();
    
    void onMouseEvent(po::scene::MouseEvent &event);
    
    
    void setup(float length, float radius, ci::Color buttonColor, ci::Color buttonActiveColor, std::string buttonText, ci::Color textColor, ci::Color textActiveColor, float textSize, bool clickable);
    void addShape();
    void addText(std::string buttonText);
    
    po::scene::ShapeRef mBgCircleLeft;
    po::scene::ShapeRef mBgCircleRight;
    po::scene::ShapeRef mBgRect;
    
    po::scene::TextBoxRef  mButtonText;
    
    
    float       mRadius;
    float       mLength;
    ci::Color   mButtonColor;
    ci::Color   mTextColor;
    float       mTextSize;
    
    ci::Color   mButtonActivateColor;
    ci::Color   mTextActivateColor;
    
    //  Signal
    ButtonClickedSignal     mButtonClickedSignal;
    bool        mIsActivate;
    bool        mClickable;

};

#endif /* button_hpp */
