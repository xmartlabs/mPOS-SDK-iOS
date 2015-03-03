//
//  ADYTransactionData.h
//  AdyenPOSLib
//
//  Created by Jeroen Koops on 4/23/13.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "ADYConstants.h"

@class ADYReceipt;
@class ADYDeviceData;
@class CLLocation;

// deprecated, definition at end of file
@class ADYCancelInfo;
@class ADYDeclineInfo;
/////


static NSString *ADYTransactionFailureDomain = @"TransactionFailureDomain";


typedef NS_ENUM(NSInteger, ADYTransactionFailureCode) {

    ADYTransactionFailureCodeUnknown                = 40000,

    ADYTransactionFailureCodeInitializationError    = 40001,

    // cancel
    ADYTransactionFailureCodeCardRemoved            = 40002,
    ADYTransactionFailureCodeShopperCancelled       = 40003,
    ADYTransactionFailureCodeMerchantCancelled      = 40004,

    // error
    ADYTransactionFailureCodeTechnicalProblem       = 40005,
    ADYTransactionFailureCodeFailedToPrintReceipt   = 40006,
    ADYTransactionFailureCodeCardReadFailed         = 40007,
    ADYTransactionFailureCodeConnectionLost         = 40008,

    //decline
    ADYTransactionFailureCodeCardDeclined           = 40009,
    ADYTransactionFailureCodeRequestReferral        = 40010,
    ADYTransactionFailureCodeInsufficientFunds      = 40011,
    ADYTransactionFailureCodePinDeclined            = 40012

};


/**
 * Data made available about a transaction when it is complete.
 * Inspect the `finalState` property to see if the transaction succeeded or not. 
 */
@interface ADYTransactionData : NSObject

@property (nonatomic, strong) NSString* mid;
@property (nonatomic, strong) NSString* tid;
@property (nonatomic, strong) NSString* posEntryMode;
@property (nonatomic, strong) NSString* txRef;
@property (nonatomic, strong) NSString* tenderReference;
@property (nonatomic, strong) NSString* shopperReference;
@property (nonatomic, strong) NSString* shopperEmail;
@property (nonatomic, assign) ADYTransactionType transactionType;

@property (nonatomic, strong) NSNumber* amountValue;                // originalAmount
@property (nonatomic, strong) NSString* amountCurrency;             // originalAmountCurrency
@property (nonatomic, strong) NSNumber* adjustedAmountValue;        // usually a discount (negative) amount for loyalty programs etc (added to amountValue)
@property (nonatomic, strong) NSString* adjustedAmountCurrency;
@property (nonatomic, strong) NSNumber* gratuityAmountValue;        // the amount given as gratuity (added to amountValue)
@property (nonatomic, strong) NSString* gratuityAmountCurrency;
@property (nonatomic, strong) NSNumber* additionalAmountValue;      // the sum of adjustedAmount and gratuityAmount
@property (nonatomic, strong) NSString* additionalAmountCurrency;
@property (nonatomic, strong) NSNumber* authAmountValue;            // the amount that was authorised by Adyen, can be converted to different currency (dcc)
@property (nonatomic, strong) NSString* authAmountCurrency;         // can be in a different currency than amountCurrency due to dcc

@property (nonatomic, readonly) NSNumber* finalAmountValue;         // final amount of transaction for the merchant, including gratuity etc
@property (nonatomic, readonly) NSString* finalAmountCurrency;      // final amount currency for the merchant (same as amountCurrency)

@property (nonatomic, strong) NSString* aidCode;
@property (nonatomic, strong) NSString* applicationPreferredName;
@property (nonatomic, strong) NSString* merchantReference;
@property (nonatomic, strong) NSNumber* taxPercentage;
@property (nonatomic, strong) NSString* cardType;
@property (nonatomic, strong) NSString* cardNumber;
@property (nonatomic, strong) NSString* cardSeq;
@property (nonatomic, strong) NSString* cardHolderName;
@property (nonatomic, strong) NSString* cardExpiryYear;
@property (nonatomic, strong) NSString* cardExpiryMonth;
@property (nonatomic, strong) NSString* cardEffectiveYear;
@property (nonatomic, strong) NSString* cardEffectiveMonth;
@property (nonatomic, strong) NSString* paymentVerificationData;
@property (nonatomic, strong) NSString* issuerCountry;
@property (nonatomic, strong) NSString* cardBin;
@property (nonatomic, strong) NSString* applicationLabel;
@property (nonatomic, strong) NSString* cardHolderVerificationMethodResults;
@property (nonatomic, strong) NSString* txDate;
@property (nonatomic, strong) NSString* txTime;

