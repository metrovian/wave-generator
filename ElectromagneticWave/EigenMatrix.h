#pragma once
#include "Eigen/Dense"

Eigen::MatrixXcd pinvSVD(const Eigen::MatrixXcd& _mat);
Eigen::MatrixXcd pinvMP(const Eigen::MatrixXcd& _mat);