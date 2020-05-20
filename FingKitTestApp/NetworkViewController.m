//
//  NetworkViewController.m
//  FingKitTestApp
//
//  Copyright © 2019 Fing Ltd. All rights reserved.
//

#import "FGKUtils.h"
#import "NetworkViewController.h"

#import <FingKit/FingKit.h>
#import <CoreLocation/CoreLocation.h>

@interface NetworkViewController () <CLLocationManagerDelegate>
@property (nonatomic, strong) CLLocationManager *locationManager;
@end

@implementation NetworkViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.activityIndicator stopAnimating];
    [self setLocationManager:[CLLocationManager new]];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [self.locationManager setDelegate:nil];
}

// ------------------------------------
// IB ACTIONS
// ------------------------------------

/*!
 * Executed when the user presses the `Info` button.
 * Display current network info.
 *
 * @param   sender      The UIButton that triggered the action.
 */
- (IBAction)info:(id)sender {
    [self.activityIndicator startAnimating];
    [self.textView setText:@""];
    [FingScanner.sharedInstance networkInfo:^(NSString *result, NSError *error) {
        dispatch_async(dispatch_get_main_queue(), ^{
            NSString *header = @"--- networkInfo ---";
            NSString *formatted = [FGKUtils formatResult:result orError:error];
            NSString *content = [NSString stringWithFormat:@"%@\n%@", header, formatted];
            NSLog(@"---NETWORK INFO---\n%@", formatted);
            [self printToUI:content];
            [self.activityIndicator stopAnimating];
            // Request location permissions if necessary
            NSString *bssidIsMasked = [FGKUtils extractFromJSON:result forKey:@"bssidIsMasked"];
            NSString *ssidIsUnknown = [FGKUtils extractFromJSON:result forKey:@"ssidIsUnknown"];
            if (bssidIsMasked != nil || ssidIsUnknown != nil) {
                [self requestPermissionsToShowSsidAndBssid];
            }

        });
    }];
}

/*!
 * Executed when the user presses the `Scan` button.
 * Display current network scan.
 *
 * @param   sender      The UIButton that triggered the action.
 */
- (IBAction)scan:(id)sender {
    [self.activityIndicator startAnimating];
    [self.textView setText:@""];
    FingScanner *scanner = [FingScanner sharedInstance];
    FingScanOptions *options = [FingScanOptions systemDefault];

    // Set this to YES to simulate an externally-provided ARP table 
    BOOL useExternalInput = NO;
    if (useExternalInput) {
        FingScanInput *input = [self createMockInput:30];
        
        [self printToUI:@"--- networkScan with EXTERNAL ARP TABLE ---"];
        [scanner networkScan:options withScanInput:input completion:^(NSString *result, NSError *error) {
            NSString *completed = [FGKUtils extractFromJSON:result forKey:@"completed"];
            NSString *formatted = [FGKUtils formatResult:result orError:error];
            NSLog(@"---NETWORK SCAN---\n%@", formatted);
            dispatch_async(dispatch_get_main_queue(), ^{
                [self printToUI:formatted];
                if (completed == nil || [@"true" isEqualToString:completed])
                    [self.activityIndicator stopAnimating];
            });
        }];
    } else {
        [self printToUI:@"--- networkScan ---"];
        [scanner networkScan:options completion:^(NSString *result, NSError *error) {
            NSString *completed = [FGKUtils extractFromJSON:result forKey:@"completed"];
            NSString *formatted = [FGKUtils formatResult:result orError:error];
            NSLog(@"---NETWORK SCAN---\n%@", formatted);
            dispatch_async(dispatch_get_main_queue(), ^{
                [self printToUI:formatted];
                if (completed == nil || [@"true" isEqualToString:completed])
                    [self.activityIndicator stopAnimating];
            });
        }];
    }
}

/*!
 * Executed when the user presses the `Stop` button.
 *
 * @param   sender      The UIButton that triggered the action.
 */
- (IBAction)stop:(id)sender {
    FingScanner *scanner = [FingScanner sharedInstance];
    // Testing BB options to limit the size
    //    options.maxNetworkSize = 28;
    [self printToUI:@"--- networkScanStop ---"];
    [scanner networkScanStop];
}

