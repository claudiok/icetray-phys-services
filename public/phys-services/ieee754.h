//
//  TDS:  this is included here because OSX Leopard appears not to have
//  this header.  These machines *do*, however, implement ieee754 floating-point.
//  maybe I'm missing something and there is a magic flag to just get
//  this header from the OS someplace, but I couldn't find ieee754_double
//  anywhere.
//
//  I've made tweaks to use the right BYTE_ORDER macros and whatnot.

// if we're not on an apple and we're not leopard or later, 
// we should not be using this header.
#if !defined(__APPLE_CC__) && !defined(__FreeBSD__)
#error This header should not be included on non-apple/leopard machines
#endif

/* Copyright (C) 1992, 1995, 1996, 1999 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifndef I3_DARWIN_IEEE754_H
#define I3_DARWIN_IEEE754_H 1

#include <machine/endian.h>
#ifdef __FreeBSD__
#warning FreeBSD support is a hack of a hack.
#define __DARWIN_BYTE_ORDER _BYTE_ORDER
#define __DARWIN_BIG_ENDIAN _BIG_ENDIAN
#define __DARWIN_LITTLE_ENDIAN _LITTLE_ENDIAN
#endif

#if __DARWIN_BYTE_ORDER == __DARWIN_BIG_ENDIAN
#define __FLOAT_WORD_ORDER __DARWIN_BIG_ENDIAN
#endif

union ieee754_float
  {
    float f;

    /* This is the IEEE 754 single-precision format.  */
    struct
      {
#if	__DARWIN_BYTE_ORDER == __DARWIN_BIG_ENDIAN
	unsigned int negative:1;
	unsigned int exponent:8;
	unsigned int mantissa:23;
#endif				/* Big endian.  */
#if	__DARWIN_BYTE_ORDER == __DARWIN_LITTLE_ENDIAN
	unsigned int mantissa:23;
	unsigned int exponent:8;
	unsigned int negative:1;
#endif				/* Little endian.  */
      } ieee;

    /* This format makes it easier to see if a NaN is a signalling NaN.  */
    struct
      {
#if	__DARWIN_BYTE_ORDER == __DARWIN_BIG_ENDIAN
	unsigned int negative:1;
	unsigned int exponent:8;
	unsigned int quiet_nan:1;
	unsigned int mantissa:22;
#endif				/* Big endian.  */
#if	__DARWIN_BYTE_ORDER == __DARWIN_LITTLE_ENDIAN
	unsigned int mantissa:22;
	unsigned int quiet_nan:1;
	unsigned int exponent:8;
	unsigned int negative:1;
#endif				/* Little endian.  */
      } ieee_nan;
  };

#define IEEE754_FLOAT_BIAS	0x7f /* Added to exponent.  */


union ieee754_double
  {
    double d;

    /* This is the IEEE 754 double-precision format.  */
    struct
      {
#if	__DARWIN_BYTE_ORDER == __DARWIN_BIG_ENDIAN
	unsigned int negative:1;
	unsigned int exponent:11;
	/* Together these comprise the mantissa.  */
	unsigned int mantissa0:20;
	unsigned int mantissa1:32;
#endif				/* Big endian.  */
#if	__DARWIN_BYTE_ORDER == __DARWIN_LITTLE_ENDIAN
# if	__FLOAT_WORD_ORDER == __DARWIN_BIG_ENDIAN
	unsigned int mantissa0:20;
	unsigned int exponent:11;
	unsigned int negative:1;
	unsigned int mantissa1:32;
# else
	/* Together these comprise the mantissa.  */
	unsigned int mantissa1:32;
	unsigned int mantissa0:20;
	unsigned int exponent:11;
	unsigned int negative:1;
# endif
#endif				/* Little endian.  */
      } ieee;

    /* This format makes it easier to see if a NaN is a signalling NaN.  */
    struct
      {
#if	__DARWIN_BYTE_ORDER == __DARWIN_BIG_ENDIAN
	unsigned int negative:1;
	unsigned int exponent:11;
	unsigned int quiet_nan:1;
	/* Together these comprise the mantissa.  */
	unsigned int mantissa0:19;
	unsigned int mantissa1:32;
#else
# if	__FLOAT_WORD_ORDER == __DARWIN_BIG_ENDIAN
	unsigned int mantissa0:19;
	unsigned int quiet_nan:1;
	unsigned int exponent:11;
	unsigned int negative:1;
	unsigned int mantissa1:32;
# else
	/* Together these comprise the mantissa.  */
	unsigned int mantissa1:32;
	unsigned int mantissa0:19;
	unsigned int quiet_nan:1;
	unsigned int exponent:11;
	unsigned int negative:1;
# endif
#endif
      } ieee_nan;
  };

#define IEEE754_DOUBLE_BIAS	0x3ff /* Added to exponent.  */


union ieee854_long_double
  {
    long double d;

    /* This is the IEEE 854 double-extended-precision format.  */
    struct
      {
#if	__DARWIN_BYTE_ORDER == __DARWIN_BIG_ENDIAN
	unsigned int negative:1;
	unsigned int exponent:15;
	unsigned int empty:16;
	unsigned int mantissa0:32;
	unsigned int mantissa1:32;
#endif
#if	__DARWIN_BYTE_ORDER == __DARWIN_LITTLE_ENDIAN
# if	__FLOAT_WORD_ORDER == __DARWIN_BIG_ENDIAN
	unsigned int exponent:15;
	unsigned int negative:1;
	unsigned int empty:16;
	unsigned int mantissa0:32;
	unsigned int mantissa1:32;
# else
	unsigned int mantissa1:32;
	unsigned int mantissa0:32;
	unsigned int exponent:15;
	unsigned int negative:1;
	unsigned int empty:16;
# endif
#endif
      } ieee;

    /* This is for NaNs in the IEEE 854 double-extended-precision format.  */
    struct
      {
#if	__DARWIN_BYTE_ORDER == __DARWIN_BIG_ENDIAN
	unsigned int negative:1;
	unsigned int exponent:15;
	unsigned int empty:16;
	unsigned int one:1;
	unsigned int quiet_nan:1;
	unsigned int mantissa0:30;
	unsigned int mantissa1:32;
#endif
#if	__DARWIN_BYTE_ORDER == __DARWIN_LITTLE_ENDIAN
# if	__FLOAT_WORD_ORDER == __DARWIN_BIG_ENDIAN
	unsigned int exponent:15;
	unsigned int negative:1;
	unsigned int empty:16;
	unsigned int mantissa0:30;
	unsigned int quiet_nan:1;
	unsigned int one:1;
	unsigned int mantissa1:32;
# else
	unsigned int mantissa1:32;
	unsigned int mantissa0:30;
	unsigned int quiet_nan:1;
	unsigned int one:1;
	unsigned int exponent:15;
	unsigned int negative:1;
	unsigned int empty:16;
# endif
#endif
      } ieee_nan;
  };

#define IEEE854_LONG_DOUBLE_BIAS 0x3fff

#endif 
