//
//  Avatar.hpp
//  poScene
//
//  Created by Neil on 4/4/17.
//
//

#ifndef avatar_h
#define avatar_h

#include <stdio.h>
#include "poNodeContainer.h"
#include "poImage.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class avatar;
typedef std::shared_ptr<avatar> avatarRef;

class avatar
:public po::scene::NodeContainer
{
public:
    static avatarRef create(ci::gl::TextureRef texture);
    void setup(ci::gl::TextureRef texture);
    po::scene::ImageRef getAvatarImageRef(){return mImage;}
    
private:
    avatar();
    po::scene::ImageRef mImage;
    
};

#endif /* Avatar_hpp */
