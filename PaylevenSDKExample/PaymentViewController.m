//
//  PaymentViewController.m
//  PaylevenSDKExample
//
//  Created by Alexei Kuznetsov on 23/10/14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

#import "PaymentViewController.h"

#import <PaylevenSDK/PaylevenSDK.h>

#import "CurrencyViewController.h"
#import "ReceiptViewController.h"
#import "SignatureConfirmationViewController.h"


@interface PaymentViewController () <PLVPaymentTaskDelegate>

/** Payment amount field. */
@property(nonatomic, weak) IBOutlet UITextField *amountField;

/** Currency label. */
@property(nonatomic, weak) IBOutlet UILabel *currencyLabel;

/** Payment activity indicator. */
@property(nonatomic, weak) IBOutlet UIActivityIndicatorView *paymentActivityIndicator;

/** Currency. */
@property(nonatomic, copy) NSString *currency;

/** Number formatter. */
@property(nonatomic, strong) NSNumberFormatter *formatter;

/** Payment task. */
@property(nonatomic, strong) PLVPaymentTask *paymentTask;

/** Receipt generator. */
@property(nonatomic, strong) PLVReceiptGenerator *receiptGenerator;

/** Location Manager */
@property(nonatomic, strong) CLLocationManager* locationManager;

/** Flag for remove signature VC */
@property(nonatomic) BOOL signingViewControllerPresent;

/** Cancels the payment task and calls delegate with did-finish message. */
- (IBAction)close:(id)sender;

/** Cancels the payment task. */
- (IBAction)cancel:(id)sender;

/** Shows alert with the specified title and message. */
- (void)showAlertWithTitle:(NSString *)title message:(NSString *)message;

/** Shows receipt view controller. */
- (void)showReceiptViewControllerWithReceipt:(UIImage *)receipt;

/** Generates random alphanumeric string. */
- (NSString *)generateRandomString;

/** Updates currency label with currency. */
- (void)updateCurrencyLabelWithCurrency:(NSString *)currency;

@end


@implementation PaymentViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.currency = @"EUR";
    
    self.formatter = [[NSNumberFormatter alloc] init];
    self.formatter.numberStyle = NSNumberFormatterCurrencyStyle;
    self.formatter.maximumFractionDigits = 2;
    
    self.amountField.text = @"";
    [self updateCurrencyLabelWithCurrency:self.currency];
    
    self.locationManager = [[CLLocationManager alloc] init];
    
    self.locationManager.delegate = (id<CLLocationManagerDelegate>)self;
    
    self.signingViewControllerPresent = FALSE;
    
    NSUInteger code = [CLLocationManager authorizationStatus];
    
    if (code == kCLAuthorizationStatusNotDetermined && ([self.locationManager respondsToSelector:@selector(requestAlwaysAuthorization)] || [self.locationManager respondsToSelector:@selector(requestWhenInUseAuthorization)])) {
        // choose one request according to your business.
        if([[NSBundle mainBundle] objectForInfoDictionaryKey:@"NSLocationAlwaysUsageDescription"]){
            [self.locationManager requestAlwaysAuthorization];
        } else if([[NSBundle mainBundle] objectForInfoDictionaryKey:@"NSLocationWhenInUseUsageDescription"]) {
            [self.locationManager  requestWhenInUseAuthorization];
        } else {
            NSLog(@"Info.plist does not contain NSLocationAlwaysUsageDescription or NSLocationWhenInUseUsageDescription");
        }
    }
    
    [self.locationManager startUpdatingLocation];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    if (!self.amountField.isFirstResponder) {
        [self.amountField becomeFirstResponder];
    }
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    if (self.amountField.isFirstResponder) {
        [self.amountField resignFirstResponder];
    }
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"OpenCurrencyViewController"]) {
        CurrencyViewController *currencyViewController = segue.destinationViewController;
        currencyViewController.selectedCurrency = self.currency;
        currencyViewController.didSelectCurrencyBlock = ^(NSString *currency) {
            self.currency = currency;
            [self updateCurrencyLabelWithCurrency:currency];
        };
    }
}


#pragma mark - Private

- (IBAction)close:(id)sender {
    [self.paymentTask cancel];
    [self.delegate paymentViewControllerDidFinish:self];
}

- (IBAction)cancel:(id)sender {
    [self.paymentTask cancel];
}

- (void)showAlertWithTitle:(NSString *)title message:(NSString *)message {
    NSString *OK = NSLocalizedString(@"OK", @"OK.");
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:title
                                                    message:message
                                                   delegate:nil
                                          cancelButtonTitle:nil
                                          otherButtonTitles:OK, nil];
    [alert show];
}

- (void)showReceiptViewControllerWithReceipt:(UIImage *)receipt {
    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    UINavigationController *navigationController
        = [storyboard instantiateViewControllerWithIdentifier:@"ReceiptViewNavigationController"];
    ReceiptViewController *receiptViewController
        = (ReceiptViewController *)navigationController.topViewController;
    receiptViewController.receipt = receipt;
    receiptViewController.didFinishBlock = ^{
        [self dismissViewControllerAnimated:YES completion:nil];
    };
    
    [self presentViewController:navigationController animated:YES completion:nil];
}

