//
//  AccountViewController.m
//  FingKitTestApp
//
//  Created by Daniele Pantaleone on 19/01/17.
//  Copyright © 2017 Domotz Ltd. All rights reserved.
//

#import "AccountViewController.h"
#import "FGKUtils.h"

#import <FingKit/FingKit.h>

@interface AccountViewController ()

@end

@implementation AccountViewController

-(void)viewDidLoad {
    [super viewDidLoad];
    self.textView.text = @"";
    self.idField.text = @"test_user";
    self.nameField.text = @"John Appleseed";
    self.emailField.text = @"john@appleseed.com";
    UIView *topRect = [[UIView alloc] initWithFrame:CGRectMake(0, 84, self.view.frame.size.width, 136)];
    topRect.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    topRect.backgroundColor = [UIColor colorWithRed:0.9 green:0.9 blue:0.9 alpha:1.0];
    [self.topPanel addSubview:topRect];
    [self.activityIndicator stopAnimating];
}

/*!
 * Executed when the user presses the `Attach` button.
 * Perform the attach of the provided user account.
 *
 * @param   sender      The UIButton that triggered the action.
 */
-(IBAction)attach:(id)sender {
    [self.activityIndicator startAnimating];
    self.textView.text = @"";
    FingScanner *scanner = [FingScanner sharedInstance];
    FingAccountProfile *fap = [[FingAccountProfile alloc] init];
    fap.accountId = self.idField.text;
    fap.accountFullName = self.nameField.text;
    fap.accountEmail = self.emailField.text;
    [scanner accountInfo:^(NSString * _Nullable result, NSError * _Nullable error) {
        NSString *header = @"--- accountInfo ---";
        NSString *formatted = [FGKUtils formatResult:result orError:error];
        NSString *content = [NSString stringWithFormat:@"%@\n%@", header, formatted];
        NSLog(@"---ACCOUNT INFO---\n%@", formatted);
        [self printToUI:content];
        if (error == nil && result != nil) {
            NSString *attached = [FGKUtils extractFromJSON:result forKey:@"attached"];
            if ([@"false" isEqualToString:attached]) {
                [self printToUI:@"\nACCOUNT IS DETACHED: ATTACHING...\n"];
                [scanner accountAttach:fap withToken:@"TOKEN_123" completion:^(NSString * _Nullable result, NSError * _Nullable error) {
                    NSString *header = @"--- accountAttach ---";
                    NSString *formatted = [FGKUtils formatResult:result orError:error];
                    NSString *content = [NSString stringWithFormat:@"%@\n%@", header, formatted];
                    NSLog(@"---ACCOUNT ATTACH---\n%@", formatted);
                    [self printToUI:content];
                }];
            }
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.activityIndicator stopAnimating];
        });
    }];
}

/*!
 * Executed when the user presses the `Detach` button.
 * Perform the detach of the currently attached user account.
 *
 * @param   sender      The UIButton that triggered the action.
 */
-(IBAction)detach:(id)sender {
    [self.activityIndicator startAnimating];
    self.textView.text = @"";
    FingScanner *scanner = [FingScanner sharedInstance];
    [scanner accountInfo:^(NSString * _Nullable result, NSError * _Nullable error) {
        NSString *header = @"--- accountInfo ---";
        NSString *formatted = [FGKUtils formatResult:result orError:error];
        NSString *content = [NSString stringWithFormat:@"%@\n%@", header, formatted];
        NSLog(@"---ACCOUNT INFO---\n%@", formatted);
        [self printToUI:content];
        if (error == nil && result != nil) {
            NSString *attached = [FGKUtils extractFromJSON:result forKey:@"attached"];
            if ([@"true" isEqualToString:attached]) {
                [self printToUI:@"\nACCOUNT IS ATTACHED: DETACHING...\n"];
                [scanner accountDetach:^(NSString * _Nullable result, NSError * _Nullable error) {
                    NSString *header = @"--- accountDetach ---";
                    NSString *formatted = [FGKUtils formatResult:result orError:error];
                    NSString *content = [NSString stringWithFormat:@"%@\n%@", header, formatted];
                    NSLog(@"---ACCOUNT DETACH---\n%@", formatted);
                    [self printToUI:content];
                }];
            }
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.activityIndicator stopAnimating];
        });
    }];
}

/*!
 * Prints the given content in the UI as plaintext.
 *
 * @param   content     The text to print.
 */
-(void)printToUI:(NSString *)content {
    dispatch_async(dispatch_get_main_queue(), ^{
        NSString *toBePrinted = content;
        if ([self.textView.text length] != 0)
            toBePrinted = [NSString stringWithFormat:@"%@\n%@", self.textView.text, content];
        self.textView.text = toBePrinted;
        if (self.textView.text.length > 0)
            [self.textView scrollRangeToVisible:NSMakeRange(self.textView.text.length -1, 1)];
    });
}

@end

