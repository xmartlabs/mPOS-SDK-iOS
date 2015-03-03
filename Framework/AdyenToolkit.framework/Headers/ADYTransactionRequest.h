//
//  ADYTransactionRequest.h
//  AdyenPOSLib
//
//  Created by Jeroen Koops on 4/12/13.
//
//

#import <Foundation/Foundation.h>
#import "ADYTransactionProcessorDelegate.h"

@class ADYTransactionProcessor;
@class CLLocation;

/**
Request for a payment transaction.
 
Obtain a request by calling `createTransactionRequestWithReference:` on the `ADYDevice` instance of choice. Then,
fill in all required properties. Finally, start the transaction by calling startWithDelegate:. The
delegate will be informed of the transaction's progress, and when the transaction is complete.
Finally, you can call `requestCancel` to request cancellation of the running transaction.

As of version 1.9, no location needs to be set on the transaction using `ADYTransactionOptionLocationKey`;
 it is fetched by the Adyen Framework itself. It is however required for the user to have Location
 Services enabled. If this isn't the case, the transaction will not start.
 Adyen is legally obliged to register the location, in order to be able to prove that transactions
 are only performed in the certified area.

It is possible to pass optional parameters to the transaction via the *options* dictionary.
Use the following pre-defined constants as keys on your dictionary:

- `ADYTransactionOptionReferenceKey` : the transaction reference as a NSString instance.
- `ADYTransactionOptionLogoKey` : the merchant logo for the transaction as a UIImage instance.
- `ADYTransactionOptionShopperReferenceKey` : the shopper reference for the transaction as a NSString instance.
- `ADYTransactionOptionShopperEmailKey` : the shopper email for the transaction as a NSString instance.
- `ADYTransactionOptionShopperRecurringContractKey` : the recurring contract for the transaction. Provide none or one of the following: ADYTransactionOptionShopperRecurringContractOneClick, ADYTransactionOptionShopperRecurringContractRecurring, ADYTransactionOptionShopperRecurringContractBoth
- `ADYTransactionOptionShopperRecurringDetailNameKey` : Reserved for future use
- `ADYTransactionOptionAdditionalDataKey` : presence of this key in transaction options will trigger third-party data handling, keys with this as a prefix will be sent to the third-party data handler.
- `ADYTransactionOptionAskGratuity`: presence of this key in transaction options (value is irrelevant) will cause the payment device to ask for a gratuity.
- `ADYTransactionOptionManualKeyedEntry`: presence of this key in transaction options (value is irrelevant) will cause the payment device to use manual keyed entry mode, if supported.

If one wants to use the transaction details to be able to perform at a later stage a recurring
transaction, using the transaction details of the current POS transaction, one needs to populate
the following fields:
- ADYTransactionOptionShopperReferenceKey
- ADYTransactionOptionShopperEmailKey
- ADYTransactionOptionShopperRecurringContractKey
(see the Adyen Recurring Manual for details)

 
*/
@interface ADYTransactionRequest : NSObject

/** The type of the transaction, see `ADYTransactionType` for details. Defaults to ADYTransactionTypeGoodsServices. */
@property (nonatomic, assign) ADYTransactionType transactionType;

/** The currency to use on the transaction. */
@property (nonatomic, strong) NSString* currency;

/** The amount to process on the transaction in minor units (cents). */
@property (nonatomic, strong) NSNumber* amount;

/** Gratuity amount in cents, or `nil` if no gratuity desired. */
@property (nonatomic, strong) NSNumber* gratuity;

/** Locale of the transaction, or `nil` to use default locale. */
@property (nonatomic, strong) NSLocale* locale;

/** Optional dictionary with transaction options. Only NSString typed values are allowed */
@property (nonatomic, strong) NSDictionary* options;

/**
 * Starts the transaction.
 *
 * One of the possible error codes is `ADYErrorCodeTransactionRequiresLocationServices`, which
 * means the app is not allowed to access the Location Services. It is required to have this
 * enabled in order to start a transaction. Please ask the user to enable the Location Services
 * in general, and for your app, using Settings -> Privacy -> Location Services (-> [YOUR APP]).
 *
 * @param delegate this delegate will be informed of the transaction's progress and completion.
 * @param error if the transaction cant be started, the error will be set.
 */
-(BOOL)startWithDelegate:(id<ADYTransactionProcessorDelegate>)delegate error:(NSError**)error;

/**
 * Requests for the transaction to be cancelled.
 * This is only a _request_ for cancellation. It is up to the payment device to honour this request
 * or not. This method returns immediately, the delegate given in the call to
 * startWithDelegate: will continue to receive updates on the transaction's status, and completion. If 
 * cancellation is successful, the status of the completed transaction will be `FinalStateCANCELLED`,
 * but if the transaction could not be cancelled, it will be one of the other final states.
 */
-(void)requestCancel;

@end
