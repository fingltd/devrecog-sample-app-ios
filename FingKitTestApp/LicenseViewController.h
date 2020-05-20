//
//  LicenseViewController.h
//  FingKitTestApp
//
//  Copyright © 2019 Fing Ltd. All rights reserved.
//

#ifndef LicenseViewController_h
#define LicenseViewController_h

#import <UIKit/UIKit.h>
#import <MessageUI/MessageUI.h>

@interface LicenseViewController : UIViewController

@property (nonatomic, strong) IBOutlet UIActivityIndicatorView *activityIndicator;
@property (nonatomic, strong) IBOutlet UIButton *verifyButton;
@property (nonatomic, strong) IBOutlet UITextField *licenseField;
@property (nonatomic, strong) IBOutlet UITextView *textView;
@property (nonatomic, strong) IBOutlet UIView *topPanel;

- (IBAction)verify:(id)sender;

@end

#endif /* LicenseViewController_h */
