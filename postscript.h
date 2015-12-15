/*
* postscript.hpp
*
*  Created on: Dec,25,2015
*      Author: Nan Cheng
*Final edition
*/

#ifndef POSTSCRIPT_HPP_
#define POSTSCRIPT_HPP_
#include <iostream>
#include <fstream>
#include<string>
using namespace std;

class Postscript {
private:
	ofstream file;
public:
	Postscript(const char filename[]) :file(filename) {}

	void circle(double x, double y,double r) //to draw a circle point, and as a point, it has a default radius as 0.5.
	{
		file << x << ' ' << y << ' ' << 0.01*r << ' ' << 0 << ' ' << 360 << ' ' << "arc" << ' ' << "stroke\n";

	}
	void rectangle(double x, double y,double r) //to draw a square point, it has a default length of side as 1.
	{
		file << x - 0.01*r << ' ' << y - 0.01*r << " moveto " << x - 0.01*r << ' ' << y + 0.01*r << " lineto "
			<< x + 0.01*r << ' ' << y + 0.01*r << " lineto " << x + 0.01*r << ' ' << y - 0.01*r << " lineto " << "fill\n";
			 

	}
	void coordinate(double x, double y) //postscript has a default coordinate system, but it does not draw it on the page.
										//I use this method to draw another default coordinate system,move origin and scale the x and y axises by a factor of a parameter corresponding to the max x and y.
										//x,y means the max value of data set
	{
		file << 100 << ' ' << 100 << ' ' << "translate\n"//lower-left of images at (0.1x, 0.1y)
			<< 300.0/x << ' ' << 400.0/y << ' ' << "scale "//size of rendered image is 1.2x points by 1.2y points
			<< 0 << ' ' << 0 << " moveto " << 1.2*x << ' ' << 0 << ' ' << "lineto stroke\n"//draw x axis and the "x" in "1.2*x" means the max value of a dataset.
			<< 0 << ' ' << 0 << " moveto " << 0 << ' ' << 1.2*y << ' ' << "lineto stroke\n"//using the same method to draw y axis
			<< 1.2*x << ' ' << 0.01*y << " moveto " << 1.2*x << ' ' << -0.01*y << " lineto " << 1.25*x << ' ' << 0 << ' ' << " lineto" << ' ' << " fill "
			<< 0.01*x << ' ' << 1.2*y << " moveto " << -0.01*x << ' ' << 1.2*y << " lineto " << 0 << ' ' << 1.25*y << ' ' << "lineto" << ' ' << "fill\n";
		//fill a small triangle at the end of both axises.
	}
	void SetLineWidth(double w)//to set line width
	{
		file << w << ' ' << "setlinewidth" << '\n';
	}
	void line(double x1, double y1, double x2, double y2) //to draw a line to connect 2 points
	{
		file << x1 << ' ' << y1 << ' ' << "moveto " << x2 << ' ' << y2 << " lineto stroke\n";

	}
	void Setdash(double dashsize)//to set a dash size, so I can draw a dash line.
	{

		file << '[' << dashsize << ' ' << dashsize << ']' << ' ' << 0 << ' ' << "setdash" << '\n';
	}

	void setcolor(int r, int g, int b)//to set color
	{
		file << r << " " << g << " " << b << " " << " setrgbcolor " << '\n';
	}
	void fillRect(double x, double y, double w, double h)//to fill a rectangle when I want to draw a bar graph

	{
		file << x << ' ' << y << " moveto " << x+w << ' ' << y << " lineto "
			<< x+w << ' ' << y + h<< " lineto " << x  << ' ' << y +h << " lineto " << "fill\n";
	}
	void Type(double x, double y, string a)
	{
		file << x << ' ' << y << ' ' << "moveto" <<' '<< '(' << a << ')' << ' ' << "show" << '\n';
	}
	void Num(double x, double y, double a)
	{
		file << x << ' ' << y << ' ' << "moveto" << ' ' << '(' << a << ')' << ' ' << "show" << '\n';
	}
	void font(double x)
	{
		file << "/selectFont { exch findfont exch scalefont setfont  } def" << '\n' << "/Helvetica "<<x/6<<" selectFont" << '\n';
	}

};




#endif /* POSTSCRIPT_HPP_ */
#pragma once
