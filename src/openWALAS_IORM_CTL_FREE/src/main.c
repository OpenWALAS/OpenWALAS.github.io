/*
 ============================================================================
 Name        : main.c
 *  Created on: 2017-12-29
 *      Author: Peng Yang
 *      Email:  pycssrc@qq.com
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//划分自由面和控制面网格，需要静水面水线数据输入
//支持1/4、1/2和全网格划分
//对静水面水线的数据要求：绕z旋转，同时从船艏的中纵剖面点开始，止于中纵剖面
//对于全模型，采用立柱控制面时要求水线数据必须有3个零点（首尾点相同，2个；中间一个跨越点）

int main(int argc, char *argv[])
{
	int i, j;
	int num;
	const size_t maxNum = 1000;
	char str[maxNum];
	int xNum, zNum;//给出的型线密度
	double x, y, z;
	//x, y, z方向控制面板尺度，xCenter：中心点, a1和b1只对方形立柱情况有效
	double a, a1, b, b1, c, xCenter;
	//x, y, z方向划分的网格数量（控制面）
	int xn, yn, zn;
	//x, y方向划分的网格数量（自由面）,xnF1, xnF2, xnF3表示从艏到尾,xnF2, xnF3只在方形立柱情况使用
	int xnF1, xnF2, xnF3, ynF;
	int ISO_type;//网格类型，1：1/4， 2：1/2，4：全浮体
	int control_type;//控制面类型，1：椭球（包括圆球）；2：椭圆立柱（包括圆形立柱）；3：方形立柱
	//   "1: linear  2: polynomial\n"
	//   "3: cspline 4: cspline_periodic\n"
	//   "5: akima   6: akima_periodic\n"
	//   "7: steffen
	int spline_type;//划分网格时的插值类型
	double zWL;//水线z坐标
	const double PI = 3.1415926;

	//设置默认参数
	char *fileNameIn_params;//输入参数名称
	fileNameIn_params = "hull_line_control_free.in3";//默认参数
	//
	char* fileNameOut_control;
	fileNameOut_control = "hull_line_control.dat";//默认参数
	char* fileNameOut_free;
	fileNameOut_free = "hull_line_free.dat";//默认参数
	char *fileNameIn_waterline;
	fileNameIn_waterline = "waterline.dat";//默认参数

    if(argc == 2)//有输入参数
    	fileNameIn_params = *(argv+1);
    else if(argc == 3)
    {
    	fileNameIn_params = *(argv+1);
    	fileNameOut_control = *(argv+2);
    }
    else if(argc == 4)
    {
    	fileNameIn_params = *(argv+1);
    	fileNameOut_control = *(argv+2);
    	fileNameOut_free = *(argv+3);
    }
    else if(argc == 5)
    {
    	fileNameIn_params = *(argv+1);
    	fileNameOut_control = *(argv+2);
    	fileNameOut_free = *(argv+3);
    	fileNameIn_waterline = *(argv+4);
    }
	else;

	FILE *fin_params;
	fin_params = fopen(fileNameIn_params, "r");
	if(fin_params == NULL)
	{
		printf("Open file %s failed.\n", fileNameIn_params);
		return -1;
	}
	//
	int middle_num;//仅用于全浮体的立柱型控制面情况
	fgets(str, maxNum, fin_params);
	num = sscanf(str, "%d%d%d", &ISO_type, &control_type, &spline_type);
	if(num != 3)
	{
		printf("Read parameters from file %s error.\n", fileNameIn_params);
		return -1;
	}
	if(ISO_type == 4 && control_type == 3)
	{
		int num = sscanf(str, "%*d%*d%*d%d", &middle_num);
		if(num != 1)
		{
			printf("Read parameters from file %s error.\n", fileNameIn_params);
			return -1;
		}
	}
	//
	fgets(str, maxNum, fin_params);
	num = sscanf(str, "%lf%lf%lf%lf%lf", &a, &a1, &b, &b1, &c);
	if(num != 5)
	{
		printf("Read parameters from file %s error.\n", fileNameIn_params);
		return -1;
	}
	fgets(str, maxNum, fin_params);
	num = sscanf(str, "%lf", &xCenter);
	if(num != 1)
	{
		printf("Read parameters from file %s error.\n", fileNameIn_params);
		return -1;
	}
	fgets(str, maxNum, fin_params);
	num = sscanf(str, "%d%d", &xNum, &zNum);
	if(num != 2)
	{
		printf("Read parameters from file %s error.\n", fileNameIn_params);
		return -1;
	}
	fgets(str, maxNum, fin_params);
	num = sscanf(str, "%d%d%d", &xn, &yn, &zn);
	if(num != 3)
	{
		printf("Read parameters from file %s error.\n", fileNameIn_params);
		return -1;
	}
	fgets(str, maxNum, fin_params);
	num = sscanf(str, "%d%d%d%d", &xnF1, &xnF2, &xnF3, &ynF);
	if(num != 4)
	{
		printf("Read parameters from file %s error.\n", fileNameIn_params);
		return -1;
	}

	printf("ISO type: %-4d\n", ISO_type);
	printf("control model type: %-4d\n", control_type);
	printf("spline type: %-4d\n", spline_type);

	//open file
	FILE *fout_control;
	FILE *fout_free;
	FILE *fin_WL;
	fout_control = fopen(fileNameOut_control, "w");
	if(fout_control == NULL)
	{
		printf("Open file %s failed.\n", fileNameOut_control);
		return -1;
	}
	fout_free = fopen(fileNameOut_free, "w");
	if(fout_free == NULL)
	{
		printf("Open file %s failed.\n", fileNameOut_free);
		return -1;
	}
	fin_WL = fopen(fileNameIn_waterline, "r");
	if(fin_WL == NULL)
	{
		printf("Open file %s failed.\n", fileNameIn_waterline);
		return -1;
	}
	//读取水线信息数据
	int waterLine_point_num;//静水面水线数据点数量
	int end_index;//左半水线面的最后一个点
	fgets(str, maxNum, fin_WL);
	sscanf(str, "%d", &waterLine_point_num);
	double *xi, *yi;//静水面水线点的坐标数据
	xi = (double*)calloc(waterLine_point_num, sizeof(double));
	yi = (double*)calloc(waterLine_point_num, sizeof(double));
	for(i = 0; i < waterLine_point_num; i++)
	{
		fgets(str, maxNum, fin_WL);
		sscanf(str, "%lf%lf%lf", xi+i, yi+i, &zWL);
	}
	fclose(fin_WL);

	fprintf(fout_free, "0 0\n");
	fprintf(fout_control, "0 0\n");
	switch(control_type)
	{
	case 1://圆或者椭圆
		//free surface
		fprintf(fout_free, "1 %d\n", spline_type);
		fprintf(fout_free, "%d %d\n", ynF, xnF1);
		fprintf(fout_free, "%d\n", 2);
		fprintf(fout_free, "%d\n", ISO_type*xNum);
		//control surface
		fprintf(fout_control, "1 %d\n", spline_type);//one part
		fprintf(fout_control, "%d %d\n", zn, xn);
		fprintf(fout_control, "%d\n", zNum);
		for(i = 0; i < zNum; i++)//z,line 循环
		{
			fprintf(fout_control, "%d\n", ISO_type*xNum);
			if(i == 0)//最低点设置为平底
				z = c/(zNum-1.)*1 - c;
			else
				z = c/(zNum-1.)*i - c;//z从下往上
			for(j = 0; j < ISO_type*xNum; j++)//x
			{
				double theta;//rad
				theta = (ISO_type*PI/2.)*j/(ISO_type*xNum-1.);
				double ratio;
				ratio = sqrt(fabs(1-z*z/c/c));
				x = ratio*a*cos(theta);
				y = ratio*b*sin(theta);
				if(i != 0 || ISO_type == 4)//全模型
					fprintf(fout_control, "%11.3e %11.3e %11.3e\n", x + xCenter, y, z + zWL);
				else
					fprintf(fout_control, "%11.3e %11.3e %11.3e\n", x + xCenter, 0., z + zWL);
				//自由面
				if(i == zNum - 1)
					fprintf(fout_free, "%11.3e %11.3e %11.3e\n", x + xCenter, y, z + zWL);
			}
		}

		//free surface
		fprintf(fout_free, "%d\n", waterLine_point_num);
		for(i = 0; i < waterLine_point_num; i++)
			fprintf(fout_free, "%11.3e %11.3e %11.3e\n", xi[i], yi[i],  zWL);
		break;
	case 2://圆柱
		//free surface
		fprintf(fout_free, "1 %d\n", spline_type);
		fprintf(fout_free, "%d %d\n", ynF, xnF1);
		fprintf(fout_free, "%d\n", 2);
		fprintf(fout_free, "%d\n", ISO_type*xNum);
		//control surface
		fprintf(fout_control, "2 %d\n", spline_type);
		//***part 1***立柱
		fprintf(fout_control, "%d %d\n", zn, xn);
		fprintf(fout_control, "%d\n", 2);
		//开始计算
		for(i = 0; i < 2; i++)//z
		{
			z = c*i - c;//z从下往上
			fprintf(fout_control, "%d\n", ISO_type*xNum);
			for(j = 0; j < ISO_type*xNum; j++)//x
			{
				double theta;//rad
				theta = (ISO_type*PI/2.)*j/(ISO_type*xNum-1.);
				x = a*cos(theta);
				y = b*sin(theta);
				fprintf(fout_control, "%11.3e %11.3e %11.3e\n", x + xCenter, y, z + zWL);
				if(i == 1)
					fprintf(fout_free, "%11.3e %11.3e %11.3e\n", x + xCenter, y, z + zWL);
			}
		}

		//***part 2*** 底部圆
		fprintf(fout_control, "%d %d\n", yn, xn);
		fprintf(fout_control, "%d\n", 2);//曲线数量
		//line 1
        if(ISO_type == 4)//full model
        {
    		fprintf(fout_control, "%d\n", 1);//点数量
    		fprintf(fout_control, "%11.3e %11.3e %11.3e\n", 0. + xCenter, 0., -c + zWL);
        }
        else
        {
            //center line
        	fprintf(fout_control, "%d\n", 2);//点数量
        	fprintf(fout_control, "%11.3e %11.3e %11.3e\n", a/2 + xCenter, 0., -c + zWL);
            if(ISO_type == 1)//1/4 model
            	fprintf(fout_control, "%11.3e %11.3e %11.3e\n", 0. + xCenter, 0., -c + zWL);
            else//half model
            	fprintf(fout_control, "%11.3e %11.3e %11.3e\n", -a/2 + xCenter, 0., -c + zWL);
        }
		//line 2
		fprintf(fout_control, "%d\n", ISO_type*xNum);//点数量
		for(j = 0; j < ISO_type*xNum; j++)//x
		{
			double theta;//rad
			theta = (ISO_type*PI/2.)*j/(ISO_type*xNum-1.);
			x = a*cos(theta);
			y = b*sin(theta);
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", x + xCenter, y, -c + zWL);
		}

		//free surface
		fprintf(fout_free, "%d\n", waterLine_point_num);
		for(i = 0; i < waterLine_point_num; i++)
			fprintf(fout_free, "%11.3e %11.3e %11.3e\n", xi[i], yi[i],  zWL);
		break;
	case 3://方形
		if(ISO_type == 1 || ISO_type == 2)
			end_index = waterLine_point_num;
		else
			end_index = middle_num;

		if(ISO_type == 1)
			fprintf(fout_control, "3 %d\n", spline_type);
		else if(ISO_type == 2)
			fprintf(fout_control, "4 %d\n", spline_type);
		else
			fprintf(fout_control, "5 %d\n", spline_type);

		//***part 1***，前立面
		fprintf(fout_control, "%d %d\n", yn, zn);
		fprintf(fout_control, "%d\n", 2);
		//line 1
		fprintf(fout_control, "%d\n", 2);
		if(ISO_type == 1 || ISO_type == 2)
		{
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", a + xCenter, 0., zWL);
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", a + xCenter, 0., -c + zWL);
		}
		else
		{
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", a + xCenter, -b1, zWL);
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", a + xCenter, -b1, -c + zWL);
		}
		//line 2
		fprintf(fout_control, "%d\n", 2);
		fprintf(fout_control, "%11.3e %11.3e %11.3e\n", a + xCenter, b, zWL);
		fprintf(fout_control, "%11.3e %11.3e %11.3e\n", a + xCenter, b, -c + zWL);

		//***part 2***，左立面
		fprintf(fout_control, "%d %d\n", xn, zn);
		fprintf(fout_control, "%d\n", 2);
		//line 1
		fprintf(fout_control, "%d\n", 2);
		fprintf(fout_control, "%11.3e %11.3e %11.3e\n", a + xCenter, b, zWL);
		fprintf(fout_control, "%11.3e %11.3e %11.3e\n", a + xCenter, b, -c + zWL);
		//line 2
		fprintf(fout_control, "%d\n", 2);
		if(ISO_type == 1)
		{
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", 0. + xCenter, b, zWL);
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", 0. + xCenter, b, -c + zWL);
		}
		else
		{
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", -a1 + xCenter, b, zWL);
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", -a1 + xCenter, b, -c + zWL);
		}

		//***part 3***,后立面
		if(ISO_type == 2 || ISO_type == 4)
		{
			fprintf(fout_control, "%d %d\n", yn, zn);
			fprintf(fout_control, "%d\n", 2);
			//line 1
			fprintf(fout_control, "%d\n", 2);
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", -a1 + xCenter, b, zWL);
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", -a1 + xCenter, b, -c + zWL);
			//line 2
			fprintf(fout_control, "%d\n", 2);
			if(ISO_type == 2)
			{
				fprintf(fout_control, "%11.3e %11.3e %11.3e\n", -a1 + xCenter, 0., zWL);
				fprintf(fout_control, "%11.3e %11.3e %11.3e\n", -a1 + xCenter, 0., -c + zWL);
			}
			else
			{
				fprintf(fout_control, "%11.3e %11.3e %11.3e\n", -a1 + xCenter, -b1, zWL);
				fprintf(fout_control, "%11.3e %11.3e %11.3e\n", -a1 + xCenter, -b1, -c + zWL);
			}
		}

		//***part 4***右立面
		if(ISO_type == 4)
		{
			fprintf(fout_control, "%d %d\n", xn, zn);
			fprintf(fout_control, "%d\n", 2);
			//line 1
			fprintf(fout_control, "%d\n", 2);
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", -a1 + xCenter, -b1, zWL);
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", -a1 + xCenter, -b1, -c + zWL);
			//line 2
			fprintf(fout_control, "%d\n", 2);
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", a + xCenter, -b1, zWL);
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", a + xCenter, -b1, -c + zWL);
		}

		//***part 5***底面
		fprintf(fout_control, "%d %d\n", xn, yn);
		fprintf(fout_control, "%d\n", 2);
		//line 1
		fprintf(fout_control, "%d\n", 2);
		fprintf(fout_control, "%11.3e %11.3e %11.3e\n", a + xCenter, b, -c + zWL);
		if(ISO_type == 1 || ISO_type == 2)
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", a + xCenter, 0., -c + zWL);
		else
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", a + xCenter, -b1, -c + zWL);
		//line 2
		fprintf(fout_control, "%d\n", 2);
		if(ISO_type == 1)
		{
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", xCenter, b, -c + zWL);
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", xCenter, 0., -c + zWL);
		}
		else if(ISO_type == 2)
		{
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", -a1 + xCenter, b, -c + zWL);
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", -a1 + xCenter, 0., -c + zWL);
		}
		else
		{
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", -a1 + xCenter, b, -c + zWL);
			fprintf(fout_control, "%11.3e %11.3e %11.3e\n", -a1 + xCenter, -b1, -c + zWL);
		}

		//*******free surface***********
		if(ISO_type == 1)
			fprintf(fout_free, "2 %d\n", spline_type);
		else if(ISO_type == 2)
			fprintf(fout_free, "3 %d\n", spline_type);
		else
			fprintf(fout_free, "4 %d\n", spline_type);
		//***part1***前部
		fprintf(fout_free, "%d %d\n", ynF, xnF1);
		fprintf(fout_free, "%d\n", 2);
		//line1
		fprintf(fout_free, "%d\n", 2);
		fprintf(fout_free, "%11.3e %11.3e %11.3e\n", a + xCenter, b, zWL);
		fprintf(fout_free, "%11.3e %11.3e %11.3e\n", xi[0], b, zWL);
		//line2
		fprintf(fout_free, "%d\n", 2);
		if(ISO_type == 1 || ISO_type == 2)
		{
			fprintf(fout_free, "%11.3e %11.3e %11.3e\n", a + xCenter, 0., zWL);
			fprintf(fout_free, "%11.3e %11.3e %11.3e\n", xi[0], 0., zWL);
		}
		else
		{
			fprintf(fout_free, "%11.3e %11.3e %11.3e\n", a + xCenter, -b1, zWL);
			fprintf(fout_free, "%11.3e %11.3e %11.3e\n", xi[0], -b1, zWL);
		}

		//***part2***中部左侧
		if(ISO_type == 4)
			fprintf(fout_free, "%d %d\n", ynF/2, xnF2);
		else
			fprintf(fout_free, "%d %d\n", ynF, xnF2);
		fprintf(fout_free, "%d\n", 2);
		//line1
		fprintf(fout_free, "%d\n", 2);
		fprintf(fout_free, "%11.3e %11.3e %11.3e\n", xi[0], b, zWL);
		fprintf(fout_free, "%11.3e %11.3e %11.3e\n", xi[end_index-1], b, zWL);
		//line2
		fprintf(fout_free, "%d\n", end_index);
		for(i = 0; i < end_index; i++)
			fprintf(fout_free, "%11.3e %11.3e %11.3e\n", xi[i], yi[i], zWL);

		//***part3***后部
		if(ISO_type == 2 || ISO_type == 4)
		{
			fprintf(fout_free, "%d %d\n", ynF, xnF3);
			fprintf(fout_free, "%d\n", 2);
			//line1
			fprintf(fout_free, "%d\n", 2);
			fprintf(fout_free, "%11.3e %11.3e %11.3e\n", xi[end_index-1], b, zWL);
			fprintf(fout_free, "%11.3e %11.3e %11.3e\n", -a1 + xCenter, b, zWL);
			//line2
			fprintf(fout_free, "%d\n", 2);
			if(ISO_type == 2)
			{
				fprintf(fout_free, "%11.3e %11.3e %11.3e\n", xi[end_index-1], 0., zWL);
				fprintf(fout_free, "%11.3e %11.3e %11.3e\n", -a1 + xCenter, 0., zWL);
			}
			else
			{
				fprintf(fout_free, "%11.3e %11.3e %11.3e\n", xi[end_index-1], -b1, zWL);
				fprintf(fout_free, "%11.3e %11.3e %11.3e\n", -a1 + xCenter, -b1, zWL);
			}
		}

		//***part4***中部右侧
		if(ISO_type == 4)
		{
			if(ISO_type == 4)
				fprintf(fout_free, "%d %d\n", ynF/2, xnF2);
			else
				fprintf(fout_free, "%d %d\n", ynF, xnF2);
			fprintf(fout_free, "%d\n", 2);
			//line1
			fprintf(fout_free, "%d\n", 2);
			fprintf(fout_free, "%11.3e %11.3e %11.3e\n", xi[end_index-1], -b1, zWL);
			fprintf(fout_free, "%11.3e %11.3e %11.3e\n", xi[waterLine_point_num-1], -b1, zWL);
			//line2
			fprintf(fout_free, "%d\n", waterLine_point_num-end_index+1);
			for(i = 0; i < waterLine_point_num-end_index+1; i++)
				fprintf(fout_free, "%11.3e %11.3e %11.3e\n", xi[i+end_index-1], yi[i+end_index-1], zWL);
		}
		break;
	default:
		break;
	}
	//
	free(xi);
	free(yi);

	fclose(fout_control);
	fclose(fout_free);

	printf("SUCCESS\n");

	return EXIT_SUCCESS;
}
