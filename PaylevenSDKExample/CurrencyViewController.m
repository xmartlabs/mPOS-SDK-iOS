//
//  CurrencyViewController.m
//  PaylevenSDKExample
//
//  Created by Alexei Kuznetsov on 17.12.14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

#import "CurrencyViewController.h"


@interface CurrencyViewController ()

/** Cell representing euro. */
@property(nonatomic, weak) IBOutlet UITableViewCell *euroCell;

/** Cell representing british pound. */
@property(nonatomic, weak) IBOutlet UITableViewCell *poundCell;

/** Updates checkmark in cells. */
- (void)updateCheckmark;

@end


@implementation CurrencyViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    if (![self.selectedCurrency isEqualToString:@"EUR"] && ![self.selectedCurrency isEqualToString:@"GBP"]) {
        self.selectedCurrency = @"EUR";
    }
    [self updateCheckmark];
}


#pragma mark - UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    if (indexPath.section == 0) {
        UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
        self.selectedCurrency = cell.textLabel.text;
        [self updateCheckmark];
        if (self.didSelectCurrencyBlock != nil) {
            self.didSelectCurrencyBlock(self.selectedCurrency);
        }
    }
}


#pragma mark - Private

- (void)updateCheckmark {
    if ([self.selectedCurrency isEqualToString:@"EUR"]) {
        self.euroCell.accessoryType = UITableViewCellAccessoryCheckmark;
        self.poundCell.accessoryType = UITableViewCellAccessoryNone;
    } else if ([self.selectedCurrency isEqualToString:@"GBP"]) {
        self.euroCell.accessoryType = UITableViewCellAccessoryNone;
        self.poundCell.accessoryType = UITableViewCellAccessoryCheckmark;
    } else {
        self.euroCell.accessoryType = UITableViewCellAccessoryNone;
        self.poundCell.accessoryType = UITableViewCellAccessoryNone;
    }
}

@end
