//
//  Adyen.h
//
//  Created by maarten on 6/19/12.
//
//

#import "ADYDeviceManagerDelegate.h"
#import "ADYServerSynchronization.h"
#import "ADYLoginDelegate.h"
#import "ADYConstants.h"
#import "ADYTransactionData.h"

typedef enum {
    ADYLoginStatusLoggedOut = 0,
    ADYLoginStatusLoggingIn = 1,
    ADYLoginStatusLoggedIn = 2,
    ADYLoginStatusLoggingOut = 3
} ADYLoginStatus;

@class ADYAppData;
@class ADYDeviceData;
@class ADYPendingTransaction;
@class ADYTransactionRequest;
@class ADYTransactionData;
@class ADYDeviceRegistry;
@class ADYAccountData;
@class ADYCurrency;

/**
 * This notification is posted when an attempt from the bluetooth-device to fetch an HTTP
 * resource from a server, using the iOS device as a proxy, fails. Additional information
 * is available in the notification's <tt>userInfo</tt>:
 * <dl>
 * <dt><tt>ADYNotificationProxyFailedURLKey</tt></dt>
 * <dd>The URL of the resource the device tried to fetch, as an <tt>NSURL</tt> object</dd>
 * <dt><tt>ADYNotificationProxyFailedErrorKey</tt></dt>
 * <dd>The error that occurred, as an <tt>NSError</tt> object</dd>
 * </dl>
 */
extern NSString* const ADYNotificationProxyFailed;

/// This notification is posted when a payment transaction starts.
extern NSString* const ADYNotificationTransactionStarted;

/// This notification is posted when a payment transaction ends.
extern NSString* const ADYNotificationTransactionEnded;

/// To get the `ADYTransactionData` object from the `ADYNotificationTransactionEnded` notification userInfo.
extern NSString* const ADYNotificationTransactionDataKey;

/// Used as key in the <tt>userInfo</tt> of a <tt>ADYNotificationProxyFailed</tt> notification.
extern NSString* const ADYNotificationProxyFailedURLKey;
/// Used as key in the <tt>userInfo</tt> of a <tt>ADYNotificationProxyFailed</tt> notification.
extern NSString* const ADYNotificationProxyFailedErrorKey;

