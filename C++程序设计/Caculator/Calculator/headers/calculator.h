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
        T add(T x,T y){ //加
            return x + y;
        }
        T subtract(T x,T y){ //减
            return x - y;
        }
        T multiply(T x,T y){ //乘
            return x * y;
        }
        T divide(T x,T y){ //除
            return x / y;
        }
};

#endif /* calculator_h */
