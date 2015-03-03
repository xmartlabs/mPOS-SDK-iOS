//
//  ADYConstants.h
//  AdyenPOSLib
//
//  Created by Willem Lobbezoo on 13-04-13.
//
//

#ifndef AdyenPOSLib_ADYConstants_h
#define AdyenPOSLib_ADYConstants_h

/**-------------------------------------------------------------------------------------------------
 * @name Device Boarding States
 *  ------------------------------------------------------------------------------------------------
 */

/** **Boarding States**
 
 When a payment device is boarded, a process will take place, which will run fully automatic,
 but the App will be informed of state changes, so the GUI can be updated to teflect those state
 changes. The device boarding process contains five steps.
 
 The first step is to contact the payment device and ask it to identify itself. The payment device
 is identified by for instance brand, model, serial number, etc.
 
 - **ADYBoardingStateDeviceIdentification**
 - **ADYBoardingStateDeviceIdentified**
 - **ADYBoardingStateDeviceIdentificationFailed**
 
 The second step is to contact the Adyen system and let it know that a new payment device needs to
 be added to the collection of the payment devices owned by the merchant. These devices and their
 configuration can be viewed in the Adyen back office. The configuration can be changed there
 as well, and once done, it will automatically populate to the payment device.
 
 - **ADYBoardingStateDeviceRegistration**
 - **ADYBoardingStateDeviceRegistered**
 - **ADYBoardingStateDeviceRegistrationFailed**
 
 The third step is to load the configuration of the new payment device from the Adyen system,
 so it can be stored on the payment device.
 
 - **ADYBoardingStateDevicePSPSync**
 - **ADYBoardingStateDevicePSPSynced**
 - **ADYBoardingStateDevicePSPSyncFailed**
 
 The fourth step is to store the loaded configuration on to the payment device.
 
 - **ADYBoardingStateDeviceConfigurationSync**
 - **ADYBoardingStateDeviceConfigurationSynced**
 - **ADYBoardingStateDeviceConfigurationSyncFailed**
 
 The fifth step is to check if the payment device is successfully loaded and can be operated to
 perform transactions.
 
 - **ADYBoardingStateDeviceConfigurationCheck**
 - **ADYBoardingStateDeviceConfigurationChecked**
 - **ADYBoardingStateDeviceConfigurationCheckFailed**
 
 Each of these steps has three states, basically the step has started, the step has completed,
 the step failed. The values of the enum for each step are self explanatory.
 
 */
typedef enum {
    // step 1: identify payment device and get its credentials
    ADYBoardingStateDeviceIdentification,
    ADYBoardingStateDeviceIdentified,
    ADYBoardingStateDeviceIdentificationFailed,
    
    // step 2: register device with the Adyen system
    ADYBoardingStateDeviceRegistration,
    ADYBoardingStateDeviceRegistered,
    ADYBoardingStateDeviceRegistrationFailed,
    
    // step 3: load the payment device configuration from the Adyen system
    ADYBoardingStateDevicePSPSync,
    ADYBoardingStateDevicePSPSynced,
    ADYBoardingStateDevicePSPSyncFailed,
    
    // step 4: store the configuration on the payment device
    ADYBoardingStateDeviceConfigurationSync,
    ADYBoardingStateDeviceConfigurationSynced,
    ADYBoardingStateDeviceConfigurationSyncFailed,
    
    // step 5: check if the configuration has been stored on the payment device
    ADYBoardingStateDeviceConfigurationCheck,
    ADYBoardingStateDeviceConfigurationChecked,
    ADYBoardingStateDeviceConfigurationCheckFailed
} ADYBoardingState;

/**-------------------------------------------------------------------------------------------------
 * @name Transaction Options
 *  ------------------------------------------------------------------------------------------------
 */