/**
 * This class is the main entry point for Adyen payment functionality. Obtain an instance by calling
 * sharedInstance, then call the various methods to handle payment-devices and initiate payments.
 *
 * Notifications
 * =============
 *
 * The Adyen library emits the following notifications through the `NSNotificationCenter`:
 *
 * - `ADYNotificationTransactionStarted`: fired when a payment-transaction starts. A typical
 * use for this notifification is to temporarily stop the application idle-timer (using
 * `UIApplication.idleTimeDisabled` to prevent the iOS device to suspend when the transaction
 * is running.
 * - `ADYNotificationTransactionEnded`: fired when a payment-transaction ends.
 * - `ADYNotificationProxyFailed`: when a bluetooth-device is connected to the iOS device, it
 * will use the iOS device as a proxy to the PSP. Whenever the iOS device fails to relay a proxy-request
 * from the bluetooth device to the PSP, a `ADYNotificationProxyFailed` is fired. The `userInfo` dictionary
 * of this notification contains two keys:
 *     - `ADYNotificationProxyFailedURLKey`: the `NSURL` representing the URL that was requested.
 *     - `ADYNotificationProxyFailedErrorKey`: an `NSError` object representing the error that occurred
 *
 * ADYError
 * ======
 *
 * All `NSError`s emitted by classes in the `Adyen` library are errors in the `Adyen` error-domain. This 
 * value is available in the constant `ADYErrorDomain`. The error-codes that can occur are:
 *
 * - `ADYErrorCodeUnknownError` (0): An unknown error occurred. More information may be
 * available in the `NSError`s `userInfo` under key `NSUnderlyingErrorKey`.
 * - `ADYErrorCodeNoDeviceConnected` (100): An attempt was made to start an operation while
 * no payment device was connected.
 * - `ADYErrorCodeUnauthorizedForDevice` (101): An attempt was made to use a payment device
 * that was configured for another merchant.
 * - `ADYErrorCodeDeviceError` (102): The payment device could not execute a command
 * sent to it.
 * - `ADYErrorCodeInvalidCredentialsForPaymentDevice` (103): Error indicating that the supplied
 * merchant credentials are incorrect for the the payment device used. This may indicate that 
 * the device has not been boarded.
 * - `ADYErrorCodeAmountTooLow` (104):  Error indicating that a transaction was started with 
 * an amount that is too low.
 * - `ADYErrorCodeInvalidCredentialsForPSP` (200): Error indicating that the supplied merchant
 * credentials are incorrect for the PSP.
 * - `ADYErrorCodePaymentDeviceConnectionError` (300): Error indicating that communication with the payment
 * device failed.
 * - `ADYErrorCodeNetworkError` (400): Error indicating that communication over the network failed.
 * - `ADYErrorCodeAppRegistrationFailed` (500): Error indicating that registration of the app failed.
 * - `ADYErrorCodeNoInternetConnection` (401): Error indicating that a backend system could not be
 * reached because the iOS device does not have an internet connection.
 * - `ADYErrorCodeInvalidApp` (501): An attempt is made to register a device from an app that has
 * not been registered.
 * - `ADYErrorCodeUserPermissionError` (502): The user does not have sufficient permissions on the PSP
 * for the requested operation.
 * - `ADYErrorCodeInvalidMerchant` (503): The merchant account given is not valid
 * - `ADYErrorCodeAlreadyLoggedIn` (504): An attempt was made to log in without first logging out
 * - `ADYErrorCodeNotLoggedIn` (505): An attempt was made to log out without first logging in
 * - `ADYErrorCodeAppRegistrationTokenCheckTimeout` (506): Error indicating that, after
 *   app-registration, the generated token was not propagated across the entire backend
 *   in time.
 * - `ADYErrorCodeDeviceEMVError` (600): Error communicating with the EMV device
 * - `ADYErrorCodeDeviceSAPIError` (601): SAPI error
 * - `ADYErrorCodeDevicePrintReceiptFailed` (700): Transaction could not be performed because printing
 * the receipt failed.
 * - `ADYErrorCodePSPValidateError` (701): PSP failed to obtain additional data for card.
 *
 * @warning All method of the <tt>Adyen</tt> class, and all of its returned objects, must be run
 *          on the mainthread. Similarly, all methods invoked by an <tt>Adyen</tt> instance on
 *          one of its delegates are guaranteed to be invoked on the mainthread.
 *
 * @warning This library relies on notifications from the `EAAccessoryManager` to detect connecting
 *          and disconnecting bluetooth devices. These notifications can be disabled application-wide
 *          by calling `[EAAccessoryManager unregisterForLocalNotifications]`. To guarantee the correct
 *          functioning of the library, *never* call `[EAAccessoryManager unregisterForLocalNotifications]`
 *          from your app.
 */
@interface Adyen : NSObject

/**
 * The login status. 
 *
 * This is one of:
 *
 * - `ADYLoginStatusLoggedOut`: the library is not currently logged in.
 * - `ADYLoginStatusLoggingIn`: the library is in the process of logging in.
 * - `ADYLoginStatusLoggedIn`: the library is currently logged in.
 * - `ADYLoginStatusLoggingOut`: the library is currently in the process of logging out.
 */
@property (nonatomic, readonly) ADYLoginStatus loginStatus;

/**
 * A single login can have permission to do transactions for multiple merchants. If this is
  * the case, the `availableMerchantCodes` property exposes which merchantCodes are
  * available. Any of these merchantCodes can be assigned to the `activeMerchantCode`
  * property to change the current identity.
  *
  * Whenever a transaction is started, a transaction list fetched or a refund requested,
  * the `activeMerchantCode` will be used. So switching the entire lib to a different
  * identity only requires setting this property.
  *
  * Will return nil unless the `loginStatus` is ADYLoginStatusLoggedIn
 */
@property (nonatomic, strong) NSString *activeMerchantCode;

/**
 * The merchantCodes that can be used, with the current login, to request and initiate anything
 * in the lib. Any of the `availableMerchantCodes` can be set as the `activeMerchantCode` to
 * change the current identity used to start transactions and refunds.
 *
 * Will return nil unless the `loginStatus` is ADYLoginStatusLoggedIn
 */
@property (nonatomic, readonly) NSArray *availableMerchantCodes;

/**
 * The device-registry provides access to all connected payment-devices.
 */
@property (nonatomic, readonly) ADYDeviceRegistry* deviceRegistry;

/**
 * Maximum number of transaction to keep in the database. Set to `NSNotFound` to
 * keep all transactions in the database. This is a persistent property - once a
 * value has been set, its value will persist across app restarts.
 */
@property (nonatomic, assign) NSUInteger maximumNumberOfTransactions;

