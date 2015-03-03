//
//  ADYTransactionProcessorDelegate.h
//  AdyenPOSLib
//
//  Created by Jeroen Koops on 4/11/13.
//
//

#import "ADYConstants.h"  

@class ADYSignatureRequest;
@class ADYAdditionalDataRequest;
@class ADYPrintReceiptRequest;
@class ADYTransactionData;
@class ADYDynamicCurrencyConversionData;

typedef enum {
    ADYCardStatusCardRemoved,
    ADYCardStatusNextTransaction,
    ADYCardStatusError,
    ADYCardStatusNotSupported
} ADYCardStatus;

/**
 * Delegate used to receive updates about a transaction's progress and completion.
 */
@protocol ADYTransactionProcessorDelegate

/** @name Transaction completion */

/**
 * This method is called when the transaction completes successfully. 
 *
 * Successful completion does *not* necessarily mean that a payment has been made - 
 * the transaction may also have been declined or cancelled. This can be determined
 * by examining the given `transaction`'s `status`.
 *
 * After this method has been called, no other methods on the delegate will be called.
 * @param transaction a data-object containing transaction-details.
 */
-(void)transactionComplete:(ADYTransactionData*)transaction;

/** @name Transaction-processing callbacks */

/**
 * Called when a signature must be confirmed as part of processing a transaction.
 *
 * After this method has been called, transaction-processing will be paused until
 * either `submitConfirmedSignature:` or `submitUnconfirmedSignature:` has been called
 * on the given `signatureRequest`.
 *
 * This method must be implemented in two different ways, depending on the presence
 * of a printer on the payment-device (as determined by the `paymentDeviceHasPrinter`
 * method on the Adyen class).
 *
 * If the device has a printer, it will first print a receipt, which must be signed 
 * by the customer. The attendant will then compare this signature to the signature on
 * the card, and either confirm that they are identical, or not. This method must be 
 * implemented to show a user-interface where the attendant can choose between
 * "Confirmed" or "Not confirmed", for example by pressing a button. Subsequently,
 * the method must call either `submitConfirmedSignature:` or `submitUnconfirmedSignature:`
 * on the `signatureRequest`, both with `nil` as the `signatureImage` parameter, to
 * continue transaction processing.
 *
 * If the device does not have a printer, this method must be implemented to display 
 * a user-interface on which the customer can draw a signature. The attendant must
 * then have the choice to either confirm, or not, the drawn signature after comparing
 * it to the signature on the card - for example,
 * by pressing a button. Subsequently, the method must call either `submitConfirmedSignature:`
 * or `submitUnconfirmedSignature:` on the given `signatureRequest`, both with the drawn 
 * image as `signatureImage` parameter.
 *
 * Note that, instead of calling `submitConfirmedSignature:` or `submitUnconfirmedSignature:`,
 * it is also possible to cancel the transaction at this point as usual, by 
 * calling `[ADYTransactionRequest requestCancel]`.
 * After a transaction has been cancelled, subsequent calls to `submitConfirmedSignature:` 
 * or `submitUnconfirmedSignature:` will have no effect.
 *
 * @param signatureRequest Request-object used to continue transaction processing.
 */
 
-(void)transactionRequiresSignature:(ADYSignatureRequest*)signatureRequest;

/**
 * Called when a transaction provides additional data, for example loyalty-related data,
 * providing the app with an opportunity to modify the amount charged based on that data.
 *
 * After this method has been called, transaction-processing will be paused until
 * `continueWithUpdatedAmount:` is called on the given `additionalDataRequest`, either
 * with an `NSNumber` to update the amount, or with `nil` to continue with the original
 * amount.
 *
 * Note that, instead of calling `continueWithUpdatedAmount`, it it also possible
 * to cancel the transaction at this point as usual, by calling `[ADYTransactionRequest requestCancel]`.
 * After the transaction has been cancelled, subsequent calls to `continueWithUpdatedAmount:`
 * will have no effect.
 *
 * @param additionalDataRequest object containing the additional data, and methods to 
 * continue transaction-processing.
 */

-(void)transactionProvidesAdditionalData:(ADYAdditionalDataRequest*)additionalDataRequest;

/**
 * Called when a receipt must be printed out by the app.
 *
 * After this method has been called, transaction-processing will be paused until
 * `confirmReceiptPrinted:` is called on the given `printReceiptRequest`.
 *
 * This method must be implemented to print a receipt on paper, based on the data
 * provided in the `printReceiptRequest`.
 *
 * Note that, instead of calling `[ADYPrintReceiptRequest confirmReceiptPrinted:]`, it
 * is also possible to cancel the transaction at this point by calling 
 * `[ADYTransactionRequest requestCancel]`. If this is done, do not call `confirmReceiptPrinted:`
 * anymore. However, it is possible that `transactionRequiresPrintedReceipt:` will be called
 * a second time as part of the transaction-flow. If that happens, and it is not desirable to
 * print out a receipt at that time, cancel the transaction again.
 *
 *
 * @param printReceiptRequest object containing receipt-data, and methods to continue
 * transaction-processing.
 */