/**
 * The scheme of the card used.
 * This can be one of:
 *
 * - `ADYCardSchemeError`
 * - `ADYCardSchemeVisaVisa`
 * - `ADYCardSchemeVisaElectron`
 * - `ADYCardSchemeVisaVPay`
 * - `ADYCardSchemeVisaPlus`
 * - `ADYCardSchemeVisaDankort`
 * - `ADYCardSchemeMasterCardDebit`
 * - `ADYCardSchemeMasterCardMaestro`
 * - `ADYCardSchemeMasterCardMaestroUK`
 * - `ADYCardSchemeMasterCardMasterCard`
 * - `ADYCardSchemeAmericanExpress`
 * - `ADYCardSchemeJCB`
 * - `ADYCardSchemeDinersClub`
 * - `ADYCardSchemeDankort`
 * - `ADYCardSchemeDiscover`
 * - `ADYCardSchemeLaser`
 * - `ADYCardSchemeBCMC`
 * - `ADYCardSchemeSolo`
 * - `ADYCardSchemeBijenkorf`
 */
@property (nonatomic, assign) ADYCardScheme cardScheme;

/**
 * Human-readable form of the `cardScheme` property.
 */
@property (readonly) NSString* cardString;

/**
 * Indicates if the card was inserted into the payment device, meaning it would have to be removed
 * when the transaction is finished. It can be used to check if a "please remove card" notification
 * should be shown.
 */
@property (readonly) BOOL cardNeedsToBeRemovedAfterTransaction;

/**
 * The final state of the transaction. 
 * This can be one of:
 *
 * - `ADYFinalTenderStateNotFinal`: transaction has not reached a final state yet
 * - `ADYFinalTenderStateApproved`: the payment was approved
 * - `ADYFinalTenderStateDeclined`: the payment was declined. More info is available
 * in the `declineInfo` property.
 * - `ADYFinalTenderStateCancelled`: the payment was cancelled. More info is available
 * in the `cancelInfo` property.
 * - `ADYFinalTenderStateError`: there was an error. More info is available in the
 * `errorInfo` property.
 */
@property (nonatomic, assign) ADYFinalTenderState finalState;

/** Provides a human-readable version of the `finalState` property. */
@property (nonatomic, assign) NSString* finalStateString;

/** Indicates the current state of processing of this transaction. It could be in progress, processed, being reversed, etc */
@property (nonatomic, assign) ADYProcessingState processingState;

@property (nonatomic, strong) NSString* pspAuthCode;
@property (nonatomic, strong) NSString* pspReference;

@property (nonatomic, strong) NSDate* dateSubmitted;

@property (nonatomic, strong) NSString* terminalId;
@property (nonatomic, strong) NSString* signatureData;
@property (nonatomic, strong) CLLocation* location;


/**
 * If the transaction did not end in final state APPROVED, the abstract reason of failure can be found here.
 * The raw and more detailed reason can be found in the `rawFailureReason` property.
 */
@property (nonatomic, assign) ADYTransactionFailureCode failureReasonCode;

/**
 * If the transaction did not end in final state APPROVED, this will hold the raw failure reason code and
 * message from the payment device or the reason the payment device could not start a transaction.
 * This code and/or message should be reported to Adyen when asking for support.
 */
@property (nonatomic, strong) NSError *rawFailureReason;

/**
 * Sometimes a transaction will be declined by the card issuer because they want the card holder
 * to contact them by phone to discuss the transaction. This case is called a `REFERRAL`. If the issuer
 * and the card holder come to the conclusion that the transaction can be approved, the issuer will
 * give the card holder a authorisation code.
 *
 * This property indicates that the transaction needs a referral authorisation code before it will be
 * approved. The code can be sent using the `authoriseWithCode:` function.
 */
@property (readonly) BOOL needsReferralAuthorisation;

/**
 * The logo to be used on the receipt (provided in the `ADYTransactionRequest`)
 */
@property (nonatomic, strong) NSString* logoReceipt;
@property (nonatomic, readonly) UIImage* logoImage; // logoReceipt converted to an UImage (base64 decode)


/**
 * All details of the device used for this transaction as it was when the transaction
 * was performed. The up-to-date information can be retrieved by examining the
 * `deviceData` property of the `ADYDevice` used to initiate the `ADYTransactionRequest`.
 *
 * This property will only be set at the end of a transaction. It is not persisted and
 * won't show up if the transaction is fetched at a later time.
 */
