//
//  ADYAppData.h
//  AdyenPOSLib
//
//  Created by Jeroen Koops on 4/10/13.
//
//

#import <Foundation/Foundation.h>

/**
 * Class containing data about the app.
 */
@interface ADYAppData : NSObject

@property (nonatomic, strong) NSString *devicePlatform;
@property (nonatomic, strong) NSString *deviceName;
@property (nonatomic, strong) NSString *deviceVersion;
@property (nonatomic, strong) NSString *applicationName;
@property (nonatomic, strong) NSString *AdyenLibraryVersion;

@end
