//
// OpenVRML
//
// Copyright (C) 1998  Chris Morley
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// 

#ifndef VRMLNODESPOTLIGHT_H
#define VRMLNODESPOTLIGHT_H

#include "VrmlNodeLight.h"

class VrmlNodeSpotLight : public VrmlNodeLight {

public:

  // Define the fields of spotLight nodes
  static VrmlNodeType *defineType(VrmlNodeType *t = 0);
  virtual VrmlNodeType & nodeType() const;

  VrmlNodeSpotLight(VrmlScene *);
  virtual ~VrmlNodeSpotLight();

  virtual bool accept(VrmlNodeVisitor & visitor);
  
  virtual VrmlNodeSpotLight* toSpotLight() const;

  virtual void addToScene( VrmlScene *s, const char * );

  virtual ostream& printFields(ostream& os, int indent);

  virtual void renderScoped(Viewer *);

  virtual const VrmlField *getField(const char *fieldName) const;
  virtual void setField(const char *fieldName, const VrmlField &fieldValue);

  virtual const VrmlSFVec3f& getAttenuation() const;  //LarryD Mar 04/99
  virtual const VrmlSFVec3f& getDirection() const;  //LarryD Mar 04/99
  virtual const VrmlSFVec3f& getLocation() const;  //LarryD Mar 04/99
  virtual float getBeamWidth() { return d_beamWidth.get(); }  //LarryD Mar 04/99
  virtual float getCutOffAngle() { return d_cutOffAngle.get(); } //LarryD Mar 04/99
  virtual float getRadius() { return d_radius.get(); }  //LarryD Mar 04/99

protected:

  VrmlSFVec3f d_attenuation;
  VrmlSFFloat d_beamWidth;
  VrmlSFFloat d_cutOffAngle;
  VrmlSFVec3f d_direction;
  VrmlSFVec3f d_location;
  VrmlSFFloat d_radius;

};

#endif
