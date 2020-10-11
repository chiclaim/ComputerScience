//
//  Circle.hpp
//  BasicGrammer
//
//  Created by 余志强 on 2020/10/11.
//  Copyright © 2020 yzq. All rights reserved.
//

#ifndef Circle_hpp
#define Circle_hpp

#include <stdio.h>
#include "Point.hpp"

class Circle: public Point{
    private :
        double radius;
    public :
        Circle(double a,double b,double r);
        double area();
        ~Circle();
    
};
#endif /* Circle_hpp */
