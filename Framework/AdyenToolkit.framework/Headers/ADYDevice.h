//
//  ADYDevice.h
//  AdyenPOSLib
//
//  Created by Jeroen Koops on 4/26/13.
//
//

#import <Foundation/Foundation.h>

@class ADYDeviceData;
@class ADYTransactionRequest;
@protocol ADYDeviceManagerDelegate;
@class ADYDeviceRegistry;

typedef enum {
    ADYDeviceConnectionTypeBluetooth,
    ADYDeviceConnectionTypeWifi
} ADYDeviceConnectionType;

typedef enum {
    ADYDeviceStatusInitializing,
    ADYDeviceStatusInitialized,
    ADYDeviceStatusNotBoarded,
    ADYDeviceStatusError,
    ADYDeviceStatusStopped,
    ADYDeviceStatusGone
} ADYDeviceStatus;

@interface ADYDevice : NSObject

/** Name of the device. */
@property (nonatomic, readonly) NSString* name;

/** Hostname or IP address used to connect to a Wifi device. Not used for Bluetooth */
@property (nonatomic, readonly) NSString* hostname;

/** Type of the connection to the device */
@property (nonatomic, readonly) ADYDeviceConnectionType connectionType;

/** 
 * Current status of the device.
 * This status has one of the following values:
 *
 * - `ADYDeviceStatusInitializing`: The device is being initialized. In this status, it is 
 * not possible to perform payment-transactions with the device.
 * - `ADYDeviceStatusInitialized`: The device is ready for payment-transactions.
 * - `ADYDeviceStatusNotBoarded`: The device is ready, but not configured for use by the merchant
 * that is currently logged in. Use `boardDeviceWithDelegate:` to
 * attempt to configure the device.
 * - `ADYDeviceStatusError`: There was an error communicating with the device. Use
 * `retryConnection` to attempt to re-establish communication
 * with the device.
 * - `ADYDeviceStatusStopped`: The device was stopped because the merchant was logged out.
 * - `ADYDeviceStatusGone`: The device has disconnected. Devices with this status will
 * not appear on the `devices` list of the `ADYDeviceRegistry` anymore.
 * However, if you keep a reference to an `ADYDevice` with status `ADYDeviceStatusGone`,
 * the `ADYDevice` object will remain valid. If the device re-connects at a later
 * moment, the status of the `ADYDevice` will change back to `ADYDeviceStatusInitializing`
 * and finally `ADYDeviceStatusInitialized`, and be ready for use once more.
 */
@property (nonatomic, readonly) ADYDeviceStatus status;

/**
   Object containing additional data about the device. 
   This data is only set when the device's status is
   `ADYDeviceStatusInitialized` or `ADYDeviceStatusNotBoarded`.
 */
@property (nonatomic, readonly) ADYDeviceData* deviceData;

/**
   Error-object containing error-information about the device. This
   property is only set when the device's status is
   `ADYDeviceStatusError`.
 */
@property (nonatomic, readonly) NSError* error;

/**
   Creates an `ADYTransactionRequest`, which is the start of executing
   a payment-transaction with this device.
 
   After creating the `ADYTransactionRequest`, set all of its relevant properties,
   and then call `startWithDelegate:` to start the payment-transaction.

   @param reference a merchant-supplied reference for the transaction, as an `NSString`.
   @param error pointer to an `NSError`, which will be set if the transaction cannot
   be created for some reason.
 
   @warning When an `ADYTransactionRequest` is created, the `ADYDevice` will _not_
   keep a reference to it. Therefore, to prevent it from being deallocated, it is important
   that you keep a reference to it until after the transaction, started with
   [ADYTransactionRequest startWithDelegate:], has been finished.
 */
-(ADYTransactionRequest*)createTransactionRequestWithReference:(NSString*)reference
                                                         error:(NSError**)error;

/**
 * Creates an `ADYTransactionRequest`.
 *
 * @deprecated Use `createTransactionRequestWithReference:error:` instead. If
 * you _must_ use `createTransactionRequestWithError:`, you _have_ to manually
 * set a merchant reference by setting option `ADYTransactionOptionReferenceKey`
 * in the `options` dictionary, or else the transaction will fail.
 */
-(ADYTransactionRequest*)createTransactionRequestWithError:(NSError**)error __attribute__((deprecated));

/**
   Starts an attempt to board the device.
 
   This method will return immediately, the boarding process will proceed asynchronously.
 
   @param delegate a delegate that will be kept informed about the boarding process' progress
   and outcome.
 */
- (void)boardDeviceWithDelegate:(id<ADYDeviceManagerDelegate>)delegate;

/**
   Re-attempt to identify the payment device. Used this when the status of
   the device is `ADYDeviceStatusError` and you want to retry the connection.
   This will (normally) only be useful if something is first changed on either
   the server (uncouple terminal from Merchant) or on the terminal (delete
   settings). Otherwise, the device will keep going to status error.
 */
-(void)retryConnection;

/**
   DEPRECATED

   Instructs the device to synchronize with the backend immediately.
 
   Normally, the device performs synchronization with the backend at 
   its own discretion. Call this method to do it right now.
 
   This method returns straight away; communication with the device, and
   the actual synchronization happens in the background. When synchronization
   is complete, or an error occurs, the supplied completion-block is called.
 
   @param completion block that is called when synchronization is complete,
   or an error occurs. In the latter case, the given `NSError` is non-`nil`.

   @deprecated This method is no longer required
 */
-(void)synchronizeNowWithCompletion:(void(^)(NSError*))completion;

/**
   DEPRECATED

   Instructs the device to prompt the user for permission to install
   a new firmware-version, if a new firmware-version is available.
 
   The device is aware of the availabiliy of a new firmware-version by a
   prior call to `synchronizeNowWithCompletion:`, or a synchronization performed
   on its own initiative.
 
   This method returns straight away; communication with the device happens
   in the background. As soon as communication is finished, or an error occurs,
   the supplied completion-block is called.
 
   @param completion block that is called when synchronization is complete, or an error
   occurs. In the latter case the given `NSError` is non-`nil`. Note that the operation
   is considered complete when the device shows a prompt to the user. This doesn't
   necessarily mean that the user agrees to install the update, or that installing the update
   will succeed.

   @deprecated This method is no longer required
 */

-(void)installUpdateWhenAvailableWithCompletion:(void(^)(NSError*))completion;

/**
   Description of the device, for debug-purposes only.
 */
-(NSString*)description;

- (void)ping;
@end