/** **Transaction options**
 
 The following tender options may be specified in the options dictionary,
 which is used in the ADYTransactionRequest, which kicks off a new transaction:
 
 **ADYTransactionOptionReferenceKey**
 This defines the merchant reference of the transaction,
 which uniquely identifies the transaction for the merchant.

 **ADYTransactionOptionShopperReferenceKey**
 This defines the shopper reference, which uniquely identifies the
 shopper. It can be used for recurring transactions.
 
 **ADYTransactionOptionShopperEmailKey**
 This defines the shopper email address.
 It can be used for recurring transactions.
 
 **ADYTransactionOptionShopperRecurringContractKey**
 See the "Recurring Payment Manual", possible values
 
 ● ADYTransactionOptionShopperRecurringContractOneClick
 The shopper chooses whether to allow their credit card data to be stored for future use. The
 card's security code (CSC/CVC) must be provided during subsequent payments.
 
 ● ADYTransactionOptionShopperRecurringContractRecurring
 Credit card data is stored for future use. The card's security code (CSC/CVC) is not required
 for subsequent payments.
 
 ● ADYTransactionOptionShopperRecurringContractBoth
 Combination of the above

 **ADYTransactionOptionShopperRecurringDetailNameKey**
 Reserved for future use
 
 **ADYTransactionOptionLocationKey DEPRECATED**
 The location is determined by the lib itself.

 This is a CLLocation object that defines the geographical location of
 the place where the transaction took place.
 
 **ADYTransactionOptionLogoKey**
 This is a UIImage that will be used to display a logo on the receipt.
 
 **ADYTransactionOptionShopperLocaleKey**
 This is the shopper locale used during the transaction on the Shuttle.
 
 **ADYTransactionOptionAdditionalDataKey**
 true : an additional call will be made to the back end to connect to a merchant
        loyalty system and present data from that loyalty system at an early stage
        of transaction processing. The "TransactionProvidesAdditionalData" callback
        will be invoked in the ADYTransactionProcessorDelegate.
        The same functionality is used to provide a cardalias and will provide the
        Global Blue data.
 
 **ADYTransactionOptionAskGratuity**
 true : the Shuttle will ask for gratuity (tipping)
 
 **ADYTransactionOptionSetGratuity**
 Here the app can set the gratuity amount as an NSNumber in minor units
 
 **ADYTransactionOptionManualKeyedEntry**
 true: the Shuttle will ask for manually entering the card details
 
 **ADYTransactionOptionPaymentVerificationDataKey**
 possible value: "populate", this is used when the Shuttle is used via quick integration,
 via the HPP

 */

extern NSString * const ADYTransactionOptionReferenceKey;
extern NSString * const ADYTransactionOptionShopperReferenceKey;
extern NSString * const ADYTransactionOptionShopperEmailKey;
//extern NSString * const ADYTransactionOptionLocationKey; // deprecated, the location is determined by the lib itself
extern NSString * const ADYTransactionOptionLogoKey;
extern NSString * const ADYTransactionOptionShopperLocaleKey ;
extern NSString * const ADYTransactionOptionShopperRecurringContractKey;
extern NSString * const ADYTransactionOptionShopperRecurringDetailNameKey;
extern NSString * const ADYTransactionOptionAskGratuity;
extern NSString * const ADYTransactionOptionSetGratuity;
extern NSString * const ADYTransactionOptionManualKeyedEntry;
//extern NSString * const ADYTransactionOptionLoyaltyDataKey; // renamed to ADYTransactionOptionAdditionalDataKey, to properly reflect it's function
extern NSString * const ADYTransactionOptionAdditionalDataKey;
extern NSString * const ADYTransactionOptionPaymentVerificationDataKey;

// Possible values for ADYTransactionOptionShopperRecurringContractKey
extern NSString * const ADYTransactionOptionShopperRecurringContractOneClick;
extern NSString * const ADYTransactionOptionShopperRecurringContractRecurring;
extern NSString * const ADYTransactionOptionShopperRecurringContractBoth;

/**-------------------------------------------------------------------------------------------------
 * @name Tender States
 *  ------------------------------------------------------------------------------------------------
 */

