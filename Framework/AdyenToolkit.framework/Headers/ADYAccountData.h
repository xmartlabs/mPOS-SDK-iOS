//
//  ADYAccountData.h
//  AdyenPOSLib
//
//  Created by Jeroen Koops on 5/14/13.
//
//

#import <Foundation/Foundation.h>

/**
 * Class holding data about the account that is currently logged in.
 */

@interface ADYAccountData : NSObject

/**
 * The merchant currently logged in.
 */
@property (nonatomic, readonly) NSString* merchant;

/**
 * The username currently logged in.
 */
@property (nonatomic, readonly) NSString* username;
@end
