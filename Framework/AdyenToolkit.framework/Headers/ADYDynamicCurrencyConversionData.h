//
// Created by Jeroen Bouma on 17/03/14.
//

#import <Foundation/Foundation.h>


@interface ADYDynamicCurrencyConversionData : NSObject

@property (readonly) NSString *originalAmountCurrency;
@property (readonly) NSNumber *originalAmountValue;         //minor units (fraction depends on currency)

@property (readonly) NSString *convertedAmountCurrency;
@property (readonly) NSNumber *convertedAmountValue;        //minor units (fraction depends on currency)

@property (readonly) NSNumber *exchangeRate;

@property (readonly) NSString *source;
@property (readonly) NSNumber *commissionFee; //currency = ?
@property (readonly) NSNumber *markup; //in base points

@end