// ------------------------------------
// AUX
// ------------------------------------

-(FingScanInput *)createMockInput:(NSInteger)count {
    NSMutableArray<FingScanDeviceEntry*>* table = [NSMutableArray new];
    for (int i=0; i < count; i++) {
        FingScanDeviceEntry *entry = [FingScanDeviceEntry new];
        entry.ipAddress = [NSString stringWithFormat:@"192.168.1.%@", @(i)];
        entry.macAddress = [NSString stringWithFormat:@"02:00:FF:00:00:%02X", i];
        [table addObject:entry];
    }
    
    FingScanInput *input = [FingScanInput new];
    input.deviceEntries = table;
    
    return input;
}

/*!
 * Prints the given content in the UI as plaintext.
 *
 * @param   content     The text to print.
 */
- (void)printToUI:(NSString *)content {
    NSString *toBePrinted = content;
    if ([self.textView.text length] != 0)
        toBePrinted = [NSString stringWithFormat:@"%@\n%@", self.textView.text, content];
    self.textView.text = toBePrinted;
    if (self.textView.text.length > 0)
        [self.textView scrollRangeToVisible:NSMakeRange(self.textView.text.length -1, 1)];
}

/*!
 * Displays the alert to request location permission.
 * If the user previously denied the access to location services, will show a message to direct the user to iOS settings
 */
- (void)requestPermissionsToShowSsidAndBssid {

    CLAuthorizationStatus status = [CLLocationManager authorizationStatus];
    if (status == kCLAuthorizationStatusAuthorizedAlways || status == kCLAuthorizationStatusAuthorizedWhenInUse) {
        NSLog(@"Location permissions have been already granted!");
        return;
    }

    UIAlertController *controller = [UIAlertController
            alertControllerWithTitle:@"Location permissions required"
                             message:@"\nStarting from iOS 13, in order to request Wi-Fi network SSID and BSSID apps must:\n\n"
                                      "• Request location permissions\n"
                                      "• Declare \"Access WiFi information in \"Signing & Capabilities\""
                      preferredStyle:UIAlertControllerStyleAlert];

    [controller addAction:[UIAlertAction
            actionWithTitle:@"Cancel"
                      style:UIAlertActionStyleCancel
                    handler:nil]];

    if (status == kCLAuthorizationStatusNotDetermined) {
        [controller addAction:[UIAlertAction
                actionWithTitle:@"Request permissions"
                          style:UIAlertActionStyleDefault
                        handler:^(UIAlertAction *action) {
            [self.locationManager setDelegate:self];
            [self.locationManager requestWhenInUseAuthorization];
        }]];
    } else {
        [controller addAction:[UIAlertAction
                actionWithTitle:@"Go to iOS settings"
                          style:UIAlertActionStyleDefault
                        handler:^(UIAlertAction *action) {
            if (@available(iOS 10.0, *)) {
                [UIApplication.sharedApplication
                        openURL:[NSURL URLWithString:UIApplicationOpenSettingsURLString]
                        options:[NSDictionary dictionary]
              completionHandler:nil];
            } else {
                [UIApplication.sharedApplication openURL:[NSURL URLWithString:UIApplicationOpenSettingsURLString]];
            }
        }]];

    }

    [self presentViewController:controller animated:YES completion:nil];

}

// ------------------------------------
// LOCATION MANAGER DELEGATE
// ------------------------------------

- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status {
    dispatch_async(dispatch_get_main_queue(), ^{
        if (status == kCLAuthorizationStatusAuthorizedAlways || status == kCLAuthorizationStatusAuthorizedWhenInUse) {
            UIAlertController *controller = [UIAlertController
                    alertControllerWithTitle:@"Permissions granted!"
                                     message:@"You can now request network information to obtain Wi-Fi network SSID and BSSID!"
                              preferredStyle:UIAlertControllerStyleAlert];
            [controller addAction:[UIAlertAction
                    actionWithTitle:@"Ok"
                              style:UIAlertActionStyleDefault
                            handler:nil]];
            [self presentViewController:controller animated:YES completion:nil];
        }
        [self.locationManager setDelegate:nil];
    });
}

@end
