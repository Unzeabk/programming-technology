#include <iostream>
#include <stdexcept>

using namespace std;

class vect {
private:
    int dim;
    double* b;
    int num;
public:
    static int count;

    vect() : dim(0), b(nullptr) {
        num = ++count;
        cout << "Vector [" << num << "] created (default)" << endl;
    }

    vect(int d) : dim(d) {
        if (dim < 0) {
            throw invalid_argument("Dimension must be non-negative");
        }
        b = new double[dim]();
        num = ++count;
        cout << "Vector [" << num << "] created (dim = " << dim << ")" << endl;
    }

    vect(const vect& other) : dim(other.dim) {
        b = new double[dim];
        for (int i = 0; i < dim; ++i) {
            b[i] = other.b[i];
        }
        num = ++count;
        cout << "Vector [" << num << "] copy created from Vector [" << other.num << "]" << endl;
    }

    ~vect() {
        delete[] b;
        cout << "Vector [" << num << "] destroyed" << endl;
    }

    vect& operator=(const vect& other) {
        if (this == &other)
            return *this;
        if (dim != other.dim) {
            delete[] b;
            dim = other.dim;
            b = new double[dim];
        }
        for (int i = 0; i < dim; ++i) {
            b[i] = other.b[i];
        }
        cout << "Assigning Vector [" << other.num << "] to Vector [" << num << "]" << endl;
        return *this;
    }

    vect operator+(const vect& other) const {
        if (dim != other.dim) {
            cerr << "Error: vectors dimensions do not match for addition." << endl;
            return vect();
        }
        cout << "Adding vectors [" << num << "] and [" << other.num << "]" << endl;
        vect result(dim);
        for (int i = 0; i < dim; ++i) {
            result.b[i] = b[i] + other.b[i];
        }
        return result;
    }

    vect operator-(const vect& other) const {
        if (dim != other.dim) {
            cerr << "Error: vectors dimensions do not match for subtraction." << endl;
            return vect();
        }
        cout << "Subtracting vectors [" << other.num << "] from [" << num << "]" << endl;
        vect result(dim);
        for (int i = 0; i < dim; ++i) {
            result.b[i] = b[i] - other.b[i];
        }
        return result;
    }

    vect operator-() const {
        cout << "Negating vector [" << num << "]" << endl;
        vect result(dim);
        for (int i = 0; i < dim; ++i) {
            result.b[i] = -b[i];
        }
        return result;
    }

    vect operator*(double k) const {
        cout << "Multiplying vector [" << num << "] by scalar " << k << endl;
        vect result(dim);
        for (int i = 0; i < dim; ++i) {
            result.b[i] = k * b[i];
        }
        return result;
    }

    void print() const {
        cout << "Vector [dim=" << dim << "] : ";
        for (int i = 0; i < dim; ++i) {
            cout << b[i] << " ";
        }
        cout << endl;
    }

    int getDim() const { return dim; }
    void setValue(int i, double value) { 
        if(i >= 0 && i < dim) {
            b[i] = value;
        }
    }
    double getValue(int i) const { 
        return (i >= 0 && i < dim) ? b[i] : 0;
    }
};

int vect::count = 0;

class matr {
private:
    int dim;
    int dim2;
    double** a;
    int num;
public:
    static int count;

    matr() : dim(0), dim2(0), a(nullptr) {
        num = ++count;
        cout << "Matrix [" << num << "] created (default)" << endl;
    }

    matr(int d, int d2) : dim(d), dim2(d2) {
        if(dim < 0 || dim2 < 0)
            throw invalid_argument("Matrix dimensions must be non-negative");

        a = new double*[dim];
        for (int i = 0; i < dim; ++i) {
            a[i] = new double[dim2]();
        }
        num = ++count;
        cout << "Matrix [" << num << "] created (dim = " << dim << ", " << dim2 << ")" << endl;
    }

    matr(const matr& other) : dim(other.dim), dim2(other.dim2) {
        a = new double*[dim];
        for (int i = 0; i < dim; ++i) {
            a[i] = new double[dim2];
            for (int j = 0; j < dim2; ++j)
                a[i][j] = other.a[i][j];
        }
        num = ++count;
        cout << "Matrix [" << num << "] copy created from Matrix [" << other.num << "]" << endl;
    }

