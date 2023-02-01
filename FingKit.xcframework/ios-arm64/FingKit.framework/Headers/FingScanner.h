/**
 *  FingScanner.h
 *  FingEngine
 *
 *  Created by Domotz on 18/08/16.
 *  Copyright © 2016 Domotz Ltd. All rights reserved.
 */

#import "FingScanOptions.h"
#import "FingAccountProfile.h"
#import "FingScanInput.h"

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString* const kFingErrorDomain;
FOUNDATION_EXPORT NSInteger const kFingErrorCodeLicenseNotVerified;
FOUNDATION_EXPORT NSInteger const kFingErrorCodeLicenseForbidsUsage;
FOUNDATION_EXPORT NSInteger const kFingErrorCodeAccountFailure;
FOUNDATION_EXPORT NSInteger const kFingErrorCodeScanFailure;

/**
 * @typedef FingResultCallback
 * @brief The type of block invoked when events complete.
 *
 * @param result Optionally; the result, if any.
 * @param error Optionally; if an error occurs, this is the NSError object that describes the problem. Set to nil otherwise.
 */
typedef void (^FingResultCallback)(NSString * __nullable result, NSError * __nullable error);

/**
 * @brief The top level Fing Kit singleton that provides methods for scanning a network.
 */
@interface FingScanner : NSObject


#pragma mark ---- LIFECYCLE ----


/**
 * @brief The singleton shared instance of a Fing Scanner.
 */
+ (FingScanner *)sharedInstance;

/**
 * @brief Inform the engine that the App is about to suspend, entering background mode.
 */
- (void)willSuspend;

/**
 * @brief Inform the engine that the App is about to resume, entering foreground mode.
 */
- (void)willResume;


#pragma mark ---- LICENSE VALIDATION ----


/**
 * @brief Validates a license key, notifying results to the given completion handler.
 * 
 * @param key           the key to validate
 * @param usageToken    an optional usage token to be validated via webhook
 * @param completion    the handler of the notification event at method completion.
 */
- (void)validateLicenseKey:(NSString *)key
                 withToken:(nullable NSString *)usageToken
                completion:(nullable FingResultCallback)completion;

/**
 * @brief Validates a license key, notifying results to the given completion handler.
 *
 * @param key           the key to validate
 * @param usageToken    an optional usage token to be validated via webhook
 * @param whValue       an optional value to be passed to the webhook to track the call
 * @param completion    the handler of the notification event at method completion.
 */
- (void)validateLicenseKey:(NSString *)key
                 withToken:(nullable NSString *)usageToken
           andWebHookValue:(nullable NSString *)whValue
                completion:(nullable FingResultCallback)completion;


#pragma mark ---- ACCOUNT MANAGEMENT ----


/**
 * @brief Attaches this FingKit instance to a specific account, based on the given profile.
 *
 * @param profile       the profile object of the account to attach to.
 * @param token         an optional token to be validated via webhook
 * @param completion    the handler of the notification event at method completion.
 */
- (void)accountAttach:(FingAccountProfile *)profile
            withToken:(nullable NSString *)token
           completion:(nullable FingResultCallback)completion;

/**
 * @brief Returns a description of the account this FingKit instance is attached to, if any.
 *
 * @param completion    the handler of the notification event at method completion.
 */
- (void)accountInfo:(nullable FingResultCallback)completion;

/**
 * @brief Detaches this FingKit instance from an account, if previously attached.
 *
 * @param completion    the handler of the notification event at method completion.
 */
- (void)accountDetach:(nullable FingResultCallback)completion;


#pragma mark ---- NETWORK ----


/**
 * @brief Retrieves network details. A single event will be notified to the given completion handler.
 *
 * @param completion    the handler of the notification event at method completion.
 */
- (void)networkInfo:(nullable FingResultCallback)completion;

/**
 * @brief Executes a scan, whose events will be notified to the given completion handler.
 *
 * @param options       the options to configure the scan procedure.
 * @param completion    the handler of the notification event at method completion.
 */
- (void)networkScan:(nullable FingScanOptions *)options
         completion:(nullable FingResultCallback)completion;

/**
 * @brief Executes a scan, whose events will be notified to the given completion handler.
 *
 * @param options       the options to configure the scan procedure.
 * @param input           the additional input to provide the device definition through external sources.
 * @param completion    the handler of the notification event at method completion.
 */
- (void)networkScan:(nullable FingScanOptions *)options
      withScanInput:(nullable FingScanInput *)input
         completion:(nullable FingResultCallback)completion;

/**
 * @brief Stops a scan, if running. If the scan was not running, nothing is done.
 */
- (void)networkScanStop;

@end

NS_ASSUME_NONNULL_END
