//
//  PLVPayleven.h
//  PaylevenSDK
//
//  Created by Alexei Kuznetsov on 14.10.14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>


@class PLVDevice, PLVPaymentRequest, PLVPaymentTask;
@protocol PLVPaymentTaskDelegate;


/** Login state constants. */
typedef NS_ENUM(NSInteger, PLVPaylevenLoginState) {
    /** Logged out. */
    PLVPaylevenLoginStateLoggedOut,
    
    /** Logging in. */
    PLVPaylevenLoginStateLoggingIn,
    
    /** Logged in. */
    PLVPaylevenLoginStateLoggedIn,
    
    /** Logging out. */
    PLVPaylevenLoginStateLoggingOut
};

/**
 * PLVPayleven class is the central point of Payleven SDK.
 *
 * Steps to make a payment:
 *
 * 1. Login using Payleven username and password.
 * 2. Pair the payment device via the Bluetooth.
 * 3. Get the `PLVDevice` object from the `devices` property.
 * 4. Check if the device is ready for payments, and if not, call the perparation method.
 * 5. Create a payment task using `-paymentTaskWithRequest:device:delegate:`.
 * 6. Start the payment task.
 */
@interface PLVPayleven : NSObject

/**
 * SDKVersion
 *
 * @return String with the version of the sdk (i.e. '1.0')
 *
 */
+ (NSString*) SDKVersion;

/** The receiver's login state. KVO-observable. */
@property(nonatomic, readonly, assign) PLVPaylevenLoginState loginState;

/**
 * The array of currently available devices represented by PLVDevice objects. KVO-observable.
 *
 * @warning When the receiver logs out, all references to the device objects must be discarded. It is a programmatic
 * error to use device objects after the logout.
 */
@property(nonatomic, readonly, strong) NSArray *devices;

/**
 * Performs login attempt.
 *
 * @param username Payleven account username.
 * @param password Payleven account password.
 * @param APIKey API key.
 * @param completionHandler A block called when the login finishes or an error occurs. The block takes a single
 * parameter `error`: An NSError indicating the error during the login. `nil` indicates the successful login.
 *
 * @warning If this method is called while the login or the logout are in progress, the call is ignored and the
 * completion handler is not called.
 */
- (void)loginWithUsername:(NSString *)username
                 password:(NSString *)password
                   APIKey:(NSString *)APIKey
        completionHandler:(void (^)(NSError *error))completionHandler;

/**
 * Performs logout attempt.
 *
 * @param completionHandler Block to be called when the logout finishes or an error occurs. The block takes a single
 * parameter `error`: An NSError indicating the error during the logout. `nil` indicates the successful logout.
 *
 * @warning If this method is called while the login or the logout are in progress, the call is ignored and the
 * completion handler is not called.
 */
- (void)logoutWithCompletionHandler:(void (^)(NSError *error))completionHandler;

/**
 * Creates a payment task.
 *
 * @param request Payment request.
 * @param device Device for a payment.
 * @param delegate Payment task delegate.
 *
 * @return A newly created payment task or `nil` if the receiver is not logged in or the device is not ready. Run
 * `-[PLVPaymentTask start]` to start the payment process.
 */
- (PLVPaymentTask *)paymentTaskWithRequest:(PLVPaymentRequest *)request
                                    device:(PLVDevice *)device
                                  delegate:(id <PLVPaymentTaskDelegate>)delegate;

@end
