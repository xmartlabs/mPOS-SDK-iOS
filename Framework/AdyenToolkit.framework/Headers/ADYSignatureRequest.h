//
//  ADYSignatureRequest.h
//  AdyenPOSLib
//
//  Created by Jeroen Koops on 4/11/13.
//
//

#import <Foundation/Foundation.h>
#import "ADYConstants.h"

@class UIImage;

/**
 * Request-object used to inform the ADYTransactionProcessorDelegate
 * that the cardholder's signature must be checked. This is described
 * fully under [ADYTransactionProcessorDelegate transactionRequiresSignature:].
 */
@interface ADYSignatureRequest : NSObject

/**
 * The transactionData is an NSDictionary containing key/value pairs.
 *
 * - `key=signature.merchant.name1, value=the merchant name as used printing the receipt (first line)`
 * - `key=signature.merchant.name2, value=the merchant name as used printing the receipt (second line)`
 * - `key=signature.amount.currency, value=currency of the transaction`
 * - `key=signature.amount.value, value=ORIGINAL amount of the transaction`
 * - `key=signature.updated.amount.value, value=UPDATED  amount of the transaction`
 *
 * Please note that the updated amount can be higher (i.e. tip) or lower (i.e. discount)
 * or can be equal to the original amount
 *
 * @deprecated: the other properties of ADYSignatureRequest expose all data more conveniently.
 */
@property (readonly) NSDictionary* transactionData;

/**
 * The transactionData contains 2 merchant name lines. The first line can
 * be either a text name or an image. If the signature.merchant.name1 line
 * is an image it can be accessed through this property.
 *
 * If it is not configured it will be nil.
 */
@property (readonly) UIImage *merchantImage;

/**
 * The transactionData contains 2 merchant name lines. The first line can
 * be either a text name or an image. The second line is always text.
 *
 * This property is a convenient way to iterate through the textual lines
 * of the merchant name. The merchantImage exposes the image contained
 * by line 1 (if any).
 */
@property (readonly) NSArray *merchantNameLines;

/**
* The currency type used for the transaction
*/
@property (readonly) NSString *transactionCurrency;

/**
* The amount in minor units (int) of the transaction
*/
@property (readonly) NSNumber *transactionAmount;

/**
* The merchant reference of the transaction
*/
@property (readonly) NSString *transactionReference;


/**
* The cardHolder of the transaction
*/
@property (readonly) NSString *cardHolder;

/**
* The summary of the card used for the transaction
*/
@property (readonly) NSString *cardSummary;

/**
* The card scheme used for the transaction
*/
@property (readonly) ADYCardScheme cardScheme;

/**
* The authentication code of the card used for this transaction
*/
@property (readonly) NSString *authenticationCode;

/**
* The signature image, if the signature was given (drawn) on the
* payment device touch screen and needs to be verified by the merchant.
*/
@property (readonly) UIImage *signatureImage;

/**
 * Continue transaction-processing by confirming that the
 * signature drawn by the customer matches the signature on the card.
 *
 * @param signatureImage An image containing the signature drawn
 * by the customer, or `nil` if the customer drew their signature on 
 * a paper receipt (only possible if a printer is available).
 */
-(void)submitConfirmedSignature:(UIImage*)signatureImage;

/**
 * Continue transaction-processing by asserting that the
 * signature drawn by the customer does not match the
 * signature on the card.
 *
 * @param signatureImage An image containing the signature drawn
 * by the customer, or `nil` if the customer drew their signature on
 * a paper receipt (only possible if a printer is available).
 */ 
-(void)submitUnconfirmedSignature:(UIImage*)signatureImage;
@end
