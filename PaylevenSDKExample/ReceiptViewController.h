//
//  ReceiptViewController.h
//  PaylevenSDKExample
//
//  Created by Alexei Kuznetsov on 10.12.14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

@import UIKit;

/** A view controller that is responsible for displaying the receipt. */
@interface ReceiptViewController : UIViewController

/** The receipt image. */
@property(nonatomic, strong) UIImage *receipt;

/** Block that is called when receipt display is finished. */
@property(copy) void (^didFinishBlock)();

@end
