//
//  RootViewController.m
//  PaylevenSDKExample
//
//  Created by Alexei Kuznetsov on 14.10.14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

#import "RootViewController.h"

#import <PaylevenSDK/PaylevenSDK.h>

#import "DeviceListViewController.h"
#import "LoginViewController.h"
#import "PaymentViewController.h"


@interface RootViewController () <DeviceListViewControllerDelegate, LoginViewControllerDelegate, PaymentViewControllerDelegate>

/** Payleven. */
@property(nonatomic, strong) PLVPayleven *payleven;

/** Payment device. */
@property(nonatomic, strong) PLVDevice *device;

/** Login details label. */
@property(nonatomic, weak) IBOutlet UILabel *loginDetailsLabel;

/** Device details label. */
@property(nonatomic, weak) IBOutlet UILabel *deviceDetailsLabel;

/** Updates device details label with the specified device. */
- (void)updateDeviceDetailsLabelWithDevice:(PLVDevice *)device;

@end


@implementation RootViewController

- (void)dealloc {
    [_payleven removeObserver:self forKeyPath:@"loginState"];
    self.device = nil;
}

- (void)awakeFromNib {
    [super awakeFromNib];
    
    self.payleven = [[PLVPayleven alloc] init];
    [self.payleven addObserver:self forKeyPath:@"loginState" options:0 context:NULL];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"OpenLogin"]) {
        UINavigationController *navigationController = segue.destinationViewController;
        LoginViewController *loginViewController = (LoginViewController *)navigationController.topViewController;
        loginViewController.delegate = self;
        loginViewController.payleven = self.payleven;
        
    } else if ([segue.identifier isEqualToString:@"OpenDeviceList"]) {
        UINavigationController *navigationController = segue.destinationViewController;
        DeviceListViewController *deviceListViewController = (DeviceListViewController *)navigationController.topViewController;
        deviceListViewController.delegate = self;
        deviceListViewController.payleven = self.payleven;
        deviceListViewController.selectedDevice = self.device;
        
    } else if ([segue.identifier isEqualToString:@"OpenPayment"]) {
        UINavigationController *navigationController = segue.destinationViewController;
        PaymentViewController *paymentViewController = (PaymentViewController *)navigationController.topViewController;
        paymentViewController.delegate = self;
        paymentViewController.payleven = self.payleven;
        paymentViewController.device = self.device;
    }
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
    if (object == self.payleven && [keyPath isEqualToString:@"loginState"]) {
        assert([NSThread isMainThread]);
        NSString *loginString = nil;
        if (self.payleven.loginState == PLVPaylevenLoginStateLoggedIn) {
            loginString = NSLocalizedString(@"Successful", @"Successful login status.");
        } else {
            loginString = NSLocalizedString(@"Logged Out", @"Logged out status.");
            self.device = nil;
            [self updateDeviceDetailsLabelWithDevice:nil];
        }
        self.loginDetailsLabel.text = loginString;
        
    } else if (object == self.device && [keyPath isEqualToString:@"ready"]) {
        assert([NSThread isMainThread]);
        [self updateDeviceDetailsLabelWithDevice:self.device];
        
    } else {
        [super observeValueForKeyPath:keyPath ofObject:object change:change context:context];
    }
}


#pragma mark -

- (void)setDevice:(PLVDevice *)device {
    if (_device != device) {
        if (_device != nil) {
            [_device removeObserver:self forKeyPath:@"ready"];
        }
        _device = device;
        if (_device != nil) {
            [_device addObserver:self forKeyPath:@"ready" options:0 context:NULL];
        }
    }
}

- (void)updateDeviceDetailsLabelWithDevice:(PLVDevice *)device {
    if (device == nil) {
        self.deviceDetailsLabel.text = NSLocalizedString(@"Not Selected", @"Device not selected.");
    } else if (device.isReady) {
        if (device.name.length > 0) {
            self.deviceDetailsLabel.text = device.name;
        } else {
            self.deviceDetailsLabel.text = NSLocalizedString(@"Ready", @"Device is ready.");
        }
    } else {
        self.deviceDetailsLabel.text = NSLocalizedString(@"Not Ready", @"Device is not ready.");
    }
}


#pragma mark - LoginViewControllerDelegate

- (void)loginViewControllerDidFinish:(LoginViewController *)loginViewController {
    [self dismissViewControllerAnimated:YES completion:nil];
}


#pragma mark - DeviceListViewControllerDelegate

- (void)deviceListViewControllerDidSelectDevice:(DeviceListViewController *)deviceListViewController {
    self.device = deviceListViewController.selectedDevice;
    [self updateDeviceDetailsLabelWithDevice:self.device];
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)deviceListViewControllerDidCancel:(DeviceListViewController *)deviceListViewController {
    [self dismissViewControllerAnimated:YES completion:nil];
}


#pragma mark - PaymentViewControllerDelegate

- (void)paymentViewControllerDidFinish:(PaymentViewController *)paymentViewController {
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end
