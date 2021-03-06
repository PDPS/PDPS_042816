/* ----------------------------------------------------------------------
   PDPS - Particle Dynamics Parallel Simulator

   Copyright (2012) reserved by Lingqi Yang. 
   Email: ly2282@columbia.edu

   See the README file in the top-level PDPS directory.
------------------------------------------------------------------------- */

#ifndef PS_DOMAIN_H
#define PS_DOMAIN_H

#include "pointers.h"
#include "pdps.h"

namespace PDPS_NS {
	
class Domain : protected Pointers {
public:
	int dim;                             // Dimension = 2 or 3

	// Boundary conditoins
	int xperiodic, yperiodic, zperiodic;
	int periodicity[3];                  // xyz periodicity
	int boundary[3][2];                  // set 6 boundary 
										 // -1 = no boundary condition 
	                                     // 0 = periodic
	                                     // 1 = fix
	                                     // 2 = shrink

    int nonperiodic;                     // 0 = periodic in all 3 directions
                                         // 1 = periodic or fixed in all 6 BCs
                                         // 2 = shrink-wrap in any of 6 BCs
	// Global box
	int box_exist;                       // box exist flag:  defualt is 0
	int box_change;                      // flag for the change of box
	int deform_flag;				     // 1 if fix deform exist, else 0
	int deform_vremap;					 // 1 if fix deform remaps v, else 0
	int deform_groupbit;			   	 // particle group to perform v remap for
	double h_rate[6],h_ratelo[3];        // rate of box size/shape change

	double boxlo[3];                     // box lower bound
	double boxhi[3];                     // box upper bound
	double boxle[3];                     // box length
	double xle, yle, zle;                // length

	// Local box
	double sublo[3];
	double subhi[3];
	double suble[3];

	// Region
	class Region **regions;              // region class
	int nregions;                        // number of regions

	// Lattice 
	class Lattice *lattice;              // lattice
	double lsp[3];                       // lattice spacing (can be modified)
	char *lsp_style;                     // lattice spacing style

	double number_density;               // number of density

	Domain(class PDPS *);
	~Domain();

	virtual void init();

	void add_region(int, char **);
	int find_region(const char *);

	void pbc();
	virtual void reset_box();
	void set_boundary(int, char **);
	void set_initial_box();
	void set_global_box();
	void set_local_box();
	void set_lattice(int, char **);
	void set_num_density(int, char **);
	void boundary_string(char *);
	void print_box(const char *);
	
private:
	int maxarg;
	//virtual ~Domain();
};

}

#endif
