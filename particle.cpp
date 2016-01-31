//
//  particle.cpp
//  GPU
//
//  Created by April Wang on 1/14/16.
//  Copyright (c) 2016 April Wang. All rights reserved.
//

#include "particle.h"

Particle::Particle(){

}

Particle::~Particle(){

}

void Particle::init(){
  
  linkShader();
  
  initBuffers();
  
  GLuint gravity = glGetUniformLocation(program, "Gravity");
  GLuint plt = glGetUniformLocation(program, "ParticleLifetime");
  //GLuint ptex = glGetUniformLocation(program, "ParticleTex");
  
  glUniform1f(plt, 5.0f);
  //glUniform3f(gravity, 0.0f, -0.2f, 0.0f);
  
  angle = half_pi<float>();
  
  projection = mat4(1.0f);
  model = mat4(1.0f);
  view = lookAt(vec3(3.0f * cosf(angle), 1.5f, 3.0f * sinf(angle)), vec3(0.0f, 1.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
  
  //  glUniform1f(gravity, 9.8);
  mat4 mvpMatrix(1.0f);
  
  starttimer = clock();
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Particle::update(){
  clock_t currenttimer = clock();
  time = (float)(currenttimer - starttimer) / 100000;
//  cout<<time<<endl;
}

void Particle::display(){

  mat4 mv = view * model;
  mat4 mvp = projection * mv;
  
  GLuint MVP = glGetUniformLocation(program, "MVP");
  glUniformMatrix4fv(MVP, 1, GL_TRUE,&mvp[0][0]);
  
  GLuint ttime = glGetUniformLocation(program, "Time");
  glUniform1f(ttime, time);
  
  glClear(GL_COLOR_BUFFER_BIT);

  glPointSize(3);
  glDrawArrays(GL_POINTS, 0, nParticles);
  
  glutSwapBuffers();
}

void Particle::resize(int w, int h){
  glViewport(0, 0, w, h);
}

void Particle::keyboard(unsigned char key, int x, int y){

}

void Particle::initBuffers(){
  nParticles = 10000;
  
  //generate buffers
  GLuint vboHandles[2];
  glGenBuffers(2, vboHandles);
  initVelBufferHandle = vboHandles[0];
  startTimeBufferHandle = vboHandles[1];
  
  // set the initial velocity data
  vec3 v(0.0f);
  
  float velocity, theta, phi;
  GLfloat *datai = new GLfloat[nParticles * 3];
  
  for(unsigned int i = 0; i < nParticles; i ++) {
    theta = mix(0.0f, (float)M_PI / 6.0f, randFloat());
    phi = mix(0.0f, (float)M_PI * 2, randFloat());
    v.x = sinf(theta) * cosf(phi);
    v.y = cosf(theta);
    v.z = sinf(theta) * sinf(phi);
  
    velocity = mix(0.25f, 0.5f, randFloat());
    v = v * velocity;
    datai[3 * i] = v.x;
    datai[3 * i + 1] = v.y;
    datai[3 * i + 2] = v.z;
  }
  
  //set the start time data
  float *datas = new GLfloat[nParticles];
  float time = 0.0f, rate = 0.0005f;
  for(unsigned int i = 0; i < nParticles; i ++) {
    datas[i] = time;
    time += rate;
  }
  
  //allocate space for init velocity buffer
  glBindBuffer(GL_ARRAY_BUFFER, initVelBufferHandle);
  glBufferData(GL_ARRAY_BUFFER, nParticles * 3 * sizeof(GLfloat), datai, GL_STATIC_DRAW);
  
  
  
  //allocate space for start time buffer
  glBindBuffer(GL_ARRAY_BUFFER, startTimeBufferHandle);
  glBufferData(GL_ARRAY_BUFFER, nParticles * sizeof(GLfloat), datas, GL_STATIC_DRAW);
  
  //attach vbo to vao
  glGenVertexArrays(1, &vaoHandle);
  glBindVertexArray(vaoHandle);
  
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  
  glBindBuffer(GL_ARRAY_BUFFER, initVelBufferHandle);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
  
  glBindBuffer(GL_ARRAY_BUFFER, startTimeBufferHandle);
  glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
  
}

void Particle::linkShader(){
  // Load shaders and use the resulting shader program
  program = InitShader( "vshader.glsl", "fshader.glsl" );
  glUseProgram( program );
}

float Particle::randFloat(){
  float result = ((float)rand() / RAND_MAX);
  return result;
}