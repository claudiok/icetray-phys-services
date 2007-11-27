#ifndef FASTERLOGSUM_H_INCLUDED
#define FASTERLOGSUM_H_INCLUDED

/**
 *  copyright  (C) 2007
 *  the icecube collaboration
 *  $Id$
 *
 *  @file
 *  @version $Revision$
 *  @date $Date$
 *  @author David Boersma <boersma@icecube.wisc.edu>
 *  (with advice from Troy Straszheim <troy@resophonic.com>
 *   and Martin Merck <mmerck@icecube.wisc.edu>)
 */

#include <cmath>
#include <cassert>
#include <ieee754.h>

/**
 * @class FastLogSum
 * @brief Accelerate evaluation of sums of logs, avoiding numerical limits.
 *
 * In log-likelihood based reconstruction, we often need to compute
 * sums of logs:
 * L = sum_i log(x_i)
 * Mathematically that is equivalent to the log of a product:
 * L = log( prod_i x_i )
 * In principle the latter would be much faster to compute, because
 * there is only one log computation involved.
 * However, the practical difficulty here is that one can have many 
 * small terms x_i, which, when multiplied, might easily exit the
 * available range for (double) floating point numbers. This class
 * circumvents this difficulty by rescaling the product back to the
 * [1.0,2.0) ranger after every x_i multiplication. Thanks to the way
 * ieee754 double precision floats are laid out in memory, this is
 * a very cheap operation. Using the ieee754_double "union" it is
 * possible to access the bit patterns in a platform independent way
 * (thanks, Troy!).
 *
 * The speed gain from using this class depends on the length of the sums
 * (the more terms the better), the platform (hardware, OS, compiler)
 * and the relative fraction of the CPU time that your program spends
 * on computing (sums of) logs.  E.g. if the computation of x_i itself
 * takes a long time, then the gain from using FastLogSum is negligible,
 * but if x_i is a relatively simple expression or function that is
 * cheaper than a log, then you may expect speedups of a factor 2 to 3
 * for logsums of a hundred x_i values.
 *
 * Security: we check that the input is positive, not NAN and not INF.
 * Leaving those checks out would make the code 20 to 40% faster
 * (depending on OS, hardware and compiler), but at this point we think
 * we cannot compromise on this.
 *
 * @seealso http://en.wikipedia.org/wiki/IEEE754
 */
class FastLogSum {

    public:

    /// constructor
    FastLogSum():
        allpos_(true),
        infnan_(false),
        prod_(1.0),
        bits_(reinterpret_cast<ieee754_double&>(prod_)),
        powersum_(0){
            assert(0x3ff == IEEE754_DOUBLE_BIAS);
            assert(bits_.ieee.negative == 0);
            assert(bits_.ieee.exponent == IEEE754_DOUBLE_BIAS);
            assert(bits_.ieee.mantissa0 == 0);
            assert(bits_.ieee.mantissa1 == 0);
        }

    /// destructor
    ~FastLogSum(){}

    /// set the product back to 1 (so the sum_i log(x_i) = 0).
    void Reset(){
        allpos_ = true;
        infnan_ = false;
        prod_ = 1.0;
        powersum_ = 0;
    }

    /**
     * Add a term/factor @c x_i (from @c log(prod_i x_i) @c == @c sum_i log(x_i))
     * The @c x_i input is checked against negativity, NAN and INF.
     *
     * We assume that the double precision floating point variables
     * are stored in memory according to the IEEE 754 convention, that is
     * 1 sign bit, 11 exponent bits and 52 fraction bits. After multiplying
     * with @c x_i we take out the exponent (powers of 2) from the product and
     * add that to the powersum_ datamember.
     */
    inline void Add(double x_i){
        prod_ *= x_i;
        powersum_ += int(bits_.ieee.exponent) - int(IEEE754_DOUBLE_BIAS);
        allpos_ &= (x_i > 0.0);
        infnan_ |= (bits_.ieee.exponent == 0x7ff);
        bits_.ieee.exponent = IEEE754_DOUBLE_BIAS;
    }

    /**
     * Add a term/factor @c x_i (from @c log(prod_i x_i) @c == @c sum_i log(x_i))
     * The @c x_i input is NOT checked against negativity/NAN/INF. This saves 20-50%
     * more computing time on the logs. Use this only if you are absolutely confident
     * that the @c x_i are positive and finite.
     *
     * We assume that the double precision floating point variables
     * are stored in memory according to the IEEE 754 convention, that is
     * 1 sign bit, 11 exponent bits and 52 fraction bits. After multiplying
     * with @c x_i we take out the exponent (powers of 2) from the product and
     * add that to the powersum_ datamember.
     */
    inline void FastAdd(double x_i){
        prod_ *= x_i;
        powersum_ += int(bits_.ieee.exponent) - int(IEEE754_DOUBLE_BIAS);
        bits_.ieee.exponent = IEEE754_DOUBLE_BIAS;
    }

    /**
     * Compute the sum of the logs of the x_i collected sofar.
     * If any of the @c x_i was NAN or INF or not positive, then the
     * product will be NAN.
     */
    double GetLogSum(){
        if ( infnan_ || ! allpos_ ) return NAN;
        return (powersum_*M_LN2+log(prod_));
    }

    private:

    /// a flag which is true if *all* @c x_i were positive
    bool allpos_;
    bool infnan_;
    double prod_;
    ieee754_double &bits_;
    int powersum_;
};

#endif
