//
//  Test1Scene.hpp
//  HelloWorldDemo
//
//  Created by admindyn on 2017/8/11.
//
//

#ifndef Test1Scene_hpp
#define Test1Scene_hpp

#include <cocos2d.h>
#include <stdio.h>
/*c++ 与运算符 双冒号 cocos2d:: Scene */
class Test1Scene:public cocos2d:: Scene {
    
    
public:
    /* 声明创建当前场景的静态函数*/
    /*cocos2d 封装的场景 层 精灵 菜单 文本 地图 粒子系统等 都是以NODE 为基类*/
    static cocos2d::Scene* createScene();
    /*虚函数 会在原先类的成员函数表基础上 为类增加虚函数表 多了一个指向虚函数表的指针 多耗费一个指针的内存空间*/
    virtual bool init();
    
    /*这里传的指针类型是Ref 型 引用类型 好像cocosd 封装的 列表 数组 字典 ref都是他们的基类
     对于这些类 都是模仿Object基类 因为cocos2d-x源于iphone的cocos2d 我们 由于cocos2d-x集合了OC和C++的特点 所以cocos2d 需要xcode支持引用计数（但不能是自动引用计数 因为工程中要用到retain） 另外工程将会更强大 因为工程中的数据结构将支持两套
     第一套 源于OC的 线性列表结构 __Array；__Dictionary 需要我们遵循苹果的内存管理机制管理
     第二套 源于C++的 线性列表结构 模版类 Vector(T) 容纳Ref及子类所创建的对象指针；Map<K,V> 不需要retain等 内存管理由编译器自动处理 Map的V 必须是Ref类型 或者子类指针
     还有一个家族ValueVector与ValueMap 只能容纳C++标准数据结构类型
     */
    /*而cocos2d 封装的场景 层 精灵 菜单 文本 地图 粒子系统等 都是以NODE 为基类*/
    void delegateMessageCall(cocos2d::Ref* pSender);
    void delegateMessageCallToBack(cocos2d::Ref* pSender);
    void delegateMessageCallMore(cocos2d::Ref* pSender);
    cocos2d::__Array arrOC;
    cocos2d::ValueVector vector;
 
    CREATE_FUNC(Test1Scene);
    
};

#endif /* Test1Scene_hpp */
