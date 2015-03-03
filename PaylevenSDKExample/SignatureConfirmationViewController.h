//
//  SignatureConfirmationViewController.h
//  PaylevenSDKExample
//
//  Created by Alexei Kuznetsov on 21.11.14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

@import UIKit;

/** A view controller that is responsible for the signature confirmation. */
@interface SignatureConfirmationViewController : UITableViewController

/** The signature to confirm. */
@property(nonatomic, strong) UIImage *signature;

/** Block that is called when signature confirmation completes. */
@property(copy) void (^didFinishBlock)(BOOL confirmed);

/** Block that is called when the signature confirmation cancels. */
@property(copy) void (^didCancelBlock)();

@end