/**
 * Maximum age of transactions in the database, in days. Set to `NSNotFound` to 
 * keep all transactions in the database. If not `NSNotFound`, transactions older
 * than `maximumTransactionAgeDays` will be deleted periodically.
 * This is a persistent property - once a value has been set, its value will persist 
 * across app restarts.
 */
@property (nonatomic, assign) NSUInteger maximumTransactionAgeDays;

/**
 * When logged in, contains data about the account.
 */
@property (nonatomic, readonly) ADYAccountData* accountData;

/**
 * Software updates for the external payment devices are silently downloaded and
 * installed. The amount of data to be downloaded can be quite large, so by default
 * they are only downloaded while the device is connected to WiFi. Set
 * `allowSilentUpdateWhileOnWWAN` to YES to allow downloading of updates when only
 * a 'cell' connection (3G, 4G) is available.
 */
@property (nonatomic, assign) BOOL allowSilentUpdateWhileOnWWAN;


/**
 * For situations where there can be no internet connection while making a payment, an
 * offline transaction mechanism has been constructed. In this case, the payment device
 * will not communicate with the server directly, but pass all it's transaction data
 * to the app (this framework).
 *
 * Enabling this functionality will introduce some new behaviour in the lib, like automatic
 * downloading of transactions from the payment device (if required) and synchronizing them with
 * the server.
 *
 * If you are not sure if you require this feature, leave it disabled. Temporary connection
 * issues are handled by the lib without the enabling of offline transaction handling. This
 * functionality is used only in situations where the payments are always made while offline.
 *
 * Default: NO
 */
@property (nonatomic, assign) BOOL offlineTransactionHandlingEnabled;

/**
 * The current state of the offline transaction synchronizer. This is part of the Offline
 * Transaction Handling mechanism, which can be enabled using `offlineTransactionHandlingEnabled`.
 */
@property (nonatomic, readonly) ADYServerSynchronizerState offlineSynchronizationState;

/**
 * The date when the last offline transaction synchronization was successfully completed.
 * This is part of the Offline Transaction Handling mechanism, which can be enabled
 * using `offlineTransactionHandlingEnabled`.
 */
@property (nonatomic, readonly) NSDate* lastOfflineSynchronizationComplete;

/**
 A list of supported currencies with their corresponding details, bundled in ADYCurrency objects,
 sorted by their abbreviation.

 The Merchant account has been configured to support currencies that have been configured during the
 boarding process. These currencies can be viewed in the Adyen back office under the settings of
 the merchant code.

 This method returns the same currencies as `getCurrencies` but returns ADYCurrency objects instead
 of the plain NSString abbreviation (EUR, USD) of the currencies.
 */
@property (readonly) NSArray* currenciesWithDetails;

/**-------------------------------------------------------------------------------------------------
 * @name Initialization
 *--------------------------------------------------------------------------------------------------
 */

/**
 * Initialize the library with a custom options.
 * Calling this method is optional and needed only in case of changing the default library behaviour.
 */
+(void)initializeWithOptions:(NSDictionary *)options;

/// Option to set custom Bluetooth accessory protocol string. Example: `com.merchant.bt`
extern NSString* const ADYOptionBluetoothAccessoryProtocol;

/**-------------------------------------------------------------------------------------------------
 * @name Obtaining an instance
 *--------------------------------------------------------------------------------------------------
 */

/**
 * Obtains an instance of the Adyen class. This is a singleton instance, so there will only ever be one.
 * Calling this method is low-overhead, so you can safely call it multiple times in your app.
 */
+(Adyen*)sharedInstance;

#pragma mark - Register App methods

/**-------------------------------------------------------------------------------------------------
 * @name App Registration
 *--------------------------------------------------------------------------------------------------
 */

/**
 * Register the app for use by the given `merchantAccount`, `username`, and `password`.
 *
 * @deprecated Use `loginWithMerchantCode:withUsername:withPassword:andDelegate:` instead.
 */
- (void)loginWithMerchantCode:(NSString *)merchantCode
                 withUsername:(NSString *)username
                 withPassword:(NSString *)password
                andCompletion:(void(^)(NSError*))completionBlock __attribute__ ((deprecated));

/**
 * Register the app for use by the given `merchantAccount`, `username`, and `password`. 
 *
 * Logging in is only possible when the current `loginStatus` is equal to `ADYLoginStatusLoggedOut`.
 * Attempting to log in with a different status will lead to the delegate to be called with an error.
 *
 * Logging in can take quite a while - in extreme cases, as much as two minutes. Therefore, the caller
 * is to provide a delegate which will be called periodically to be kept informed about the progress,
 * thus enable the user interface to show some sort of progress-view.
 *
 * This method returns immediately, the login process will continue in the background.
 *
 * Note that logging in does _not_ have to take place each time the app starts up. After logging
 * in successfully, the library will save the state, and logging in again is only necessary
 * (and possible) after an explicit call to `logoutWithCompletion:`.
 *
 * @param merchantCode merchant-code as supplied by Adyen.
 * @param username username as supplied by Adyen.
 * @param password password as supplied by Adyen.
 * @param delegate caller-supplied delegate which will be kept informed about the
 * login process' progress, and outcome.
 */
