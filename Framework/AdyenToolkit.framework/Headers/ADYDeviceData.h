//
//  ADYDeviceData.h
//  AdyenPOSLib
//
//  Created by Jeroen Koops on 4/10/13.
//
//

#import <Foundation/Foundation.h>

@interface ADYDeviceData : NSObject <NSCopying>

@property (nonatomic, strong) NSString *terminalId;
@property (nonatomic, strong) NSString *terminalMacAddress;
@property (nonatomic, strong) NSString *terminalConfiguredName;
@property (nonatomic, strong) NSString *terminalBrand;
@property (nonatomic, strong) NSString *terminalType;
@property (nonatomic, strong) NSString *terminalSerialNumber;
@property (nonatomic, strong) NSString *terminalApiVersion;
@property (nonatomic, strong) NSString *terminalApiVersionUpgrade;
@property (nonatomic, strong) NSString *upgradeLastReceivedInstallOrder;
@property (nonatomic, strong) NSString *upgradeLastInstallOrderToSend;
@property (nonatomic, strong) NSString *upgradeBytesReceived;
@property (nonatomic, assign) BOOL     updateAvailable;
@property (nonatomic, strong) NSString *terminalOsVersion;
@property (nonatomic, strong) NSString *terminalHardwareVersion;
@property (nonatomic, strong) NSNumber *printerWidthInPixels;
@property (nonatomic, assign) NSUInteger terminalUnconfirmedBatches;
@property (nonatomic, strong) NSArray* terminalMerchantAccounts;
@property (nonatomic, assign) BOOL isBoarded;
@property (nonatomic, readonly) BOOL hasPrinter;
@property (nonatomic, readonly) BOOL hasPINDigitNotification;
@property (nonatomic, readonly) BOOL hasCardInsertionRemovalNotification;

/** `nil` if interface-version is unknown, a version-string if it is known. */
@property (nonatomic, strong) NSString* interfaceVersion;
@property (nonatomic, readonly) NSNumber* interfaceVersionNumber;
@end
