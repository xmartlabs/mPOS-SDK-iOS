//
//  PLVPaylevenErrors.h
//  PaylevenSDK
//
//  Created by Alexei Kuznetsov on 22/10/14.
//  Copyright (c) 2014 payleven Holding GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>


/** Payleven error domain. */
extern NSString * const PLVPaylevenErrorDomain;

enum {
    /** Parameter error. */
    PLVPaylevenParameterError,
    
    /** Amount error. */
    PLVPaylevenAmountError,
    
    /** Server returned an error. */
    PLVPaylevenServerError,
    
    /** Unexpected server response error. */
    PLVPaylevenUnexpectedServerResponseError,
    
    /** Already logged in error. */
    PLVPaylevenAlreadyLoggedInError,
    
    /** Payment service provider error. */
    PLVPaylevenPaymentServiceProviderError,
    
    /** Location services error. */
    PLVPaylevenLocationServicesError
};
