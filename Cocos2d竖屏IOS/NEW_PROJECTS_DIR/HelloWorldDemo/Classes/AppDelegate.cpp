#include "AppDelegate.h"
#include "HelloWorldScene.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif
/*USING_NS_CC 等同于 using namespace cocos2d 是Cocos2d-x提供的一个宏*/
USING_NS_CC;

/*
 这里定义了几种屏幕的分辨率尺寸
 */
static cocos2d::Size designResolutionSize = cocos2d::Size(640, 1136);
static cocos2d::Size smallResolutionSize = cocos2d::Size(640, 960);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(640, 1136);
static cocos2d::Size medium2ResolutionSize = cocos2d::Size(768, 1024);
static cocos2d::Size largeResolutionSize = cocos2d::Size(1536, 2048);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
/*
 设置opengl上下文属性
 */
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    
    /*
     设置opengl上下文属性 现在可以设置6个属性
     set OpenGL context attributes: red,green,blue,alpha,depth 深度缓存,stencil 模板缓存
     */
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    /*
     如果使用包管理器安装更多的包 不要修改删除该函数
     */
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    /*初始化导演对象*/
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        /*这里的if 语句来判断当前运行的平台*/
        glview = GLViewImpl::createWithRect("HelloWorldDemo", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("HelloWorldDemo");
#endif
        director->setOpenGLView(glview);
    }
/*设置屏幕是否显示帧率信息*/
    // turn on display FPS
    director->setDisplayStats(true);
/*这里就是我们要显示的帧率值 */
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);
    /*设置设计分辨率*/
    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
        log("屏幕宽高:%f h:%f",frameSize.width,frameSize.height);
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {
        /*
         setContentScaleFactor()决定了图片显示到屏幕的缩放因子，但是这个接口的参数不是通过资源图片的宽、高比屏幕宽、高得来。Cocos2d-x引擎设计试图屏蔽游戏开发者直接去关注屏幕，所以这个因子是资源宽、高比设计分辨率宽、高。
         setContentScaleFactor()通常有两个方式来设置参数。
         RH/DH或RW/DW
         */
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();
    /*真正IOS 入口在 ./ios/AppDelegate.mm*/
/*程序 C++入口
 
 下面是Director控制场景的常用方法：
 
 runWithScene( Scene *scene ) 启动游戏，并运行scene场景。本方法在主程序第一次启动主场景的时候调用。如果已有正在运行的场景则不能调用该方法；会调用pushScene-->startAnimation。
 pushScene( Scene *scene ) 将当前运行中的场景暂停并压入到代码执行场景栈中，再将传入的scene设置为当前运行场景，只有存在正在运行的场景时才调用该方法；
 replaceScene( Scene *scene ) 直接使用传入的scene替换当前场景来切换画面，当前场景被释放。这是切换场景时最常用的方法。
 popScene() 释放当前场景，再从代码执行场景中弹出栈顶的场景，并将其设置为当前运行场景。如果栈为空，直接结束应用。和PushScene结对使用
 end() 释放和终止执行场景，同时退出应用
 pause() 暂停当前运行场景中的所有计时器和动作，场景仍然会显示在屏幕上
 resume () 恢复当前运行场景的所有计时器和动作，场景仍然会显示在屏幕上
 同时场景是层的容器，包含了所有需要显示的游戏元素。通常，当我们需要完成一个场景时候，会创建一个Scene的子类，并在子类中实现我们需要的功能。比如，我们可以在子类的初始化中载入游戏资源，为场景添加层，启动音乐播放等等。
 */
    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    /*运行*/
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
/*如果使用simpleaudioengine播放音乐 则在该方法中暂停*/
#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
/*如果使用simpleaudioengine播放音乐 则在该方法中继续*/
#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
