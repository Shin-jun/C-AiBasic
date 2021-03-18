#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM_INPUT_NODE 2	
#define MAXNUM_NUM_DATA_SET 100

#define LEARNING_RATE 0.01
#define MAX_EPOCH 10000

void initw(double weight[NUM_INPUT_NODE + 1]);
int getdata(double e[][NUM_INPUT_NODE + 1], double desired[]);
double forward(double input[NUM_INPUT_NODE + 1], double weight[NUM_INPUT_NODE + 1]);
double ActivationFunc(double sum);

void neural_forward(double in[][NUM_INPUT_NODE + 1], double w[NUM_INPUT_NODE + 1], int n_of_set, double out[MAXNUM_NUM_DATA_SET]);
double neural_learning(double in[][NUM_INPUT_NODE + 1], double w[NUM_INPUT_NODE + 1], int n_of_set, double dout[MAXNUM_NUM_DATA_SET]);
int main()
{
	double x[MAXNUM_NUM_DATA_SET][NUM_INPUT_NODE + 1]; // 입력데이터세트
	double w[NUM_INPUT_NODE + 1]; // 가중치와 바이어스
	double desired[MAXNUM_NUM_DATA_SET];	// 정답
	double output[MAXNUM_NUM_DATA_SET];		// 출력값

	double o; // 출력
	int n_of_set; // 입력된 데이터세트 개수
	double err;
	int i, j;	// 제어문
	
	double error_epoch = 0.0;
	int epoch = 0;

	// 가중치 초기화
	initw(w);

	// 입력 데이터 읽어들이기
	n_of_set = getdata(x, desired);
	printf("데이터세트 개수 : %d\n", n_of_set);

	// 현재의 출력값 계산, 출력
	neural_forward(x, w, n_of_set, output);
	for (i = 0; i < n_of_set; ++i)
	{
		printf("%d", i);
		for (j = 1; j <= NUM_INPUT_NODE; ++j)
			printf("%lf ", x[i][j]);
		printf(" =%lf\n", output[i]);
	}

	// 학습 시작
	printf("\n ------학습시작-------\n");
	for (epoch = 0; epoch < MAX_EPOCH; epoch++)
	{
		err = neural_learning(x, w, n_of_set, desired);
		printf("epoch=%d avg err=%lf\n", epoch, err);
		if (err == 0.0)
			break;
	}
	printf("-----학습종료-----\n");
	
	// 학습완료후 출력값 계산, 출력
	neural_forward(x, w, n_of_set, output);
	for (i = 0; i < n_of_set; ++i)
	{
		printf("%d", i);
		for (j = 1; j <= NUM_INPUT_NODE; ++j)
			printf("%lf ", x[i][j]);
		printf(" =%lf\n", output[i]);
	}

	// 학습완료된 가중치
	printf("bais_weight=%lf\n", w[0]);
	for (j = 1; j <= NUM_INPUT_NODE; ++j)
		printf("weight%d=%lf", j, w[j]);
	printf("\n");

	return 0;
}

// 가중치 초기화
void initw(double weight[NUM_INPUT_NODE + 1])
{
	srand(time(NULL));
	for (int i = 0; i < NUM_INPUT_NODE + 1; i++)
		weight[i] = (double)rand() / RAND_MAX - 0.5;	// -0.5 ~ 0.5

}

// 데이터 입력
int getdata(double in[][NUM_INPUT_NODE + 1], double desired[])
{
	int n_of_x = 0; // 데이터세트 개수
	int j = 0; // 반복 제어용

	// 바이어스
	in[0][0] = 1; in[0][1] = 0; in[0][2] = 0; desired[0] = 1;
	in[1][0] = 1; in[1][1] = 0; in[1][2] = 1; desired[1] = 1;
	in[2][0] = 1; in[2][1] = 1; in[2][2] = 0; desired[2] = 0;
	in[3][0] = 1; in[3][1] = 1; in[3][2] = 1; desired[3] = 0;
	n_of_x = 4;

	return n_of_x;
}

// 순방향 계산
double forward(double input[NUM_INPUT_NODE + 1], double weight[NUM_INPUT_NODE + 1])
{
	int i; // 반복제어
	double weightsum;	// 가중합
	double result;		// 출력

	// 계산
	weightsum = 0.0;
	weightsum += (1 * weight[0]); // 바이어스 처리
	for (i = 1; i <= NUM_INPUT_NODE; ++i)
		weightsum += (input[i] * weight[i]);

	// 출력값 계산
	result = ActivationFunc(weightsum);
	return result;
}

// 활성함수
double ActivationFunc(double sum)
{
	// 계단 함수 계산
	if (sum >= 0) return 1.0;
	else          return 0.0;

	// return (sum >=0)? 1.0:0.0;

	// 시그모이드 함수
	// return 1.0/(1.0+exp(-u));
}

void neural_forward(double in[][NUM_INPUT_NODE + 1], double w[NUM_INPUT_NODE + 1], int n_of_set, double out[MAXNUM_NUM_DATA_SET])
{
	int i;

	// 계산 본체
	for (i = 0; i < n_of_set; i++)
		out[i] = forward(in[i], w);
}

// 전체 데이터 학습 진행 
double neural_learning(double in[][NUM_INPUT_NODE + 1], double w[NUM_INPUT_NODE + 1], int n_of_set, double dout[MAXNUM_NUM_DATA_SET])	// 세트 갯수 , 정답
{
	int i, j;
	double out;
	double err;
	double error_sum;

	for (j = 0; j < n_of_set; j++)
	{
		out = forward(in[j], w);
		err = dout[j] - out;
		w[0] = w[0] + LEARNING_RATE * 1 * err;	// 바이어스
		for (i = 1; i <= NUM_INPUT_NODE; i++)
			w[i] = w[i] + LEARNING_RATE * in[j][i] * err;
	}

	// 평균 에러값 계산
	error_sum = 0.0;
	for (j = 0; j < n_of_set; j++)
	{
		out = forward(in[j], w);
		err = (dout[j] - out) * (dout[j] - out);
		error_sum += fabs(err);
	}

	return error_sum / n_of_set;

}