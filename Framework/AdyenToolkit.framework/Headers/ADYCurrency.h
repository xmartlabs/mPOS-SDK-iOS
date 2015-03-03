//
// Created by Jeroen Bouma on 10/11/13.
//


#import <Foundation/Foundation.h>


@interface ADYCurrency : NSObject

/*
 The short notation of the name of the currency, like EUR for Euros, USD for
 United States Dollars and JPY for Japanese Yen
 */
@property (nonatomic, readonly) NSString* abbreviation;

/*
 The symbol for this currency, like $ for Dollars, € for Euros and ¥ for
 both the Chinese Yuan and Japanese Yen
 */
@property (nonatomic, readonly) NSString* symbol;

/*
 The number of decimal digits this currency has. For example: Euros have
 two fractional digits called cents; EUR 1.887,95. Other currencies like the
 Hungarian HUF have no fractional digits ( HUF 1.887 ) and some have three.
 */
@property (nonatomic, readonly) NSUInteger numFractionalDigits;

// used by lib to initialize object
- (id)initWithAbbreviation:(NSString*)abbr symbol:(NSString*)sym numFractionalDigits:(NSUInteger)decimals;

@end