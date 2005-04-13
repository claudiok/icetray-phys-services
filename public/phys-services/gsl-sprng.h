#ifndef _GSL_SPRNG
#define _GSL_SPRNG

#include <sprng.h>
/**
 * gsl-sprng.h
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: gsl-sprng.h,v 1.1 2005/04/13 16:29:34 juancarlos Exp $
 *
 * @brief SPRNG Implementation of the I3RandomService interface.  
 * This implementation uses a combination of SPRNG and GSL to generate
 * statistically independent streams of pseudo-random number distributions.
 * SPRNG (Scalable Pseudo-Random Number Generator) is a library developed by
 * Michael Mascagni, et al at Florida State University, http://sprng.cs.fsu.edu
 *
 * The purpose of this implementation is to provide an I3RandomService that
 * can be used in a distributed computing environment and ensuring little
 * correlation between parallel streams of numbers.
 *
 * The basic approach for this is based on code from Darren Wilkinson
 * http://www.staff.ncl.ac.uk/d.j.wilkinson/ who wrote an MPI simple interface
 * that doesn't make use of streams.
 *
 * @version $Revision: 1.1 $
 * @date $Date: 2005/04/13 16:29:34 $
 * @author juancarlos
 *
 * @todo 
 */


typedef struct
{
   int seed;
   int streamnum;
   int nstreams;
   int *streamptr;
} gsl_sprng_stream;


static void sprng_set(void * vstate,unsigned long int s)
{
  gsl_sprng_stream *stream = (gsl_sprng_stream*) vstate;

  stream->seed = s;
  stream->streamptr = init_sprng(
		DEFAULT_RNG_TYPE, 
  		stream->streamnum, 
		stream->nstreams, 
		stream->seed,
		SPRNG_DEFAULT);
}

static unsigned long sprng_get(void * vstate)
{
  gsl_sprng_stream *stream = (gsl_sprng_stream*) vstate;
  return( (long) isprng(stream->streamptr) );
}

static double sprng_get_double(void * vstate)
{
  gsl_sprng_stream *stream = (gsl_sprng_stream*) vstate;
  return( (double) sprng(stream->streamptr));
}

static const gsl_rng_type gsl_rng_sprng20 =
  {"sprng20",        	/* name */
   0x7fffffffUL,     	/* RAND_MAX */
   0,                	/* RAND_MIN */
   0,                	/* size of state - not sure about this */
   &sprng_set,          /* initialisation */
   &sprng_get,          /* get integer RN */
   &sprng_get_double  	/* get double RN */
};

inline gsl_rng *gsl_sprng_init(int seed, int nstreams, int streamnum)
{
   gsl_sprng_stream* s = 
   	  (gsl_sprng_stream*)  malloc( sizeof( gsl_sprng_stream ) );

   if (s == 0) {
       GSL_ERROR_VAL (
	   	"failed to allocate space for gsl_sprng_stream struct",
                     GSL_ENOMEM, 0);
   };

   /*Allocate memory for stream parameters*/
   s->seed		= seed;
   s->streamnum = streamnum;
   s->nstreams 	= nstreams;

   /*Initialize stream*/
   s->streamptr = 
   		init_sprng(
			DEFAULT_RNG_TYPE, 
			streamnum, 
			nstreams, 
			seed, 
			SPRNG_DEFAULT);

   /*Allocate memory for rng parameters*/
   gsl_rng *r 	= (gsl_rng *) malloc (sizeof (gsl_rng));
   if (r == 0) {
       GSL_ERROR_VAL ("failed to allocate space for rng struct",
                        GSL_ENOMEM, 0);
	   free(s);
   };

   /*Set rng parameters*/
   r->type    = &gsl_rng_sprng20;
   r->state   = s;

   return r;
}

inline void gsl_sprng_free (gsl_rng * r)
{
  free (r->state);
  free (r);
}

#endif
