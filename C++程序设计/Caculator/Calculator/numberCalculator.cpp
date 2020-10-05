//
//  实数的计算器
//
//  Created by 余志强 on 2020/9/26.
//  Copyright © 2020 yzq. All rights reserved.
//

#include <math.h>
#include <iostream>
#include "headers/numberCalculator.h"

double numberCalculator::add(double x,double y){
    return x+y;
}

double numberCalculator::subtract(double x, double y){
    return x-y;
}

double numberCalculator::multiply(double x, double y){
    return x*y;
}

double numberCalculator::divide(double x, double y){
    if(y == 0) {
        throw std::runtime_error("division is zero");
    }
    return x/y;
}

double numberCalculator::mypow(double x, double y){
    return pow(x, y);
}

double numberCalculator::mysqrt(double x){
    return sqrt(x);
}
