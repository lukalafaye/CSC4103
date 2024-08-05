#ifndef NBODY_H
#define NBODY_H

struct vector {
  double x;
  double y;
};

/*
  This structure holds information for a single particle,
  including position, velocity, and mass.
*/
typedef struct particle{
  struct vector* pos;
  struct vector* vel;
  struct vector* force;
  /*
  double x_pos, y_pos;
  double x_vel, y_vel;
  double x_force, y_force;
  */
  double mass;
} particle_t;

extern int nparticles;		/* number of particles to simulate */

#define DUMP_RESULT 1

#define DISPLAY_SIZE       512      /* pixel size of display window */
#define SCALE               0.03    /* sets the magnification at the origin */
                                    /* smaller #'s zoom in */
#define XMIN (-1/SCALE)
#define XMAX (1/SCALE)
#define YMIN (-1/SCALE)
#define YMAX (1/SCALE)

#define GRAV_CONSTANT       0.01    /* proportionality constant of
                                       gravitational interaction */

#define POS_TO_SCREEN(pos)   ((int) ((pos/SCALE + DISPLAY_SIZE)/2))

#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))  /* utility function */


#endif
