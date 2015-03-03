//
//  LoginViewController.m
//  PaylevenSDKExample
//
//  Created by Alexei Kuznetsov on 14.10.14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

#import "LoginViewController.h"

#import <PaylevenSDK/PaylevenSDK.h>


@interface LoginViewController () <UITextFieldDelegate>

/** Username field. */
@property(nonatomic, weak) IBOutlet UITextField *usernameField;

/** Password field. */
@property(nonatomic, weak) IBOutlet UITextField *passwordField;

/** Login cell. */
@property(nonatomic, weak) IBOutlet UITableViewCell *loginCell;

/** Logout cell. */
@property(nonatomic, weak) IBOutlet UITableViewCell *logoutCell;

/** Login label. */
@property(nonatomic, weak) IBOutlet UILabel *loginLabel;

/** Logout label. */
@property(nonatomic, weak) IBOutlet UILabel *logoutLabel;

/** Login activity indicator. */
@property(nonatomic, weak) IBOutlet UIActivityIndicatorView *loginActivityIndicator;

/** Logout activity indicator. */
@property(nonatomic, weak) IBOutlet UIActivityIndicatorView *logoutActivityIndicator;

/** Calls did-finish on delegate. */
- (IBAction)cancel:(id)sender;

/** Starts login attempt. */
- (void)logIn;

/** Shows login failure alert. */
- (void)showLoginFailureAlertWithError:(NSError *)error;

/** Shows logout failure alert. */
- (void)showLogoutFailureAlertWithError:(NSError *)error;

/** Enables login cell. */
- (void)enableLoginCell;

/** Disables login cell. */
- (void)disableLoginCell;

/** Enables logout cell. */
- (void)enableLogoutCell;

/** Disables logout cell. */
- (void)disableLogoutCell;

/** Updates cells according to login state. */
- (void)updateCellsWithLoginState:(PLVPaylevenLoginState)loginState;

@end


@implementation LoginViewController

- (void)dealloc {
    self.payleven = nil;
}

- (void)setPayleven:(PLVPayleven *)payleven {
    if (_payleven != payleven) {
        if (_payleven != nil) {
            [_payleven removeObserver:self forKeyPath:@"loginState" context:NULL];
        }
        _payleven = payleven;
        if (_payleven != nil) {
            [_payleven addObserver:self forKeyPath:@"loginState" options:0 context:NULL];
        }
    }
}


#pragma mark -

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    [self updateCellsWithLoginState:self.payleven.loginState];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    [self.usernameField becomeFirstResponder];
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
    if ([keyPath isEqualToString:@"loginState"]) {
        assert([NSThread isMainThread]);
        PLVPayleven *payleven = object;
        [self updateCellsWithLoginState:payleven.loginState];
    } else {
        [super observeValueForKeyPath:keyPath ofObject:object change:change context:context];
    }
}


#pragma mark -

- (IBAction)cancel:(id)sender {
    [self.delegate loginViewControllerDidFinish:self];
}

- (void)logIn {
    assert(self.payleven != nil);
    if (self.payleven.loginState == PLVPaylevenLoginStateLoggingIn || self.payleven.loginState == PLVPaylevenLoginStateLoggingOut) {
        return;
    }
    [self.loginActivityIndicator startAnimating];
    [self.payleven loginWithUsername:self.usernameField.text
                            password:self.passwordField.text
                              APIKey:@"5e627efa546b4e3883d0da68b430725f"
                   completionHandler:^(NSError *error) {
        [self.loginActivityIndicator stopAnimating];
        if (error == nil) {
            [self.delegate loginViewControllerDidFinish:self];
        } else {
            [self showLoginFailureAlertWithError:error];
        }
    }];
}

- (void)logOut {
    assert(self.payleven != nil);
    if (self.payleven.loginState == PLVPaylevenLoginStateLoggingOut || self.payleven.loginState == PLVPaylevenLoginStateLoggingIn) {
        return;
    }
    [self.logoutActivityIndicator startAnimating];
    [self.payleven logoutWithCompletionHandler:^(NSError *error) {
        [self.logoutActivityIndicator stopAnimating];
        if (error != nil) {
            [self showLogoutFailureAlertWithError:error];
        }
    }];
}

- (void)showLoginFailureAlertWithError:(NSError *)error {
    NSString *title = NSLocalizedString(@"Could Not Log In", @"Login failure alert title.");
    NSString *OK = NSLocalizedString(@"OK", @"OK.");
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:title
                                                    message:error.localizedDescription
                                                   delegate:nil
                                          cancelButtonTitle:nil
                                          otherButtonTitles:OK, nil];
    [alert show];
}

- (void)showLogoutFailureAlertWithError:(NSError *)error {
    NSString *title = NSLocalizedString(@"Could Not Log Out", @"Logout failure alert title.");
    NSString *OK = NSLocalizedString(@"OK", @"OK.");
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:title
                                                    message:error.localizedDescription
                                                   delegate:nil
                                          cancelButtonTitle:nil
                                          otherButtonTitles:OK, nil];
    [alert show];
}

- (void)enableLoginCell {
    self.loginCell.selectionStyle = UITableViewCellSelectionStyleDefault;
    self.loginLabel.textColor = [UIColor colorWithRed:0.0 green:(128.0 / 255.0) blue:(255.0 / 255.0) alpha:1.0];
}

- (void)disableLoginCell {
    self.loginCell.selectionStyle = UITableViewCellSelectionStyleNone;
    self.loginLabel.textColor = [UIColor lightGrayColor];
}

- (void)enableLogoutCell {
    self.logoutCell.selectionStyle = UITableViewCellSelectionStyleDefault;
    self.logoutLabel.textColor = [UIColor colorWithRed:0.0 green:(128.0 / 255.0) blue:(255.0 / 255.0) alpha:1.0];
}

- (void)disableLogoutCell {
    self.logoutCell.selectionStyle = UITableViewCellSelectionStyleNone;
    self.logoutLabel.textColor = [UIColor lightGrayColor];
}

- (void)updateCellsWithLoginState:(PLVPaylevenLoginState)loginState {
    switch (loginState) {
        case PLVPaylevenLoginStateLoggingIn:
        case PLVPaylevenLoginStateLoggingOut:
            [self disableLoginCell];
            [self disableLogoutCell];
            break;
        case PLVPaylevenLoginStateLoggedIn:
            [self disableLoginCell];
            [self enableLogoutCell];
            break;
        case PLVPaylevenLoginStateLoggedOut:
            [self enableLoginCell];
            [self disableLogoutCell];
        default:
            break;
    }
}


#pragma mark - UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    if (indexPath.section == 1) {
        if (indexPath.row == 0) {
            [self logIn];
        } else if (indexPath.row == 1) {
            [self logOut];
        }
    }
}


#pragma mark - UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    if ([textField isEqual:self.usernameField]) {
        [self.passwordField becomeFirstResponder];
    } else if ([textField isEqual:self.passwordField]) {
        [self logIn];
        [textField resignFirstResponder];
    }
    
    return YES;
}

@end
