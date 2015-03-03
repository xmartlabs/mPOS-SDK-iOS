//
//  PaymentViewController.h
//  PaylevenSDKExample
//
//  Created by Alexei Kuznetsov on 23/10/14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

@import UIKit;

@class PLVDevice, PLVPayleven;
@protocol PaymentViewControllerDelegate;

/** Payment view controller. */
@interface PaymentViewController : UITableViewController

/** The receiver's delegate. */
@property(nonatomic, weak) id <PaymentViewControllerDelegate> delegate;

/** Payleven. */
@property(nonatomic, strong) PLVPayleven *payleven;

/** Payment device. */
@property(nonatomic, strong) PLVDevice *device;

@end


/** The protocol defines delegate method for PaymentViewController objects. */
@protocol PaymentViewControllerDelegate <NSObject>

@required

/** Called when payment process finishes. */
- (void)paymentViewControllerDidFinish:(PaymentViewController *)paymentViewController;

@end
