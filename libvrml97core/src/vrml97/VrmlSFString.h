//
//  Vrml 97 library
//  Copyright (C) 1998 Chris Morley
//  See the file COPYING for license details.
//
#ifndef VRMLSFSTRING_H
#define VRMLSFSTRING_H

#include "VrmlField.h"

class VrmlSFString : public VrmlSField {
public:

  VrmlSFString(const char *s = 0);
  VrmlSFString(const VrmlSFString&);
  ~VrmlSFString();

  // Assignment.
  void set(const char *s);
  VrmlSFString& operator=(const VrmlSFString& rhs);

  virtual ostream& print(ostream& os) const;

  virtual VrmlField *clone() const;

  virtual VrmlFieldType fieldType() const;
  virtual const VrmlSFString* toSFString() const;
  virtual VrmlSFString* toSFString();

  const char *get(void) const		{ return d_s; }

private:

  char *d_s;

};

# endif
