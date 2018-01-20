/*
 * MFE class test
 *
 * Keith O'Hara
 * 08/01/2016
 */

#include "trame.hpp"

int main()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    //
    // inputs:

    int nbX = 18;
    int nbY = 5;
    double sigma = 1;

    arma::vec n = arma::ones(nbX,1);
    arma::vec m = arma::ones(nbY,1);

    arma::mat alpha  = arma::randu(nbX,nbY);
    arma::mat gamma  = arma::randu(nbX,nbY);
    arma::mat lambda = 1 + arma::randu(nbX,nbY);
    arma::mat zeta   = 1 + arma::randu(nbX,nbY);

    arma::mat phi = alpha + gamma;

    arma::mat lambda_LTU = lambda/(lambda+zeta);
    arma::mat phi_LTU = (lambda%alpha + zeta%gamma) / (lambda+zeta);

    //
    // results

    printf("\n*===================   Start of MFE Test   ===================*\n");
    printf("\n");

    //
    // build

    trame::mfe<trame::mmfs::geo> mfe_obj_TU(sigma,false);
    mfe_obj_TU.build(n,m,phi);

    trame::mfe<trame::mmfs::cd> mfe_obj_LTU(sigma,false);
    mfe_obj_LTU.build(n,m,lambda_LTU,phi_LTU);

    trame::mfe<trame::mmfs::min> mfe_obj_NTU(sigma,false);
    mfe_obj_NTU.build(n,m,alpha,gamma);

    //
    //

    double tol = 1E-06;
    int max_iter = 5000;

    arma::vec mux0, mu0y, u, v;
    arma::mat mu_TU, U, V;
    //trame::ipfp(mfe_obj_TU, mu_TU, mux0, mu0y, U, V, u, v);
    trame::ipfp(mfe_obj_TU,mu_TU);
    trame::ipfp(mfe_obj_TU,mu_TU,tol);
    trame::ipfp(mfe_obj_TU,mu_TU,max_iter);
    trame::ipfp(mfe_obj_TU,mu_TU,tol,max_iter);

    mfe_obj_TU.solve(mu_TU);

    arma::cout << "Solution of TU-logit problem using ipfp:\n" << mu_TU << arma::endl;

    arma::mat mu_NTU;
    trame::ipfp(mfe_obj_NTU,mu_NTU);

    arma::cout << "Solution of NTU-logit problem using ipfp:\n" << mu_NTU << arma::endl;

    arma::mat mu_LTU;
    trame::ipfp(mfe_obj_LTU,mu_LTU);

    arma::cout << "Solution of LTU-logit problem using ipfp:\n" << mu_LTU << arma::endl;

    //
    printf("\n*===================    End of MFE Test    ===================*\n");
    printf("\n");
    //

    end = std::chrono::system_clock::now();
        
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
    
    //

    return 0;
}