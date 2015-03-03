//
// Created by Jeroen Bouma on 04/03/14.
//

#import <Foundation/Foundation.h>

@class ADYTransactionData;

/**
Request for a Mail Order/Telephone Order (MOTO) payment transaction.

Simply create a request by allocating/initializing it.

It is possible to pass optional parameters to the transaction via the *options* dictionary.
Use the following pre-defined constants as keys on your dictionary:

- `ADYTransactionOptionShopperReferenceKey` : the shopper reference for the transaction as a NSString instance.
- `ADYTransactionOptionShopperEmailKey` : the shopper email for the transaction as a NSString instance.
- `ADYTransactionOptionShopperRecurringContractKey` : the recurring contract for the transaction. Provide none or one of the following: ADYTransactionOptionShopperRecurringContractOneClick, ADYTransactionOptionShopperRecurringContractRecurring, ADYTransactionOptionShopperRecurringContractBoth
- `ADYTransactionOptionShopperRecurringDetailNameKey` : Reserved for future use

If one wants to use the transaction details to be able to perform at a later stage a recurring
transaction, using the transaction details of the current POS transaction, one needs to populate
the following fields:
- ADYTransactionOptionShopperReferenceKey
- ADYTransactionOptionShopperEmailKey
- ADYTransactionOptionShopperRecurringContractKey
(see the Adyen Recurring Manual for details)

*/
@interface ADYMotoTransactionRequest : NSObject

/** The currency to use on the transaction. */
@property (nonatomic, strong) NSString* currency;

/** The amount to process on the transaction in minor units (cents). */
@property (nonatomic, strong) NSNumber* amount;

/** The (merchant) reference for the transacion */
@property (nonatomic, strong) NSString* reference;

/** The credit card number, 12-19 digits. Example: "1234567812345678" */
@property (nonatomic, strong) NSString* cardNumber;

/** The expiry month of the card. January = 1, Februari = 2, etc */
@property (nonatomic, strong) NSString* cardExpiryMonth;

/** The expiry year of the card */
@property (nonatomic, strong) NSString* cardExpiryYear;

/** The card holder name, embossed in the card */
@property (nonatomic, strong) NSString* cardHolder;

/** Optional, The Card Verification Code, this is the the CVC2 code (for MasterCard), CVV2 (for Visa) or CID (for American Express). */
@property (nonatomic, strong) NSString* cardCvc;

/** Optional dictionary with transaction options. */
@property (nonatomic, strong) NSDictionary* options;

/** Initializes the request */
- (id) init;

/**
 * Starts the MOTO asynchronous request and invokes the `completion` block when finished.
 *
 * If something went wrong during the request, the error object will contain the details.
 *
 * If the `result` object is not nil, the request was successfull. The `finalState` will indicate
 * whether the transaction was APPROVED, DECLINED or ERROR. Check the `declineInfo` and `errorInfo` properties
 * for more info.
 */
- (void) startWithCompletion:(void (^)(ADYTransactionData *result, NSError *error))completion;

@end