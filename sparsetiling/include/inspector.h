/*
 *  inspector.h
 *
 * Define data structure and prototypes to build an inspector
 */

#ifndef _INSPECTOR_H_
#define _INSPECTOR_H_

#include "parloop.h"

/*
 * The inspector main data structure.
 */
typedef struct {
  /* the base loop index */
  int seed;
  /* initial partitioning of the base loop */
  map_t* itset2tile;
  /* initial tile size */
  int tileSize;
  /* list of loops spanned by a tile */
  loop_list* loops;

} inspector_t;

enum insp_info {INSP_OK, INSP_ERR};
enum insp_verbose {LOW = 20, MEDIUM = 40, HIGH};

/*
 * Initialize a new inspector
 *
 * input:
 * tileSize: average tile size after partitioning of the base loop's iteration set
 *
 * output:
 * an inspector data structure
 */
inspector_t* insp_init (int tileSize);

/*
 * Add a parloop to the inspector
 *
 * input:
 * insp: the inspector data structure
 * loopName: identifier name of the parloop
 * setSize: size of the iteration set
 * descriptors: list of access descriptors used by the parloop. Each descriptor
 *              specifies what and how a dataset is accessed.
 *
 * output:
 * the inspector is updated with a new loop the tiles will have to cross
 */
insp_info insp_add_parloop (inspector_t* insp, char* loopName, int setSize,
                            desc_list* descriptors);

/*
 * Inspect a sequence of parloops and compute a tiled scheduling
 *
 * input:
 * insp: the inspector data structure, already defined over a range of parloops
 * seed: start point of the tiling (a number between 0 and the number of
 *       parloops spanned by the inspector)
 *
 * output:
 * on return from the function, insp will contain a list of tiles, each tile
 * characterized by a list of iterations that are supposed to be executed, for each
 * crossed parloop
 */
insp_info insp_run (inspector_t* insp, int seed);

/*
 * Print a summary of the inspector
 *
 * input:
 * insp: the inspector data structure
 */
void insp_print (inspector_t* insp, insp_verbose level);

/*
 * Destroy an inspector
 */
void insp_free (inspector_t* insp);

#endif
