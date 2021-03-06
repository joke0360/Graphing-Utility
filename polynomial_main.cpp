 /*
 * polynomial_main.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: Zhen Qiu
 */

#include <iostream>
#include <vector>
#include "postscript.hpp"
#include "csv_parser.hpp"
#include "polynomial.cpp"
using namespace std;

int main(void){
	const int dot_num=20;
	const double xscale=40.;
	const double yscale=100.;
	const char *filename="polynomial_data.csv";
	FILE *in_file=fopen(filename,"r");
	const char field_terminator = ',';
	const char line_terminator  = '\n';
	const char enclosure_char   = '"';
	csv_parser p=csv_parser();
	if(!p.csv_parser::init(in_file)){
	   std::cout << "can not read a file" <<endl;
	   exit(-1);
	}
	p.set_skip_lines(1);
	p.set_enclosed_char(enclosure_char, ENCLOSURE_OPTIONAL);
	p.set_field_term_char(field_terminator);
	p.set_line_term_char(line_terminator);
	unsigned int row_count = 1U;
	vector<int> index;
	vector<double> coefficient;
	while(p.has_more_rows())
	        {
	                unsigned int i = 0;
	                csv_row row = p.get_row();
	                for (i = 0; i < row.size(); i++)
	                {
	                        printf("COLUMN %02d : %s\n", i + 1U, row[i].c_str());
	                }
	                index.push_back(atoi(row[0].c_str()));
	                coefficient.push_back(atoi(row[1].c_str()));
	                printf("====================================================================\n");
	                printf("END OF ROW %02d\n", row_count);
	                printf("====================================================================\n");
	                row_count++;
	        }
	for(int i=0;i<row_count-1;i++){
	    	cout << index[i] << " " << coefficient[i] << "\n";
	}
    const char out_file[]="poly_test.ps";
	Postscript poly_post(out_file);
    Polynomial poly(index, coefficient);
    graphic_value v=new double[dot_num][2];
    v=poly.polynomial_to_graphic(dot_num, xscale);
    for(int i=0;i<dot_num;i++){
    	for(int j=0;j<2;j++){
    		cout << v[i][j] << " " ;
    	}
    	cout << "\n";
    }
    poly_post.SetLineWidth(6);
    poly_post.coordinate(xscale,yscale);
    poly_post.setcolor(1,0,1);
    for(int i=0;i<dot_num-1;i++){
       poly_post.line(**(v+i),*(*(v+i)+1),**(v+i+1),*(*(v+i+1)+1));
    }
}






