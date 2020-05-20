//
//  LicenseViewController.m
//  FingKitTestApp
//
//  Copyright © 2019 Fing Ltd. All rights reserved.
//

#import "FGKUtils.h"
#import "LicenseViewController.h"

#import <FingKit/FingKit.h>

@implementation LicenseViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.textView setText:@""];
    [self.licenseField setPlaceholder:@"<Your License Key>"];
    [self.licenseField setText:@""];
    [self.activityIndicator stopAnimating];
}

/*!
 * Executed when the user presses the `Verify` button.
 * Perform the validation of the inserted License Key with the API.
 *
 * @param   sender      The UIButton that triggered the action.
 */
- (IBAction)verify:(id)sender {
    [self.activityIndicator startAnimating];
    [self.textView setText:@""];
    [FingScanner.sharedInstance
            validateLicenseKey:self.licenseField.text
                     withToken:nil
                    completion:^(NSString *result, NSError *error) {
        NSString *header = @"--- validateLicenseKey ---";
        NSString *formatted = [FGKUtils formatResult:result orError:error];
        NSString *content = [NSString stringWithFormat:@"%@\n%@", header, formatted];
        NSLog(@"---VERIFY LICENSE KEY---\n%@", formatted);
        dispatch_async(dispatch_get_main_queue(), ^{
            [self printToUI:content];
            [self.activityIndicator stopAnimating];
        });
    }];
}

/*!
 * Prints the given content in the UI as plaintext.
 *
 * @param   content     The text to print.
 */
- (void)printToUI:(NSString *)content {
    [self.textView setText:content];
    if (self.textView.text.length > 0) {
        [self.textView scrollRangeToVisible:NSMakeRange(self.textView.text.length -1, 1)];
    }
}

@end
