//
//  LabelScene.hpp
//  HelloWorldDemo
//
//  Created by admindyn on 2017/8/31.
//
//

#ifndef LabelScene_hpp
#define LabelScene_hpp

#include <cocos2d.h>
#include <stdio.h>

class LabelScene : public cocos2d::Scene
{
public:
    /*声明创建当前场景的静态函数*/
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void delegateClickCallBack(cocos2d::Ref* pSender);
    void delegateClickTextMenuBack(cocos2d::Ref* pSender);
    
    CREATE_FUNC(LabelScene);

};


#endif /* LabelScene_hpp */
