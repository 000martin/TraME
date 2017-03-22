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
 * Transferable Utility (TU) Marriage Matching Functions (MMFs) class
 *
 * Keith O'Hara
 * 08/15/2016
 *
 * This version:
 * 03/21/2017
 */

#include "trame.hpp"

void trame::mmfs::tu::build(const arma::mat& phi_TU, bool need_norm_TU)
{
    need_norm = need_norm_TU;

    nbX = phi_TU.n_rows;
    nbY = phi_TU.n_cols;
    nbParams = nbX*nbY;

    phi = phi_TU;
    aux_phi_exp = arma::exp(phi_TU / 2.0);
}

void trame::mmfs::tu::trans()
{
    int nbX_temp = nbX;

    nbX = nbY;
    nbY = nbX_temp;
    
    phi = phi.t();
    aux_phi_exp = aux_phi_exp.t();
}

//
// MFE-related functions

arma::mat trame::mmfs::tu::M(const arma::mat& a_xs, const arma::mat& b_ys)
const
{
    arma::mat ret = this->M(a_xs,b_ys,NULL,NULL);
    //
    return ret;
}

arma::mat trame::mmfs::tu::M(const arma::mat& a_xs, const arma::mat& b_ys, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1); 
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat term_1 = aux_phi_exp(x_ind,y_ind);
    arma::mat term_2 = arma::sqrt(a_xs * b_ys.t());

    arma::mat ret = term_1 % term_2;
    //
    return ret;
}

arma::mat trame::mmfs::tu::M(const double& a_xs, const arma::mat& b_ys, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1); 
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat term_1 = aux_phi_exp(x_ind,y_ind);
    arma::mat term_2 = arma::sqrt(a_xs * b_ys.t());

    arma::mat ret = term_1 % term_2;
    //
    return ret;
}

arma::mat trame::mmfs::tu::M(const arma::mat& a_xs, const double& b_ys, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1); 
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat term_1 = aux_phi_exp(x_ind,y_ind);
    arma::mat term_2 = arma::sqrt(a_xs * b_ys);

    arma::mat ret = term_1 % term_2;
    //
    return ret;
}

arma::mat trame::mmfs::tu::Mx0(const arma::mat& a_x)
const
{
    return a_x;
}

arma::mat trame::mmfs::tu::M0y(const arma::mat& b_y)
const
{
    return b_y;
}