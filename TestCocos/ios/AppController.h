#import <UIKit/UIKit.h>
#import "MyViewController.h"

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate>

@property (nonatomic, retain) UIWindow *window;

@property (nonatomic, retain) UINavigationController* navController;

@property (nonatomic, retain)MyViewController* myController;

@end

