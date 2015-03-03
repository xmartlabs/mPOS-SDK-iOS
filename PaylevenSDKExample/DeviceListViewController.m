//
//  DeviceListViewController.m
//  PaylevenSDKExample
//
//  Created by Alexei Kuznetsov on 15.10.14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

#import "DeviceListViewController.h"

#import <ExternalAccessory/ExternalAccessory.h>
#import <PaylevenSDK/PaylevenSDK.h>


@interface DeviceListViewController ()

/** Sorted device list. */
@property(nonatomic, strong) NSArray *sortedDevices;

/** Opens external accessory bluetooth picker. */
- (IBAction)openDevicePicker:(id)sender;

/** Reports the delegate that device selection is cancelled. */
- (IBAction)cancel:(id)sender;

/** Updates @em sortedDevices. */
- (void)updateSortedDevices;

/** Shows device selection failure alert. */
- (void)showDeviceSelectionAlertWithError:(NSError *)error;

@end


@implementation DeviceListViewController

- (void)dealloc {
    self.payleven = nil;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    [self updateSortedDevices];
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
    if (object == self.payleven && [keyPath isEqualToString:NSStringFromSelector(@selector(devices))]) {
        assert([NSThread isMainThread]);
        [self updateSortedDevices];
        [self.tableView reloadData];
    } else {
        [super observeValueForKeyPath:keyPath ofObject:object change:change context:context];
    }
}

#pragma mark - Private

- (void)setPayleven:(PLVPayleven *)payleven {
    if (_payleven != payleven) {
        if (_payleven != nil) {
            [_payleven removeObserver:self forKeyPath:NSStringFromSelector(@selector(devices)) context:NULL];
        }
        _payleven = payleven;
        if (_payleven != nil) {
            [_payleven addObserver:self forKeyPath:NSStringFromSelector(@selector(devices)) options:0 context:NULL];
        }
    }
}

- (IBAction)openDevicePicker:(id)sender {
    EAAccessoryManager *accessoryManager = [EAAccessoryManager sharedAccessoryManager];
    [accessoryManager showBluetoothAccessoryPickerWithNameFilter:nil completion:nil];
}

- (IBAction)cancel:(id)sender {
    [self.delegate deviceListViewControllerDidCancel:self];
}

- (void)updateSortedDevices {
    NSSortDescriptor *descriptor = [NSSortDescriptor sortDescriptorWithKey:@"name"
                                                                 ascending:YES
                                                                  selector:@selector(localizedCaseInsensitiveCompare:)];
    self.sortedDevices = [self.payleven.devices sortedArrayUsingDescriptors:@[descriptor]];
}

- (void)showDeviceSelectionAlertWithError:(NSError *)error {
    NSString *title = NSLocalizedString(@"Could Not Prepare Device", @"Device preparation error alert title.");
    NSString *OK = NSLocalizedString(@"OK", @"OK.");
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:title
                                                    message:error.localizedDescription
                                                   delegate:nil
                                          cancelButtonTitle:nil
                                          otherButtonTitles:OK, nil];
    [alert show];
}


#pragma mark - UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    assert(section == 0);
    return self.sortedDevices.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"Device" forIndexPath:indexPath];
    PLVDevice *device = self.sortedDevices[indexPath.row];
    cell.textLabel.text = device.name;
    if ([device isEqual:self.selectedDevice]) {
        cell.accessoryType = UITableViewCellAccessoryCheckmark;
    } else {
        cell.accessoryType = UITableViewCellAccessoryNone;
    }
    
    return cell;
}


#pragma mark - UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
    UIActivityIndicatorView *spinner = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    cell.accessoryView = spinner;
    [spinner startAnimating];
    
    PLVDevice *device = self.sortedDevices[indexPath.row];
    [device prepareWithCompletionHandler:^(NSError *error) {
        assert([NSThread isMainThread]);
        cell.accessoryView = nil;
        if (device.isReady) {
            cell.accessoryType = UITableViewCellAccessoryCheckmark;
            self.selectedDevice = device;
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                [self.delegate deviceListViewControllerDidSelectDevice:self];
            });
        } else {
            cell.accessoryType = UITableViewCellAccessoryNone;
            [self showDeviceSelectionAlertWithError:error];
        }
    }];
}

@end
