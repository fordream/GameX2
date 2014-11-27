#ifndef MATRIX_H
#define MATRIX_H
#include "Defines.h"
template<class T>
class Matrix{
private:
public:
	int row;
	int col;
	T *datas;

	void SetSize(int r, int c){
		row = r; col = c;
		int msize = r*c;
		if (datas != NULL)delete[] datas;
		if (msize == 0)return;
		datas = new T[msize];
		for (int i = 0; i < msize; i++){
			*(datas + i) = 0;
		}
	}

	Matrix(int r, int c){
		//先行后列
		//A(r,c) datas[r][c]
		row = r; col = c;
		int msize = r*c;
		if (msize == 0)return;
		datas = new T[msize];
		for (int i = 0; i < msize; i++){
			*(datas + i) = 0;
		}
	}
	Matrix(){
		row = col = 0;
		datas = NULL;
	}
	~Matrix(){
		//if(row>0)delete [] datas;
	}
	void CopyTo(Matrix<T> *target){
		if (target == this)return;
		int msize = row*col;
		target->datas = new T[msize];
		target->row = row;
		target->col = col;
		for (int i = 0; i < msize; i++)
			target->datas[i] = datas[i];
	}

	T * const operator[](const int k){
		return &datas[k*col];
	}
	friend ostream & operator << (ostream &os, Matrix &s){
		for (int y = 0; y < s.row; y++){
			for (int x = 0; x < s.col; x++){
				os << s[y][x] << " ";
			}
			os << endl;
		}
		return os;
	}
	void Set(int r, int c, T num){
		//出于数组储存需要,这里有(0,0)
		(*this)[r][c] = num;
	}

	//暂时不作矩阵检查
	Matrix operator+(Matrix &right){
		Matrix temp;// = *this;
		CopyTo(&temp);
		for (int x = 0; x < col; x++){
			for (int y = 0; y < row; y++){
				temp[y][x] += right[y][x];
			}
		}
		return temp;
	}
	Matrix operator-(Matrix &right){
		Matrix temp;// = *this;
		CopyTo(&temp);
		for (int x = 0; x < col; x++){
			for (int y = 0; y < row; y++){
				temp[y][x] -= right[y][x];
			}
		}
		return temp;
	}
	Matrix operator*(Matrix &right){
		Matrix temp(row, right.col);
		for (int x = 0; x < temp.col; x++){
			for (int y = 0; y < temp.row; y++){
				T num = 0;//元素[y][x]
				for (int z = 0; z < col; z++){
					//cout<<(*this)[y][z]<<" * "<<right[z][x]<<" + ";
					num += (*this)[y][z] * right[z][x];
				}
				temp[y][x] = num;
				//cout<<endl;
			}
		}
		return temp;
	}

	Matrix operator*(const T &num){
		Matrix temp(row, col);
		CopyTo(&temp);
		int msize = col * row;
		for (int i = 0; i < msize; i++)
			*(temp.datas + i) = num;

		return temp;
	}
	Matrix& operator*=(const T &num){
		int msize = col * row;
		for (int i = 0; i < msize; i++)
			*(datas + i) *= num;

		return *this;
	}
	Matrix operator/(const T &num){
		Matrix temp(row, col);
		CopyTo(&temp);
		int msize = col * row;
		for (int i = 0; i < msize; i++)
			*(temp.datas + i) /= num;

		return temp;
	}

	Matrix& operator/=(const T &num){
		int msize = col * row;
		for (int i = 0; i < msize; i++)
			*(datas + i) /= num;

		return *this;
	}
	// ELEMENTARY ROW OPERATIONS	
	void Identity(){
		for (int x = 0; x < col; x++){
			for (int y = 0; y < row; y++){
				(*this)[y][x] = (x == y) ? T(1) : T(0);
			}
		}
	}
	void Interchange(int r1, int r2){
		if (r1 == r2)return;
		T temp;
		for (int i = 0; i < col; i++){
			temp = (*this)[r1][i];
			(*this)[r1][i] = (*this)[r2][i];
			(*this)[r2][i] = temp;
		}
	}
	void Scaling(int r, T m){
		for (int i = 0; i < col; i++){
			(*this)[r][i] *= m;
		}
	}
	void Replacement(int r1, int r2, T m){
		for (int i = 0; i < col; i++){
			(*this)[r1][i] += (*this)[r2][i] * m;
		}
	}

