//
//  PLVPaymentResultAdditionalData.h
//  PaylevenSDK
//
//  Created by Alexei Kuznetsov on 04.12.14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "PLVPaymentResult.h"


/** Payment result additional data. */
@interface PLVPaymentResultAdditionalData : NSObject

/** Primary account number (PAN), also known as card number. Truncated for security reasons. */
@property(nonatomic, readonly, copy) NSString *primaryAccountNumber;

/** Maximum length of the untruncated primary account number for the card brand specified in cardBrandIdentifier. */
@property(nonatomic, readonly, assign) NSUInteger maximumPrimaryAccountNumberLength;

/** Primary account number sequence number. Identifies and differentiates cards with the same PAN. */
@property(nonatomic, readonly, copy) NSString *primaryAccountNumberSequenceNumber;

/** POS entry mode. */
@property(nonatomic, readonly, assign) PLVPointOfSaleEntryMode pointOfSaleEntryMode;

/** Cardholder verification method. */
@property(nonatomic, readonly, assign) PLVCardholderVerificationMethod cardholderVerificationMethod;

/** Card application identifier (AID). */
@property(nonatomic, readonly, copy) NSString *applicationIdentifier;

/** Card authorization code. */
@property(nonatomic, readonly, copy) NSString *authorizationCode;

/** Card brand identifier. */
@property(nonatomic, readonly, copy) NSString *cardBrandIdentifier;

/** Card brand name. */
@property(nonatomic, readonly, copy) NSString *cardBrandName;

@end
