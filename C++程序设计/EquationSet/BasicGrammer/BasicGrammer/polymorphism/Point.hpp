//
//  Point.hpp
//  BasicGrammer
//
//  Created by 余志强 on 2020/10/11.
//  Copyright © 2020 yzq. All rights reserved.
//

#ifndef Point_hpp
#define Point_hpp

#include <stdio.h>

class Point{
    
    private :
        double x,y;
    public :
        Point(double i,double j);
        virtual double area();
    
};

#endif /* Point_hpp */
