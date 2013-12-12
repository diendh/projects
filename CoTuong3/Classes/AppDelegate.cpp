#include "AppDelegate.h"
#include "MenuGame.h"
#include "ChoiDon.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    pDirector->getOpenGLView()->setDesignResolutionSize(480, 800, kResolutionShowAll);
#else
    pDirector->getOpenGLView()->setDesignResolutionSize(480, 800, kResolutionShowAll);
#endif

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = ChoiDon::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
     SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    if(DataEncrypt::share()->getBoolForKey("music", true))
     SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::musicButton(){
    if (DataEncrypt::share()->getBoolForKey("music", true))
        SimpleAudioEngine::sharedEngine()->playEffect("Sound/4/S_Button.mp3", false);
}
