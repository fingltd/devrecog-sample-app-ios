//
//  AccountViewController.h
//  FingKitTestApp
//
//  Created by Daniele Pantaleone on 19/01/17.
//  Copyright © 2017 Domotz Ltd. All rights reserved.
//

#ifndef AccountViewController_h
#define AccountViewController_h

#import <UIKit/UIKit.h>
#import <MessageUI/MessageUI.h>

@interface AccountViewController : UIViewController

@property (retain) IBOutlet UIActivityIndicatorView *activityIndicator;
@property (retain) IBOutlet UITextField *idField;
@property (retain) IBOutlet UITextField *nameField;
@property (retain) IBOutlet UITextField *emailField;
@property (retain) IBOutlet UIButton *attachButton;
@property (retain) IBOutlet UIButton *detachButton;
@property (retain) IBOutlet UITextView *textView;
@property (retain) IBOutlet UIView *topPanel;

-(IBAction)attach:(id)sender;
-(IBAction)detach:(id)sender;

@end

#endif /* AccountViewController_h */