- (NSString *)generateRandomString {
    static NSString * const alphabet = @"abcdefghijklmnopqrstuvwxyz1234567890";
    NSUInteger alphabetLength = alphabet.length;
    const NSUInteger stringLength = 20;
    NSMutableString *string = [NSMutableString stringWithCapacity:stringLength];
    for (NSUInteger i = 0; i < stringLength; i++) {
        u_int32_t randomIndex = arc4random() % alphabetLength;
        unichar c = [alphabet characterAtIndex:randomIndex];
        [string appendFormat:@"%C", c];
    }
    
    return string;
}

- (void)updateCurrencyLabelWithCurrency:(NSString *)currency {
    NSLocale *locale = nil;
    if ([currency isEqualToString:@"EUR"]) {
        locale = [NSLocale localeWithLocaleIdentifier:@"de_DE"];
    } else if ([currency isEqualToString:@"GBP"]) {
        locale = [NSLocale localeWithLocaleIdentifier:@"en_GB"];
    }
    self.currencyLabel.text = [NSString stringWithFormat:@" %@", [locale objectForKey:NSLocaleCurrencySymbol]];
}


#pragma mark - UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    if (indexPath.section == 1 && indexPath.row == 0 && self.paymentTask == nil) {
        NSLocale *locale = [NSLocale currentLocale];
        NSDecimalNumber *amount = [NSDecimalNumber decimalNumberWithString:self.amountField.text locale:locale];

        CLLocationCoordinate2D coordinate = self.locationManager.location.coordinate;
            
        if (!CLLocationCoordinate2DIsValid(coordinate)) {
            NSAssert(Nil, @"Invalid Coordinate");
        }
        
        PLVPaymentRequest *request = [[PLVPaymentRequest alloc] initWithIdentifier:[self generateRandomString]
                                                                            amount:amount
                                                                          currency:self.currency
                                                                        coordinate:coordinate];
        self.paymentTask = [self.payleven paymentTaskWithRequest:request device:self.device delegate:self];
        if (self.paymentTask == nil) {
            NSString *title = NSLocalizedString(@"Could Not Create Payment", @"Alert title.");
            NSString *message = NSLocalizedString(@"Error creating payment task. "
                                                   "Make sure you’re logged in and the payment device is ready.",
                                                  @"Alert message");
            [self showAlertWithTitle:title message:message];
        } else {
            [self.paymentTask start];
            [self.paymentActivityIndicator startAnimating];
        }
    }
}


#pragma mark - PLVPaymentTaskDelegate

- (void)paymentTask:(PLVPaymentTask *)paymentTask
        needsSignatureWithCompletionHandler:(void (^)(BOOL, CGImageRef))completionHandler {
    
    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    UINavigationController *navigationController
        = [storyboard instantiateViewControllerWithIdentifier:@"SignatureConfirmationNavigationController"];
    SignatureConfirmationViewController *signatureConfirmationViewController
        = (SignatureConfirmationViewController *)navigationController.topViewController;
    
    NSURL *signatureURL = [[NSBundle mainBundle] URLForResource:@"signature" withExtension:@"png"];
    UIImage *signature = [UIImage imageWithContentsOfFile:signatureURL.path];
    signatureConfirmationViewController.signature = signature;
    
    signatureConfirmationViewController.didFinishBlock = ^(BOOL confirmed) {
        completionHandler(confirmed, signature.CGImage);
        [self dismissViewControllerAnimated:YES completion:^{
            self.signingViewControllerPresent = FALSE;
        }];
    };
    signatureConfirmationViewController.didCancelBlock = ^{
        [self dismissViewControllerAnimated:YES completion:^{
            self.signingViewControllerPresent = FALSE;
            [self cancel:self];
        }];
    };
    
    self.signingViewControllerPresent = TRUE;
    [self presentViewController:navigationController animated:YES completion:nil];
}

- (void)paymentTaskDidFinish:(PLVPaymentTask *)paymentTask {
    assert([NSThread isMainThread]);
    [self.paymentActivityIndicator stopAnimating];
    
    if (self.signingViewControllerPresent) {
        [self dismissViewControllerAnimated:NO completion:^{
            self.signingViewControllerPresent = FALSE;
            [self presentReceiptFor:paymentTask];
        }];
    } else {
        [self presentReceiptFor:paymentTask];
    }
}

- (void) presentReceiptFor:(PLVPaymentTask *)paymentTask {
    
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
         [self showReceiptViewControllerWithReceipt:image];
         self.receiptGenerator = nil;
     }];
    
    self.paymentTask = nil;
    
}

- (void)paymentTask:(PLVPaymentTask *)paymentTask didFailWithError:(NSError *)error {
    assert([NSThread isMainThread]);
    [self.paymentActivityIndicator stopAnimating];
    
    NSString *title = NSLocalizedString(@"Payment Error", @"Payment error alert title.");
    [self showAlertWithTitle:title message:error.localizedDescription];
    
    self.paymentTask = nil;
}

@end
