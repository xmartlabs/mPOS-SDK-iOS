//
//  CurrencyViewController.h
//  PaylevenSDKExample
//
//  Created by Alexei Kuznetsov on 17.12.14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

@import UIKit;

/** A view controller for selecting currency. */
@interface CurrencyViewController : UITableViewController

/** Selected currency. */
@property(nonatomic, copy) NSString *selectedCurrency;

/** Block that is called when the currency selection changes. */
@property(copy) void (^didSelectCurrencyBlock)(NSString *currency);

@end
