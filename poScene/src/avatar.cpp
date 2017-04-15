//
//  Avatar.cpp
//  poScene
//
//  Created by Neil on 4/4/17.
//
//

#include "avatar.h"
using namespace ci;
using namespace ci::app;
using namespace std;

avatarRef avatar::create(ci::gl::TextureRef texture)
{
    avatarRef ref = std::shared_ptr<avatar>(new avatar);
    ref->setup(texture);
    return ref;
}

avatar::avatar()
{
}

void avatar::setup(ci::gl::TextureRef texture)
{
    mImage = po::scene::Image::create(texture);
    mImage->setScale(0.5);
    mImage->setAlignment(po::scene::Alignment::CENTER_CENTER);
    
    
    addChild(mImage);
}
