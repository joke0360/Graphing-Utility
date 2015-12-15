//author:Nan Cheng
//by myself
//Final edition
#include<iostream>
#include<fstream>
#include<vector>
#include"POSTSCRIPT.h"
#include<string>
#include<sstream>
using namespace std;
void Timeseries(string a)// a function to read in a file with time and corresponding data and draw a timeseries script
{
	Postscript A("Timeseries.ps");//construct a Postscript.
	ifstream in(a);//read in a file.
	vector<double> array;
	double buffer = 0;
	while (in >> buffer)
	     array.push_back(buffer);//read in every number in this file.
	int n = array.size();//consider the first half of this array means defferent timings and the second half is corresponding data.
	double MaxX, MaxY,t;//to find max x and max y so that I can draw an appropriate coordinate system.
	double* x = new double[n / 2];
	double* y = new double[n / 2];
	for (int i = 0; i < n / 2; i++)
	{
		x[i] = array[i];
	}
	for (int i = 0; i < n / 2-1; i++)
	{
		if (x[i] > x[i + 1])
		{
			t = x[i + 1];
			x[i + 1] = x[i];
			x[i] = t;
		}
	}
	for (int i = 0; i < n / 2; i++)
	{
		y[i] = array[i+n/2];
	}
	for (int i = 0; i < n / 2 - 1; i++)
	{
		if (y[i] > y[i + 1])
		{
			t = y[i + 1];
			y[i + 1] = y[i];
			y[i] = t;
		}
	}
	MaxX = x[n / 2 - 1];
	MaxY = y[n / 2 - 1];
	
    cout << "choose script type:1.solid line and circle points 2.dash line and square points";
	int choice;//defferent kinds of script
	cin >> choice;
	cout << "Please set line width";
	double w;//set line width
	cin >> w;
	A.SetLineWidth(w);
	A.coordinate(MaxY, MaxY);//draw coordinate system.
	if (choice == 1)
	{
		for (int i = 0; i < n / 2; i++)
		{
			A.circle(array[i]*MaxY/MaxX, array[i + n / 2] ,MaxY);// draw points
		}
		for (int i = 0; i < n / 2 - 1; i++)// draw lines
		{
			A.line(array[i] * MaxY / MaxX, array[i + n / 2] , array[i + 1] * MaxY / MaxX, array[i + 1 + n / 2] );
		}
	}
	else 
	{
		
		double size=0.01*MaxY;
		
		A.Setdash(size);
		for (int i = 0; i < n / 2; i++)
		{
			A.rectangle(array[i] * MaxY / MaxX, array[i + n / 2] ,MaxY);//draw points
		}
		for (int i = 0; i < n / 2 - 1; i++)
		{
			A.line(array[i] * MaxY / MaxX, array[i + n / 2] , array[i + 1] * MaxY / MaxX, array[i + 1 + n / 2] );//draw lines
		}
		
	}
	double wi = MaxY*4 / n;
	A.font(wi);
	for (int i = 0; i < n / 2; i++)
	{
		A.Num(x[i] * MaxY / MaxX, -0.05*MaxY, x[i]);
	}
	for (int i = 0; i < n / 2; i++)
	{
		A.Num(-2*w*MaxY / MaxX, y[i], y[i]);
	}


}
void Bargraph(string a)//read in a file with different kinds of data.
{
	Postscript A("Bargraph.ps");//construct a Postscript.
	ifstream in(a);//read in a file.
	vector<string> array;
	string buffer;
	while (in >> buffer)
		array.push_back(buffer);//read in terms or numbers in this file.
	int n = array.size();
	string* type = new string[n / 2];//restore each term which shows kinds like 'basketball' 'socker''volleyball' or something
	for (int i = 0; i < n / 2; i++)
	{
		type[i] = array[i];
	}
	double b;
	stringstream buffer1;
	double* data = new double[n / 2];//restore each number
	for (int i = n / 2; i < n; i++)
	{
		buffer1 << array[i];
		buffer1 >> b;//convert data type from string to double.
		buffer1.clear();
		data[i - n / 2] = b;

	}
	double MaxY,t;
	double* y = new double[n / 2];
	for (int i = 0; i < n / 2; i++)
	{
		y[i] = data[i];
	}
	for (int i = 0; i < n / 2 - 1; i++)
	{
		if (y[i] > y[i + 1])
		{
			t = y[i + 1];
			y[i + 1] = y[i];
			y[i] = t;
		};
	}
	MaxY = y[n / 2 - 1];//find the max number so I can draw appropriate coordinate system.
	cout << "set bar width";
	double w= MaxY /n;
	//set bar width
	A.SetLineWidth(0);
	A.coordinate(w*(n+1), MaxY);//draw coordinate system
	for (int i = 0; i < n / 2; i++)
	{
		A.fillRect((2*i + 1)*w, 0, w, data[i]);//draw each bar
	}
	A.font(w*2);
	for (int i = 0; i < n / 2; i++)
	{
		A.Type((2*i + 1)*w, -0.05*MaxY, type[i]);
	}
	for (int i = 0; i < n / 2; i++)
	{
		A.Num(-w, data[i], data[i]);
	}


}
void main()
{
	cout << "please enter file name";
	string a;
	cin >> a;
	cout << "1.Timeseries 2.Bargraph";
	int choice;
	cin >> choice;
	if (choice == 1)
		Timeseries(a);
	else Bargraph(a);


}
