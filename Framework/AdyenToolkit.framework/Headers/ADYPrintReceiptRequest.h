//
//  ADYPrintReceiptRequest.h
//  AdyenPOSLib
//
//  Created by Jeroen Koops on 4/11/13.
//
//

#import <Foundation/Foundation.h>

@class ADYReceipt;
@class ADYTransactionData;

/**
 * Request-object used to inform the ADYTransactionProcessorDelegate that
 * a receipt must be printed.
 */

extern NSString* const ADYPrintReceiptRequestAmountKey;
extern NSString* const ADYPrintReceiptRequestUpdatedAmountKey;
extern NSString* const ADYPrintReceiptRequestCurrencyKey;
extern NSString* const ADYPrintReceiptRequestMerchantName1Key;
extern NSString* const ADYPrintReceiptRequestMerchantName2Key;
extern NSString* const ADYPrintReceiptRequestUpdatedAmountKey;
extern NSString* const ADYPrintReceiptRequestMerchantReferenceKey;
extern NSString* const ADYPrintReceiptRequestAuthCodeKey;
extern NSString* const ADYPrintReceiptRequestCardHolderKey;
extern NSString* const ADYPrintReceiptRequestCardSummaryKey;
extern NSString* const ADYPrintReceiptRequestCardSchemeKey;
extern NSString* const ADYPrintReceiptRequestSignatureData;
extern NSString* const ADYPrintReceiptRequestSignatureMimeType;

@interface ADYPrintReceiptRequest : NSObject

/** Data about the transaction in progress. */
@property (readonly) ADYTransactionData* transactionData;

/** The merchant-receipt to be printed. */
@property (readonly) ADYReceipt* merchantReceipt;

/** The cardholder-receipt to be printed. */
@property (readonly) ADYReceipt* cardHolderReceipt;

/** 
 * Continue transaction processing after receipt has been printed.
 *
 * @param success `YES` if printing was successful, `NO` if it wasn't.
 */
-(void)confirmReceiptPrinted:(BOOL)success;
@end
