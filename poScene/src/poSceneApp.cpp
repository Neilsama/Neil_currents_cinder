#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "poScene.h"
#include "poScene.h"
#include "poImage.h"

#include "bgBubbles.h"
#include "avatar.h"
#include "button.h"
#include "text.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class poSceneApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    void onActived(bool state);
    
    po::scene::SceneRef     mScene;
    po::scene::NodeContainerRef     mNodeContainer;
    po::scene::ShapeRef     mBgShape;
    
    //  background and bubbles
    bgBubblesRef    mBgBubbles;
    ci::Color mBgColor = ci::Color::hex(0xc9669b);
    ci::Color mBgActivateColor = ci::Color::hex(0x49cab3);
    
    //  avatar
    avatarRef      mAvatar;
    ci::gl::TextureRef      mAvatarTexture;
    
    // button
    buttonRef          mButton;
    
    buttonRef       mName;
    
    //  text
    textRef     mIntroduction;
};

void poSceneApp::setup()
{
    setWindowSize(750/2, 1334/2);
    
    //  create boss container
    mNodeContainer = po::scene::NodeContainer::create();
    mScene = po::scene::Scene::create(mNodeContainer);
    
    //  background shape
    glm::vec2 backgroundSize = ci::app::getWindowSize();
    mBgShape = po::scene::Shape::createRect(backgroundSize.x, backgroundSize.y);
    mBgShape->setFillColor(mBgColor);
    mNodeContainer->addChild(mBgShape);
    
    //  background bubbles & bind with signals
    mBgBubbles = bgBubbles::create();
    mNodeContainer->addChild(mBgBubbles);
    
    //  avatar
    mAvatarTexture = ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset("avatar.png")));
    mAvatar = avatar::create(mAvatarTexture);
    mAvatar->setPosition(vec2(373/2.f, 252/2.f));
    mNodeContainer->addChild(mAvatar);
    
    //  button
    mButton = button::create(100, 24, ci::Color::hex(0xfdbd24), ci::Color::hex(0x629cd3), "FOLLOW", ci::Color::hex(0xad497e), ci::Color::hex(0xffe1f1), 17, true);
    mButton->setAlignment(po::scene::Alignment::CENTER_CENTER);
    mButton->setPosition(vec2(377/2.f, 1123/2.f));
    mNodeContainer->addChild(mButton);
    
    //  name
    mName = button::create(75, 35/2.f, ci::Color::hex(0xaf4f82), ci::Color::hex(0x30a792), "Neil", ci::Color::white(), ci::Color::white(), 20, false);
    mName->setAlignment(po::scene::Alignment::CENTER_CENTER);
    mName->setPosition(vec2(375/2.f, 480/2.f));
    mNodeContainer->addChild(mName);
    
    //  textBox
    string intro = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries.setting";
    
    mIntroduction = text::create(intro);
    mIntroduction->setPosition(vec2(190, 370));
    mIntroduction->setAlignment(po::scene::Alignment::CENTER_CENTER);

    mNodeContainer->addChild(mIntroduction);
    
    //  Signals
    mButton->getButtonClickedSignal().connect(std::bind(&poSceneApp::onActived, this, std::placeholders::_1));

    
}

void poSceneApp::mouseDown( MouseEvent event )
{
}

void poSceneApp::onActived(bool state)
{
    if (state) {
        cout<<"state is true"<<endl;
        ci::app::timeline().apply(&mBgShape->getFillColorAnim(),mBgActivateColor,0.5f, ci::EaseInAtan());
        ci::app::timeline().apply(&(mAvatar->getAvatarImageRef())->getRotationAnim(),0.0f, ci::toRadians(360.0f), 1.0f, ci::EaseOutQuad());
        mBgBubbles->setVisible(false);
        mBgBubbles->reset();
        mName->setButtonActive();
        
    }
    else{
        cout<<"state is false"<<endl;
        mName->setButtonNormal();
        ci::app::timeline().apply(&mBgShape->getFillColorAnim(),mBgColor,0.f);
        mBgBubbles->setVisible(true);
        
        
    }
}

void poSceneApp::update()
{
    mScene->update();
    
}

void poSceneApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    mScene->draw();
}

CINDER_APP( poSceneApp, RendererGl(RendererGl::Options().msaa( 8 ))  )
