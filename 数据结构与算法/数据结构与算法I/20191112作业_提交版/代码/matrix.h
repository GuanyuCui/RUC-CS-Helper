#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cfloat>
#include <random>
#include "myexception.h"

const double EPSILON = 1e-9;

class Matrix
{
    public:
        //构造
        Matrix(unsigned int row, unsigned int col);
        Matrix(const Matrix & m);
        virtual ~Matrix();

        //读取数据
        void readData();
        //随机填充 T 类型数据
        template <typename T>
            void randomFill(double _min, double _max);

        //操作符重载
        //加法
        Matrix operator +(const Matrix & m);
        //减法
        Matrix operator -(const Matrix & m);
        //乘法
        Matrix operator *(const Matrix & m);
        //数乘
        Matrix operator *(double d);
        friend Matrix operator *(double d, const Matrix & m);
        //赋值
        Matrix operator =(const Matrix & m);
        //输出
        friend std::ostream & operator <<(std::ostream & out, Matrix A);
        //下标
        double * operator[](unsigned int row);

        //转置
        Matrix transpose();
        //迹
        double trace();
        //秩
        unsigned int rank();
        //基于初等变换的行列式
        double det();
        //基于初等变换的求逆矩阵
        Matrix inverse();
        //基于Householder方法的QR分解
        void QRDecomp(Matrix * Q, Matrix * R);
        //基于QR方法的特征值 —— 迭代iterTimes次
        void eigen_QR(unsigned int iterTimes);

    protected:
        //初等变换
        //交换rowA, rowB两行
        void swapRow(unsigned int rowA, unsigned int rowB);
        //交换两列
        void swapCol(unsigned int colA, unsigned int colB);
        //_row行乘以常数c
        void rowMul(unsigned int _row, double c);
        //_col列乘以常数c
        void colMul(unsigned int _col, double c);
        //rowB行乘以常数c加到rowA行
        void rowMulAdd(unsigned int rowA, unsigned int rowB, double c);
        //colB列乘以常数c加到colA列
        void colMulAdd(unsigned int colA, unsigned int colB, double c);
        //获取行向量
        Matrix getRow(unsigned int _row);
        //获取列向量
        Matrix getCol(unsigned int _col);
        //定位col列从start行向下第一个非零元, -1 表示全为0
        int colFindNZ(unsigned int col, unsigned int start = 0);
        //模长
        double len();
        //模长的平方
        double lenSqr();
        //QR分解过程中, 获得某一列(之上抹零)
        Matrix getCol_QR(unsigned int _col);
        //QR算法过程中, 确认某主元下侧左侧是否全为0
        bool isDownLeftZero(unsigned int _row, unsigned int _col);

        unsigned int row;
        unsigned int col;
        double ** data;
};

//n阶单位阵
class ElemMatrix : public Matrix
{
    public:
        ElemMatrix(unsigned int n);
};

Matrix::Matrix(unsigned int _r, unsigned int _c)
:row(_r), col(_c)
{
    data = new double*[row];
    for(unsigned int i = 0; i < row; i++)
    {
        data[i] = new double[col];
        for(unsigned int j = 0; j < col; j++)
        {
            data[i][j] = 0;
        }
    }
}

Matrix::Matrix(const Matrix & m)
{
    row = m.row;
    col = m.col;

    data = new double*[row];
    for(unsigned int i = 0; i < row; i++)
    {
        data[i] = new double[col];
        for(unsigned int j = 0; j < col; j++)
        {
            data[i][j] = m.data[i][j];
        }
    }
}

