//
//  numberCalculator.h
//  Calculator
//
//  Created by 余志强 on 2020/9/26.
//  Copyright © 2020 yzq. All rights reserved.
//

#ifndef numberCalculator_h
#define numberCalculator_h

#include "calculator.h"


class numberCalculator : public calculator<double> {
    
    public :
        double mypow(double x,double y);
        double mysqrt(double x);
};

#endif /* numberCalculator_h */
