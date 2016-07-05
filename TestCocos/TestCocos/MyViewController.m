//
//  MyViewController.m
//  NewGame
//
//  Created by fuze on 16/7/4.
//
//

#import "MyViewController.h"
#import "RootViewController.h"

@interface MyViewController ()

@end

@implementation MyViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    UIButton *button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    button.frame = CGRectMake(0, 100, 100, 50);
    [button setTitle:@"跳到 Scene" forState:UIControlStateNormal];
    [button addTarget:self action:@selector(buttonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:button];

    //    _viewController.wantsFullScreenLayout = YES;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/
-(void)buttonPressed:(id)sender
{
    RootViewController* rootController = [[RootViewController alloc]init];
    [self.navigationController pushViewController:rootController animated:YES];
}

@end