Matrix::~Matrix()
{
    for(unsigned int i = 0; i < row; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}

void Matrix::readData()
{
    double input;
    for(unsigned int i = 0; i < row; i++)
    {
        for(unsigned int j = 0; j < col; j++)
        {
            std::cin >> input;
            data[i][j] = input;
        }
    }
    std::cout << "你输入的矩阵为:" << std::endl;
    std::cout << *this;
}

template <typename T>
void Matrix::randomFill(double _min, double _max)
{
    //将用于获得随机数引擎的种子
    std::random_device rd;
    //以 rd() 播种的标准 mersenne_twister_engine
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(_min, _max);
    for(unsigned int i = 0; i < row; i++)
    {
        for(unsigned int j = 0; j < col; j++)
        {
            data[i][j] = T(dis(gen));
        }
    }
}

std::ostream & operator <<(std::ostream & out, Matrix A)
{
    out.flags(std::ios::fixed);
    out.precision(5);
    for(unsigned int i = 0; i < A.row; i++)
    {
        out << "[";
        for(unsigned int j = 0; j < A.col; j++)
        {
            out.width(10);
            out << A.data[i][j] << ( (j == A.col - 1) ? "]" : ", " );
        }
        if(i < A.row)
        {
            out << std::endl;
        }
    }
    return out;
}

double * Matrix::operator[](unsigned int row)
{
    return data[row];
}

Matrix Matrix::transpose()
{
    Matrix retVal(col, row);
    for(unsigned int j = 0; j < col; j++)
    {
        for(unsigned int i = 0; i < row; i++)
        {
            retVal[j][i] = data[i][j];
        }
    }
    return retVal;
}

Matrix Matrix::operator +(const Matrix & m)
{
    if(row != m.row || col != m.col)
    {
        IllegalCalc e;
        throw e;
    }
    Matrix retVal(m);
    for(unsigned int i = 0; i < row; i++)
    {
        for(unsigned int j = 0; j < col; j++)
        {
            retVal.data[i][j] += data[i][j];
        }
    }
    return retVal;
}

Matrix Matrix::operator -(const Matrix & m)
{
    if(row != m.row || col != m.col)
    {
        IllegalCalc e;
        throw e;
    }
    Matrix retVal(*this);
    for(unsigned int i = 0; i < row; i++)
    {
        for(unsigned int j = 0; j < col; j++)
        {
            retVal.data[i][j] -= m.data[i][j];
        }
    }
    return retVal;
}

//注: 使用naive算法, 时间复杂度(设两个矩阵都为n阶方阵)为O(n^3)
//另有文献指出, Strassen算法(1969)为O(n^2.81), 目前最优算法(2014)为O(n^2.373)左右
Matrix Matrix::operator *(const Matrix & m)
{
    if(col != m.row)
    {
        IllegalCalc e;
        throw e;
    }
    Matrix retVal(this -> row, m.col);
    for(unsigned int i = 0; i < retVal.row; i++)
    {
        for(unsigned int j = 0; j < retVal.col; j++)
        {
            for(unsigned int k = 0; k < this -> col; k++)
            {
                retVal.data[i][j] += this -> data[i][k] * m.data[k][j];
            }
            if(retVal.data[i][j] < EPSILON && retVal.data[i][j] > -EPSILON)
            {
                retVal.data[i][j] = 0;
            }
        }
    }
    return retVal;
}

//数乘
Matrix Matrix::operator *(double d)
{
    Matrix retVal(*this);
    for(unsigned int i = 0; i < this -> row; i++)
    {
        for(unsigned int j = 0; j < this -> col; j++)
        {
            retVal.data[i][j] *= d;
        }
    }
    return retVal;
}

Matrix operator *(double d, const Matrix & m)
{
    Matrix retVal(m);
    for(unsigned int i = 0; i < m.row; i++)
    {
        for(unsigned int j = 0; j < m.col; j++)
        {
            retVal.data[i][j] *= d;
        }
    }
    return retVal;
}

//赋值
Matrix Matrix::operator =(const Matrix & m)
{
    if(this -> data)
    {
        for(unsigned int i = 0; i < row; i++)
        {
            delete[] data[i];
        }
        delete[] data;
    }
    row = m.row;
    col = m.col;
    data = new double*[row];
    for(unsigned int i = 0; i < row; i++)
    {
        data[i] = new double[col];
        for(unsigned int j = 0; j < col; j++)
        {
            data[i][j] = m.data[i][j];
        }
    }
    return (*this);
}

//获取行向量
Matrix Matrix::getRow(unsigned int _row)
{
    if(_row >= row)
    {
        IllegalCalc e;
        throw e;
    }
    Matrix retVal(1, col);
    for(unsigned int i = 0; i < col; i++)
    {
        retVal[0][i] = data[_row][i];
    }
    return retVal;
}

//获取列向量
Matrix Matrix::getCol(unsigned int _col)
{
    if(_col >= col)
    {
        IllegalCalc e;
        throw e;
    }
    Matrix retVal(row, 1);
    for(unsigned int i = 0; i < row; i++)
    {
        retVal[i][0] = data[i][_col];
    }
    return retVal;
}

double Matrix::len()
{
    if(row != 1 && col != 1)
    {
        IllegalCalc e;
        throw e;
    }
    double sum = 0;
    if(row == 1)
    {
        for(unsigned int j = 0; j < col; j++)
        {
            sum += data[0][j] * data[0][j];
        }
    }
    else if(col == 1)
    {
        for(unsigned int i = 0; i < row; i++)
        {
            sum += data[i][0] * data[i][0];
        }
    }
    return std::sqrt(sum);
}

double Matrix::lenSqr()
{
    if(row != 1 && col != 1)
    {
        IllegalCalc e;
        throw e;
    }
    double sum = 0;
    if(row == 1)
    {
        for(unsigned int j = 0; j < col; j++)
        {
            sum += data[0][j] * data[0][j];
        }
    }
    else if(col == 1)
    {
        for(unsigned int i = 0; i < row; i++)
        {
            sum += data[i][0] * data[i][0];
        }
    }
    return sum;
}

//基于Householder方法的QR分解
//时间复杂度: O(n^2), 设矩阵是n*n的
void Matrix::QRDecomp(Matrix * Q, Matrix * R)
{
    auto mySgn = [=](double x) -> int
    {
        if(x > EPSILON)
        {
            return 1;
        }
        else //if(x > eps)
        {
            return -1;
        }
        //return 0;
    };

    //迭代次数
    unsigned int t = std::min(row, col);
    //m阶单位矩阵
    ElemMatrix Em_m(row);
    //R矩阵是不断对原矩阵变换的结果
    Matrix RAns(*this);
    //Q矩阵是E不断乘以变换矩阵的结果
    Matrix QAns = Em_m;

    for(unsigned int i = 0; i < t; i++)
    {
        Matrix originCol = RAns.getCol_QR(i);

        //单位列向量
        Matrix e_i(row, 1);
        e_i[i][0] = 1;
        //处理后列向量
        Matrix colVec = originCol + mySgn(RAns.data[i][i]) * originCol.len() * e_i;
        //Householder矩阵
        Matrix H = Em_m - (2.0 / colVec.lenSqr()) * (colVec * colVec.transpose());
        RAns = H * RAns;
        QAns = QAns * H;
    }
    *Q = QAns;
    *R = RAns;
}

//行列式
//注: 根据北京大学版《高等代数》, 该使用初等变换的行列式算法复杂度为O(n^3)
double Matrix::det()
{
    if(row != col)
    {
        IllegalCalc e;
        throw e;
    }
    //符号, 交换行时变号
    int sgn = 1;
    Matrix tmp(*this);
    //化为上三角
    //每一列处理
    for(unsigned int i = 0; i < col; i++)
    {
        //把第一个非零元调换到主对角线上
        int notZero = tmp.colFindNZ(i, i);
        //主对角线及以下找不到非零元
        if(notZero == -1)
        {
            return 0.0;
        }
        else if(notZero != i)
        {
            tmp.swapRow(i, notZero);
            sgn *= -1;
        }
        //把这一列主对角线以下化为0
        for(unsigned int j = i + 1; j < row; j++)
        {
            tmp.rowMulAdd(j, i, -tmp.data[j][i] / tmp.data[i][i]);
        }
    }
    //主对角线相乘
    double retVal = sgn;
    for(unsigned int i = 0; i < row; i++)
    {
        retVal *= tmp.data[i][i];
    }
    return retVal;
}

//特征值及特征向量
//注: 使用QR算法. 根据Wikipedia, 每次迭代复杂度为O(n^2), 收敛速度为立方级
void Matrix::eigen_QR(unsigned int iterTimes)
{
    if(row != col)
    {
        IllegalCalc e;
        throw e;
    }
    std::cout << "注意: 当为Hessenberg/Symmetric Matrix时, 结果是准确的, 否则只有部分结果是准确的!" << std::endl;
    //迭代的矩阵
    Matrix origin(*this);
    //QR分解出的矩阵
    Matrix Q(row, row);
    Matrix R(row, row);

    //特征向量矩阵
    Matrix V = ElemMatrix(row);

    //迭代
    for(int i = 0; i < iterTimes; i++)
    {
        origin.QRDecomp(&Q, &R);
        origin = R * Q;
        V = V * Q;
    }
    //std::cout << "迭代完毕矩阵:" << std::endl;
    //std::cout << origin << std::endl;
    unsigned int eigenCount = 0;
    //处理迭代完毕的矩阵的每一列
    for(unsigned int i = 0; i < col; i++)
    {
        //全是零
        if(origin.isDownLeftZero(i, i))
        {
            eigenCount++;
            double eigenVal = origin.data[i][i];
            Matrix eigenVec = V.getCol(i);
            std::cout << "(实)特征值:" << eigenVal << std::endl;
            std::cout << "(单位)特征向量:" << std::endl << eigenVec.transpose() << std::endl;
        }
    }
    if(eigenCount == 0)
    {
        std::cout << "(用QR算法无法得到特征值/特征向量)" << std::endl;
    }
}

Matrix Matrix::inverse()
{
    if(row != col)
    {
        IllegalCalc e;
        throw e;
    }
    //合并成增广矩阵
    Matrix expand(row, 2 * col);
    for(unsigned int i = 0; i < row; i++)
    {
        for(unsigned int j = 0; j < col; j++)
        {
            expand.data[i][j] = data[i][j];
        }
        expand.data[i][col + i] = 1;
    }
    //把左边化为单位阵
    //化为上三角
    for(unsigned int i = 0; i < row; i++)
    {
        //把第一个非零元调换到主对角线上
        int notZero = expand.colFindNZ(i, i);
        //主对角线及以下找不到非零元, 说明矩阵不可逆
        if(notZero == -1)
        {
            SingularMatrix e;
            throw e;
        }
        else if(notZero != i)
        {
            expand.swapRow(i, notZero);
        }
        //把这一列主对角线以下化为0
        for(unsigned int j = i + 1; j < row; j++)
        {
            expand.rowMulAdd(j, i, -expand.data[j][i] / expand.data[i][i]);
        }
        //把这一行主元化为1
        expand.rowMul(i, 1 / expand.data[i][i]);
    }
    //化为单位阵
    for(unsigned int i = 1; i < col; i++)
    {
        for(unsigned int j = i + 1; j <= row; j++)
        {
            expand.rowMulAdd(row - j, row - i, -expand.data[row - j][row - i] / expand.data[row - i][row - i]);
        }
    }
    //把右边拿出来
    Matrix retVal(row, row);
    for(unsigned int i = 0 ; i < row; i++)
    {
        for(unsigned int j = 0; j < col; j++)
        {
            retVal.data[i][j] = expand.data[i][row + j];
        }
    }
    return retVal;
}

double Matrix::trace()
{
    if(row != col)
    {
        IllegalCalc e;
        throw e;
    }
    double retVal = 0;
    for(unsigned int i = 0; i < row; i++)
    {
        retVal += data[i][i];
    }
    return retVal;
}

unsigned int Matrix::rank()
{
    Matrix tmp(*this);
    //化为上三角
    //每一列处理
    for(unsigned int i = 0; i < col; i++)
    {
        //把第一个非零元调换到主对角线上
        int notZero = tmp.colFindNZ(i, i);
        //主对角线及以下找不到非零元
        if(notZero == -1)
        {
            continue;
        }
        else if(notZero != i)
        {
            tmp.swapRow(i, notZero);
        }
        //把这一列主对角线以下化为0
        for(unsigned int j = i + 1; j < row; j++)
        {
            tmp.rowMulAdd(j, i, -tmp.data[j][i] / tmp.data[i][i]);
        }
    }
    unsigned int retVal = 0;
    unsigned t = std::min(row, col);
    for(unsigned int i = 0; i < t; i++)
    {
        retVal += (tmp.data[i][i] > EPSILON || tmp.data[i][i] < -EPSILON);
    }
    return retVal;
}

void Matrix::swapRow(unsigned int rowA, unsigned int rowB)
{
    for(unsigned int i = 0; i < col; i++)
    {
        double tmp = 0;
        tmp = data[rowA][i];
        data[rowA][i] = data[rowB][i];
        data[rowB][i] = tmp;
    }
}

void Matrix::swapCol(unsigned int colA, unsigned int colB)
{
    for(unsigned int i = 0; i < row; i++)
    {
        double tmp = 0;
        tmp = data[i][colA];
        data[i][colA] = data[i][colB];
        data[i][colB] = tmp;
    }
}

void Matrix::rowMul(unsigned int _row, double c)
{
    for(unsigned int i = 0; i < col; i++)
    {
        data[_row][i] *= c;
    }
}

void Matrix::colMul(unsigned int _col, double c)
{
    for(unsigned int i = 0; i < row; i++)
    {
        data[i][_col] *= c;
    }
}

void Matrix::rowMulAdd(unsigned int rowA, unsigned int rowB, double c)
{
    for(unsigned int i = 0; i < col; i++)
    {
        data[rowA][i] += data[rowB][i] * c;
    }
}

void Matrix::colMulAdd(unsigned int colA, unsigned int colB, double c)
{
    for(unsigned int i = 0; i < row; i++)
    {
        data[i][colA] += data[i][colB] * c;
    }
}

int Matrix::colFindNZ(unsigned int col, unsigned int start)
{
    unsigned int pos = start;
    while(pos < this -> row)
    {
        if(std::abs(data[pos][col]) > EPSILON)
        {
            break;
        }
        pos++;
    }
    return (pos < this -> row) ? int(pos) : -1;
}

Matrix Matrix::getCol_QR(unsigned int _col)
{
    Matrix retVal(row, 1);
    for(unsigned int i = _col; i < row; i++)
    {
        retVal.data[i][0] = data[i][_col];
    }
    return retVal;
}

bool Matrix::isDownLeftZero(unsigned int _row, unsigned int _col)
{
    for(unsigned int i = 0; i < _col; i++)
    {
        if(data[_row][_col - i - 1] > EPSILON || data[_row][_col - i - 1] < -EPSILON)
        {
            return false;
        }
    }
    for(unsigned int j = _row + 1; j < row; j++)
    {
        if(data[j][_col] > EPSILON || data[j][_col] < -EPSILON)
        {
            return false;
        }
    }
    return true;
}

ElemMatrix::ElemMatrix(unsigned int n)
: Matrix(n, n)
{
    for(unsigned int i = 0; i < n; i++)
    {
        data[i][i] = 1;
    }
}

#endif