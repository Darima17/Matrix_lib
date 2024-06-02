#ifndef CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <stdexcept>

class S21Matrix {
 private:
  // Attributes
  int rows_ = 0, cols_ = 0;    // Rows and columns
  double **matrix_ = nullptr;  // Pointer to the memory where the matrix is

 public:
  S21Matrix();                             // Default constructor
  S21Matrix(const S21Matrix &other);       // Copy constructor
  S21Matrix(S21Matrix &&other) noexcept;   // Move constructor
  explicit S21Matrix(int rows, int cols);  // Parametrized constructor
  ~S21Matrix();                            // Destructor

  void Create_matrix(int rows, int cols);
  void Delete_matrix();
  void Copy_matrix(double **matrix);
  bool Eq_Size(const S21Matrix &other);
  S21Matrix Minor_matrix(int row, int col) const;

  // Operation
  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // Getters and setters
  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int rows);
  void SetCols(int cols);

  // Operators
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix &other);
  void operator+=(const S21Matrix &other);
  void operator-=(const S21Matrix &other);
  void operator*=(const S21Matrix &other);
  void operator*=(const double num);
  double &operator()(int i, int j);
  const double &operator()(int i, int j) const;
};

#endif  // CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_H_
