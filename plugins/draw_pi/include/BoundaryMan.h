/***************************************************************************
 * 
 * Project:  OpenCPN
 * Purpose:  Boundary Manager
 * Author:   Jon Gough
 *
 ***************************************************************************
 *   Copyright (C) 2010 by David S. Register                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 **************************************************************************/


#ifndef BOUNDARYMAN_H
#define BOUNDARYMAN_H

#include "PathMan.h"
#include "ocpn_draw_pi.h"

class Boundary;
class BoundaryPoint;

class BoundaryMan : public PathMan
{
    public:
        wxString    FindPointInBoundary( double lat, double lon, int type, int state = ID_BOUNDARY_ANY );
        bool        FindPointInBoundary( Boundary *pBoundary, double lat, double lon );
        bool        FindPointInBoundary( wxString l_GUID, double lat, double lon );
        wxString    FindPointInBoundaryPoint( double lat, double lon, int type );
        bool        FindPointInBoundaryPoint( BoundaryPoint *pBoundaryPoint, double lat, double lon );
        bool        FindPointInBoundaryPoint( wxString l_GUID, double lat, double lon );
        
    private:
        bool    pointInPolygon(int polyCorners, double *polyX, double *polyY, double x, double y);
};

#endif // BOUNDARYMAN_H
