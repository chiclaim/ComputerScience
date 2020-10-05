//
//  复数计算器
//
//  Created by 余志强 on 2020/9/26.
//  Copyright © 2020 yzq. All rights reserved.
//

#include "headers/complexCalculator.h"
#include <math.h>

complex complexCalculator::add(complex x,complex y){
    return x+y;
}

complex complexCalculator::subtract(complex x, complex y){
    return x-y;
}

complex complexCalculator::multiply(complex x, complex y){
    return x*y;
}

complex complexCalculator::divide(complex x, complex y){
    return x/y;
}
