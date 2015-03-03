PaylevenSDK integration

1. Drag PaylevenSDK.framework, AdyenToolkit.framework, and AdyenToolkit.bundle into Xcode project.

2. Open the Build Phases of your target and add the following frameworks to the Link Binary With Libraries section:

   CoreData.framework
   CoreLocation.framework
   ExternalAccessory.framework
   SystemConfiguration.framework
   libsqlite3.0.dylib

3. Open the Build Settings of your target and add -ObjC flag to Other Linker Flags.

4. Open the Info.plist and add the following entries:

   o CFBundleDisplayName with the display name for your app.
   o UISupportedExternalAccessoryProtocols with an array of just one value 'com.adyen.bt1'.
   o For iOS 8: NSLocationWhenInUseUsageDescription or NSLocationAlwaysUsageDescription, for iOS 7:
     NSLocationUsageDescription with the location usage description message for the users.

6. Import PaylevenSDK into your files:

   #import <PaylevenSDK/PaylevenSDK.h>

7. See the PLVPayleven class description on how to login and make a payment.
