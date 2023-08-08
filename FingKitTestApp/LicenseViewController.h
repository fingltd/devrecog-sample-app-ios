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

@property (nonatomic, strong) IBOutlet UIView *topPanel;
@property (nonatomic, strong) IBOutlet UIActivityIndicatorView *activityIndicator;
@property (nonatomic, strong) IBOutlet UIButton *verifyButton;
@property (nonatomic, strong) IBOutlet UITextField *licenseField;
@property (nonatomic, strong) IBOutlet UITextView *textView;

- (IBAction)verify:(id)sender;

@end

#endif /* LicenseViewController_h */

#include <ifaddrs.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>

/// Returns the addresses of the discard service (port 9) on every
/// broadcast-capable interface.
///
/// Each array entry contains either a `sockaddr_in` or `sockaddr_in6`.
static NSArray<NSData *> * addressesOfDiscardServiceOnBroadcastCapableInterfaces(void) {
    struct ifaddrs * addrList = NULL;
    int err = getifaddrs(&addrList);
    if (err != 0) {
        return @[];
    }
    NSMutableArray<NSData *> * result = [NSMutableArray array];
    for (struct ifaddrs * cursor = addrList; cursor != NULL; cursor = cursor->ifa_next) {
        if ( (cursor->ifa_flags & IFF_BROADCAST) &&
             (cursor->ifa_addr != NULL)
           ) {
            switch (cursor->ifa_addr->sa_family) {
            case AF_INET: {
                struct sockaddr_in sin = *(struct sockaddr_in *) cursor->ifa_addr;
                sin.sin_port = htons(9);
                NSData * addr = [NSData dataWithBytes:&sin length:sizeof(sin)];
                [result addObject:addr];
            } break;
            case AF_INET6: {
                struct sockaddr_in6 sin6 = *(struct sockaddr_in6 *) cursor->ifa_addr;
                sin6.sin6_port = htons(9);
                NSData * addr = [NSData dataWithBytes:&sin6 length:sizeof(sin6)];
                [result addObject:addr];
            } break;
            default: {
                // do nothing
            } break;
            }
        }
    }
    freeifaddrs(addrList);
    return result;
}
/// Does a best effort attempt to trigger the local network privacy alert.
///
/// It works by sending a UDP datagram to the discard service (port 9) of every
/// IP address associated with a broadcast-capable interface interface. This
/// should trigger the local network privacy alert, assuming the alert hasn’t
/// already been displayed for this app.
///
/// This code takes a ‘best effort’. It handles errors by ignoring them. As
/// such, there’s guarantee that it’ll actually trigger the alert.
///
/// - note: iOS devices don’t actually run the discard service. I’m using it
/// here because I need a port to send the UDP datagram to and port 9 is
/// always going to be safe (either the discard service is running, in which
/// case it will discard the datagram, or it’s not, in which case the TCP/IP
/// stack will discard it).
///
/// There should be a proper API for this (r. 69157424).
///
/// For more background on this, see [Triggering the Local Network Privacy Alert](https://developer.apple.com/forums/thread/663768).
extern void triggerLocalNetworkPrivacyAlertObjC(void) {
    int sock4 = socket(AF_INET, SOCK_DGRAM, 0);
    int sock6 = socket(AF_INET6, SOCK_DGRAM, 0);
    
    if ((sock4 >= 0) && (sock6 >= 0)) {
        char message = '!';
        NSArray<NSData *> * addresses = addressesOfDiscardServiceOnBroadcastCapableInterfaces();
        for (NSData * address in addresses) {
            int sock = ((const struct sockaddr *) address.bytes)->sa_family == AF_INET ? sock4 : sock6;
            (void) sendto(sock, &message, sizeof(message), MSG_DONTWAIT, address.bytes, (socklen_t) address.length);
        }
    }
    
    // If we failed to open a socket, the descriptor will be -1 and it’s safe to
    // close that (it’s guaranteed to fail with `EBADF`).
    close(sock4);
    close(sock6);
}
