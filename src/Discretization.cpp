#include "Discretization.hpp"

#include <cmath>

double Discretization::_dx = 0.0;
double Discretization::_dy = 0.0;
double Discretization::_gamma = 0.0;

Discretization::Discretization(double dx, double dy, double gamma) {
    _dx = dx;
    _dy = dy;
    _gamma = gamma;
}

/***********************************************************************
The following function returns the convection due to u in equation (9)
The discritization for the 2 terms are found in first 2 equations of (4)
***********************************************************************/
double Discretization::convection_u(const Matrix<double> &U, const Matrix<double> &V, int i, int j) {
    double du2_dx = 1/ _dx * (pow((U(i,j)+U(i + 1,j)) / 2, 2) - pow((U(i,j)+U(i - 1, j)) / 2, 2)) +
                        _gamma/_dx * ((std::abs(U(i, j)+U(i + 1, j)) * (U(i, j)-U(i+1, j)) / 4) -
                        std::abs(U(i, j)+U(i - 1, j))*(U(i - 1, j)-U(i, j)) / 4) ;
    double duv_dy = 1/ _dy * (((V(i, j) + V(i + 1, j)) * (U(i, j) + U(i, j + 1))) / 4 - ( (V(i, j - 1) +
                            V(i + 1, j - 1 )) * (U(i, j - 1) + U(i, j))) / 4 ) +
                            _gamma / _dy * ( (std::abs(V(i, j)+V(i + 1, j))*(U(i, j) - U(i, j + 1)) / 4) - 
                            (std::abs(V(i, j - 1) + V(i + 1, j - 1)) * (U(i, j - 1) - U(i, j)) / 4 ));    

    double result = du2_dx + duv_dy;
    return result;
}

/***********************************************************************
The following function returns the convection due to v in equation (10)
The discritization for the 2 terms are found in first 2 equations of (5)
***********************************************************************/
double Discretization::convection_v(const Matrix<double> &U, const Matrix<double> &V, int i, int j) {
    double dv2_dy = 1 / _dy * (pow((V(i, j) + V(i, j + 1)) / 2, 2) - pow((V(i, j - 1) + V(i, j)) / 2, 2)) +
                    _gamma / _dy * (std::abs(V(i, j) + V(i, j + 1)) * (V(i, j) - V(i, j + 1)) / 4 - 
                                    std::abs(V(i, j - 1) + V(i, j)) * (V(i, j - 1) - V(i, j)) / 4);
    double duv_dx = 1 / _dx * ((U(i, j) + U(i, j + 1)) * (V(i, j) + V(i+1, j)) / 4 - 
                               (U(i - 1, j) + U(i - 1, j + 1)) * (V(i - 1, j) + V(i, j)) / 4) +
                    _gamma / _dx * (std::abs(U(i, j) + U(i, j + 1)) * (V(i, j) - V(i + 1, j)) / 4 - 
                                    std::abs(U(i - 1, j) + U(i - 1, j + 1)) * (V(i - 1, j) - V(i, j)) / 4);
    double result = dv2_dy + duv_dx;
    return result;
}

/*****************************************************************************************
The following function returns the diffusion due to u or v in equation (9)/(10)
The discritization for the 2 terms are found in third and fourth  equation of (4)/(5)
******************************************************************************************/
double Discretization::diffusion(const Matrix<double> &A, int i, int j) {
    double result = (A(i + 1, j) - 2.0 * A(i, j) + A(i - 1, j)) / (_dx * _dx) +
                    (A(i, j + 1) - 2.0 * A(i, j) + A(i, j - 1)) / (_dy * _dy);

    return result;
}

double Discretization::convection_Tu(const Matrix<double> &T, const Matrix<double> &U, int i, int j)
{
    double result;
    result = 1/_dx * ( U(i, j) * (T(i, j) + T(i + 1, j)) / 2 - U(i - 1,j) * (T(i - 1, j) + T(i, j)) / 2 ) + 
                        _gamma/_dx * ( std::abs(U(i,j)) * (T(i, j) - T(i + 1, j)) / 2 - std::abs(U(i - 1,j)) * (T(i - 1, j) - T(i, j)) / 2 );
    return result;
}

double Discretization::convection_Tv(const Matrix<double> &T, const Matrix<double> &V, int i, int j)
{
    double result;
    result = 1/_dy * ( V(i, j) * (T(i, j) + T(i , j + 1)) / 2 - V(i,j - 1) * (T(i, j - 1) + T(i, j)) / 2 ) + 
                        _gamma/_dy * ( std::abs(V(i,j)) * (T(i, j) - T(i, j + 1)) / 2 - std::abs(V(i,j - 1)) * (T(i, j - 1) - T(i, j))/2 );
    return result;
}


double Discretization::laplacian(const Matrix<double> &P, int i, int j) {
    double result = (P(i + 1, j) - 2.0 * P(i, j) + P(i - 1, j)) / (_dx * _dx) +
                    (P(i, j + 1) - 2.0 * P(i, j) + P(i, j - 1)) / (_dy * _dy);
    return result;
}

double Discretization::sor_helper(const Matrix<double> &P, int i, int j) {
    double result = (P(i + 1, j) + P(i - 1, j)) / (_dx * _dx) + (P(i, j + 1) + P(i, j - 1)) / (_dy * _dy);
    return result;
}






double Discretization::interpolate(const Matrix<double> &A, int i, int j, int i_offset, int j_offset) {}
