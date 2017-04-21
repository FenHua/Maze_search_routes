// MazeFroutes.cpp : 定义控制台应用程序的入口点。
#include"iostream"
#include<assert.h>
using namespace std;
template<typename T>class Stack
{
protected:
	T*_ptr;
	int _size;
	int _capacity;
	void _CheckCapcity()
	{
		if (_size == _capacity)
		{
			int NewCapacity = 2 * _capacity + 2;
			T*tmp = new T[NewCapacity];
			for (int i = 0; i < _size; i++)
			{
				tmp[i] = _ptr[i];
			}
			delete[]_ptr;
			_ptr = tmp;
			_capacity = NewCapacity;
		}
	}
public:
	Stack() :_ptr(NULL), _size(0), _capacity(0)
	{}
	~Stack()
	{
		if (_ptr != NULL)
		{
			delete[]_ptr;
			_ptr = NULL;
		}
		_size = 0;
		_capacity = 0;
	}
	void Push(const T&x)
	{
		_CheckCapcity();
		_ptr[_size++] = x;
	}
	void Pop()
	{
		assert(_size >= 0);
		_size--;
	}
	bool Empty()
	{
		return _size == 0;
	}
	T&Top()
	{
		return _ptr[_size - 1];
	}
	size_t Size()
	{
		return _size;
	}
};
const int N = 10;
struct Pos
{
	int _row;
	int _col;
	Pos(int row = 0, int col = 0)
	{
		_row = row;
		_col = col;
	}
};
void InitMaze(int*mz)
{
	char tmp;
	Pos enter;
	FILE*pf = fopen("mazeMap.txt", "r");
	assert(pf);
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N;)
		{
			tmp = fgetc(pf);
			if (tmp == '0' || tmp == '1')
			{
				mz[i*N + j] = tmp - '0';//二维转一维数组
				++j;
			}
		}
	}
}
bool CheckReason(int*mz, Pos pos)
{
	if ((pos._row >= 0) && (pos._row < N) && (pos._row >= 0) && (pos._col < N) && (mz[pos._row*N + pos._col] == 0))
	{
		return true;//有路
	}
	return false;
}
bool FindPath(int *mz, int rows, int cols, Stack<Pos>&s, Pos enter)
{
	s.Push(enter);
	mz[enter._row*cols + enter._col] = 2;
	while (!s.Empty())
	{
		//栈为空，表示无解
		Pos cur = s.Top();
		Pos next = cur;
		if ((next._row == 0) || (next._row == rows - 1) || (next._col == cols - 1))
		{
			//走出迷宫
			return true;
		}
		//往上走
		next._row -= 1;
		if (CheckReason(mz, next))
		{
			s.Push(next);
			mz[next._row*cols + next._col] = 2;//标记
			continue;
		}
		next._row += 1;//复原
		//往右走
		next._col += 1;
		if (CheckReason(mz, next))
		{
			s.Push(next);
			mz[next._row*cols + next._col] = 2;
			continue;
		}
		next._col -= 1;
		//往左走
		next._col -= 1;
		if (CheckReason(mz, next))
		{
			s.Push(next);
			mz[next._row*cols + next._col] = 2;
			continue;
		}
		next._col += 1;
		//往下走
		next._row += 1;
		if (CheckReason((int *)mz, next))
		{
			s.Push(next);
			mz[next._row*cols + next._col] = 2;
			continue;
		}
		next._row -= 1;
		mz[cur._row*cols + cur._col] = 3;//回溯
		s.Pop();
	}
	return false;
}
void PrintMaze(int*mz)
{
	//一维变二维输出
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			cout << mz[i*N + j] << " ";
		}
		cout << endl;
	}
}
int main()
{
	Stack<Pos> s;
	Pos enter;
	enter._col = 0;
	enter._row = 2;
	int*mz = new int[100];
	InitMaze(mz);
	FindPath(mz, 10, 10, s, enter); 
	PrintMaze(mz);
	system("pause");
}