//
//  PLVReceiptGenerator.h
//  PaylevenSDK
//
//  Created by Alexei Kuznetsov on 10.12.14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>


/** PLVReceiptGenerator creates receipt images. */
@interface PLVReceiptGenerator : NSObject

/**
 * Generates the receipt image.
 *
 * @param width Receipt image width.
 * @param fontSize Receipt font size.
 * @param lineSpacing Receipt text line spacing.
 * @param padding Receipt contents padding.
 * @param completionHandler Block that is called when the receipt generation finishes. The block takes a single
 *                          parameter `receipt`.
 */
- (void)generateReceiptWithWidth:(CGFloat)width
                        fontSize:(CGFloat)fontSize
                     lineSpacing:(CGFloat)lineSpacing
                         padding:(CGFloat)padding
               completionHandler:(void (^)(CGImageRef receipt))completionHandler;

@end
