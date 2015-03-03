//
// AdyenPOSLib
// 
// Created by Jeroen Bouma on 10/30/13.
//

#import <Foundation/Foundation.h>
#import "ADYConstants.h"

/**
 * Instances of this class represent a refund on a particular transaction.
 *
 * A single transaction can have multiple refund instances. This is because
 * a transaction can be refunded as a whole or partially. For example: when
 * a customer purchased more than one item with one payment, but decides later on
 * that one of the items is not satisfactory, only a part of the original
 * transaction should be refunded.
 *
 * This can occur a number of times until all of the original amount has been
 * refunded.
 *
 * The amount has to be refunded in the same currency as the original transaction.
 */
@interface ADYRefundData : NSObject

/**
 * The unique pspReference to identify this refund.
 */
@property (nonatomic, strong) NSString * pspReference;

/**
 * The amount that was refunded
 */
@property (nonatomic, strong) NSNumber * amount;

/**
 * The date/time this refund was completed
 */
@property (nonatomic, strong) NSDate * date;

/**
 * An optional reference or description for this refund
 */
@property (nonatomic, strong) NSString * reference;

/**
 * The processing state of the refund, indicating if the refund
 * was already submitted to the server or is waiting for a working
 * internet connection. Can be `ADYProcessingStateProcessed` or
 * `ADYProcessingStateReversalPending`.
 */
@property (nonatomic, assign) ADYProcessingState processingState;

@end