@property (nonatomic, copy) ADYDeviceData *deviceData;

/**
 * The refunds that were completed for this transaction, encapsulated by ADYRefundData
 * objects. The sum of all refunds can never be more than the original transaction amount.
 */
@property (nonatomic, strong) NSArray *refunds;

/**
 * The number of receipts in this transaction.
 */
@property (readonly) NSUInteger receiptCount;

/**
 * Returns the receipt of the indicated type at the indicated index.
 * @param receiptIndex An integer greater than or equal to 0, and
 * smaller than `receiptCount`.
 * @param receiptType Use `ADYReceiptTypeMerchant` to get the merchant copy,
 * or `ADYReceiptTypeCardholder` to get the cardholder copy.
 */
- (ADYReceipt *)getReceiptForIndex:(NSUInteger)receiptIndex
                           andType:(ADYReceiptType)receiptType;

@property (nonatomic, strong) NSMutableArray *cardHolderReceipts;


////////////////////////////

/**
 * Only set in case `finalState` is `ADYFinalTenderStateCancelled`; provides
 * the reason for cancellation.
 *
 * @deprecated
 */
@property (nonatomic, strong) ADYCancelInfo* cancelInfo;

/**
 * Only set in case `finalState` is `ADYFinalTenderStateDeclined`; provides
 * the reason the transaction was declined.
 *
 * @deprecated
 */
@property (nonatomic, strong) ADYDeclineInfo* declineInfo;

/**
 * Only set in case `finalState` is `ADYFinalTenderStateError`; provides additional
 * info about the error that occurred. The error-code is one of the codes
 * of the `Adyen` error-domain (which can be found in the reference of the `Adyen` class).
 *
 * @deprecated
 */
@property (nonatomic, strong) NSError* errorInfo;

@end













#pragma mark - DEPRECATED

typedef enum {
    ADYCancelCodeShopperCancelledAppSelection = 30000,
    ADYCancelCodeShopperCancelledDuringPINEntry = 30001,
    ADYCancelCodeMerchantCancelled = 30002,
    ADYCancelCodeDeviceTimedOutCardEntry = 30003,
    ADYCancelCodeFailedToPrintReceipt = 30004,
    ADYCancelCodeMerchantDisapprovedSignature = 30005,
    ADYCancelCodeCardRemoved = 30006,
    ADYCancelCodeShopperCancelledTransaction = 30007,
    ADYCancelCodeEmvError = 30008,
    ADYCancelCodeSapiError = 30009,
    ADYCancelCodeFailedToRetrieveAdditionalData = 30010,
    ADYCancelCodeUnknown = 30999
} ADYCancelCode;

/**
 * Class for objects providing information about the reason
 * a transaction was cancelled.
 */
@interface ADYCancelInfo : NSObject

/**
 * A code identifying the reason for cancellation.
 *
 * Possible values are:
 *
 * - `ADYCancelCodeShopperCancelledAppSelection` (30000): The shopper cancelled
 * the transaction while app selection was performed by the terminal.
 * - `ADYCancelCodeShopperCancelledDuringPINEntry` (30001): The shopper cancelled
 * the transaction when he was requested to enter his pincode.
 * - `ADYCancelCodeMerchantCancelled` (30002): The transaction was cancelled by the
 * merchant.
 * - `ADYCancelCodeDeviceTimedOutCardEntry` (30003): The shopper did not insert a
 * card in time.
 * - `ADYCancelCodeFailedToPrintReceipt` (30004): The receipt for the transaction
 * could not be printed.
 * - `ADYCancelCodeMerchantDisapprovedSignature` (30005): The merchant did not
 * approve the signature of the shopper.
 * - `ADYCancelCodeCardRemoved` (30006): The card was removed before the transaction
 * could be completed.
 * - `ADYCancelCodeShopperCancelledTransaction` (30007): The shopper cancelled the
 * transaction by pressing the cancel button.
 * - `ADYCancelCodeEmvError` (30008): An error occured while communicating with the
 * EMV payment device.
 * - `ADYCancelCodeSapiError` (30009): SAPI error.
 * - `ADYCancelCodeFailedToRetrieveAdditionalData` (30010): The additional data
 * for this transaction could not be retrieved.
 * - `ADYCancelCodeUnknown` (30999): Unknown cancellation reason.
 */
@property (nonatomic, readonly) ADYCancelCode code;

/**
 * Human-readable message containing the reason for cancellation.
 */
@property (readonly) NSString* message;

