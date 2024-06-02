#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

class MatrixTest : public ::testing::Test {
 public:
  S21Matrix FillMatrix_add(int rows, int cols) {
    int num = 1;
    S21Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        result(i, j) = num;
        num++;
      }
    }
    return result;
  }

  S21Matrix FillMatrix_same(int rows, int cols, float num) {
    S21Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        result(i, j) = num;
      }
    }
    return result;
  }

  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(MatrixTest, TestGetRows) {
  S21Matrix result = FillMatrix_add(3, 2);
  int expected_rows = 3;
  int actual_rows = result.GetRows();
  ASSERT_EQ(expected_rows, actual_rows);
}

TEST_F(MatrixTest, TestGetRowsEmptyMatrix) {
  // Testing if the GetRows function returns 0 for an empty matrix
  S21Matrix result;
  int expected_rows = 0;
  int actual_rows = result.GetRows();
  ASSERT_EQ(expected_rows, actual_rows);
}

TEST_F(MatrixTest, TestGetRowsSingleRow) {
  // Testing if the GetRows function returns 1 for a matrix with a single row
  S21Matrix result = FillMatrix_add(1, 2);
  int expected_rows = 1;
  int actual_rows = result.GetRows();
  ASSERT_EQ(expected_rows, actual_rows);
}

TEST_F(MatrixTest, TestGetCols) {
  S21Matrix result = FillMatrix_add(3, 2);
  int expected_cols = 2;
  int actual_cols = result.GetCols();
  ASSERT_EQ(expected_cols, actual_cols);
}

TEST_F(MatrixTest, TestSetRows_less) {
  S21Matrix matrix = FillMatrix_same(3, 2, 3.14);
  matrix.SetRows(1);
  S21Matrix res = FillMatrix_same(1, 2, 3.14);
  ASSERT_TRUE(res.EqMatrix(res));
}

TEST_F(MatrixTest, TestSetRows_more) {
  S21Matrix matrix = FillMatrix_same(1, 1, 3.14);
  matrix.SetRows(3);
  S21Matrix result(3, 1);
  result(0, 0) = 3.14;
  result(1, 0) = 0;
  result(2, 0) = 0;
  ASSERT_TRUE(result == matrix);
}

TEST_F(MatrixTest, TestSetCols_less) {
  S21Matrix matrix = FillMatrix_same(3, 2, 3.14);
  matrix.SetCols(1);
  S21Matrix res = FillMatrix_same(3, 1, 3.14);
  ASSERT_TRUE(res.EqMatrix(res));
}

TEST_F(MatrixTest, TestSetCols_more) {
  S21Matrix matrix = FillMatrix_same(1, 1, 3.14);
  matrix.SetCols(3);
  S21Matrix result(1, 3);
  result(0, 0) = 3.14;
  result(0, 1) = 0;
  result(0, 2) = 0;
  ASSERT_TRUE(result == matrix);
}

TEST_F(MatrixTest, TestSum) {
  S21Matrix matrix1 = FillMatrix_same(3, 2, 3.14);
  S21Matrix matrix2 = FillMatrix_same(3, 2, -3.14);
  matrix1.SumMatrix(matrix2);
  S21Matrix res = FillMatrix_same(3, 2, 0);
  ASSERT_TRUE(matrix1.EqMatrix(res));
}

TEST_F(MatrixTest, TestSum_operation) {
  S21Matrix matrix1 = FillMatrix_same(3, 2, 3.14);
  S21Matrix matrix2 = FillMatrix_same(3, 2, -3.14);
  S21Matrix sum = matrix1 + matrix2;
  matrix1 += matrix2;
  S21Matrix res = FillMatrix_same(3, 2, 0);
  ASSERT_TRUE(matrix1 == res);
  ASSERT_TRUE(sum == res);
}

TEST_F(MatrixTest, TestSub) {
  S21Matrix matrix1 = FillMatrix_same(3, 2, 3.14);
  S21Matrix matrix2 = FillMatrix_same(3, 2, -3.14);
  matrix1.SubMatrix(matrix2);
  S21Matrix res = FillMatrix_same(3, 2, 6.28);
  ASSERT_TRUE(matrix1.EqMatrix(res));
}

