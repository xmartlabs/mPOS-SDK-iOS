//
//  ADYDeviceRegistry.h
//  AdyenPOSLib
//
//  Created by Jeroen Koops on 4/24/13.
//
//

#import <Foundation/Foundation.h>

@class ADYDevice;

@interface ADYDeviceRegistry : NSObject

/**
   List of currently connected devices.
 
   When new devices
   become connected, they will be added to this list, and
   when devices go away, they'll be taken out of this list.
 
   This list is fully KVO-compliant. This means that if you
   add an observer like this:
  
       [deviceRegistry addObserver:observer
                        forKeyPath:@"devices"
                           options:NSKeyValueObservingOptionsInitial|
                                   NSKeyValueObservingOptionsOld|
                                   NSKeyValueObservingOptionsNew
                           context:NULL];
  
   ..., then your observer will be notified immediately of the
   devices present, and after that of any change.

   @note when a device disconnects, the corresponding `ADYDevice` will be removed
   from the `devices` array. If you still have a reference to the `ADYDevice` instance,
   however, you can keep using it. Its status will be set to `ADYDeviceStatusGone` to 
   indicate that it's no longer connected. If the device reconnects at some later moment,
   the same `ADYDevice` instance will be reused, and its status will be updated to reflect
   the fact that it is now, once again, connected.

   @return a list of currently connected devices
 */
 
@property (nonatomic, readonly) NSMutableArray* devices;

/**
 * Finds a bluetooth `ADYDevice` with the given name.
 *
 * Note that, if `name` is not `nil`, this method will _always_ 
 * return an `ADYDevice`,
 * even when a bluetooth device by that name is not currently
 * connected. In that case, the state of the returned device
 * will be `ADYDeviceStatusGone`. If a bluetooth-device with
 * the given name is connected later, the state of the 
 * returned `ADYDevice` will change first to `ADYDeviceStatusInitializing`
 * and then to `ADYDeviceStatusInitialized`, and it will have become
 * an `ADYDevice` usable for transactions.
 *
 * What this means is that, if you know the name of the device to be
 * used (because you stored it in the `NSUserDefaults`, for example) you
 * can simply call `findDeviceByName:` to get an `ADYDevice`, and then
 * observe its `status` using key-value observing to be notified when
 * it becomes available or unavailable.
 *
 * @return an `ADYDevice` representing the bluetoothdevice with the given
 * name, or `nil` if `name` is `nil`.
 */
-(ADYDevice*)findDeviceByName:(NSString*)name;


/**
 * Adds a WiFi `ADYDevice` with the given hostname/ip address.
 *
 * Just like `findDeviceByName:`, this method will _always_
 * return an `ADYDevice` if hostname is not `nil`.
 *
 * The `ADYDeviceRegistry` will attempt to connect to the device
 * and after connecting it will periodically check if the device
 * is still online. The `state` of the returned device will be updated
 * accordingly.
 *
 * Overall, Wifi devices will behave very similar to bluetooth
 * devices. The only difference is that WiFi devices will _always_ be
 * present in the `devices` array, even if they are not connected/online.
 */
-(ADYDevice*)addDeviceWithHostname:(NSString*)hostname;

/**
 * Removes `ADYDevice`s that were added using `addDeviceWithHostname:`.
 */
-(void)removeDeviceWithHostname:(NSString *)hostname;

/// Bonjour
- (void)startPolling;
- (void)stopPolling;

@end
