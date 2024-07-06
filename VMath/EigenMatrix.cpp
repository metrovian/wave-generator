#include "EigenMatrix.h"
#include <iostream>

Eigen::MatrixXd pinv(const Eigen::MatrixXd& _mat)
{
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(_mat, Eigen::ComputeFullU | Eigen::ComputeFullV);

    Eigen::MatrixXd sinv(_mat.cols(), _mat.rows());
    sinv.setZero();

    const auto& singular = svd.singularValues();

    for (unsigned int i = 0; i < singular.size(); ++i)
    {
        if (singular(i) > 1.0E-10)
        {
            sinv(i, i) = 1.0 / singular(i);
        }
    }

    return svd.matrixV() * sinv * svd.matrixU().transpose();
}
