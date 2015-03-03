//
//  SignatureConfirmationViewController.m
//  PaylevenSDKExample
//
//  Created by Alexei Kuznetsov on 21.11.14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

#import "SignatureConfirmationViewController.h"


@interface SignatureConfirmationViewController ()

/** Signature image view. */
@property(nonatomic, weak) IBOutlet UIImageView *imageView;

/** Calls the did-cancel block. */
- (IBAction)cancel:(id)sender;

@end


@implementation SignatureConfirmationViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.imageView.image = self.signature;
}


#pragma mark - Private

- (IBAction)cancel:(id)sender {
    if (self.didCancelBlock != nil) {
        self.didCancelBlock();
    }
}


#pragma mark - UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    if (indexPath.section == 0 && self.didFinishBlock != nil) {
        if (indexPath.row == 0) {
            self.didFinishBlock(YES);
        } else if (indexPath.row == 1) {
            self.didFinishBlock(NO);
        }
    }
}

@end
