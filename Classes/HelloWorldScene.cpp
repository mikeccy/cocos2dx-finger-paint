#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("YoYo Checkitout!", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    /////////////////////////////
    // finger paint implementation
    
    // enable touch events
    setTouchEnabled( true );
    
    // create a canvas to draw on
    canvas = CCRenderTexture::create(size.width, size.height,
                                     kCCTexture2DPixelFormat_RGBA8888);
    
    // position on the center of the screen
    canvas->setPosition(ccp(size.width / 2, size.height / 2));
    
    // used later do not release
    canvas->retain();
    
    // set target as child and z order to 1
    this->addChild(canvas, 1);

    // init the brush tip
    brush = CCSprite::create("brush.png");
    
    // used later do not release
    brush->retain();

    return true;
}

void HelloWorld::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    CCTouch* touch = (CCTouch*)touches->anyObject();
    
    // get start & end location
    CCPoint start = touch->getLocationInView();
    CCPoint end = touch->getPreviousLocationInView();
    
    // get corrected location
    start = CCDirector::sharedDirector()->convertToGL(start);
    end = CCDirector::sharedDirector()->convertToGL(end);

    // draw line on the canvas
    canvas->begin();

    float distance = ccpDistance(start, end);

    for (int i = 0; i < distance; i++)
    {
        float diffX = end.x - start.x;
        float diffY = end.y - start.y;
        float delta = (float)i / distance;
        brush->setPosition(ccp(start.x + (diffX * delta), start.y + (diffY * delta)));
        brush->visit();
    }

    canvas->end();
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