- (void)loginWithMerchantCode:(NSString *)merchantCode
                 withUsername:(NSString *)username
                 withPassword:(NSString *)password
                  andDelegate:(id<ADYLoginDelegate>)delegate;

/** Unregister the App
 
 When the App is registered, it is registered for the merchant account that has been used to 
 register it. There might be situations where one wants to switch the App from one merchant code to
 another merchant code. This will mainly be applicable for integrators and not for merchants.
 
 If a switch from one merchant account to another is required, this logout method can be used to do
 so. In this case, also the settings need to be deleted from the payment device, since it will need
 to be re-boarded and the payment device needs to be released from the previous merchant account,
 using the Terminal Fleet Management functionality in the Adyen system.
 
 To delete settings from the payment device, use key "9", hold it for 10 seconds and release it. 
 In the menu that will appear, there is an option to delete settings. The password required to
 access the menu can be obtained from Adyen Support.
 
 @param none
 @deprecated Use logoutWithCompletion: instead.
 @return void
 */
- (void)logout __attribute__ ((deprecated));

/**
 * Unregisters the app. This happens asynchronously - if the library is processing a transaction,
 * this transaction is finished first before the actual logout is done. 
 * @param completion block called when logout is complete.
 */
- (void)logoutWithCompletion:(void(^)(NSError* error))completion;

/** Retrieve the data that identifies the iOS device and the App
 *
 * The data available via this method is:
 *    - the iOS device platform
 *    - the iOS device name
 *    - the iOS device version
 *    - the application name
 *    - the version of the Adyen library
 *
 * @return an ADYAppData object containing the mentioned data elements
 */
- (ADYAppData*)getAppData;

#pragma mark - Transaction Processing Configuration

/**-------------------------------------------------------------------------------------------------
 * @name Transaction Processing Configuration
 *  ------------------------------------------------------------------------------------------------
 */

/**
 Get a list of supported currencies.
 
 The merchant account has been configured to support certain currencies. These currencies can be viewed
 in the Adyen back office under the settings of the merchant code.
 
 See also the `currenciesWithDetails` property for more details about these currencies.
 
 @param none
 @return An array of NSString objects, containing the supported ISO 4217 Currency codes, like "EUR"
 */
- (NSArray *)getCurrencies;


/*
 Searches for the currency with the provided abbreviation and returns its details if found.

 @param the abbreviation (ISO 4217 Currency code) to find the corresponding currency details for (EUR, USD, etc)
 @return the `ADYCurrency` object containing the details for `abbr` or nil if no currency was found
 */
- (ADYCurrency *)currencyForAbbreviation:(NSString *)abbr;


/** Get a list of supported Payment Methods.
 
 The payment device has been configured to support payment methods that have been configured during the
 boarding process. These payment methods can be viewed in the Adyen back office under the settings of
 the merchant code under which the payment device has been configured.
 
 By calling this method, the App is being informed of these payment methods.
 
 @param none
 @return An array of NSString objects, containing the supported payment methods, like "visa" or "mc"
 */
- (NSArray *)getSupportedPaymentMethods;

/**
 Define whether the library should store every transaction within its database or not.
 Its default value is YES.
 
 @param yesOrNo Whether every transaction is stored within the library database or not.
 */
- (void)setShouldStoreTransactionsInDatabase:(BOOL)yesOrNo;

#pragma mark - Transaction Processing

/**-------------------------------------------------------------------------------------------------
 * @name Transaction Processing
 *  ------------------------------------------------------------------------------------------------
 */

