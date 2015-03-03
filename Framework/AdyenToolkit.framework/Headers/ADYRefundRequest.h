//
// Created by Jeroen Bouma on 30/07/14.
//

#import <Foundation/Foundation.h>
#import "ADYConstants.h"

@class ADYCurrency;
@class ADYTransactionData;

/**
 * Sends a request to refund the `refundAmount` from the transaction corresponding with the supplied `pspReference`
 * or `tenderReference`/`terminalId` pair.
 *
 * It can refund an existing ADYTransactionData, retrieved from the local database, or it can be used to refund
 * transaction that are not in the local database (not performed on the current device).
 * If the transaction does not exist in the local database, it will be created with the data supplied to the
 * refund request. All other fields of the 'fake' transaction will be `nil`.
 *
 * Either the `pspReference` or the `tenderReference` and `terminalId` must be supplied in order for the request
 * to find the corresponding transaction.
 * Also the `originalAmount`, `currency` and (obviously) `refundAmount` and `refundReference` are mandatory.
 * All other parameters are optional (though encouraged) and used only as reference points for the transaction.
 *
 * Be warned: The refund service only confirms the reception of the refund request, *no* confirmation of the
 * completion of the refund itself is given. This behaviour arises from the asynchronous handling of requests
 * by the server. Because of this, it is difficult to tell whether the refund was indeed performed. Users
 * should be *very* careful when entering the `pspReference` or `tenderReference`/`terminalId` manually.
 *
 */
@interface ADYRefundRequest : NSObject

@property (nonatomic, strong) ADYTransactionData *transaction;

@property (nonatomic, strong) NSString *pspReference;
@property (nonatomic, strong) NSString *tenderReference;
@property (nonatomic, strong) NSString *terminalId;
@property (nonatomic, strong) NSString *merchantReference;
@property (nonatomic, strong) NSNumber *originalAmountMinorUnits; // the amount of the original transaction in minor units (example: cents)
@property (nonatomic, strong) ADYCurrency *currency;
@property (nonatomic, strong) NSDate *transactionDate;
@property (nonatomic, strong) NSNumber *refundAmount;
@property (nonatomic, strong) NSString *refundReference;

/**
 * Init the request to refund a transaction that is not in the local database. Either a `pspReference` or a
 * `tenderReference`/`terminalId` pair has to be set in the properties. On top of that the `originalAmountMinorUnits`,
 * `currency`, `refundAmount` and `refundReference` have to be set. The other properties are optional and used only to
 * make the transaction more identifiable for the user.
 */
- (id)init;

/**
 * Init the request with an existing transaction and the refund information. No other properties need to be set.
 */
- (id)initWithTransaction:(ADYTransactionData *)transaction amount:(NSNumber *)refundAmount reference:(NSString *)refundReference;


- (void)startWithCompletion:(void (^)(ADYProcessingState refundState, NSError *error))completion;

@end