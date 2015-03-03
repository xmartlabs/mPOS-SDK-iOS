//
//  PLVDevice.h
//  PaylevenSDK
//
//  Created by Alexei Kuznetsov on 15.10.14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

@import Foundation;

/** PLVDevice class represents a payment device. */
@interface PLVDevice : NSObject

/** The device name. */
@property(nonatomic, readonly, copy) NSString *name;

/** A Boolean value indicating if the device is ready for payments. */
@property(nonatomic, readonly, getter=isReady, assign) BOOL ready;

/**
 * Prepares the device for payments.
 *
 * @param completionHandler A block that is called when the preparation attempt finishes. Check the receiver's `ready`
 * property to get the current state. The block takes a single parameter `error` containing error information in case
 * of preparation error.
 */
- (void)prepareWithCompletionHandler:(void (^)(NSError *error))completionHandler;

@end
