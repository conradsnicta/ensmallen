/**
 * @file wood_function.hpp
 * @author Ryan Curtin
 * @author Marcus Edel
 *
 * Definition of the Wood function.
 *
 * ensmallen is free software; you may redistribute it and/or modify it under
 * the terms of the 3-clause BSD license.  You should have received a copy of
 * the 3-clause BSD license along with ensmallen.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef ENSMALLEN_PROBLEMS_WOOD_FUNCTION_HPP
#define ENSMALLEN_PROBLEMS_WOOD_FUNCTION_HPP

namespace ens {
namespace test {

/**
 * The Wood function, defined by
 *  f(x) = f1(x) + f2(x) + f3(x) + f4(x) + f5(x) + f6(x)
 *  f1(x) = 100 (x2 - x1^2)^2
 *  f2(x) = (1 - x1)^2
 *  f3(x) = 90 (x4 - x3^2)^2
 *  f4(x) = (1 - x3)^2
 *  f5(x) = 10 (x2 + x4 - 2)^2
 *  f6(x) = (1 / 10) (x2 - x4)^2
 *  x_0 = [-3, -1, -3, -1]
 *
 * This should optimize to f(x) = 0, at x = [1, 1, 1, 1].
 *
 * For more information, please refer to:
 *
 * @code
 * @article{Grippo1989,
 *   title   = {A truncated Newton method with nonmonotone line search for
 *              unconstrained optimization},
 *   author  = {Grippo, L. and Lampariello, F. and Lucidi, S.},
 *   journal = {Journal of Optimization Theory and Applications},
 *   year    = {1989},
 *   volume  = {60},
 *   number  = {3},
 *   pages   = {401--419},
 * }
 * @endcode
 */
class WoodFunction
{
 public:
  //! Initialize the WoodFunction.
  WoodFunction();

  /**
   * Shuffle the order of function visitation. This may be called by the
   * optimizer.
   */
  void Shuffle();

  //! Return 1 (the number of functions).
  size_t NumFunctions() const { return 1; }

  //! Get the starting point.
  template<typename MatType = arma::mat>
  MatType GetInitialPoint() const { return MatType("-3; -1; -3; -1"); }

  //! Get the final point.
  template<typename MatType = arma::mat>
  MatType GetFinalPoint() const { return MatType("1; 1; 1; 1"); }

  //! Get the final objective.
  const double GetFinalObjective() const { return 0.0; }

  /**
   * Evaluate a function for a particular batch-size.
   *
   * @param coordinates The function coordinates.
   * @param begin The first function.
   * @param batchSize Number of points to process.
   */
  template<typename MatType>
  typename MatType::elem_type Evaluate(const MatType& coordinates,
                                       const size_t begin,
                                       const size_t batchSize) const;

  /**
   * Evaluate a function with the given coordinates.
   *
   * @param coordinates The function coordinates.
   */
  template<typename MatType>
  typename MatType::elem_type Evaluate(const MatType& coordinates) const;

  /**
   * Evaluate the gradient of a function for a particular batch-size.
   *
   * @param coordinates The function coordinates.
   * @param begin The first function.
   * @param gradient The function gradient.
   * @param batchSize Number of points to process.
   */
  template<typename MatType, typename GradType>
  void Gradient(const MatType& coordinates,
                const size_t begin,
                GradType& gradient,
                const size_t batchSize) const;

  /**
   * Evaluate the gradient of a function with the given coordinates.
   *
   * @param coordinates The function coordinates.
   * @param gradient The function gradient.
   */
  template<typename MatType, typename GradType>
  void Gradient(const MatType& coordinates, GradType& gradient) const;
};

} // namespace test
} // namespace ens

// Include implementation.
#include "wood_function_impl.hpp"

#endif // ENSMALLEN_PROBLEMS_WOOD_FUNCTION_HPP
