//
//  cube.cpp
//  GPU
//
//  Created by April Wang on 1/15/16.
//  Copyright (c) 2016 April Wang. All rights reserved.
//

#include "cube.h"


void Cube::init(){
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  vertices[0] = vec4( -0.5, -0.5,  0.5, 1.0 );
  vertices[1] = vec4( -0.5,  0.5,  0.5, 1.0 );
  vertices[2] = vec4(  0.5,  0.5,  0.5, 1.0 );
  vertices[3] = vec4(  0.5, -0.5,  0.5, 1.0 );
  vertices[4] = vec4( -0.5, -0.5, -0.5, 1.0 );
  vertices[5] = vec4( -0.5,  0.5, -0.5, 1.0 );
  vertices[6] = vec4(  0.5,  0.5, -0.5, 1.0 );
  vertices[7] = vec4(  0.5, -0.5, -0.5, 1.0 );
  
  vertex_colors[0] = vec4( 0.0, 0.0, 0.0, 1.0 );  // black
  vertex_colors[1] = vec4( 1.0, 0.0, 0.0, 1.0 ); // red
  vertex_colors[2] = vec4( 1.0, 1.0, 0.0, 1.0 );  // yellow
  vertex_colors[3] = vec4( 0.0, 1.0, 0.0, 1.0 );  // green
  vertex_colors[4] = vec4( 0.0, 0.0, 1.0, 1.0 );  // blue
  vertex_colors[5] = vec4( 1.0, 0.0, 1.0, 1.0 );  // magenta
  vertex_colors[6] = vec4( 1.0, 1.0, 1.0, 1.0 );  // white
  vertex_colors[7] = vec4( 0.0, 1.0, 1.0, 1.0 );  //cyan
  Numvertices = 36;
  Index = 0;
  
  quad(1, 0, 3, 2);
  
  // Create a vertex array object
  GLuint vao;
  glGenVertexArrays( 1, &vao );
  glBindVertexArray( vao );
  
  // Create and initialize a buffer object
  GLuint buffer[2];
  glGenBuffers( 2, buffer );
  GLuint colorBuffer = buffer[0];
  GLuint pointBuffer = buffer[1];
  
  glBindBuffer( GL_ARRAY_BUFFER, pointBuffer );
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
  
  // Load shaders and use the resulting shader program
  GLuint program = InitShader( "vshader1.glsl", "fshader1.glsl" );
  glUseProgram( program );
  
  // set up vertex arrays
  GLuint vPosition = glGetAttribLocation( program, "vPosition" );
  glEnableVertexAttribArray( vPosition );
  
  glBindBuffer(GL_ARRAY_BUFFER, pointBuffer);
  glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, (GLubyte*) NULL);

  GLuint vColor = glGetAttribLocation( program, "vColor" );
  glEnableVertexAttribArray( vColor );
  
  glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
  glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (GLubyte*) NULL);
  
  glEnable( GL_DEPTH_TEST );
  glClearColor( 0, 0, 0, 0 );
  

  
}

void Cube::quad( int a, int b, int c, int d )
{
  colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
  colors[Index] = vertex_colors[b]; points[Index] = vertices[b]; Index++;
  colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
  colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
  colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
  colors[Index] = vertex_colors[d]; points[Index] = vertices[d]; Index++;
}

void Cube::display(){
  
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
  
  glPointSize(8);
  glDrawArrays( GL_POINTS, 0, Numvertices );
  
  glutSwapBuffers();

}