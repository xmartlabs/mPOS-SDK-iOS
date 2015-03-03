//
//  ADYReceiptLine.h
//  DeepThoughts
//
//  Created by Willem Lobbezoo on 29-04-12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum {
    ADYReceiptLineTypeEmpty,
    ADYReceiptLineTypeNameValue,
    ADYReceiptLineTypeName,
    ADYReceiptLineTypeImage
} ADYReceiptLineType;

/**
 * Instances of this class represent one line in a receipt.
 * 
 * A line can consist of either a name and a value, only
 * a name, or nothing at all (an empty line).
 */

@interface ADYReceiptLine : NSObject <NSCoding>

/**
 * @deprecated Use `isEmphasized` instead.
 */
@property (strong, nonatomic) NSString* format;

/**
 * @deprecated Use `type` instead.
 */
@property (strong, nonatomic) NSString* mustPrint;

/**
 * @deprecated Use the position in the containing
 * `ADYReceipt` instead.
 */
@property (strong, nonatomic) NSString* position;

/**
 * The name of the line.
 */
@property (strong, nonatomic) NSString* name;

/** 
 * The value of the line.
 */
@property (strong, nonatomic) NSString* value;

/**
 * The image of the line. Usually a logo to go on top of the receipt or
 * the signature.
 * Check the `type` property to determine if this line is an image.
 */
@property (readonly) UIImage *image;

/**
 * Boolean indicating if the line should be printed
 * with emphasis (i.e. with a bold font).
 */
@property (readonly) BOOL isEmphasized;

/**
 * The type of the line.
 *
 * This can be one of the following:
 *
 * - `ADYReceiptLineTypeEmpty`: neither the `name` nor the `value`
 * are valid, an empty line must be printed.
 * - `ADYReceiptLineTypeNameValue`: both the `name` and the `value`
 * are valid, both must be printed.
 * - `ADYReceiptLineTypeName`: only the `name` is valid and must be printed.
 * - `ADYReceiptLineTypeImage`: the line represents an image. Usually a logo.
 */
@property (readonly) ADYReceiptLineType type;

- (void)encodeWithCoder:(NSCoder *)coder;
//- (void) debug;

@end
