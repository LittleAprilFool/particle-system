//
//  particle.h
//  GPU
//
//  Created by April Wang on 1/14/16.
//  Copyright (c) 2016 April Wang. All rights reserved.
//

#ifndef __GPU__particle__
#define __GPU__particle__

#include <stdio.h>
#include "gpu.h"

class Particle {
  
public:
  Particle();
  ~Particle();
  void init();
  void update();
  void display();
  void resize(int w, int h);
  void keyboard(unsigned char key, int x, int y);
private:
  GLuint program;
  GLuint vaoHandle;
  GLuint initVelBufferHandle, startTimeBufferHandle;
  
  void initBuffers();
  void linkShader();
  
  int nParticles;
  int width, height;
  
  mat4 model;
  mat4 view;
  mat4 projection;
  
  float time;
  float angle;
  
  float randFloat();
  
  clock_t starttimer;
};

#endif /* defined(__GPU__particle__) */
