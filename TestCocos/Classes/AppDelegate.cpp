#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("Pianot", Rect(0, 0, 960, 640));
        director->setOpenGLView(glview);
    }

     //-----start适配-----------------------------------

	Size frame_size = glview->getFrameSize();

	//以最大的那张图片为参照
	Size win_size = Size(1280, 800);
	float widt_rete = frame_size.width / win_size.width;
	float height_rete = frame_size.height / win_size.height;

	if (widt_rete > height_rete)
	{
		glview->setDesignResolutionSize(win_size.width,
			win_size.height * height_rete / widt_rete, ResolutionPolicy::NO_BORDER);
	}
	else
	{
		glview->setDesignResolutionSize(win_size.width * widt_rete / height_rete,
			win_size.height, ResolutionPolicy::NO_BORDER);
	}

	//---------------------end----------------------

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
 //   Director::getInstance()->stopAnimation();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	//auto director = Director::getInstance();
	//auto scene = HelloWorld::createScene();
	//director->runWithScene(scene);
//	Director::getInstance()->end();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
 //   Director::getInstance()->startAnimation();
//	AppDelegate::applicationDidFinishLaunching();
	auto director = Director::getInstance();
	auto scene = HelloWorld::createScene();
	director->runWithScene(scene);

    // run
 //   Director::pushScene(scene);
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