-(id)initWithCode:(ADYCancelCode)code;

- (id)initWithUnknownReason:(NSString *)unknownReason;
@end

typedef enum {
    ADYDeclineCodePSPCouldNotDetermineVariant = 31000,
    ADYDeclineCodePSPDoesNotSupportPaymentDetails = 31001,
    ADYDeclineCodeDeviceSignatureFailed = 31002,
    ADYDeclineCodeAcquirerDeclined = 31003,
    ADYDeclineCodeAcquirerReferral = 31004,
    ADYDeclineCodeAcquirerError = 31005,
    ADYDeclineCodeAcquirerBlockCard = 31006,
    ADYDeclineCodeAcquirerCardExpired = 31007,
    ADYDeclineCodeAcquirerInvalidAmount = 31008,
    ADYDeclineCodeAcquirerInvalidCard = 31009,
    ADYDeclineCodeAcquirerIssuerUnavailable = 31010,
    ADYDeclineCodeAcquirerNotSupported = 31011,
//    ADYDeclineCodeAcquirerNot3DAuthenticated = 31012,
            ADYDeclineCodeAcquirerNotEnoughBalance = 31013,
    ADYDeclineCodeAcquirerPending = 31014,
    ADYDeclineCodeAcquirerFraud = 31015,
    ADYDeclineCodeAcquirerCancelled = 31016,
    ADYDeclineCodeAcquirerShopperCancelled = 31017,
    ADYDeclineCodeAcquirerInvalidPin = 31018,
    ADYDeclineCodeAcquirerPinTriesExceeded = 31019,
    ADYDeclineCodeAcquirerPinValidationNotPossible = 31020,
    ADYDeclineCodeNotAllowed = 31021,
    ADYDeclineCodeCardRemoved = 31022,
    ADYDeclineCodeUnknown = 31999
} ADYDeclineCode;

/**
 * Class for objects containing information about the reason
 * a transaction was declined.
 */
@interface ADYDeclineInfo : NSObject

/**
 * Code indicating the reason a transaction was declined.
 *
 * Possible values are:
 *
 * - `ADYDeclineCodePSPCouldNotDetermineVariant` (31000): PSP could not determine variant
 * - `ADYDeclineCodePSPDoesNotSupportPaymentDetails` (31001): PSP does not support payment method (card not supported)
 * - `ADYDeclineCodeDeviceSignatureFailed` (31002): Signature was not approved
 * - `ADYDeclineCodeAcquirerDeclined` (31003): Acquirer declined transaction
 * - `ADYDeclineCodeAcquirerReferral` (31004): Merchant should contact acquirer
 * - `ADYDeclineCodeAcquirerError` (31005): Acquirer error
 * - `ADYDeclineCodeAcquirerBlockCard` (31006): Card is blocked
 * - `ADYDeclineCodeAcquirerCardExpired` (31007): Card is expired
 * - `ADYDeclineCodeAcquirerInvalidAmount` (31008): ADYAmount is invalid
 * - `ADYDeclineCodeAcquirerInvalidCard` (31009): Card is invalid
 * - `ADYDeclineCodeAcquirerIssuerUnavailable` (31010): Issuer is unavailable
 * - `ADYDeclineCodeAcquirerNotSupported` (31011):  Acquirer is not supported
 * - `ADYDeclineCodeAcquirerNot3DAuthenticated` (31012): No 3D authentication was performed
 * - `ADYDeclineCodeAcquirerNotEnoughBalance` (31013): Not enough balance on card
 * - `ADYDeclineCodeAcquirerPending` (31014): Pending
 * - `ADYDeclineCodeAcquirerFraud` (31015): Fraud
 * - `ADYDeclineCodeAcquirerCancelled` (31016): Cancelled
 * - `ADYDeclineCodeAcquirerShopperCancelled` (31017): Shopper cancelled
 * - `ADYDeclineCodeAcquirerInvalidPin` (31018): Invalid PIN
 * - `ADYDeclineCodeAcquirerPinTriesExceeded` (31019): Number of PIN attempts exceeded
 * - `ADYDeclineCodeAcquirerPinValidationNotPossible` (31020): Pin validation not possible
 * - `ADYDeclineCodeUnknown` (31999): Unknown decline reason
 */
@property (nonatomic, readonly) ADYDeclineCode code;

/**
 * Human-readable message containing the reason for declination.
 */
@property (readonly) NSString* message;

-(id)initWithCode:(ADYDeclineCode)code;

-(id)initWithUnknownReason:(NSString *)unknownReason;
@end