/**
 * Send a request to refund the given amount from the given transaction.
 *
 * The response from the server can't indicate if the refund was performed or not, only if the refund
 * -request- was successfully received. The reason for this, is that the refund modification request
 * is added to a queue for processing at a later time. Therefor the webservice can't respond with
 * any more info than 'request received'.
 *
 * However, once the request was successfull, if the pspReference of
 * the original transaction is valid and the transaction was not already refunded, the refund will
 * always succeed.
 *
 * If there is currently no internet connection or the first attempt to make the request fails, the
 * system will store the request and try to send it to the backend at a later time. If this is the case,
 * the `refundState` will be ADYProcessingStateReversalPending. When something went severely wrong,
 * the `refundState` will be ADYProcessingStateReversalError and the error will be attached.
 * If all went well, ADYProcessingStateProcessed is returned.
 *
 * When the transactions are retrieved and their refunds are examined, each refund will have a processingState
 * to indicate the progress of the refund-request. It can be one of pending, reversed (refunded) or error.
 * This can be used to inform the user of the status of the refund.
 *
 * @deprecated use ADYRefundRequest instead
 */
- (void)requestRefundForTransaction:(ADYTransactionData *)transaction
                       refundAmount:(NSNumber *)amount
                          reference:(NSString *)reference
                       onCompletion:(void (^)(ADYProcessingState refundState, NSError *error))completion;


/**
* Sometimes a transaction will be declined by the card issuer because they want the card holder
* to contact them by phone to discuss the transaction. This case is called a `REFERRAL`. If the issuer
* and the card holder come to the conclusion that the transaction can be approved, the issuer will
* give the card holder a authorisation code.
*
* That code can be submitted to Adyen using this function. On completion it will return whether or not
* the code was accepted. If the code is authorised, the transaction will be completed and no longer DECLINED.
* The status will be updated accordingly in the database.
*
* Use `needsReferralAuthorisation` on `ADYTransactionData` to check if that transaction is waiting for an authorisation code.
*/
- (void)authoriseTransaction:(ADYTransactionData *)transaction withCode:(NSString *)authCode completion:(void (^)(BOOL authorised, NSError *error))completion;


#pragma mark - Transaction Retrieval

/**-------------------------------------------------------------------------------------------------
 * @name Transaction Retrieval
 *  ------------------------------------------------------------------------------------------------
 */

/**
 Get a list of all previously processed payments for the `activeMerchantCode`.
 
 @return A list of previously processed payments as ADYTransactionData objects or nil if
         not logged in.
 */
- (NSArray *)getTransactions;

/**
 Get a list of all previously processed payments for the `activeMerchantCode` that match the
 given search string.

 @return A list of previously processed payments as ADYTransactionData objects or nil if
         not logged in.
 */
- (NSArray *)getTransactionsWithSearch:(NSString *)search;

/**
 Get a transaction (for the `activeMerchantCode`) associated with a given merchant reference.
 
 @param merchantReference the requested merchant reference.
 @return An ADYTransactionData associated with the given merchant reference or nil if
         not logged in.
 @deprecated Use getTransactionsWithSearch: instead.
 */
- (ADYTransactionData *)getTransactionWithReference:(NSString *)merchantReference;

/**
 The number of transactions for the `activeMerchantCode` associated with a given search string.
 
 @param search the requested search string or nil for all transactions.
 @return The number of transactions in the internal database associated with the given search string or zero if
         not logged in.
 */
- (NSUInteger)numberOfTransactionsInSearch:(NSString *)search;

/**
 Get a transaction (for the `activeMerchantCode`) from an internal array of transactions that response to a given search string.

 @param row zero-based position in an internal array.
 @param search a search string or nil to query all transactions.
 @return A transaction associated with the given search string or nil if not logged in.
 */
- (ADYTransactionData *)getTransactionAtRow:(NSUInteger)row andSearch:(NSString *)search;

/**
 Get a unique transaction by its PSP reference (for the `activeMerchantCode`).

 @param pspRef The unique PSP reference of the transaction
 @return The transaction identified by the PSP reference or nil if none are in the local DB for the active merchant.
 */
- (ADYTransactionData *)getTransaction:(NSString *)pspRef;

#pragma mark - Logging

/**
 * @name Logging
 */

/**
 * Sends a crash report to the Adyen logging servers.
 *
 * A crash report is, as the name suggest, a report with details about an
 * app crash. It is _not_ for generic error reporting. Such a report can
 * easily be created using tools like `PLCrashReporter` and/or `Quincy`'s
 * `BWCrashReportTextFormatter`.
 *
 * A log of the internal `AdyenToolkit` processes will be appended and the
 * whole will be logged as an app crash on the Adyen logging servers for
 * debugging purposes.
 */
- (void)sendCrashReport:(NSString *)crashReport;

/**
 * @name Offline synchronization
 */

- (NSArray *)pendingOfflineItemIds;

-(BOOL)hasPendingOfflineItems;

-(NSDate*)getOldestNewOfflineItemCreation;

-(NSDate*)getOldestRetryableOfflineItemSubmission;

@end
