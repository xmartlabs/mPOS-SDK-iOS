//
//  ADYReceipt.h
//  DeepThoughts
//
//  Created by Willem Lobbezoo on 29-04-12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

@class ADYReceiptLine;

@interface ADYReceipt : NSObject

@property (strong, nonatomic) NSMutableArray *header;
@property (strong, nonatomic) NSMutableArray *content;
@property (strong, nonatomic) NSMutableArray *footer;

- (ADYReceipt *)init;

+ (ADYReceipt *)createTestReceipt;
+ (NSString *)getReceiptFormatted:(NSArray *)receipt;
+ (NSString *)getReceiptLineFormatted:(ADYReceiptLine *)receiptLine;

- (NSArray *)getReceiptCustomized;

@end
