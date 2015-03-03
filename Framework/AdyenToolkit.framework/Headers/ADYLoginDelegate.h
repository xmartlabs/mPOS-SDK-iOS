//
//  ADYLoginDelegate.h
//  AdyenPOSLib
//
//  Created by Jeroen Koops on 6/18/13.
//
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, ADYLoginDelegateStatus) {
    ADYLoginDelegateStatusLoggingIn,
    ADYLoginDelegateStatusLoggedIn,
    ADYLoginDelegateStatusPreSettling,
    ADYLoginDelegateStatusVerifyingToken,
    ADYLoginDelegateStatusTokenNotYetValid,
    ADYLoginDelegateStatusTokenValid,
    ADYLoginDelegateStatusPostSettling
};

/**
 * Protocol specifying a callback from the library into 
 * the app, to indicate login progress and outcome.
 */
@protocol ADYLoginDelegate <NSObject>

/**
 * This method is called periodically during a login, to
 * report progress.
 * @param progress a number from `0.0` to `1.0`, indicating how
 * much of the login-process has already been executed.
 */
- (void)loginUpdatedProgress:(float)progress;

/**
 * This method is called by the library when the login
 * was completed successfully.
 * @param info reserved for future use.
 */
- (void)loginCompletedSuccessfullyWithInfo:(NSDictionary*)info;

/**
 * This method is called by the library when the login
 * failed for some reason.
 * @param error the error that prevented the login from completing.
 */
- (void)loginFailedWithError:(NSError*)error;

/**
 * This method is called periodically by the library to indicate
 * the activity currently performed. 
 *
 * The given status is one of:
 *
 * - `ADYLoginDelegateStatusLoggingIn`: the library has sent a login-request to the backend
 * - `ADYLoginDelegateStatusLoggedIn`: login was successful, but token is not verified yet
 * - `ADYLoginDelegateStatusPreSettling`: after successful login, start waiting for some time
 * to allow the token to propagate across the cluster
 * - `ADYLoginDelegateStatusVerifyingToken`: attempt to use the generated token to see if it
 * has already propagated
 * - `ADYLoginDelegateStatusTokenNotValid`: token has not propagated across the cluster yet, another attempt
 * will be made
 * - `ADYLoginDelegateStatusTokenValid`: token has propagated across the cluster
 * - `ADYLoginDelegateStatusPostSettling`: after successful token propagation, wait a short while to
 * let the system settle
 */

- (void)loginChangedStatus:(ADYLoginDelegateStatus)status;
@end