/** **Tender States**
 
 A Tender is progressing through a sequence of different states. The App must continue processing
 until one of the final tender states has been reached. Only then has the tender finished.
 These states can be used to indicate progress in the App.
 
 The following will describe the various tender states that the tender might go through,
 in a chronological order.
 
 **In Process Tender States**
 
 The tender will start from its initial state and progress through the tender created state into the
 processing state. Please note that states can be skipped, i.e. a tender might progress from its
 initial state right towards any other state.
 
 - *ADYTenderStateInitial*
 This is the initial state where the tender will start from.
 
 - *ADYTenderStateCreated*
 This is the state where the tender has been created in the payment device and a transaction is
 born. From this state onwards, transactions will be recorded in the transaction history,
 independent of the final state of such transaciton.
 
 - *ADYTenderStateProcessing*
 This is the state after tender creation where the transaction is in progress.
 
 Optionally the payment device might support Manual Key Entry (MKE) processing. When manual key
 entry is performed from the App, the following two tender states are relevant.
 
 - *ADYTenderStateProvideCardDetails*
 The payment device is waiting for the card details to be provided by the App.
 
 - *ADYTenderStateCardDetailsProvided*
 The payment device has receievd the provided card details and is processing these.
 
 Once the card has been read, there is an optional feature to contact an external system, in general
 a merchant back office system, where based upon the card number read, information is retrieved from
 the merchant back office to be made available to the App.
 
 This is typically done for loyalty systems, where the card number may not be revealed to the App,
 due to PCI rules and regulations. The card number can be used as the key to the shopper data,
 and when retrieved, this data is fed back to the App as additional data. The payment device will
 collect this information autonomously and fully DUKPT encrypted, so this information exchange
 is invisible to the App and the App does not have access to this information flow. The App will
 only have access to the information passed on to it.
 
 The App can then decide based upon this information whether or not the transaciton details will
 be changed, typically the amount (discount), but other data could be changed as well.
 
 - *ADYTenderStateAdditionalDataAvailable*
 Additional data is available and is passed to the App.
 
 - *ADYTenderStateWaitForAmountAdjustment*
 The payment device is waiting for any tender updates the App might decide to,
 based upon the information passed to the App in the previous state.
 
 During the transaction the payment device might need to request a referral. A referral takes place
 when a transaction is sent for authorisation to the Acquiring and Issueing banks, during which
 prerocess, the Issueing bank requires the merchant to make a phonecall to the Issueing bank in
 order to get a verbal authorisation code. This code then needs to be communicated back to the
 payment device by the App.
 
 - *ADYTenderStateReferral*
 The Issueing bank requests a referral (not implemented yet)
 
 - *ADYTenderStateReferralChecked*
 The authorisation code, as retrieved form the Issueing bank, is sent to the payment device.
 
 During the transaction the payment device might need to request a signature from the shopper,
 which signature my be provided on paper or by electronic means, like using the iOS device to
 capture the signature. When the signature is captured on the iOS device, the signature needs
 to be passed back to the payment device. The payment device will communicate this to the Adyen
 system, so the signature can be viewed in the Adyen Back Office. In both cases
 (signature on screen/signature on paper) the merchant needs to confirm whether he/she accepts the
 signature or rejects it. When it is rejected, the transaction will be declined. However, the App
 may never assume the transaction will be declined, it needs to continue and wait for the final
 state as it will be presented by the payment device.
 
 - *ADYTenderStateCheckSignature*
 The signature needs to be recorded/checked.
 
 - *ADYTenderStateSignatureChecked*
 The signature has been recorded/processed.
 
 During the transaction there can be multiple situations where a receipt needs to be printed
 (or made available to the shopper by other means, like email). The simple situation is where
 ONE receipt is printed at the end of the transaction that say is APPROVED or DECLINED.
 
 A situation where two receipts will need to be handled is when a signature on paper is requested,
 after which the shopper needs to sign and the merchant needs to check if the signature will be
 accepted or not. In the case it is not accepted, another void receipt will have to be printed or
 made available to the shopper. Also in case of an error, or a cancelled transaction, a void
 receipts may need to be printed or made available to the shopper. So, it is really important that
 the App can handle the processing of multiple receipts. There can be one, two or more receipts.
 
 The receipts will be sent by the payment device to the Adyen Back Office as well, so these can be
 viewed there as part of each transaction.
 
 Please note that when mentioning a "receipt", it in fact is already a set of two receipts,
 the merchant receipt and the shopper receipt.
 
 - *ADYTenderStatePrintReceipt*
 The receipt is provided to the App and needs to be processed.
 
 - *ADYTenderStateReceiptPrinted*
 The receipt has been processed.

 - *ADYTenderStateWaitingForAppSelection*
 The payment method is being selected.

 - *ADYTenderStateAppSelected*
 The payment method has been selected. The selected payment method is passed to the
 `ADYTransactionProcessorDelegate` function `transactionApplicationSelected:`.

 - *ADYTenderStateWaitingForPin*
 The payment device is waiting for the customer to enter their PIN.

 - *ADYTenderStatePinDigitEntered*
 The customer has entered a PIN digit. The total number of digits provided is passed to the
 `ADYTransactionProcessorDelegate` function `transactionPinDigitEntered:`.

 - *ADYTenderStatePinEntered*
 The customer has completed entering their PIN.

 - *ADYTenderStateCardSwiped*
 The customer swiped a payment card through the swipe slot.

 - *ADYTenderStateCardInserted*
 The customer inserted their card into the EMV slot.

 - *ADYTenderStateCardRemoved*
 The customer removed their card from the EMV slot.

 - *ADYTenderStateAskDcc*
 The customer is being asked if Dynamic Currency Conversion should be applied

 - *ADYTenderStateDccAccepted*
 The customer accepted the Dynamic Currency Conversion

 - *ADYTenderStateDccRejected*
 The customer rejected Dynamic Currency Conversion


 **Final Tender States**
 
 - *ADYTenderStateApproved*
 The transaction has been completed with result: APPROVED
 
 - *ADYTenderStateDeclined*
 The transaction has been completed with result: DECLINED
 
 - *ADYTenderStateCancelled**
 The transaction has been completed with result: CANCELLED
 
 - *ADYTenderStateError**
 The transaction has been completed with result: ERROR
 
 **Miscellaneous Tender States**
 
 The miscellaneous tender states are for reference only and should not occur.
 If they occur, they can be ignored.
 
 - *ADYTenderStateRetrying**
 - *ADYTenderStatePending**
 - *ADYTenderStateAcknowledged**
 - *ADYTenderStateUnknown**
 For reference ony, this state should never be reached
 */
