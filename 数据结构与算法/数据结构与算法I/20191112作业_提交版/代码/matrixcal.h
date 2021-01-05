#ifndef MATRIXCAL_H
#define MATRIXCAL_H

#include "matrix.h"

class MatrixCal
{
    public:
        MatrixCal(){}
        void task10()
        {
            std::cout << std::endl << "以下是矩阵运算演示:" << std::endl;

            std::cout << "请输入所需的运算\n(+/-/*/DET(行列式)/INV(逆矩阵)/\nRANK(秩)/TRACE(迹)/\nQR(QR分解)/EIGEN(特征值与特征向量))/\nRDINT(随机整数矩阵测试)/RDDBL(随机浮点数矩阵测试):";
            std::string op;
            std::cin >> op;

            std::cout << "请输入矩阵的行数与列数:";
            int rowA, colA;
            std::cin >> rowA >> colA;
            Matrix A(rowA, colA);
            if(op != "RDINT" && op != "RDDBL")
            {
                std::cout << "请按行顺序输入矩阵的数据:" << std::endl;
                A.readData();
            }
            if(op == "+")
            {
                Matrix B(rowA, colA);
                std::cout << "请按行顺序输入另一矩阵的数据:" << std::endl;
                B.readData();
                try
                {
                    Matrix C = A + B;
                    std::cout << "结果:" << std::endl;
                    std::cout << C << std::endl;
                }
                catch(const MyException & e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
            else if(op == "-")
            {
                Matrix B(rowA, colA);
                std::cout << "请按行顺序输入另一矩阵的数据:" << std::endl;
                B.readData();
                try
                {
                    Matrix C = A - B;
                    std::cout << "结果:" << std::endl;
                    std::cout << C << std::endl;
                }
                catch(const MyException & e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
            else if(op == "*")
            {
                std::cout << "请输入另一矩阵的列数:";
                int colB;
                std::cin >> colB;
                Matrix B(colA, colB);
                std::cout << "请按行顺序输入另一矩阵的数据:" << std::endl;
                B.readData();
                try
                {
                    Matrix C = A * B;
                    std::cout << "结果:" << std::endl;
                    std::cout << C << std::endl;
                }
                catch(const MyException & e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
            else if(op == "DET")
            {
                try
                {
                    double ans = A.det();
                    std::cout << "结果:" << std::endl;
                    std::cout << ans << std::endl;
                }
                catch(const MyException & e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
            else if(op == "INV")
            {
                try
                {
                    std::cout << "结果:" << std::endl;
                    std::cout << A.inverse() << std::endl;
                }
                catch(const MyException & e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
            else if(op == "RANK")
            {
                try
                {
                    std::cout << "结果:" << std::endl;
                    std::cout << A.rank() << std::endl;
                }
                catch(const MyException & e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
            else if(op == "TRACE")
            {
                try
                {
                    std::cout << "结果:" << std::endl;
                    std::cout << A.trace() << std::endl;
                }
                catch(const MyException & e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
            else if(op == "QR")
            {
                std::cout << "结果:" << std::endl;
                Matrix Q(rowA, rowA);
                Matrix R(rowA, colA);
                A.QRDecomp(&Q, &R);
                std::cout << "Q=" << std::endl;
                std::cout << Q << std::endl;

                std::cout << "R=" << std::endl;
                std::cout << R << std::endl;
            }
            else if(op == "EIGEN")
            {
                std::cout << "请输入迭代次数:";
                unsigned int iterTimes;
                std::cin >> iterTimes;
                try
                {
                    std::cout << "结果:" << std::endl;
                    A.eigen_QR(iterTimes);
                }
                catch(const MyException & e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
            else if(op == "RDINT" || op == "RDDBL")
            {
                double _min, _max;
                std::cout << "请输入随机矩阵要求最小值与最大值:";
                std::cin >> _min >> _max;

                if(op == "RDINT")
                {
                    A.randomFill<int>(_min, _max);
                }
                else
                {
                    A.randomFill<double>(_min, _max);
                }

                unsigned int iterTimes;
                std::cout << "请输入QR方法求特征值的迭代次数:";
                std::cin >> iterTimes;

                std::cout << "A=" << std::endl << A << std::endl;
                try
                {
                    std::cout << "|A|=" << A.det() << std::endl << std::endl;
                    std::cout << "A^-1=" << std::endl << A.inverse() << std::endl;
                }
                catch(const MyException & e)
                {
                    std::cout << e.what() << std::endl;
                }
                try
                {
                    std::cout << "rank(A)=" << A.rank() << std::endl << std::endl;
                    std::cout << "trace(A)=" << A.trace() << std::endl << std::endl;

                    Matrix Q(rowA, rowA);
                    Matrix R(rowA, colA);
                    A.QRDecomp(&Q, &R);
                    std::cout << "QR Decomposition:" << std::endl << "Q=" << std::endl;
                    std::cout << Q << std::endl;
                    std::cout << "R=" << std::endl;
                    std::cout << R << std::endl;
                    
                    std::cout << "Eigenvalues and eigenvectors of A:" << std::endl;
                    A.eigen_QR(iterTimes);
                }
                catch(const MyException & e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
            else
            {
                std::cout << "运算符不合法!";
            }   
        }
};

#endif