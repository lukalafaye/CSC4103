/*
** nbody.c - nbody simulation using the brute-force algorithm (O(n*n))
**
**/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>
#include <assert.h>
#include <unistd.h>

#include "nbody.h"

int nparticles=10;      /* number of particles */
float T_FINAL=1.0;     /* simulation end time */
particle_t*particles;

double sum_speed_sq = 0;
double max_acc = 0;
double max_speed = 0;

/* print the particles */
void print_particles() {
  int i;
  for (i = 0; i < nparticles; i++) {
    particle_t *p = &particles[i];
    printf("particle[%d]={pos=(%f,%f), vel=(%f,%f)}\n",
	   i, p->pos->x, p->pos->y, p->vel->x, p->vel->y);
  }
}

/*
  Place particles in their initial positions.
*/
void all_init_particles(int num_particles, particle_t *particles)
{
  int    i;
  double total_particle = num_particles;

  for (i = 0; i < num_particles; i++) {
    particle_t *particle = &particles[i];
    particle->pos = malloc(sizeof(struct vector));
    particle->vel = malloc(sizeof(struct vector));
    particle->force = malloc(sizeof(struct vector));

    particle->pos->x = i*2.0/nparticles - 1.0;
    particle->vel->y = particle->pos->x;
    particle->mass = 1.0 + (num_particles+i)/total_particle;
  }
}

/* compute the force that a particle with position (x_pos, y_pos) and mass 'mass'
 * applies to particle p
 */
void compute_force(particle_t*p, double x_pos, double y_pos, double mass) {
  double x_sep, y_sep, dist_sq, grav_base;

  x_sep = x_pos - p->pos->x;
  y_sep = y_pos - p->pos->y;
  dist_sq = MAX((x_sep*x_sep) + (y_sep*y_sep), 0.01);

  /* Use the 2-dimensional gravity rule: F = d * (GMm/d^2) */
  grav_base = GRAV_CONSTANT*(p->mass)*(mass)/dist_sq;

  p->force->x += grav_base*x_sep;
  p->force->y += grav_base*y_sep;
}

/* compute the new position/velocity */
void move_particle(particle_t*p, double step) {

  p->pos->x += (p->vel->x)*step;
  p->pos->y += (p->vel->y)*step;
  double x_acc = p->force->x/p->mass;
  double y_acc = p->force->y/p->mass;
  p->vel->x += x_acc*step;
  p->vel->y += y_acc*step;

  /* compute statistics */
  double cur_acc = (x_acc*x_acc + y_acc*y_acc);
  cur_acc = sqrt(cur_acc);
  double speed_sq = (p->vel->x)*(p->vel->x) + (p->vel->y)*(p->vel->y);
  double cur_speed = sqrt(speed_sq);

  sum_speed_sq += speed_sq;
  max_acc = MAX(max_acc, cur_acc);
  max_speed = MAX(max_speed, cur_speed);
}


/*
  Move particles one time step.

  Update positions, velocity, and acceleration.
  Return local computations.
*/
void all_move_particles(double step)
{
  /* First calculate force for particles. */
  int i;
  for(i=0; i<nparticles; i++) {
    int j;
    particles[i].force->x = 0;
    particles[i].force->y = 0;
    for(j=0; j<nparticles; j++) {
      particle_t*p = &particles[j];
      /* compute the force of particle j on particle i */
      compute_force(&particles[i], p->pos->x, p->pos->y, p->mass);
    }
  }

  /* then move all particles and return statistics */
  for(i=0; i<nparticles; i++) {
    move_particle(&particles[i], step);
  }
}

void run_simulation() {
  double t = 0.0, dt = 0.01;
  while (t < T_FINAL && nparticles>0) {
    /* Update time. */
    t += dt;
    /* Move particles with the current and compute rms velocity. */
    all_move_particles(dt);

    /* Adjust dt based on maximum speed and acceleration--this
       simple rule tries to insure that no velocity will change
       by more than 10% */

    dt = 0.1*max_speed/max_acc;
  }
}

/*
  Simulate the movement of nparticles particles.
*/
int main(int argc, char**argv)
{
  if(argc >= 2) {
    nparticles = atoi(argv[1]);
  }
  if(argc == 3) {
    T_FINAL = atof(argv[2]);
  }

  /* Allocate global shared arrays for the particles data set. */
  particles = malloc(sizeof(particle_t)*nparticles);
  all_init_particles(nparticles, particles);

  /* Initialize thread data structures */
  struct timeval t1, t2;
  gettimeofday(&t1, NULL);

  /* Main thread starts simulation ... */
  run_simulation();

  gettimeofday(&t2, NULL);

  double duration = (t2.tv_sec -t1.tv_sec)+((t2.tv_usec-t1.tv_usec)/1e6);

  printf("-----------------------------\n");
  printf("nparticles: %d\n", nparticles);
  printf("T_FINAL: %f\n", T_FINAL);
  printf("-----------------------------\n");
  printf("Simulation took %lf s to complete\n", duration);

#ifdef DUMP_RESULT
  print_particles();
#endif

  free(particles);
  return 0;
}
