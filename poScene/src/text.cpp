//
//  text.cpp
//  poScene
//
//  Created by Neil on 4/4/17.
//
//

#include "text.h"
using namespace ci;
using namespace ci::app;
using namespace std;

textRef text::create(string textContent)
{
    textRef ref = std::shared_ptr<text>(new text);
    ref->setup(textContent);
    return ref;
    
}

text::text(){}

void text::setup(string textContent)
{
    ci::TextBox ciTextBox = ci::TextBox();
    ciTextBox.text(textContent);
    ciTextBox.size(324, 138);
    ciTextBox.alignment(ci::TextBox::Alignment::CENTER);
    ciTextBox.font(ci::Font("Arial", 14));
    ciTextBox.setColor(ci::Color::hex(0xffebf6));
    
    mTextBox = po::scene::TextBox::create(ciTextBox);
    
    addChild(mTextBox);
    
}
