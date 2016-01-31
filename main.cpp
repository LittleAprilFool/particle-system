//
//  main.cpp
//  GPU
//
//  Created by April Wang on 12/7/15.
//  Copyright (c) 2015 April Wang. All rights reserved.
//

#include "particle.h"
//#include "cube.h"
Particle * particle;
//Cube *cube;

//  opengl initialize
void init()
{
// cube->init();
particle->init();
}

void
display( void )
{
  particle->display();
//  cube->display();
}

void
keyboard( unsigned char key, int x, int y )
{
//  particle->keyboard(key, x, y);
}

void update(){
  float t;
  particle->update();
  glutPostRedisplay();
  usleep(600);
}


void
reshape( int width, int height )
{
//  particle->resize(width, height);
//  glViewport( 0, 0, width, height );
}

int main( int argc, char **argv )
{
  particle = new Particle();
  
//  cube = new Cube();
  
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE );
  //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize( 800, 800 );
  glutCreateWindow( "My Particle" );
  
  init();
  
  glutDisplayFunc( display );
  glutIdleFunc(update);
  glutKeyboardFunc( keyboard );
  glutReshapeFunc( reshape );
  
  glutMainLoop();
  
  return 0;
}