//
//  text.hpp
//  poScene
//
//  Created by Neil on 4/4/17.
//
//

#ifndef text_hpp
#define text_hpp

#include <stdio.h>
#include "poNodeContainer.h"
#include "poTextBox.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class text;
typedef std::shared_ptr<text> textRef;

class text
:public po::scene::NodeContainer
{
public:
    static textRef create(string textContent);
    
private:
    text();
    void setup(string textContent);
    
    po::scene::TextBoxRef     mTextBox;
    
};

#endif /* text_hpp */
