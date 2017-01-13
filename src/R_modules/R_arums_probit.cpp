/*################################################################################
  ##
  ##   Copyright (C) 2015 - 2017 the TraME Team:
  ##      Alfred Galichon
  ##      Keith O'Hara
  ##      Simon Weber
  ##
  ##   This file is part of TraME.
  ##
  ##   TraME is free software: you can redistribute it and/or modify
  ##   it under the terms of the GNU General Public License as published by
  ##   the Free Software Foundation, either version 2 of the License, or
  ##   (at your option) any later version.
  ##
  ##   TraME is distributed in the hope that it will be useful,
  ##   but WITHOUT ANY WARRANTY; without even the implied warranty of
  ##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  ##   GNU General Public License for more details.
  ##
  ##   You should have received a copy of the GNU General Public License
  ##   along with TraME. If not, see <http://www.gnu.org/licenses/>.
  ##
  ################################################################################*/

/*
 * probit class module
 *
 * Keith O'Hara
 * 08/08/2016
 */

#include "trameR.hpp"

RCPP_EXPOSED_CLASS(empirical_R)
RCPP_EXPOSED_CLASS(probit_R)

RCPP_MODULE(probit_module)
{
    using namespace Rcpp ;

    void (trame::probit::*build_1)(int, int, bool) = &trame::probit::build;
    void (trame::probit::*build_2)(int, int, double, bool) = &trame::probit::build;

    void (trame::probit::*unifCorrelCovMatrices_1)() = &trame::probit::unifCorrelCovMatrices;
    void (trame::probit::*unifCorrelCovMatrices_2)(double) = &trame::probit::unifCorrelCovMatrices ;
  
    // now we can declare the class
    class_<trame::probit>( "probit" )
        .default_constructor()

        // basic objects
        .field( "nbX", &trame::probit::nbX )
        .field( "nbY", &trame::probit::nbY )

        .field( "nbParams", &trame::probit::nbParams )
        .field( "aux_nbOptions", &trame::probit::aux_nbOptions )
        .field( "outsideOption", &trame::probit::outsideOption )

        .field( "rho", &trame::probit::rho )

        .field( "Covar", &trame::probit::Covar )

        // read only objects
        //.field_readonly( "", &probit:: )

        // member functions
        .method( "build", build_1 )
        .method( "build", build_2 )
        .method( "unifCorrelCovMatrices", unifCorrelCovMatrices_1 )
        .method( "unifCorrelCovMatrices", unifCorrelCovMatrices_2 )
    ;

    class_<probit_R>( "probit_R" )
        .derives<trame::probit>( "probit" )
        .default_constructor()

        .method( "simul", &probit_R::simul_R )
    ;
}

// wrapper functions to catch errors and handle memory pointers
empirical_R probit_R::simul_R(int nbDraws)
{
    trame::empirical emp_obj = this->simul(&nbDraws,NULL);

    empirical_R emp_R_obj = static_cast<empirical_R&>(emp_obj);

    return emp_R_obj;
}
