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
#ifndef VRMLSFIMAGE_H
#define VRMLSFIMAGE_H

#include "VrmlField.h"


/**
 * A single uncompressed 2-dimensional pixel image. The first
 * hexadecimal value is the lower left pixel and the last value is the
 * upper right pixel.Pixel values are limited to 256 levels of
 * intensity. A one-component image specifies one-byte greyscale
 * values. A two-component image specifies the intensity in the first
 * (high) byte and the alpha opacity in the second (low) byte. A
 * three-component image specifies the red component in the first
 * (high) byte, followed by the green and blue components.
 * Four-component images specify the alpha opacity byte after
 * red/green/blue.
 *
 */
class VrmlSFImage : public VrmlField {
public:

  /**
   * Create an SFImage.
   * <p>
   * Note that the pixels read from lower left to upper right, which
   * is a reflection around the y-axis from the "normal" convention.
   * <p>
   * Note also that width and height are specified in pixels, and a
   * pixel may be more than one byte wide. For example, an image with
   * a width and height of 16, and nc==3, would have a pixel array
   * w*h*nc = 16*16*3 = 768 bytes long. See the class intro above for
   * the interpretation of different pixel depths.
   * 
   * @param w width in pixels
   * @param h height in pixels
   * @param nc number of components/pixel (see above)
   * @param pixels the caller owns the bytes, so this ctr makes a copy
   *
   */
  VrmlSFImage(int w = 0, int h = 0, int nc = 0, unsigned char const * pixels = 0);

  VrmlSFImage(const VrmlSFImage&);

  ~VrmlSFImage();

  // Assignment.
  VrmlSFImage& operator=(const VrmlSFImage& rhs);

  virtual ostream& print(ostream& os) const;

  virtual VrmlField *clone() const;

  virtual VrmlFieldType fieldType() const;
  virtual const VrmlSFImage* toSFImage() const;
  virtual VrmlSFImage* toSFImage();

  int width()				{ return d_w; }
  int height()         			{ return d_h; }
  int nComponents()			{ return d_nc; }
  unsigned char *pixels()		{ return d_pixels; }

  void setSize( int w, int h )		{ d_w = w; d_h = h; }

private:

  int d_w, d_h, d_nc;
  unsigned char *d_pixels;	// nc bytes/pixel, lower left to upper right

};

#endif
