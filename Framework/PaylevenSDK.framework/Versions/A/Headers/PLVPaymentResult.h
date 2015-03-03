//
//  PLVPaymentResult.h
//  PaylevenSDK
//
//  Created by Alexei Kuznetsov on 21/10/14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>


/** Payment result state. */
typedef NS_ENUM(NSInteger, PLVPaymentResultState) {
    
    /** Approved. */
    PLVPaymentResultStateApproved,
    
    /** Declined. */
    PLVPaymentResultStateDeclined,
    
    /** Cancelled. */
    PLVPaymentResultStateCancelled
};

/** POS entry mode constants. */
typedef NS_ENUM(NSInteger, PLVPointOfSaleEntryMode) {
    
    /** Unknown mode. */
    PLVPointOfSaleEntryModeUnknown,
    
    /** ICC (chip) mode. */
    PLVPointOfSaleEntryModeIntegratedCircuitCard,
    
    /** Swipe mode. */
    PLVPointOfSaleEntryModeMagneticStripeReader,
    
    /** Manual mode. */
    PLVPointOfSaleEntryModePANKeyEntry
};

/** Cardholder verification method constants. */
typedef NS_ENUM(NSInteger, PLVCardholderVerificationMethod) {
    
    /** Could not detect CVM or CVM is unknown. */
    PLVCardholderVerificationMethodUnknown,
    
    /** No CVM required. */
    PLVCardholderVerificationMethodNone,
    
    /** PIN verification. */
    PLVCardholderVerificationMethodPIN,
    
    /** Signature verification. */
    PLVCardholderVerificationMethodSignature,
    
    /** PIN and signature verification .*/
    PLVCardholderVerificationMethodPINSignature
};

@class PLVReceiptGenerator, PLVPaymentResultAdditionalData;

/** PLVPaymentResult class represents payment results. */
@interface PLVPaymentResult : NSObject

/** Payment identifier. */
@property(nonatomic, readonly, copy) NSString *identifier;

/** Payment state. */
@property(nonatomic, readonly, assign) PLVPaymentResultState state;

/** Payment amount. */
@property(nonatomic, readonly, copy) NSDecimalNumber *amount;

/** Payment currency. */
@property(nonatomic, readonly, copy) NSString *currency;

/** Payment date. */
@property(nonatomic, readonly, strong) NSDate *date;

/** Signature image URL. */
@property(nonatomic, readonly, strong) NSURL *signatureImageURL;

/** Receipt generator. */
@property(nonatomic, readonly, strong) PLVReceiptGenerator *receiptGenerator;

/** Additional payment result data. */
@property(nonatomic, readonly, strong) PLVPaymentResultAdditionalData *additionalData;

@end