-(void)transactionRequiresPrintedReceipt:(ADYPrintReceiptRequest*)printReceiptRequest;


/**
 * The payment device found it possible to allow the shopper to pay in their own currency
 * using Direct Currency Conversion. The payment device is currently displaying this
 * option to the shopper. This call is only informative, the shopper has to decide.
 *
 * @param data The details of the DCC option.
 */
- (void)transactionSuggestsDcc:(ADYDynamicCurrencyConversionData *)data;

/**
 * The shopper has entered a gratuity on the payment device. This can only occur if the
 * `ADYTransactionOptionAskGratuity' option was passed to the ADYTransactionRequest.
 * Setting this option triggers the payment device to ask the shopper if they would like
 * to give a gratuity (tip) to the merchant.
 *
 * @param gratuityAmountMinorUnits The amount of gratuity given in minor units. The currency
 * is the same as the transaction.
 */
- (void)transactionGratuityEntered:(int)gratuityAmountMinorUnits;

/** @name Transaction progress */

/**
 * Called when the state of the transaction changes.
 *
 * This method can be used to reflect the progress in the user-interface.
 *
 * @param state the new transaction-processing state.
 */
-(void)transactionStateChanged:(ADYTenderState)state;

/**
 * Indicates that an application has been selected by the user.
 * In payment terms, an application is a manner to make a payment -
 * for example, one single card can allow for both Maestro and Mastercard
 * payments. After the card has been inserted, the cardholder will be prompted
 * by the terminal to select one of the supported applications. After
 * he's made his choice, the `transactionApplicationSelected:` callback will
 * be called, with the name of the selected application as argument.
 *
 * @note Application selection events are only supported on terminals with firmware
 * version p30 or greater.
 */
-(void)transactionApplicationSelected:(NSString*)application;

/**
 * Indicates that one digit of a pincode has been entered. The total number
 * of digits entered so far is passed as an argument.
 *
 * Note that there's no way to know in advance of how many digits the pincode
 * exists - it may be 4, 5, or 6 digits, or even more. However, before the
 * the pincode is entered, `transactionStatChanged:` will be called with
 * a `state` of `ADYTenderStateWaitingForPin`, and after the pincode has been 
 * completed, it will be called again with a state of `ADYTenderStatePinEntered`.
 *
 * Note also backspaces entered by the user while entering the pincode are not 
 * transmitted. This means that if the user enters two digits, then presses 
 * backspace, then enters another digits, `transactionPinDigitEntered:` will
 * be called three times: the first time with an argument of `1`, then with
 * an argument of `2`, and finally again with an argument of `2`.
 *
 * @note PIN entry events are only supported on terminals with firmware
 * version p30 or greater.
 */
-(void)transactionPinDigitEntered:(NSUInteger)numberOfDigitsEntered;

/**
 * After the transaction has finished, indicates whether the card 
 * was removed. 
 * This option is only supported by certain terminal firmware versions.
 * Possible values of the `status` are:
 * 
 * - `ADYCardStatusRemoved`: the card has been removed from the terminal.
 * - `ADYCardStatusNextTransaction`: a subsequent transaction was started 
 * on the terminal before the card was removed. 
 * - `ADYCardStatusError`: an error occurred communicating with the terminal
 * before the card was removed.
 * - `ADYCardStatusNotSupported`: card removal notification is not supported 
 * by this version of the terminal firmware.
 */
-(void)transactionCardRemoved:(ADYCardStatus)status;

/**
 * If the connection with the payment device is lost during a transaction,
 * it is no longer possible for us to get the status or send commands. The
 * delegate will be notified of this situation through the
 * `transactionConnectionLost` and `transactionConnectionRestored` methods.
 * The `TransactionProcessor` will wait for the device to reconnect and try
 * to resume the transaction until a timeout occurs.
 *
 * While the connection is lost, no commands will be delivered to the device
 * and no state changes can take place. The delegate is therefor expected to
 * respect this state and block user interaction that would trigger status
 * changes for the transaction; example: submitting a signature.
 *
 * Cancelling the transaction will be instant while the connection is lost;
 * the device won't be updated and the transaction will simply be discarded.
 * Although the lib/iOS application can continue at this point, the device
 * may wait for a timeout on their side. Until that point, a new transaction
 * can not be started.
 */
-(void)transactionConnectionLost;

/**
 * If the connection with the payment device is lost during a transaction,
 * it is no longer possible for us to get the status or send commands. The
 * delegate will be notified of this situation through the
 * `transactionConnectionLost` and `transactionConnectionRestored` methods.
 * The `TransactionProcessor` will wait for the device to reconnect and try
 * to resume the transaction until a timeout occurs.
 *
 * While the connection is lost, no commands will be delivered to the device
 * and no state changes can take place. The delegate is therefor expected to
 * respect this state and block user interaction that would trigger status
 * changes for the transaction; example: submitting a signature.
 *
 * Cancelling the transaction will be instant while the connection is lost;
 * the device won't be updated and the transaction will simply be discarded.
 * Although the lib/iOS application can continue at this point, the device
 * may wait for a timeout on their side. Until that point, a new transaction
 * can not be started.
 */
-(void)transactionConnectionRestored;

@end
