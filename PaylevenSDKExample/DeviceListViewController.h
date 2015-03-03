//
//  DeviceListViewController.h
//  PaylevenSDKExample
//
//  Created by Alexei Kuznetsov on 15.10.14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

@import UIKit;

@class PLVDevice, PLVPayleven;

@protocol DeviceListViewControllerDelegate;

/** A view controller that displays the list of devices and allows to prepare the devices for payments. */
@interface DeviceListViewController : UITableViewController

/** The receiver's delegate. */
@property(nonatomic, weak) id <DeviceListViewControllerDelegate> delegate;

/** Payleven instance. */
@property(nonatomic, strong) PLVPayleven *payleven;

/** Device that is currently selected for payments. */
@property(nonatomic, strong) PLVDevice *selectedDevice;

@end


/**
 * DeviceListViewControllerDelegate protocol must be adopted by objects that want to act as DeviceListViewController's
 * delegate.
 */
@protocol DeviceListViewControllerDelegate <NSObject>

@required

/**
 * Called when DeviceListViewController selects a device.
 *
 * The @em selectedDevice property contains the selected device or nil if no device was selected.
 */
- (void)deviceListViewControllerDidSelectDevice:(DeviceListViewController *)deviceListViewController;

/** Called when device selection cancels. */
- (void)deviceListViewControllerDidCancel:(DeviceListViewController *)deviceListViewController;

@end
