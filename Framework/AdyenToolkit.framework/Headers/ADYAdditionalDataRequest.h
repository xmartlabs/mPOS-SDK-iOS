//
//  ADYAdditionalDataRequest.h
//  AdyenPOSLib
//
//  Created by Jeroen Koops on 4/11/13.
//
//

#import <Foundation/Foundation.h>

@class ADYTransactionProcessor;

/**
 * Request-object used to inform the ADYTransactionProcessorDelegate that
 * additional data is available.
 */

@interface ADYAdditionalDataRequest : NSObject

/** Merchant specific additional data. */
@property (readonly) NSDictionary* additionalData;

/** The original transaction amount, in minor currency units (e.g. cents). */
@property (readonly) NSNumber* transactionAmount;

/** The transaction currency. */
@property (readonly) NSString* transactionCurrency;

/**
 * Continue transaction-processing, either was an updated amount, 
 * or with the same amount.
 *
 * @param amount may be <tt>nil</tt> to continue with
 * the current amount, or an amount in minor currency units (e.g. cents)
 * to continue with an updated amount.
 */
-(void)continueWithUpdatedAmount:(NSNumber*)amount;

@end