    ~matr() {
        for (int i = 0; i < dim; ++i) {
            delete[] a[i];
        }
        delete[] a;
        cout << "Matrix [" << num << "] destroyed" << endl;
    }

    matr& operator=(const matr& other) {
        if (this == &other)
            return *this;

        for (int i = 0; i < dim; ++i) {
            delete[] a[i];
        }
        delete[] a;

        dim = other.dim;
        dim2 = other.dim2;
        a = new double*[dim];
        for (int i = 0; i < dim; ++i) {
            a[i] = new double[dim2];
            for (int j = 0; j < dim2; ++j)
                a[i][j] = other.a[i][j];
        }
        cout << "Assigning Matrix [" << other.num << "] to Matrix [" << num << "]" << endl;
        return *this;
    }

    matr operator+(const matr& other) const {
        if (dim != other.dim || dim2 != other.dim2) {
            cerr << "Error: matrix dimensions do not match for addition." << endl;
            return matr();
        }
        cout << "Adding matrices [" << num << "] and [" << other.num << "]" << endl;
        matr result(dim, dim2);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim2; ++j) {
                result.a[i][j] = a[i][j] + other.a[i][j];
            }
        }
        return result;
    }

    matr operator-(const matr& other) const {
        if (dim != other.dim || dim2 != other.dim2) {
            cerr << "Error: matrix dimensions do not match for subtraction." << endl;
            return matr();
        }
        cout << "Subtracting matrices [" << other.num << "] from [" << num << "]" << endl;
        matr result(dim, dim2);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim2; ++j) {
                result.a[i][j] = a[i][j] - other.a[i][j];
            }
        }
        return result;
    }

    matr operator-() const {
        cout << "Negating matrix [" << num << "]" << endl;
        matr result(dim, dim2);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim2; ++j) {
                result.a[i][j] = -a[i][j];
            }
        }
        return result;
    }

    matr operator*(const matr& other) const {
        if (dim2 != other.dim) {
            cerr << "Error: matrix dimensions do not match for multiplication." << endl;
            return matr();
        }
        cout << "Multiplying matrices [" << num << "] and [" << other.num << "]" << endl;
        matr result(dim, other.dim2);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < other.dim2; ++j) {
                result.a[i][j] = 0;
                for (int k = 0; k < dim2; ++k) {
                    result.a[i][j] += a[i][k] * other.a[k][j];
                }
            }
        }
        return result;
    }

    matr operator*(double k) const {
        cout << "Multiplying matrix [" << num << "] by scalar " << k << endl;
        matr result(dim, dim2);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim2; ++j) {
                result.a[i][j] = k * a[i][j];
            }
        }
        return result;
    }

    vect operator*(const vect& v) const {
        if (dim2 != v.getDim()) {
            cerr << "Error: matrix and vector dimensions do not match for multiplication." << endl;
            return vect();
        }
        cout << "Multiplying matrix [" << num << "] by vector" << endl;
        vect result(dim);
        for (int i = 0; i < dim; ++i) {
            double sum = 0;
            for (int j = 0; j < dim2; ++j) {
                sum += a[j][i] * v.getValue(j);
            }
            result.setValue(i, sum);
        }
        return result;
    }

    void print() const {
        cout << "Matrix [" << dim << "x" << dim2 << "]:" << endl;
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim2; ++j) {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
    }

    int getRows() const { return dim; }
    int getCols() const { return dim2; }
    void setValue(int i, int j, double value) { 
         if(i >= 0 && i < dim && j >= 0 && j < dim2)
             a[i][j] = value; 
    }
    double getValue(int i, int j) const { 
         return (i >= 0 && i < dim && j >= 0 && j < dim2) ? a[i][j] : 0;
    }
};

int matr::count = 0;

