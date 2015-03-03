//
//  ReceiptViewController.m
//  PaylevenSDKExample
//
//  Created by Alexei Kuznetsov on 10.12.14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

#import "ReceiptViewController.h"


@interface ReceiptViewController ()

/** Receipt image view. */
@property(nonatomic, weak) IBOutlet UIImageView *imageView;

@end


@implementation ReceiptViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.imageView.image = self.receipt;
}


#pragma mark -

- (IBAction)close:(id)sender {
    if (self.didFinishBlock != nil) {
        self.didFinishBlock();
    }
}

@end
