[![CocoaPods](https://img.shields.io/badge/Licence-MIT-brightgreen.svg?style=flat-square)]()
[![CocoaPods](https://img.shields.io/badge/Platform-iOS-yellow.svg?style=flat-square)]()
[![CocoaPods](https://img.shields.io/github/tag/Payleven/mPOS-SDK-iOS.svg?style=flat-square)]()
[![CocoaPods](https://img.shields.io/badge/Made%20in-Berlin-red.svg?style=flat-square)]()

# payleven mPOS SDK

This project provides an iOS API to communicate with the payleven Chip & PIN card reader in order to accept debit and credit card payments. Learn more about the Chip & PIN card reader and payment options on one of payleven's regional [websites](https://payleven.com/).

### Prerequisites
1. Register with [payleven](http://payleven.com) in order to get personal merchant credentials and a card reader.
2. Get API key on payleven [developer portal](https://payleven.de/developers/).

### Installation

##### CocoaPods

Coming soon...

##### Manual Set-Up

1. Drag *PaylevenSDK.framework*, *AdyenToolkit.framework*, and *AdyenToolkit.bundle* into your Xcode project.

2. Open the *Build Phases* of your target and add the following frameworks to the *Link Binary With Libraries* section:

        CoreData.framework  
        CoreLocation.framework
        ExternalAccessory.framework
        SystemConfiguration.framework
        libsqlite3.0.dylib

3. Open the *Build Settings* of your target and add `-ObjC` flag to Other Linker Flags.

4. Open the *Info.plist* and add the following entries:

  * `CFBundleDisplayName` with the display name for your app.
  * `UISupportedExternalAccessoryProtocols` with an array of just one value `com.adyen.bt1`.
  * For iOS 8: `NSLocationWhenInUseUsageDescription` or `NSLocationAlwaysUsageDescription`,\n for iOS 7: `NSLocationUsageDescription` with the location usage description message for the users.

5. Import PaylevenSDK into your files:

        #import <PaylevenSDK/PaylevenSDK.h>


#### Getting Started    
##### Authenticate your App
Use API key received from payleven together with your payleven merchant account to authenticate your app. 
Hint: Check out our Sample Demo to see how you can easily observe the Login State using KVO.
 ```c

 PLVPayleven * payleven = [[PLVPayleven alloc] init];
 [payleven loginWithUsername:@"aUsernameString"
                    password:@"aPasswordString"
                      APIKey:@"anApiKey"
           completionHandler:^(NSError *error) {
           
        if (error == nil) {
            // Congrats, you're Logged In
        } else {
            // Error Handling
        }
    }];
 ```
  
##### Select the Card Reader
Once a `PLVPayleven` instance is created you need to select the card reader for your future payments.

 ```c
 //You probably want to visualize the devices in a UITableView
 NSArray * pairedDevices = self.payleven.devices;
 
 //Get the selected device from the list
  PLVDevice *device = self.sortedDevices[indexPath.row];
  NSString * deviceName = device.name;

 ```

##### Prepare Device for Payment
Prepare selected device for upcoming payment.  

 ```c
 [device prepareWithCompletionHandler:^(NSError *error) {
        if (device.isReady) {
			//Device is Ready, now let's do some Payment
        } else {
            // Error Handling
        }
    }];
 ```
  
##### Start payment
Initialize the actual payment request. For security purposes we must provide the user's current location.

 ```c
 //Here we are using an arbitrary location. In your app you must provide the user's current location
 CLLocationCoordinate2D coordinate = CLLocationCoordinate2DMake(52.5243700, 13.4105300);
 
 NSLocale* locale = [NSLocale currentLocale];
 NSDecimalNumber* amount = [NSDecimalNumber decimalNumberWithString:@"1.00" locale:locale];
 
 PLVPaymentRequest* request = [[PLVPaymentRequest alloc] initWithIdentifier:@"anArbitraryUniqueIdentifier"
                                                                     amount:amount
                                                                   currency:@"EUR"
                                                                 coordinate:coordinate];
                                                                 
 //Hint: the corresponding delegate is PLVPaymentTaskDelegate                                                                
 self.paymentTask = [self.payleven paymentTaskWithRequest:request device:self.device delegate:self]
 if (self.paymentTask == nil) {
    //Could not create Payment  
 } else {
    [self.paymentTask start];
 }

 ```
 
##### Handle payment
Implement PLVPaymentTaskDelegate's methods to respond to payment events such as the request of a payer's signature, its final approval or any errors.

 ```c
 - (void)paymentTask:(PLVPaymentTask *)paymentTask
        needsSignatureWithCompletionHandler:(void (^)(BOOL, CGImageRef))completionHandler {
    
    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    UINavigationController *navigationController
        = [storyboard instantiateViewControllerWithIdentifier:@"SignatureConfirmationNavigationController"];
    SignatureConfirmationViewController *signatureConfirmationViewController
        = (SignatureConfirmationViewController *)navigationController.topViewController;
    

	//Get Payer's signature and return using completionBlock (See our Sample App for full implementation)
	UIImage * signature = ...
    completionHandler(true, signature.CGImage);

 }

 - (void)paymentTaskDidFinish:(PLVPaymentTask *)paymentTask { 
	   
    self.receiptGenerator = paymentTask.result.receiptGenerator;
    CGFloat scale = [UIScreen mainScreen].scale;
    [self.receiptGenerator generateReceiptWithWidth:(384.0 * scale)
                                           fontSize:(16.0 * scale)
                                        lineSpacing:(8.0 * scale)
                                            padding:(20.0 * scale)
                                  completionHandler:
     ^(CGImageRef receipt) {
         CGFloat scale = [UIScreen mainScreen].scale;
         UIImage *image = [UIImage imageWithCGImage:receipt scale:scale orientation:UIImageOrientationUp];
         self.receiptGenerator = nil;
     }];
    
    self.paymentTask = nil;
 }

 - (void)paymentTask:(PLVPaymentTask *)paymentTask didFailWithError:(NSError *)error {
   	//Error handling
    self.paymentTask = nil;
 }

 ```
   
#### Documentation
[API Reference](https://github.com/payleven/mPOS-SDK-iOS)