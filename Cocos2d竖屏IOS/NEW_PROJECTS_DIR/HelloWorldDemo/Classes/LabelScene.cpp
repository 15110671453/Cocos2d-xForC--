//
//  LabelScene.cpp
//  HelloWorldDemo
//
//  Created by admindyn on 2017/8/31.
//
//

#include "LabelScene.hpp"


USING_NS_CC;

Scene* LabelScene::createScene(){
    return LabelScene::create();
}

static void problemLoading(const char* filename){

    printf("Error while loading:%s\n",filename);
    printf("Depending on how you compiled you might have to addd 'Resources/' in front of filenames in LabelScene.cpp\n");
}

bool LabelScene::init()
{

    if (!Scene::init()) {
        return false;
    }
    
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    log("可视化尺寸w:%f h:%f",visibleSize.width,visibleSize.height);
    /*定义视图的可视化原点*/
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    log("可视化原点x:%f y:%f",origin.x,origin.y);
    log("OpenGL坐标系 原点 在左下角;IOS 坐标系 在 左上角");
    
    /*
     #define CC_CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
     
     上面 定义宏 CC_CALLBACK_0(__selector__,__target__, ...)
     
     将按照以下展开
     std::bind(&__selector__,__target__, ##__VA_ARGS__)
     展开中使用了std::bind 函数 函数传递参数 为 函数指针引用 函数调用对象 也就是作用域对象 
     然后是参数列表
     
     
     */
    auto bg =LayerColor::create(Color4B(255,255,255,255));
    this->addChild(bg,0);
    
    double offsetNav=40;
    double navH=80;
    auto navBg=LayerColor::create(Color4B(10,90,20,255));
    navBg->setContentSize(Size(Vec2(visibleSize.width,navH)));
    navBg->setPosition(0, visibleSize.height-navH-offsetNav);
    navBg->setAnchorPoint(Vec2(0,0));
    this->addChild(navBg,0);
    
    double offsetStart = 20;
    auto backItem = MenuItemImage::create("back1.png","back2.png",CC_CALLBACK_1(LabelScene::delegateClickCallBack, this));
    
    if (backItem == nullptr|| backItem->getContentSize().width<=0||backItem->getContentSize().height<=0) {
        problemLoading("'back1.png' and 'back2.png'");

    }else
    {
        float x = origin.x+offsetStart+backItem->getContentSize().width/2;
        float y = origin.y+visibleSize.height-offsetNav-backItem->getContentSize().height/2;
        
          backItem->setPosition(Vec2(x,y));
    }
    
    auto menu = Menu::create(backItem,NULL);
    
    menu->setPosition(Vec2::ZERO);
    
    this->addChild(menu,1);
    
    /*标签*/
    
    auto label1 = Label::createWithSystemFont("系统字体", "Arial", 36);
    label1->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height-offsetNav-navH/2));
    
    this->addChild(label1,1);
    
    //创建系统字体标签
    
    auto label2 = Label::createWithTTF("TTF字体文本", "fonts/Marker Felt.ttf", 36);
    label2->setColor(Color3B::BLUE);
    label2->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height-offsetNav-navH-label2->getContentSize().height/2));
    
    this->addChild(label2,1);
    
    //创建位图字体标签
    double spaceLabel=60;
//    auto label3 = Label::createWithBMFont("fonts/BMFont.fnt", "Hello World");
//    label3->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height-offsetNav-navH-label2->getContentSize().height-spaceLabel-label3->getContentSize().height/2));
//    this->addChild(label3);
    
    TTFConfig ttfConfig("fonts/Marker Felt.ttf",36,GlyphCollection::DYNAMIC);
    
    auto label4 = Label::createWithTTF(ttfConfig, "HelloWorld Cocos2d-x");
    label4->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height-offsetNav-navH-label2->getContentSize().height-spaceLabel-label4->getContentSize().height/2));
    label4->setColor(Color3B::MAGENTA);
    this->addChild(label4,1);
    
    ttfConfig.outlineSize =
    4;
    auto label5 = Label::createWithTTF(ttfConfig, "HelloWorld shadow Cocos2d-x");
    label5->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height-offsetNav-navH-label2->getContentSize().height-spaceLabel*2-label4->getContentSize().height-label5->getContentSize().height/2));
    label5->enableShadow(Color4B(255,255,255,128),Size(4,-4));
    label5->setColor(Color3B::MAGENTA);
    this->addChild(label5,1);
    
     /*文本菜单*/
    
    MenuItemFont::setFontName("Times New Roman");
   
    MenuItemFont::setFontSize(86);
    
    //设置第一个菜单项
    
    MenuItemFont* item1 = MenuItemFont::create("Start",CC_CALLBACK_1(LabelScene::delegateClickTextMenuBack, this));
    item1->setColor(Color3B::RED);
  
    
    Menu* mn = Menu::create(item1,NULL);
    
    mn->alignItemsVertically();
    
    this->addChild(mn);
    
    
    
    
    
    
    return true;
}

void LabelScene::delegateClickCallBack(cocos2d::Ref *pSender){
    Director::getInstance()->popScene();
}

void LabelScene::delegateClickTextMenuBack(cocos2d::Ref *pSender){
    Director::getInstance()->popScene();
}



