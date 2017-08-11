/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2017 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "RootViewController.h"
#import "cocos2d.h"
#import "platform/ios/CCEAGLView-ios.h"


@implementation RootViewController

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
    // Initialize the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [UIScreen mainScreen].bounds
                                         pixelFormat: (__bridge NSString *)cocos2d::GLViewImpl::_pixelFormat
                                         depthFormat: cocos2d::GLViewImpl::_depthFormat
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: NO
                                     numberOfSamples: 0 ];
    
    // Enable or disable multiple touches
    [eaglView setMultipleTouchEnabled:NO];
    
    // Set EAGLView as view of RootViewController
    self.view = eaglView;
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Do any additional setup after loading the view.
    NSString *str = @"viewDidLoad";
    NSLog(@"viewDidLoad 改变前:%@",str);
    [self changNSString:str];
    NSLog(@"viewDidLoad 改变后:%@",str);
    NSLog(@"NSMutableString---");
    NSMutableString *mStr = [NSMutableString stringWithString:@"viewDidLoadMSTR"];
    NSLog(@"viewDidLoad 改变前:%@",mStr);
    [self changeMutableString:&mStr];
    NSLog(@"viewDidLoad 改变后:%@",mStr);
    
    NSMutableArray *mArray = [NSMutableArray arrayWithObjects:@"1",@"2", nil];
    NSLog(@"ARRAY---");
    for (NSString *str in mArray) {
        NSLog(@"viewDidLoad 改变前 %@",str);
    }
    [self changeMutableArray:mArray];
    for (NSString *str in mArray) {
        NSLog(@"viewDidLoad 改变后 %@",str);
    }
    
}
- (void)changNSString:(NSString *)str {
    NSLog(@"changNSString 改变前:%@",str);
    str = @"changNSString";
    NSLog(@"changNSString 改变后:%@",str);
}
- (void)changeMutableString:(NSMutableString **)mStr {
    NSLog(@"changNSMutableString 改变前:%@",*mStr);
//    mStr = [NSMutableString stringWithString:@"changeMutableString"];
    *mStr=[NSMutableString stringWithString:@"changeMutableString&&&&&"] ;
    NSLog(@"changNSMutableString 改变后:%@",*mStr);
}
- (void)changeMutableArray:(NSMutableArray *)array {
    [array addObject:@"3"];
    for (NSString *str in array) {
        NSLog(@"changeMutableArrayING-- %@",str);
    }
}

- (void)createCat {
//    Cat *cat = [Cat new];
//    cat.name = @"xiaomao";
//    cat.age = @"17";
//    NSLog(@"%@",cat);
//    [self catObjectTest:cat];
//    NSLog(@"%@",cat);
}
//- (void)catObjectTest:(Cat *)cat {
////    cat.name = @"newxiaomao";
////    cat.age = @"89";
////    NSLog(@"%@",cat);
//}


- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
}


// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
#ifdef __IPHONE_6_0
- (NSUInteger) supportedInterfaceOrientations{
    return UIInterfaceOrientationMaskPortrait;
}
#endif

- (BOOL) shouldAutorotate {
#pragma mark-竖屏NO还是横屏YES
    return NO;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();

    if (glview)
    {
        CCEAGLView *eaglview = (__bridge CCEAGLView *)glview->getEAGLView();

        if (eaglview)
        {
            CGSize s = CGSizeMake([eaglview getWidth], [eaglview getHeight]);
            cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
        }
    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];

    // Release any cached data, images, etc that aren't in use.
}


@end
