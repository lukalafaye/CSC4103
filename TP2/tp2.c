#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int sort_get_index(float tab[], int top, float val) {
  int i=0;
  while((i<top) && (tab[i]<val)) {
    i++;
  }
  return i;
}

void sort_insert_at(float tab[], int i, int top, float val) {
  // Déplace les éléments entre i et top d'une case vers la droite
  // Insère val à l'indice i
  for(int l=top-1; l>=i; l--) {
    tab[l+1] = tab[l];
  }
  tab[i] = val;
}

void sort_insert(float tab[], int top, float val) {
  int i = sort_get_index(tab, top, val);
  sort_insert_at(tab, i, top, val);
}

void print_tab(float tab[], int top) {
  for (int i=0; i<top; i++) {
    printf("%f \n", tab[i]);
  }
}

int nb_columns() {
  return 129;
}

int nb_lines() {
  return 65;
}

void grid_init(char grid[], char pixel) {
  int lines = nb_lines();
  int cols = nb_columns();
  for (int i=0; i<lines*cols; i++) {
    grid[i] = pixel;
  }
}

void grid_display(char grid[]) {
  int lines = nb_lines();
  int cols = nb_columns();
  for (int i=0; i<lines; i++) {
    for (int j=0; j<cols; j++) {
      printf("%c", grid[i*cols+j]);
    }
    printf("\n");
  }
  printf("\n");
}

void tab_display(float tab[], int top) {
  for (int i=0; i<top; i++) {
    printf("%f ", tab[i]);
  }
  printf("\n");
}

void plot_point(char grid[], int x, int y, char pixel) {
  int lines = nb_lines();
  int cols = nb_columns();
  if ((x<0) || (x>cols) || (y>lines) || (y<0)) {
    printf("x or y out of range \n");
    printf("%d %d \n", x, y);
    exit(EXIT_FAILURE);
  }
  int i = (lines - y - 1)*cols + x;
  grid[i] = pixel;
}

void plot_vline(char grid[], int x, float fy0, float fy1, char pixel) {
  int y0 = (int)(fy0+0.5);
  int y1 = (int)(fy1+0.5);

  if (fy0 == y0 - 0.5) {
    y0 -= 1;
  }
  
  for (int y=y0; y<=y1; y++) {
    plot_point(grid, x, y, pixel);
  }
}

struct point {
  float x;
  float y;
};

void plot_poly_sweep(char grid[], struct point p[], int n, int x, char pixel) {
  int lines = nb_lines();
  int cols = nb_columns();
  int j=0;
  //printf("sweep %d\n", x);
  for (int y=0; y<lines; y++) {
    //printf("%c", grid[(lines - y - 1)*cols + x]);
  }

  float vlines[n*4];
  int top = 0;

  float intersect_y = 0.0;
  j = n-1;

  
  for (int i=0; i<n; i++) {
    if (p[i].x == x) {
      if (p[j].x == x) {
	if (p[i].y < p[j].y) {
	  plot_vline(grid, x, p[i].y, p[j].y, pixel);
	} else {
	  plot_vline(grid, x, p[j].y, p[i].y, pixel);
	}
      }
      else {
	plot_vline(grid, x, p[i].y, p[i].y, pixel);
      }
    }

    if ( (p[i].x <= x && x < p[j].x) || (p[j].x <= x && x < p[i].x )) {
      intersect_y = p[i].y + (x - p[i].x) * ((p[j].y - p[i].y) / (p[j].x - p[i].x));
      // printf("%f ", intersect_y);
      sort_insert(vlines, top, intersect_y);
      top+=1;
    }
    j=i;
  }

  // tab_display(vlines, top);

  int nb_paires = top/2;

  for (int l=0; l<nb_paires; l++) {
    //printf("%f %f %d \n", vlines[l*2], vlines[l*2+1], x);
    plot_vline(grid, x, vlines[l*2], vlines[l*2+1], pixel);
  }
  
  //printf("\n");
}

void plot_poly(char grid[], struct point p[], int num_points, char pixel) {
  int cols = nb_columns();
  for (int x=0; x<cols; x++) {
    plot_poly_sweep(grid, p, num_points, x, pixel);
  }
}


void plot_triangle(char grid[], struct point p1, struct point p2, struct point p3, char pixel) {
  struct point p[] = {p1, p2, p3};
  plot_poly(grid, p, 3, pixel);
  //grid_display(grid);
}

struct point line_middle(struct point p1, struct point p2) {
  float x = (p1.x + p2.x) / 2.0;
  float y = (p1.y + p2.y) / 2.0;
  struct point p = {x, y};
  return p;
}

void sierpinski(char grid[], struct point p1, struct point p2, struct point p3, int n, char pixel) {
  if (n==1) {
    plot_triangle(grid, p1, p2, p3, pixel);
  }
  else {
    struct point new_p1 = line_middle(p1, p2);
    struct point new_p2 = line_middle(p2, p3);
    struct point new_p3 = line_middle(p1, p3);
    
    sierpinski(grid, p1, new_p1, new_p3, n-1, pixel);
    sierpinski(grid, new_p1, p2, new_p2, n-1, pixel);
    sierpinski(grid, new_p3, new_p2, p3, n-1, pixel);
  }
}

int main(void) {
  //float tab[5] = {1, 3, 5, 7, 0};
  //print_tab(tab, 5);
  //int top=4;
  //printf("Insert 0 at 0, 3.5 at 2, 10 at 4 \n");
  //sort_get_index(tab, top, 0);
  //sort_get_index(tab, top, 3.5);
  //sort_get_index(tab, top, 10);  
  //sort_insert_at(tab, 2, 4, 3.5);
  //sort_insert(tab, top, 3.5);
  //print_tab(tab, 5);
  int ROWS = nb_lines();
  int COLS = nb_columns();
  char grid[ROWS*COLS];
  //grid_init(grid, ' ');
  //printf("%c", grid[4]);
  // grid_display(grid);
  // plot_point(grid, 3, 1, ' ');
  // grid_display(grid);
  // plot_point(grid, 3, 100, ' ');
  //plot_vline(grid, 1, 2, 3, '|');
  //plot_vline(grid, 2, 1.7, 3.3, '|');
  //plot_vline(grid, 3, 1.2, 3.8, '|');
  //plot_vline(grid, 7, 0.5, 1.5, 'X');
  //grid_display(grid);

  //struct point p[] = {{ 2, 13 }, { 10, 13 }, { 30, 7 }, { 10, 1 }, { 2, 1 }, { 18, 7 }};

  //plot_poly(grid, p, 6, '-');
  
  struct point p1 = {0.0, 0.0};
  struct point p2 = {64.0, 64.0};
  struct point p3 = {128.0, 0.0};

  grid_init(grid, ' ');
  // plot_triangle(grid, p1, p2, p3, '*');
  sierpinski(grid, p1, p2, p3, 6, "*");
  grid_display(grid);
}
