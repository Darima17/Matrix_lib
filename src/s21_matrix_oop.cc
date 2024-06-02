#include "s21_matrix_oop.h"

//*** Methods ***
S21Matrix::~S21Matrix() { Delete_matrix(); }

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) { Create_matrix(rows, cols); };

S21Matrix::S21Matrix(const S21Matrix &other) {
  Create_matrix(other.rows_, other.cols_);
  Copy_matrix(other.matrix_);
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

//*** Getters and setters ***
int S21Matrix::GetRows() const noexcept { return rows_; }
int S21Matrix::GetCols() const noexcept { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows <= 0) {
    throw std::range_error(
        "Invalid size of matrix: rows or/and columns have to be more than 0!");
  }
  S21Matrix result(rows, cols_);
  int min_rows = std::min(rows, rows_);
  for (int i = 0; i < min_rows; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[i][j];
    }
  }
  if (rows > rows_) {
    for (int i = rows_; i < rows; i++) {
      for (int j = 0; j < cols_; j++) {
        result.matrix_[i][j] = 0;
      }
    }
  }
  *this = std::move(result);
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) {
    throw std::range_error(
        "Invalid size of matrix: rows or/and columns have to be more than 0!");
  }
  S21Matrix result(rows_, cols);
  int min_cols = std::min(cols, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < min_cols; j++) {
      result.matrix_[i][j] = matrix_[i][j];
    }
  }
  if (cols > cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = cols_; j < cols; j++) {
        result.matrix_[i][j] = 0;
      }
    }
  }
  *this = std::move(result);
}

//*** Helper functions ***
void S21Matrix::Create_matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  if (rows <= 0 || cols <= 0)
    throw std::range_error(
        "Invalid size of matrix: rows or/and columns have to be more than 0!");
  matrix_ = new double *[rows_] {};
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{};
  }
}

void S21Matrix::Delete_matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

void S21Matrix::Copy_matrix(double **matrix) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix[i][j];
    }
  }
}

bool S21Matrix::Eq_Size(const S21Matrix &other) {
  return rows_ == other.rows_ && cols_ == other.cols_;
}

S21Matrix S21Matrix::Minor_matrix(int row, int col) const {
  S21Matrix result(rows_ - 1, cols_ - 1);
  int minor_row = 0, minor_col = 0;
  for (int i = 0; i < rows_; i++) {
    if (i != row) {
      minor_col = 0;
      for (int j = 0; j < cols_; j++) {
        if (j != col) {
          result.matrix_[minor_row][minor_col] = matrix_[i][j];
          minor_col++;
        }
      }
      minor_row++;
    }
  }
  return result;
}

//*** Operations ***

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = true;
  if (!Eq_Size(other)) {
    result = false;
  }
  for (int i = 0; i < rows_ && result; i++) {
    for (int j = 0; (j < cols_) && result; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-6) {
        result = false;
      }
    }
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (!Eq_Size(other)) {
    throw std::length_error(
        "Size of matrix is different, try sum same size matrix");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (!Eq_Size(other)) {
    throw std::length_error(
        "Size of matrix is different, try sub same size matrix");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::length_error(
        "Size of matrix is different, try mul same size matrix");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int k = 0; k < other.rows_; k++) {
      for (int j = 0; j < other.cols_; j++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  std::swap(*this, result);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::length_error(
        "Matrix  isn't square, can't calculate its complements");
  }
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = pow(-1, i + j) * Minor_matrix(i, j).Determinant();
    }
  }

  return result;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::length_error(
        "Matrix  isn't square, can't calculate its determinant");
  }
  if (rows_ == 1) {
    return matrix_[0][0];
  }
  if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  }
  double result = 0;
  for (int i = 0; i < rows_; i++) {
    result += pow(-1, i) * matrix_[0][i] * Minor_matrix(0, i).Determinant();
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_ || Determinant() == 0) {
    throw std::length_error(
        "Matrix  isn't square or has zero determinant, can't calculate its "
        "inverse matrix");
  }
  S21Matrix result(rows_, cols_);
  result = CalcComplements().Transpose();
  result.MulNumber(1 / Determinant());
  return result;
}

//*** Operators ***

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (&other == this) return *this;
  Delete_matrix();
  matrix_ = other.matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
  return *this;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    *this = S21Matrix(other);
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

void S21Matrix::operator+=(const S21Matrix &other) { SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix &other) { SubMatrix(other); }

void S21Matrix::operator*=(const S21Matrix &other) { MulMatrix(other); }

void S21Matrix::operator*=(const double num) { MulNumber(num); }

double &S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || i < 0 || j >= cols_ || j < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[i][j];
}

const double &S21Matrix::operator()(int i, int j) const {
  if (i >= rows_ || i < 0 || j >= cols_ || j < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[i][j];
}