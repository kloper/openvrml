//
//  Vrml 97 library
//  Copyright (C) 1998 Chris Morley
//  See the file COPYING for license details.
//
#ifndef VRMLSFFLOAT_H
#define VRMLSFFLOAT_H

#include "VrmlField.h"


class VrmlSFFloat : public VrmlSField {
public:

  VrmlSFFloat(float value = 0.0);

  virtual ostream& print(ostream& os) const;

  virtual VrmlField *clone() const;

  virtual VrmlFieldType fieldType() const;
  virtual const VrmlSFFloat* toSFFloat() const;
  virtual VrmlSFFloat* toSFFloat();

  float get(void) const		{ return d_value; }
  void set(float value)		{ d_value = value; }

private:
  float d_value;

};

#endif