typedef enum {
    // in process tender states
    
    ADYTenderStateInitial,
    ADYTenderStateCreated,
    
    ADYTenderStateProcessing,
    
    ADYTenderStateAdditionalDataAvailable,
    ADYTenderStateWaitForAmountAdjustment,
    
    ADYTenderStateProvideCardDetails,
    ADYTenderStateCardDetailsProvided,

    ADYTenderStateAskSignature,
    ADYTenderStateCheckSignature,
    ADYTenderStateSignatureChecked,
    
    ADYTenderStateReferral,
    ADYTenderStateReferralChecked,
    
    ADYTenderStatePrintReceipt,
    ADYTenderStateReceiptPrinted,

    ADYTenderStateWaitingForAppSelection,
    ADYTenderStateAppSelected,
    ADYTenderStateWaitingForPin,
    ADYTenderStatePinDigitEntered,
    ADYTenderStatePinEntered,

    ADYTenderStateAskGratuity,
    ADYTenderStateGratuityEntered,

    ADYTenderStateAskDcc,
    ADYTenderStateDccAccepted,
    ADYTenderStateDccRejected,

    ADYTenderStateCardSwiped,
    ADYTenderStateCardInserted,
    ADYTenderStateCardRemoved,

    // final tender states
    ADYTenderStateApproved,
    ADYTenderStateDeclined,
    ADYTenderStateCancelled,
    ADYTenderStateError,
    
    // Miscellaneous tender states
    ADYTenderStateRetrying,
    ADYTenderStatePending,
    ADYTenderStateAcknowledged,
    ADYTenderStateUnknown

} ADYTenderState;

typedef enum {
    ADYFinalTenderStateNotFinal = -1,
    ADYFinalTenderStateApproved = ADYTenderStateApproved,
    ADYFinalTenderStateDeclined = ADYTenderStateDeclined,
    ADYFinalTenderStateCancelled = ADYTenderStateCancelled,
    ADYFinalTenderStateError = ADYTenderStateError
} ADYFinalTenderState;

/**-------------------------------------------------------------------------------------------------
 * @name Card Schemes
 *  ------------------------------------------------------------------------------------------------
 */

/**
 **Card Schemes**
 
 Here is the enumeration of supported card schemes.
 
 Currently Adyen supports the Mastercard, Visa and Amex brands,
 including all their sub-brands, be it debit or credit.
 
 Possible values:
    VISA
    MC
    AMEX
    JCB
    SOLO
    MAESTRO
    DINERS
    VISADANKORT
    ELECTRON
    DANKORT
    MCDEBIT
    BCMC
    LASER
    MAESTROUK
    DISCOVER
    BIJENKORF
 */
