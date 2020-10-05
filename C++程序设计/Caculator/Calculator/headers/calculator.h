//
//  test.h
//  Caculator
//
//  Created by 余志强 on 2020/9/26.
//  Copyright © 2020 yzq. All rights reserved.
//

#ifndef calculator_h
#define calculator_h

template <typename T>
class calculator{
    
    public :
        virtual T add(T x,T y) = 0; //加
        virtual T subtract(T x,T y) = 0; //减
        virtual T multiply(T x,T y)= 0; //乘
        virtual T divide(T x,T y)= 0; //除
};

#endif /* calculator_h */
