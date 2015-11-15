#include "AppDelegate.h"
#include "Level0.h"

USING_NS_CC;

typedef struct tagResource
{
	cocos2d::CCSize size;
	char directory[100];
}Resource;

static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(1920, 1080);
static Resource smallResolutionSize = { cocos2d::CCSizeMake(1280, 720), "Resolutions/HD/" };
static Resource mediumResolutionSize = { cocos2d::CCSizeMake(1366, 768), "Resolutions/MedHD/" };
static Resource largeResolutionSize = { cocos2d::CCSizeMake(1920, 1080), "Resolutions/FullHD/" };

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

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        //glview = GLViewImpl::createWithRect("AnotherFate", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
		//glview = cocos2d::GLViewImpl::create("AnotherFate");
		glview = cocos2d::GLViewImpl::createWithFullScreen("AnotherFate");
#else
        glview = cocos2d::GLViewImpl::create("AnotherFate");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(0.01/30);

    // Set the design resolution
	Size frameSize = glview->getFrameSize();
	glview->setFrameSize(designResolutionSize.width, designResolutionSize.height);
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::EXACT_FIT);

	std::vector<std::string> resDirectory;

    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.size.height)
    {        
		std::string str(largeResolutionSize.directory);
		resDirectory.push_back(str);
		cocos2d::FileUtils::getInstance()->setSearchPaths(resDirectory);
        director->setContentScaleFactor(MIN(largeResolutionSize.size.height/designResolutionSize.height, largeResolutionSize.size.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.size.height)
    {       
		std::string str(mediumResolutionSize.directory);
		resDirectory.push_back(str);
		cocos2d::FileUtils::getInstance()->setSearchPaths(resDirectory);
        director->setContentScaleFactor(MIN(mediumResolutionSize.size.height/designResolutionSize.height, mediumResolutionSize.size.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
		std::string str(smallResolutionSize.directory);
		resDirectory.push_back(str);
		cocos2d::FileUtils::getInstance()->setSearchPaths(resDirectory);
        director->setContentScaleFactor(MIN(smallResolutionSize.size.height/designResolutionSize.height, smallResolutionSize.size.width/designResolutionSize.width));
    }

    register_all_packages();

    // create a scene. it's an autorelease object
	auto scene = Level0::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
