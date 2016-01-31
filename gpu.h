//
//  gpu.h
//  GPU
//
//  Created by April Wang on 12/7/15.
//  Copyright (c) 2015 April Wang. All rights reserved.
//

#ifndef GPU_gpu_h
#define GPU_gpu_h

//  Include system headers
//
#include <cmath>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

//  Define M_PI in the case it's not defined in the math header file
//
#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif

//  Include OpenGL header files and helpers
//
#include <OpenGL/gl3.h>
#include <GLUT/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

//  Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))
namespace gpu {
  
  //  Helper function to load vertex and fragment shader files
  GLuint InitShader( const char* vertexShaderFile,
                    const char* fragmentShaderFile );
  
  //  Defined constant for when numbers are too small to be used in the
  //    denominator of a division operation.  This is only used if the
  //    DEBUG macro is defined.
  const GLfloat  DivideByZeroTolerance = GLfloat(1.0e-07);
  
  //  Degrees-to-radians constant
  const GLfloat  DegreesToRadians = M_PI / 180.0;
}

//  Globally use our namespace in our example programs.
using namespace gpu;

#endif