int main() {
    // Работа с векторами
    vect v1(3), v2(3);
    for (int i = 0; i < v1.getDim(); ++i) {
        v1.setValue(i, i + 1);       // 1, 2, 3
        v2.setValue(i, (i + 1) * 10);  // 10, 20, 30
    }
    
    vect v3 = v1 + v2;
    v3.print();
    
    vect v4 = v2 - v1;
    v4.print();
    
    vect v5 = -v1;
    v5 = v5 * 5;
    v5.print();

    // Работа с матрицами
    matr m3(2, 2);
    m3.setValue(0, 0, 1); m3.setValue(0, 1, 2);
    m3.setValue(1, 0, 3); m3.setValue(1, 1, 4);
    m3.print();
    
    matr m4 = m3 + m3;
    m4.print();
    
    matr m5 = m3 - m3;
    m5.print();
    
    matr m6 = -m3;
    m6.print();
    
    matr m7(2, 2), m8(2, 2);
    m7.setValue(0, 0, 1); m7.setValue(0, 1, 2);
    m7.setValue(1, 0, 3); m7.setValue(1, 1, 4);
    m8.setValue(0, 0, 5); m8.setValue(0, 1, 6);
    m8.setValue(1, 0, 7); m8.setValue(1, 1, 8);
    
    m7.print();
    m8.print();
    
    matr m9 = m7 * m8;
    m9.print();
    
    matr m10 = m7 * 2;
    m10.print();
    
    vect v7(2);
    v7.setValue(0, 1); v7.setValue(1, 2);
    vect v8 = m7 * v7;
    v8.print();

    return 0;
}

/*

Vector [1] created (dim = 3)
Vector [2] created (dim = 3)
Adding vectors [1] and [2]
Vector [3] created (dim = 3)
Vector [4] copy created from Vector [3]
Vector [3] destroyed
Vector [dim=3] : 11 22 33 
Subtracting vectors [1] from [2]
Vector [5] created (dim = 3)
Vector [6] copy created from Vector [5]
Vector [5] destroyed
Vector [dim=3] : 9 18 27 
Negating vector [1]
Vector [7] created (dim = 3)
Multiplying vector [7] by scalar 5
Vector [8] created (dim = 3)
Assigning Vector [8] to Vector [7]
Vector [8] destroyed
Vector [dim=3] : -5 -10 -15 
Matrix [1] created (dim = 2, 2)
Matrix [2x2]:
1 2 
3 4 
Adding matrices [1] and [1]
Matrix [2] created (dim = 2, 2)
Matrix [3] copy created from Matrix [2]
Matrix [2] destroyed
Matrix [2x2]:
2 4 
6 8 
Subtracting matrices [1] from [1]
Matrix [4] created (dim = 2, 2)
Matrix [5] copy created from Matrix [4]
Matrix [4] destroyed
Matrix [2x2]:
0 0 
0 0 
Negating matrix [1]
Matrix [6] created (dim = 2, 2)
Matrix [2x2]:
-1 -2 
-3 -4 
Matrix [7] created (dim = 2, 2)
Matrix [8] created (dim = 2, 2)
Matrix [2x2]:
1 2 
3 4 
Matrix [2x2]:
5 6 
7 8 
Multiplying matrices [7] and [8]
Matrix [9] created (dim = 2, 2)
Matrix [10] copy created from Matrix [9]
Matrix [9] destroyed
Matrix [2x2]:
19 22 
43 50 
Multiplying matrix [7] by scalar 2
Matrix [11] created (dim = 2, 2)
Matrix [2x2]:
2 4 
6 8 
Vector [9] created (dim = 2)
Multiplying matrix [7] by vector
Vector [10] created (dim = 2)
Vector [11] copy created from Vector [10]
Vector [10] destroyed
Vector [dim=2] : 7 10 
Vector [11] destroyed
Vector [9] destroyed
Matrix [11] destroyed
Matrix [10] destroyed
Matrix [8] destroyed
Matrix [7] destroyed
Matrix [6] destroyed
Matrix [5] destroyed
Matrix [3] destroyed
Matrix [1] destroyed
Vector [7] destroyed
Vector [6] destroyed
Vector [4] destroyed
Vector [2] destroyed
Vector [1] destroyed

*/