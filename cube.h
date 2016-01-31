//
//  cube.h
//  GPU
//
//  Created by April Wang on 1/15/16.
//  Copyright (c) 2016 April Wang. All rights reserved.
//

#ifndef __GPU__cube__
#define __GPU__cube__

#include <stdio.h>
#include "gpu.h"

class Cube{
public:
  void init();
  void display();
  
private:
  
  vec4 vertices[8];
  vec4 vertex_colors[8];
  vec4 colors[36];
  vec4 points[36];
  int Numvertices;
  int Index;
  void quad(int a, int b, int c, int d);

};

#endif /* defined(__GPU__cube__) */