typedef enum {
    ADYCardSchemeError = 0,
    ADYCardSchemeVisaVisa = 1,
    ADYCardSchemeVisaElectron = 2,
    ADYCardSchemeVisaVPay = 3,
    ADYCardSchemeVisaPlus = 4,
    ADYCardSchemeVisaDankort = 5,
    ADYCardSchemeMasterCardDebit = 6,
    ADYCardSchemeMasterCardMaestro = 7,
    ADYCardSchemeMasterCardMaestroUK = 8,
//    ADYCardSchemeMasterCardCirrus = 9, // network, not card type, not implemented
    ADYCardSchemeMasterCardMasterCard = 10,
    ADYCardSchemeAmericanExpress = 11,
    ADYCardSchemeJCB = 12,
    ADYCardSchemeDinersClub = 13,
    ADYCardSchemeDankort = 14,
    ADYCardSchemeDiscover = 15,
    ADYCardSchemeLaser = 16,
    ADYCardSchemeBCMC = 17,
    ADYCardSchemeSolo = 18,
    ADYCardSchemeBijenkorf = 19,

    ADYCardSchemeUnknownMoto = 1000
} ADYCardScheme;


/**-------------------------------------------------------------------------------------------------
 * @name Receipt types
 *  ------------------------------------------------------------------------------------------------
 */

/** **Receipt types**

 Receipts always come in pairs of two: a Merchant and a Cardholder copy.
 When fetching a receipt, this enumeration is used to determine which of the
 two is requested.
 */
typedef enum {
    ADYReceiptTypeCardholder,
    ADYReceiptTypeMerchant
} ADYReceiptType;


/**-------------------------------------------------------------------------------------------------
 * @name Transaction Types
 *  ------------------------------------------------------------------------------------------------
 */
/** **Transaction types**
 *
 * The type of the `ADYTransactionRequest` determines the behaviour of the transaction.
 *
 * - *ADYTransactionTypeGoodsServices*
 * The default, initiates a normal transaction where the payment is made by the shopper and
 * added to the account of the merchant.
 *
 * - *ADYTransactionTypeRefund*
 * Initiates a refund transaction, where the payment is made by the merchant to the shopper.
 *
 */
typedef enum {
    ADYTransactionTypeGoodsServices,
    ADYTransactionTypeRefund
} ADYTransactionType;


/**-------------------------------------------------------------------------------------------------
 * @name Processing states
 *  ------------------------------------------------------------------------------------------------
 */
/**
 * Transactions and refunds can have a `ADYProcessingState` other than `ADYProcessingStateProcessed`
 * if they could not be completed in their entirety and need more processing at a later time. For
 * example: If a transaction fails due to problems with the payment device connection, a technical
 * reversal will be performed to inform the server that the transaction must be cancelled.
 *
 * - *ADYProcessingStateProcessing*
 * The initial state for a transaction/refund
 *
 * - *ADYProcessingStateProcessed*
 * All processing was completed, no further work is required.
 *
 * - *ADYProcessingStateReversalPending*
 * If a technical reversal/refund is required but can't be performed straight away due to internet
 * connection issues, the reversal/refund will remain pending. It will then be performed at a later time.
 *
 * - *ADYProcessingStateReversed*
 * The transaction was reversed with a technical reversal, no further work is required.
 *
 * - *ADYProcessingStateReversalError*
 * The processing could not be performed, no further attempts will be made.
 *
 */
typedef enum {
    ADYProcessingStateProcessing,       // initial state, while transaction/refund is being performed
    ADYProcessingStateProcessed,        // processed normally, nothing to do
    ADYProcessingStateReversalPending,  // waiting for a connection so the transaction can be reversed (technical reversal) or so the refund can be performed
    ADYProcessingStateReversed,         // transaction reversed (technical reversal), nothing more to do
    ADYProcessingStateReversalError     // the technical reversal/refund could not be submitted, no further attempts will be made
} ADYProcessingState;


/**
 * Transaction final states
 */
extern NSString* const FinalStateAPPROVED;
extern NSString* const FinalStateDECLINED;
extern NSString* const FinalStateCANCELLED;
extern NSString* const FinalStateERROR;


#endif