//
//  PLVPaymentRequest.h
//  PaylevenSDK
//
//  Created by Alexei Kuznetsov on 21/10/14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>
#import <Foundation/Foundation.h>


/** A payment request. */
@interface PLVPaymentRequest : NSObject

/** Payment identifier. */
@property(nonatomic, readonly, copy) NSString *identifier;

/**
 * Payment amount.
 *
 * The value can be fractional, maximum two fraction digits are allowed.
 *
 * When creating `NSDecimalNumber` from `NSString`, don't forget to take the current locale and the decimal separator
 * into account.
 */
@property(nonatomic, readonly, copy) NSDecimalNumber *amount;

/** Three-letter ISO 4217 currency code. For example, EUR. */
@property(nonatomic, readonly, copy) NSString *currency;

/** Current device coordinate. */
@property(nonatomic, readonly, assign) CLLocationCoordinate2D coordinate;

/**
 * Initializes the receiver with the specified identifier, amount, currency, and coordinate.
 *
 * @param identifier Payment identifier.
 * @param amount Payment amount. The value can be fractional, maximum two fraction digits are allowed. When creating
 *               `NSDecimalNumber` from `NSString`, don't forget to take the current locale and the decimal separator
 *               into account.
 * @param currency Three-letter ISO 4217 currency code. For example, EUR.
 * @param coordinate Current device coordinate.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier
                            amount:(NSDecimalNumber *)amount
                          currency:(NSString *)currency
                        coordinate:(CLLocationCoordinate2D)coordinate;

@end
