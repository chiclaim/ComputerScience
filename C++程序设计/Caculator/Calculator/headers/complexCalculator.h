//
//  complexCalculator.h
//  Calculator
//
//  Created by 余志强 on 2020/9/26.
//  Copyright © 2020 yzq. All rights reserved.
//

#ifndef complexCalculator_h
#define complexCalculator_h

#include "calculator.h"
#include "complex.h"



class complexCalculator : public calculator<complex> {
    public :
        complex add(complex x,complex y);
        complex subtract(complex x,complex y);
        complex multiply(complex x,complex y);
        complex divide(complex x,complex y);
};


#endif /* complexCalculator_h */
