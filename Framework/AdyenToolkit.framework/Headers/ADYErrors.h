//
//  ADYError.h
//  AdyenPOSLib
//
//  Created by Jeroen Koops on 4/10/13.
//
//

#ifndef AdyenPOSLib_ADYErrors_h
#define AdyenPOSLib_ADYErrors_h

static NSString* const ADYErrorDomain = @"Adyen";

// Errorcodes used in range 0 - 9999
typedef enum {
    /**
     * Error indicating that an error occurred that cannot
     * be categorized as one of the other errors.
     */
    ADYErrorCodeUnknownError = 0,

    /**
     * Error occurring when an attempt is made to use
     * a payment device while no payment device is
     * connected.
     */
    ADYErrorCodeNoDeviceConnected = 100,

    /**
     * Error occurring when an attempt is made to use
     * a payment device that has been configured for another
     * merchant.
     */
    ADYErrorCodeUnauthorizedForDevice = 101,
    
    /**
     * The payment device could not execute a command
     * sent to it.
     */
    ADYErrorCodeDeviceError = 102,
    
    /**
     * Error indicating that the supplied merchant credentials
     * are incorrect for the payment device used.
     */
    ADYErrorCodeInvalidCredentialsForPaymentDevice = 103,
    
    /**
     * Error indicating that a transaction was started with an amount that
     * is too low.
     */
    ADYErrorCodeAmountTooLow = 104,

    /**
     * Error indicating that the transaction could not be started due to
     * some invalid parameters used to start it. Example: invalid currency,
     * manual keyed entry not allowed, amount too low, etc.
     *
     * Check the root error (userInfo: NSUnderlyingErrorKey) for more details.
     */
    ADYErrorCodeTransactionInitializationError = 105,

    /**
     * Error indicating that app does not appear to have rights to use the
     * Location Services of the device. The user is required to allow use
     * of these services so the Adyen framework can determine the location
     * where the transaction is being started. Adyen is required to know
     * the location of it's transactions because of certification.
     */
    ADYErrorCodeTransactionRequiresLocationServices = 106,

    /**
     * Error indicating that the supplied merchant credentials
     * are incorrect for the backend.
     */
    ADYErrorCodeInvalidCredentialsForPSP = 200,
    
    /**
     * Error indicating that communication with the payment
     * device failed.
     */
    ADYErrorCodePaymentDeviceConnectionError = 300,
    
    /**
     * Error indicating that communication over the network 
     * failed.
     */
    ADYErrorCodeNetworkError = 400,

    /**
     * Error indicating that a backend system could not be reached
     * because the iOS device does not have an internet connection.
     */
    ADYErrorCodeNoInternetConnection = 401,

    /**
     * An unrecoverable error occured on the server.
     */
    ADYErrorCodeInternalServerError = 402,

    /**
     * Error indicating that registration of the app failed.
     */
    ADYErrorCodeAppRegistrationFailed = 500,
    
    /**
     * An attempt is made to register a device from an app that has not been registered
     */
    ADYErrorCodeInvalidApp = 501,
    
    /**
     * The user does not have sufficient permissions on the PSP for the requested operation
     */
    ADYErrorCodeUserPermissionError = 502,
    
    /**
     * The merchant account given is not valid.
     */
    ADYErrorCodeInvalidMerchant = 503,
    
    /**
     * An attempt was made to log in without first logging out
     */
    ADYErrorCodeAlreadyLoggedIn = 504,
    
    /**
     * An attempt was made to log out without first logging in
     */
    ADYErrorCodeNotLoggedIn = 505,

    /**
     * Error indicating that the token did not become valid
     * on the PAL in time after app registration.
     */
    ADYErrorCodeAppRegistrationTokenCheckTimeout = 506,

    /**
     * The requested action is not supported by the payment terminal
     */
    ADYErrorCodeNotSupported = 507,

    /**
     * One or more used parameters are incorrect or missing
     */
    ADYErrorCodeInvalidParameter = 508,

    /**
     * Transaction errors
     */
    ADYErrorCodeDeviceEMVError = 600,
    ADYErrorCodeDeviceSAPIError = 601,
    ADYErrorCodeDevicePrintReceiptFailed = 700,
    ADYErrorCodePSPValidateError = 701,

} ADYErrorCode;

#endif
