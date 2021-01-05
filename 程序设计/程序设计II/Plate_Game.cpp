#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class Piece
{
	private:
		//卡片位置
		int posX;
		int posY;
		//值
		int val;
	public:
		//constructor
		Piece(){};
		//destructor
		~Piece(){};
		//初始化
		void init(int x, int y, int value)
		{
			posX = x;
			posY = y;
			val = value;
		}
		//重设值
		void setVal(int value)
		{
			val = value;
		}
		//获得值
		int getVal()
		{
			return val;
		}
};

class Plate
{
	private:
		//盘面高度
		int height;
		//盘面宽度
		int width;
		//用于存放卡片对象的指针
		Piece * pieces;
		//打印卡片水平线
		void printHorizental(int rownum);
		//打印垂直线
		void printVertical(int rownum);
		//打印值
		void printValue(int rownum);
		//打印一行卡片
		void printRow(int rownum);
		//空白的位置
		int blankX;
		int blankY;
		
	public:
		//分配卡片地址
		void getPieces();
		//consturctor
		//一旦初始化便不再修改，故不提供修改高度宽度的接口
		Plate(int h, int w)
		{
			height = h;
			width = w;
			getPieces();
		}
		//destructor
		~Plate(){delete[] pieces;}
		//初始化盘面
		void initVal();
		//根据命令更新盘面
		void update(char op);
		//打印当前盘面
		void print();
};

void Plate::getPieces()
{
	pieces = new Piece[height * width];
}

int myrand(int i) {return rand() % (i + 1);}
void Plate::initVal()
{
	//产生随机全排列
	int total = height * width;
	vector <int> preSet;
	//初值
	for(int i = 0; i < total; i++)
	{
		preSet.push_back(i);
	}
	//随机种子生成
	srand(time(nullptr));
	//打乱
	random_shuffle(preSet.begin(), preSet.end(), myrand);
	//根据打乱的顺序初始化pieces
	for(int i = 0; i < total; i++)
	{
		pieces[i].init(i % width, i / width, preSet[i]);
		if(preSet[i] == 0)
		{
			blankX = i % width;
			blankY = i / width;
		}
	}
}

void Plate::update(char op)
{
	//空白卡片和下面的互换
	if(op == 'U' || op == 'u')
	{
		if(blankY < height - 1)
		{
			int tmpVal = pieces[width * (blankY + 1) + blankX].getVal();
			pieces[width * (blankY + 1) + blankX].setVal(0);
			pieces[width * blankY + blankX].setVal(tmpVal);
			blankY++;
		}
	}
	//空白卡片和上面的互换
	else if(op == 'D' || op == 'd')
	{
		if(blankY > 0)
		{
			int tmpVal = pieces[width * (blankY - 1) + blankX].getVal();
			pieces[width * (blankY - 1) + blankX].setVal(0);
			pieces[width * blankY + blankX].setVal(tmpVal);
			blankY--;
		}
	}
	//空白卡片和右面的互换
	else if(op == 'L' || op == 'l')
	{
		if(blankX < width - 1)
		{
			int tmpVal = pieces[width * blankY + blankX + 1].getVal();
			pieces[width * blankY + blankX + 1].setVal(0);
			pieces[width * blankY + blankX].setVal(tmpVal);
			blankX++;
		}
	}
	//空白卡片和左面的互换
	else if(op == 'R' || op == 'r')
	{
		if(blankX > 0)
		{
			int tmpVal = pieces[width * blankY + blankX - 1].getVal();
			pieces[width * blankY + blankX - 1].setVal(0);
			pieces[width * blankY + blankX].setVal(tmpVal);
			blankX--;
		}
	}
}
void Plate::printHorizental(int rownum)
{
	for(int i = 0; i < width; i++)
	{
		if(rownum == blankY && i == blankX)
		{
			cout << "       ";
		}
		else
		{
			cout <<"o----o ";
		}
	}
	cout << endl;
}
void Plate::printVertical(int rownum)
{
	for(int i = 0; i < width; i++)
	{
		if(rownum == blankY && i == blankX)
		{
			cout << "       ";
		}
		else
		{
			cout <<"|    | ";
		}
	}
	cout << endl;
}
void Plate::printValue(int rownum)
{
	for(int i = 0; i < width; i++)
	{
		if(rownum == blankY && i == blankX)
		{
			cout << "       ";
		}
		else
		{
			cout << "| ";
			cout.width(2);
			cout << pieces[rownum * width + i].getVal();
			cout << " | ";
		}
	}
	cout << endl;
}

void Plate::printRow(int rownum)
{
	printHorizental(rownum);
	printVertical(rownum);
	printValue(rownum);
	printVertical(rownum);
	printHorizental(rownum);
}
void Plate::print()
{
	for(int i = 0; i < height; i++)
	{
		printRow(i);
	}
}

int main(int argc, char *argv[])
{
	int height, width;
	cout << ">Please input the size of the plate:";
	cin >> height >> width;
	Plate plate(height, width);
	plate.initVal();
	plate.print();
	cout << ">What's your next move:";
	char op;
	cin >> op;
	while(op != 'q' && op != 'Q')
	{
		plate.update(op);
		plate.print();
		cout << ">What's your next move:";
		cin >> op;
	}
	return 0;
}