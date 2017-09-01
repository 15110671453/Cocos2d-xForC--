//
//  Test1Scene.cpp
//  HelloWorldDemo
//
//  Created by admindyn on 2017/8/11.
//
//

#include "LabelScene.hpp"
#include "Test1Scene.hpp"

USING_NS_CC;

Scene* Test1Scene::createScene()
{
    return Test1Scene::create();

}

/*
 print useful error message instead
 
 of segfaulting when files are not there
 
 */


static void problemLoading(const char* filename)
{
    printf("Error while loading:%s\n",filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Test1Scene.cpp\n");
}
/*
 on "init" you need to initialize your instance
 */
bool Test1Scene::init()
{
    /*初始化父类 super init first*/
    
    if (!Scene::init()) {
        return false;
    }
    /*
     init  函数主要是初始化TestScene场景和层 层中包括里面的精灵 菜单 文字等内容
     */
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    log("可视化尺寸w:%f h:%f",visibleSize.width,visibleSize.height);
    
    /*
     定义试图的可视化原点
     */

    Vec2 origin= Director::getInstance()->getVisibleOrigin();
    
    log("可视化原点x:%f y:%f",origin.x,origin.y);
    log("OpenGL坐标系 原点 在左下角;IOS 坐标系 在 左上角");
   
    //创建 背景块
    
    auto bg =LayerColor::create(Color4B(255,255,255,255));
    this->addChild(bg,0);
    
    
    double offsetNav=40;
    double navH=80;
    auto navBg=LayerColor::create(Color4B(10,90,20,255));
    navBg->setContentSize(Size(Vec2(visibleSize.width,navH)));
    navBg->setPosition(0, visibleSize.height-navH-offsetNav);
    navBg->setAnchorPoint(Vec2(0,0));
    this->addChild(navBg,0);
    /*图片菜单*/
    double offsetStartBack = 20;
    auto backItem = MenuItemImage::create("back1.png","back2.png",CC_CALLBACK_1(Test1Scene::delegateMessageCallToBack, this));
    
    if (backItem == nullptr|| backItem->getContentSize().width<=0||backItem->getContentSize().height<=0) {
        problemLoading("'back1.png' and 'back2.png'");
        
    }else
    {
        float x = origin.x+offsetStartBack+backItem->getContentSize().width/2;
        float y = origin.y+visibleSize.height-offsetNav-backItem->getContentSize().height/2;
        
        backItem->setPosition(Vec2(x,y));
    }
    
    double offsetStartMore = 20;
    auto moreItem = MenuItemImage::create("more1.png","more2.png",CC_CALLBACK_1(Test1Scene::delegateMessageCallMore, this));
    
    if (moreItem == nullptr|| moreItem->getContentSize().width<=0||moreItem->getContentSize().height<=0) {
        problemLoading("'more1.png' and 'more2.png'");
        
    }else
    {
        float x = origin.x+visibleSize.width-offsetStartMore-moreItem->getContentSize().width/2;
        float y = origin.y+visibleSize.height-offsetNav-moreItem->getContentSize().height/2;
        
        moreItem->setPosition(Vec2(x,y));
    }

    auto menu2 = Menu::create(backItem,moreItem,NULL);
    
    menu2->setPosition(Vec2::ZERO);
    
    this->addChild(menu2,1);
    
    auto contentBg =LayerColor::create(Color4B(100,0,20,255));
    contentBg->setContentSize(Size(Vec2(320,310)));
    contentBg->setPosition(160, 200);
    //    tabBg->setAnchorPoint(Vec2(,1.0));
    this->addChild(contentBg,1);
    
    
    /*Item传递 四个参数 前两个参数 为状态图片 未点击 点击 失效 ；最后一个为点击响应函数*/
    double space = (visibleSize.width-46*4-46*2)/3;
    double offsetTabStart=46;
    double offsetTabH=20;
    auto listItem1 = MenuItemImage::create("node1.png","node11.png",CC_CALLBACK_1(Test1Scene::delegateMessageCall, this));
    if (listItem1==nullptr|| listItem1->getContentSize().width<=0||listItem1->getContentSize().height<=0) {
        problemLoading("node1.png and node11.png");
    }else
    {
        float x = origin.x+offsetTabStart+listItem1->getContentSize().width/2;
        
        float y = origin.y +listItem1->getContentSize().height/2+offsetTabH;
        
        listItem1->setPosition(Vec2(x,y));
        
    }
    auto listItem2 = MenuItemImage::create("node2.png","node22.png",CC_CALLBACK_1(Test1Scene::delegateMessageCall, this));
    if (listItem2==nullptr|| listItem2->getContentSize().width<=0||listItem2->getContentSize().height<=0) {
        problemLoading("node2.png and node22.png");
    }else
    {
        float x = origin.x+offsetTabStart+listItem1->getContentSize().width+space+listItem2->getContentSize().width/2;
        
        float y = origin.y +listItem2->getContentSize().height/2+offsetTabH;
        
        listItem2->setPosition(Vec2(x,y));
        
    }
    
    auto listItem3 = MenuItemImage::create("node3.png","node33.png",CC_CALLBACK_1(Test1Scene::delegateMessageCall, this));
    if (listItem3==nullptr|| listItem3->getContentSize().width<=0||listItem3->getContentSize().height<=0) {
        problemLoading("node3.png and node33.png");
    }else
    {
        float x = origin.x+offsetTabStart+listItem1->getContentSize().width+space+listItem2->getContentSize().width+space+listItem3->getContentSize().width/2;
        
        float y = origin.y +listItem3->getContentSize().height/2+offsetTabH;
        
        listItem3->setPosition(Vec2(x,y));
        
    }
    
    auto listItem4 = MenuItemImage::create("node4.png","node44.png",CC_CALLBACK_1(Test1Scene::delegateMessageCall, this));
    if (listItem4==nullptr|| listItem4->getContentSize().width<=0||listItem4->getContentSize().height<=0) {
        problemLoading("node4.png and node44.png");
    }else
    {
        float x = origin.x+visibleSize.width-listItem4->getContentSize().width/2-offsetTabStart;
        
        float y = origin.y +listItem4->getContentSize().height/2+offsetTabH;
        
        listItem4->setPosition(Vec2(x,y));
        
    }
    

    auto tabBg =LayerColor::create(Color4B(0,100,20,255));
    tabBg->setContentSize(Size(Vec2(visibleSize.width,(2*offsetTabH+listItem4->getContentSize().height))));
//    tabBg->setAnchorPoint(Vec2(,1.0));
    this->addChild(tabBg,1);
    
    auto menu = Menu::create(listItem1,listItem2,listItem3,listItem4,NULL);
    menu->setColor(Color3B(100,0,20));
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    
     return true;
}

void Test1Scene::delegateMessageCall(cocos2d::Ref *pSender)
{
    
    log("TestScene点击事件");
}
void Test1Scene::delegateMessageCallToBack(cocos2d::Ref *pSender)
{
    /*退出当前场景 返回上一个场景*/
    Director::getInstance()->popScene();
    
    log("TestScene点击事件");
}

void Test1Scene::delegateMessageCallMore(cocos2d::Ref *pSender)
{
    /*切换到下一个场景 当前场景挂起 压入下一个场景*/
    
    auto sc = LabelScene::create();
    
    Director::getInstance()->pushScene(sc);
    

    log("TestScene点击事件");
}


