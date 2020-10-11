//
//  Point.hpp
//  BasicGrammer
//
//  Created by 余志强 on 2020/10/11.
//  Copyright © 2020 yzq. All rights reserved.
//

#ifndef Point_hpp
#define Point_hpp

#include "Base.hpp"

class Point : public Base {
    
    private :
        double x,y;
    public :
        static int bb;
        Point(double i,double j);
        virtual double area();
        ~Point(); // 虚析构函数
    
};
// 编译报错
//int Point::bb = 10;

#endif /* Point_hpp */
