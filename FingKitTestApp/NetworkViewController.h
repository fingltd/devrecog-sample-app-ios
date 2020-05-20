//
//  NetworkViewController.h
//  FingKitTestApp
//
//  Copyright © 2019 Fing Ltd. All rights reserved.
//

#ifndef NetworkViewController_h
#define NetworkViewController_h

#import <UIKit/UIKit.h>
#import <MessageUI/MessageUI.h> 

@interface NetworkViewController : UIViewController

@property (nonatomic, strong) IBOutlet UIActivityIndicatorView *activityIndicator;
@property (nonatomic, strong) IBOutlet UIButton *infoButton;
@property (nonatomic, strong) IBOutlet UIButton *scanButton;
@property (nonatomic, strong) IBOutlet UIButton *stopButton;
@property (nonatomic, strong) IBOutlet UITextView *textView;
@property (nonatomic, strong) IBOutlet UIView *topPanel;

- (IBAction)info:(id)sender;
- (IBAction)scan:(id)sender;
- (IBAction)stop:(id)sender;

@end

#endif /* NetworkViewController_h */