TEST_F(MatrixTest, TestSub_operation) {
  S21Matrix matrix1 = FillMatrix_same(3, 2, 3.14);
  S21Matrix matrix2 = FillMatrix_same(3, 2, -3.14);
  S21Matrix sub = matrix1 - matrix2;
  matrix1 -= matrix2;
  S21Matrix res = FillMatrix_same(3, 2, 6.28);
  ASSERT_TRUE(matrix1.EqMatrix(res));
  ASSERT_TRUE(sub == res);
}

TEST_F(MatrixTest, TestCopy_operation) {
  S21Matrix matrix1 = FillMatrix_same(3, 2, 3.14);
  S21Matrix matrix3 = FillMatrix_same(3, 2, 3.14);
  S21Matrix matrix2(3, 2);
  matrix2 = matrix1;
  ASSERT_TRUE(matrix2 == matrix3);
}

TEST_F(MatrixTest, TestMulNum) {
  double num = 4;
  S21Matrix matrix1 = FillMatrix_same(2, 3, 1);
  S21Matrix matrix2 = FillMatrix_same(2, 3, 2);
  S21Matrix res1(2, 3);
  res1 = matrix1 * num;
  matrix2 *= num;
  S21Matrix res2 = FillMatrix_same(2, 3, 4);
  S21Matrix res3 = FillMatrix_same(2, 3, 8);
  ASSERT_TRUE(res1 == res2);
  ASSERT_TRUE(matrix2 == res3);
}

TEST_F(MatrixTest, TestMul) {
  S21Matrix matrix1 = FillMatrix_same(3, 3, 1);
  S21Matrix matrix2 = FillMatrix_same(3, 3, 2);
  matrix1.MulMatrix(matrix2);
  S21Matrix res = FillMatrix_same(3, 3, 6);
  ASSERT_TRUE(matrix1 == res);
}

TEST_F(MatrixTest, TestMul_matrix_operation) {
  S21Matrix matrix1 = FillMatrix_same(3, 3, 1);
  S21Matrix matrix2 = FillMatrix_same(3, 3, 2);
  matrix1 *= matrix2;
  S21Matrix res = FillMatrix_same(3, 3, 6);
  ASSERT_TRUE(matrix1 == res);
}

TEST_F(MatrixTest, TestMul_matrix_operation_sec) {
  S21Matrix matrix1 = FillMatrix_same(2, 3, 1);
  S21Matrix matrix2 = FillMatrix_same(3, 2, 2);
  S21Matrix result(3, 3);
  result = (matrix1 * matrix2);
  S21Matrix res = FillMatrix_same(2, 2, 6);
  ASSERT_TRUE(result == res);
}

TEST_F(MatrixTest, MatrixTest_EqMatr_operation) {
  S21Matrix matrix1 = FillMatrix_same(3, 2, 3.14);
  S21Matrix matrix2 = FillMatrix_same(3, 2, 3.14);
  bool res = matrix1 == matrix2;
  ASSERT_TRUE(res);
}

TEST_F(MatrixTest, Determ_Matrix) {
  S21Matrix matrix1 = FillMatrix_add(2, 2);
  double det = matrix1.Determinant();
  ASSERT_EQ(-2, det);
}

TEST_F(MatrixTest, Determ_Matrix_zero) {
  S21Matrix matrix1 = FillMatrix_same(4, 4, 1);
  double det = matrix1.Determinant();
  ASSERT_EQ(0, det);
}

TEST_F(MatrixTest, Transpose_Matrix) {
  S21Matrix matrix1 = FillMatrix_add(2, 2);
  S21Matrix result(2, 2);
  result(0, 0) = 1;
  result(0, 1) = 3;
  result(1, 0) = 2;
  result(1, 1) = 4;
  bool res = (result == matrix1.Transpose());
  ASSERT_TRUE(res);
}

TEST_F(MatrixTest, Invers_Matrix) {
  S21Matrix matrix1 = FillMatrix_add(2, 2);
  S21Matrix result(2, 2);
  result(0, 0) = -2;
  result(0, 1) = 1;
  result(1, 0) = 1.5;
  result(1, 1) = -0.5;
  bool res = (result == matrix1.InverseMatrix());
  ASSERT_TRUE(res);
}

TEST_F(MatrixTest, Copy_Matrix) {
  S21Matrix matrix1 = FillMatrix_add(2, 2);
  S21Matrix result(2, 2);
  result = S21Matrix(matrix1);
  ASSERT_TRUE(result == matrix1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
