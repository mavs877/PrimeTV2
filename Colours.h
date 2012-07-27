/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) <year>  <name of author>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
    Author : Jose Fernandez Navarro  -  jc.fernandez.navarro@gmail.com

 */

#ifndef COLOURS_H
#define COLOURS_H
#include "Color.h"
#include <string>
#include <sstream>

using namespace std;

class Colours
{

  
  public:
    
    Color default_foreground_color; // Draw the sequence names
    Color gene_edge_color;
    Color gene_lgt_color;	/* Not in use! */
    Color gene_dupl_color;
    Color gene_spec_color;

    Color species_edge_color;
    Color species_edge_contour_color;
    Color species_node_color; 
    Color species_node_contour_color;

    Color markerColor; //marker color
    Color umColor;

    Colours();
    void setColors(const char *set);
    const char* getSet();
    
private :
   const char *set;
};



#endif