	//无参数输入时，为自我进行REF
	void REF(Matrix *result = NULL){
		//Row Echelon Form
		int x, y, z;
		z = 0;
		if (result == NULL)result = this;

		CopyTo(result);

		for (x = 0; x < col; x++){
			for (y = z; y < row; y++){
				if ((*result)[y][x] != 0)break;
			}
			if (y == row)continue;
			result->Interchange(z, y);
			for (int q = y + 1; q < row; q++){
				if ((*result)[q][x] != 0){
					T sc = -(*result)[q][x] / (*result)[z][x];
					result->Replacement(q, z, sc);
				}
			}
			z++;
		}
	}

	void RREF(Matrix *result = NULL){
		//Reduced Row Echelon Form
		int x, y, z;
		z = 0;
		if (result == NULL)result = this;
		CopyTo(result);

		for (x = 0; x < col; x++){
			for (y = z; y < row; y++){
				if ((*result)[y][x] != 0)break;
			}
			if (y == row)continue;
			result->Interchange(z, y);
			result->Scaling(z, T(1) / (*result)[z][x]);
			for (int q = 0; q < row; q++){
				if ((*result)[q][x] != 0 && q != z){
					T sc = -(*result)[q][x];
					result->Replacement(q, z, sc);
				}
			}
			z++;
		}
	}

	void Rotate180(Matrix<T> *result = NULL){
		Matrix<T> *source;
		if (result == NULL){
			result = this;
			source = new Matrix(row, col);
			CopyTo(source);
		}
		else{
			source = this;
		}
		for (int y = 0; y < row; y++){
			for (int x = 0; x < col; x++){
				(*result)[y][x] = (*source)[row - 1 - y][col - 1 - x];
			}
		}
	}

	void Transpose(Matrix<T> *result = NULL){
		Matrix<T> *source;
		if (result == NULL){
			result = this;
			source = new Matrix(col, row);
			CopyTo(source);
		}
		else{
			source = this;
		}
		for (int y = 0; y < row; y++){
			for (int x = 0; x < col; x++){
				result[x][y] = (*source)[y][x];
			}
		}
	}

	void Convolution(Matrix<T> &mould, Matrix<T> *result = NULL){
		Matrix<T> *source;
		if (result == NULL){
			result = this;
			source = new Matrix(col, row);
			CopyTo(source);
		}
		else{
			source = this;
		}
		int newRow = row - mould.row + 1;
		int newCol = col - mould.col + 1;
		if (newCol < 1 || newRow < 1){
			result->SetSize(0, 0);
			//(*result)[0][0] = T(0);
			return;
		}
		result->SetSize(newRow, newCol);
		T sum;
		for (int x = 0; x < newCol; x++){
			for (int y = 0; y < newRow; y++){
				sum = T(0);
				for (int mx = 0; mx < mould.col; mx++){
					for (int my = 0; my < mould.row; my++){
						sum += mould[mould.row - 1 - my][mould.col - 1 - mx] * (*source)[y + my][x + mx];
					}
				}
				(*result)[y][x] = sum;
			}
		}
	}

	bool Invert(Matrix *ra = NULL){
		if (row != col)return false;
		Matrix &result = *ra;
		int newcol = col * 2;
		Matrix temp(row, newcol);
		for (int y = 0; y < row; y++){
			for (int x = 0; x < col; x++){
				temp[y][x] = (*this)[y][x];
			}
		}
		for (int y = 0; y < row; y++){
			for (int x = col; x < newcol; x++){
				temp[y][x] = (y == x - col) ? T(1) : T(0);
			}
		}
		//cout<<temp<<endl;
		temp.RREF();
		//cout<<temp<<endl;
		for (int y = 0; y < row; y++){
			for (int x = 0; x < col; x++){
				if (temp[y][x] != ((y == x) ? T(1) : T(0)))return false;
			}
		}
		if (ra == NULL) ra = this;
		if (ra != NULL){
			*ra = Matrix(row, col);
			for (int y = 0; y < row; y++){
				for (int x = col; x <= newcol; x++){
					(*ra)[y][x - col] = temp[y][x];
				}
			}
		}
		return true;
	}
};
#endif
