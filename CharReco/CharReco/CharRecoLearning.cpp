#include <stdio.h>

#include "MLP.h"
CMLP MultiLayer;

#define NUM_TRAINING_SET	3
#define NUM_INPUT			9
#define NUM_OUTPUT			3

#define MAX_EPOCH	100000

int main() {

	int n, p;
	int epoch;


	// 신경망 네트워크 구성
	int HiddenNodes[1] = { 2 };	// [1] 이랑 1이 같아야함
	int numofHiddenLayer = 1;
	MultiLayer.Create(NUM_INPUT, HiddenNodes, NUM_OUTPUT, numofHiddenLayer);

	// 학습 데이터 준비
	double x[NUM_TRAINING_SET][NUM_INPUT] = { {1, 1, 1,			// ㄱ
											   0, 0, 1,
											   0, 0, 1},
											  {1, 0, 0,			// ㄴ
											   1, 0, 0,
											   1, 1, 1},
											  {1, 1, 1,			// ㄷ
											   1, 0, 0,
											   1, 1, 1} };

	// 정답
	double d[NUM_TRAINING_SET][NUM_OUTPUT] = { {1,0,0}, {0,1,0}, {0,0,1} };

	// 가중치 불러오기
	if (MultiLayer.LoadWeight((char*)"..\\Weight\\weight.txt"))
	{
		printf("기존의 가중치로부터 학습을 시작합니다.\n");
	}
	else
	{
		printf("랜덤 가중치로부터 처음으로 시작합니다.\n");
	}


	// 결과 출력
	for (n = 0; n < NUM_TRAINING_SET; n++)
	{
		for (p = 0; p < NUM_INPUT; p++)
		{
			MultiLayer.pInValue[p + 1] = x[n][p];
		}
		// 출력값
		MultiLayer.Forward();

		for (p = 1; p <= NUM_INPUT; p++)
			printf("%.0f", MultiLayer.pInValue[p]);
		printf(" = ");
		for (p = 1; p <= NUM_OUTPUT; p++)
			printf("%lf,", MultiLayer.pOutValue[p]);
		printf("\n");
	}

	getchar();

	// 학습진행
	double MSE;
	for (epoch = 0; epoch < MAX_EPOCH; epoch++)
	{
		MSE = 0.0;
		// 입력과 정답을 전달
		for (n = 0; n < NUM_TRAINING_SET; n++)
		{
			// 입력 전달
			for (p = 0; p < NUM_INPUT; p++)
			{
				MultiLayer.pInValue[p + 1] = x[n][p];
			}
			// 정답 전달
			for (p = 0; p < NUM_OUTPUT; p++)
				MultiLayer.pCorrectOutValue[p + 1] = d[n][p];

			// 출력값 계산
			MultiLayer.Forward();
			// 역전파 학습
			MultiLayer.BackPropagationLearning();


			// 갱신후에 출력과 에러값을 계산
			MultiLayer.Forward();

			for (p = 1; p <= NUM_OUTPUT; p++)
				MSE += (MultiLayer.pCorrectOutValue[p] - MultiLayer.pOutValue[p]) * (MultiLayer.pCorrectOutValue[p] - MultiLayer.pOutValue[p]);
			
		}
		MSE /= NUM_TRAINING_SET;
		printf("Epoch%d(MES)=%.15f\n", epoch, MSE);
		if (MSE < 0.0001)
			break;
	}

	MultiLayer.SaveWeight((char*)"..\\Weight\\weight.txt");

	// 결과 출력
	for (n = 0; n < NUM_TRAINING_SET; n++)
	{
		for (p = 0; p < NUM_INPUT; p++)
		{
			MultiLayer.pInValue[p + 1] = x[n][p];
		}
		// 출력값
		MultiLayer.Forward();

		for (p = 1; p <= NUM_INPUT; p++)
			printf("%.0f", MultiLayer.pInValue[p]);
		printf(" = ");
		for (p = 1; p <= NUM_OUTPUT; p++)
			printf("%lf,", MultiLayer.pOutValue[p]);
		printf("\n");
	}

	return 0;
}