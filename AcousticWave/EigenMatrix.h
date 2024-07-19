#pragma once
#include "Eigen/Dense"

Eigen::MatrixXd pinvSVD(const Eigen::MatrixXd& _mat);
Eigen::MatrixXd pinvMP(const Eigen::MatrixXd& _mat);