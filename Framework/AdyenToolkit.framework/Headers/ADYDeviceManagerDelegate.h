//
//  ADYDeviceManagerDelegate.h
//  AdyenPOSLib
//
//  Created by Jeroen Koops on 4/11/13.
//
//

#ifndef AdyenPOSLib_ADYEMVDeviceManagerDelegate_h
#define AdyenPOSLib_ADYEMVDeviceManagerDelegate_h

/**
 * Delegate used by [Adyen boardDeviceWithDelegate:] to keep the caller
 * informed about the configuration's progress and completion.
 * 
 * Configuring a device consists of 5 steps. These are represented by the
 * enum `ADYEMVDeviceManagerStep`, with possible values:
 *
 * 1. `ADYEMVDeviceManagerStepIdentifyPaymentDevice`: query the payment device about its identity.
 * 2. `ADYEMVDeviceManagerStepRegisterPaymentDevice`: register the payment device with the backend.
 * 3. `ADYEMVDeviceManagerStepLoadConfiguration`: load the device's configuration from the backend.
 * 4. `ADYEMVDeviceManagerStepStoreConfiguration`: store the new configuration on the device.
 * 5. `ADYEMVDeviceManagerStepCheckConfiguration`:  check that the new configuration has been installed successfully.
 */

// Documenting enums is not supported by appledoc, hence the kludge
typedef enum {
    ADYEMVDeviceManagerStepIdentifyPaymentDevice,
    ADYEMVDeviceManagerStepRegisterPaymentDevice,
    ADYEMVDeviceManagerStepLoadConfiguration,
    ADYEMVDeviceManagerStepStoreConfiguration,
    ADYEMVDeviceManagerStepCheckConfiguration
} ADYEMVDeviceManagerStep;

@protocol ADYDeviceManagerDelegate

/**
 * Called to indicate that the given configuration-step will be executed.
 * @param step step that will be executed
 */
-(void)deviceManagerWillBeginStep:(ADYEMVDeviceManagerStep)step;

/**
 * Called to indicate that the given configuration-step has been executed successfully
 * @param step step that has been executed
 */
-(void)deviceManagerDidCompleteStep:(ADYEMVDeviceManagerStep)step;

/**
 * Called to indicate that the given configuration-step failed to execute. After this
 * method has been called, configuration is terminated and no more methods will be called
 * on the delegate.
 * @param step step that failed to executed
 */
-(void)deviceManagerDidFailStep:(ADYEMVDeviceManagerStep)step withError:(NSError*)error;

/**
 * Called to indicate that configuration was successful. After this method has been called,
 * no more methods will be called on the delegate.
 */
-(void)deviceManagerDidComplete;

@end

#endif