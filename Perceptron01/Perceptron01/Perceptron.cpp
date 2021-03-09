#include <iostream>

#define NUM_INPUT_NODE 2
#define NUM_DATA_SET 5

void initw(double weight[NUM_INPUT_NODE + 1]);
int getdata(double e[][NUM_INPUT_NODE + 1]);
double forward(double input[NUM_INPUT_NODE + 1], double weight[NUM_INPUT_NODE + 1]);
double ActivationFunc(double sum);

void main() 
{
	double x[NUM_DATA_SET][NUM_INPUT_NODE + 1]; // 데이터세트
	double w[NUM_INPUT_NODE + 1]; // 가중치와 바이어스
	double o; // 출력
	int n_of_set; // 입력된 데이터세트 개수

	// 가중치 초기화
	initw(w);

	// 입력 데이터 읽어들이기
	n_of_set = getdata(x);
	printf("데이터세트 개수 : %d\n", n_of_set);

	// 계산
	int i, j;
	for (i = 0; i < n_of_set; ++i)
	{
		printf("%d", i);
		for (j = 1; j <= NUM_INPUT_NODE; ++j)
			printf("%lf", x[i][j]);
		o = forward(x[i], w);
		printf("%lf\n", o);
	}
}

// 가중치 초기화
void initw(double weight[NUM_INPUT_NODE + 1])
{
	// 상수를 가중치로 할당
	weight[0] = -0.5;
	weight[1] = 1;
	weight[2] = 1;
}

// 데이터 입력
int getdata(double e[][NUM_INPUT_NODE + 1])
{
	int nset_of_x = 0; // 데이터세트 개수
	int j = 1; // 반복 제어용

	// 데이터 입력
	while (scanf("%lf", &e[nset_of_x][j]) != EOF)
	{
		++j;
		if (j > NUM_INPUT_NODE)
		{	// 다음 데이터
			j = 1; 
			++nset_of_x;
		}
		if (nset_of_x == NUM_DATA_SET)
			break;
	}
	return nset_of_x;
}

// 순방향 계산
double forward(double input[NUM_INPUT_NODE + 1], double weight[NUM_INPUT_NODE + 1])
{
	int i; // 반복제어
	double weightsum, o; // 가중합과 출력
	// 계산
	weightsum = 0;
	weightsum = weight[0] * 1; // 바이어스 처리
	for (i = 1; i <= NUM_INPUT_NODE; ++i)
		weightsum += input[i] * weight[i];

	// 출력값 계산
	o = ActivationFunc(weightsum);
	return o;
}

// 활성함수
double ActivationFunc(double sum)
{
	// 계단 함수 계산
	if (sum >= 0) return 1.0;
	else          return -1.0;

	// 시그모이드 함수
	// return 1.0/(1.0+exp(-u));
}