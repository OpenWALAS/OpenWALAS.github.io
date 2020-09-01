/*
 ============================================================================
 Name        : irregFreq.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	int i, j;
	double PI = 3.1415926535898;
	double G = 9.81;

	//不规则频率点个数
	int num = 3;
	int num2 = num*num*2;

	//输入参数
    //a: length
    //b: broadth
    //T: draught
	double L, B, T;
	L = 100.0;//长
	B = 25;//宽
	T = 2.5;//吃水

	double *w0 = (double*)calloc(num2, sizeof(double));
	if(w0 == NULL)
	{
		printf("Memory allocate error.\n");
		return -1;
	}

	int count = 0;
	for(i = 1; i <= num;i ++)
	{
		for(j = 1; j <= num; j++)
		{
			double kn, w;
			double r = sqrt(pow(i*PI/L, 2.) + pow(j*PI/B, 2.));
			kn = r/tanh(r*T);//波数
			w = sqrt(G*kn);
			w0[count] = w;
			count++;

			r = sqrt(pow((i-0.5)*PI/L, 2.) + pow((j-0.5)*PI/B, 2.));
			kn = r/tanh(r*T);//波数
			w = sqrt(G*kn);
			w0[count] = w;
			count++;

		}
	}

	//冒泡升序排列
	for(i = num2 - 1; i >= 1; i--)
		for(j = 0; j < i; j++)
		{
			if(w0[j] > w0[j+1])
			{
					double tt = w0[j];
					w0[j] = w0[j+1];
					w0[j+1] = tt;
			}
		}
	for(i = 0; i < num2; i++)
		printf("w%-d = %8.3f\n", i+1, w0[i]);

	free(w0);

	return 0;

}
