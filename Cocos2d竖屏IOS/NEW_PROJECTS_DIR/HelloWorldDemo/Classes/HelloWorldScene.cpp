
#include "Test1Scene.hpp"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    /*初始化父类*/
    if ( !Scene::init() )
    {
        return false;
    }
    /*init 函数主要是初始化HelloWorld场景 和 层 层中 包括里面的精灵 菜单 文字等内容*/
    /*Director是整个cocos2dx引擎的核心，是整个游戏的导航仪，游戏中的一些常用操作就是由Director来控制的，比如OpenGL ES的初始化，场景的转换，游戏暂停继续的控制，世界坐标和GL坐标之间的切换，对节点（游戏元素）的控制等，还有一些游戏数据的保存调用，屏幕尺寸的获取等都要由Director类来管理控制的。
     
     因为Director是游戏项目的总导演，会经常调用进行一些控制，所以该Director利用了单件设计模式，也就是项目里取到的director都是同一个。用getInstance() 方法取得Director的实例，*/
    /*定义视图的可视化尺寸*/
    auto visibleSize = Director::getInstance()->getVisibleSize();
    log("可视化尺寸w:%f h:%f",visibleSize.width,visibleSize.height);
    /*定义视图的可视化原点*/
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    log("可视化原点x:%f y:%f",origin.x,origin.y);
    log("OpenGL坐标系 原点 在左下角;IOS 坐标系 在 左上角");

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    /*创建图片菜单项对象*/
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }
/*创建Menu菜单对象 是菜单项的管理对象吗 ?*/
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //创建 背景块
    
    auto bg =LayerColor::create(Color4B(255,255,255,255));
    this->addChild(bg,0);
    /*经过AppDelegate中
     setContentScaleFactor()决定了图片显示到屏幕的缩放因子，但是这个接口的参数不是通过资源图片的宽、高比屏幕宽、高得来。Cocos2d-x引擎设计试图屏蔽游戏开发者直接去关注屏幕，所以这个因子是资源宽、高比设计分辨率宽、高。
     setContentScaleFactor()通常有两个方式来设置参数。
     RH/DH或RW/DW
     
     我们以后调试的屏幕的点变为 640点宽 1136点高来设置
     
     cocos2d分辨率适配 让开发者忽略原有设备的屏幕分辨率
     
     我们自己定义设计分辨率
     
     和确定资源分辨率 通过换算来适配屏幕
     */

    //创建 node1
    
    auto node1= Sprite::create("node4.png");
    node1->setPosition(Vec2(46,46));
    node1->setAnchorPoint(Vec2(1.0,1.0));
    this->addChild(node1,0);
    
    
    auto node2= Sprite::create("node3.png");
    node2->setPosition(Vec2(102,46));
    node2->setAnchorPoint(Vec2(1.0,1.0));
    this->addChild(node2,0);
    
    Vec2 point1 = node1->convertToNodeSpace(node2->getPosition());
    Vec2 point2 = node1->convertToNodeSpaceAR(node2->getPosition());
    
    log("Node2 NodeSpace=(%f,%f)",point1.x,point1.y);
    log("Node2 NodeSpaceAR=(%f,%f)",point2.x,point2.y);
    
    Vec2 point3 = node1->convertToWorldSpace(node2->getPosition());
    Vec2 point4 = node1->convertToWorldSpaceAR(node2->getPosition());
    
    log("Node2 WorldSpace=(%f,%f)",point3.x,point3.y);
    log("Node2 WorldSpaceAR=(%f,%f)",point4.x,point4.y);
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
/*展示一个HelloWorld文本标签对象*/
    /*这里创建一个LabelTTF标签对象*/
    auto label = Label::createWithTTF("YNGame", "fonts/arial.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height-20));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    /*Cocos2d中的精灵和其他游戏引擎中的精灵相似，它可以移动，旋转，缩放，执行动画，并接受其他转换。Cocos2dx的Sprite由Texure，frame和animation组成，由openes负责渲染。
     使用Texture2D加载图片，可以用Texture2D生成对应的SpriteFrame（精灵帧），将SpriteFrame添加到Animation生成动画数据，用Animation生成Animate（就是最终的动画动作），最后用Sprite执行这个动作*/
    /*
     创建精灵的几种方式：
     直接创建:
     使用纹理来创建精灵
     使用精灵帧来创建精灵
     */
    /*
     在Cocos2dx中实现精灵显示的基本过程如下：
     //创建Scene
     //创建层
     //把层加入场景中
     //创建一个精灵
     //把精灵加到层里
     */
    /*创建精灵对象*/
    auto sprite = Sprite::create("man.jpg");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    /*终止程序运行并退出应用程序 */
//    Director::getInstance()->end();
//
//    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
    /*切换到下一个场景 当前场景挂起 压入下一个场景*/
    
    auto sc = Test1Scene::create();
    
    Director::getInstance()->pushScene(sc);
    

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
