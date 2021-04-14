#include <stdio.h>

#include "MLP.h"
CMLP MultiLayer;

#define NUM_TRAINING_SET	3
#define NUM_INPUT			9
#define NUM_OUTPUT			3


int main() {

	int p;


	// 신경망 네트워크 구성
	int HiddenNodes[1] = { 2 };	// [1] 이랑 1이 같아야함
	int numofHiddenLayer = 1;
	MultiLayer.Create(NUM_INPUT, HiddenNodes, NUM_OUTPUT, numofHiddenLayer);


	// 가중치 불러오기
	if (MultiLayer.LoadWeight((char*)"..\\Weight\\weight.txt"))
	{
		printf("기존의 가중치로부터 학습을 시작합니다.\n");
	}
	else
	{
		printf("랜덤 가중치로부터 처음으로 시작합니다.\n");
	}

	// 테스트 입력
	int test_input[NUM_INPUT] = { 1,0,1,
								 1,1,0,
								 0,1,1 };

	// 입력전달
	for (p = 0; p < NUM_INPUT; p++)
	{
		MultiLayer.pInValue[p + 1] = test_input[p];
	}

	// 계산 결과
	MultiLayer.Forward();

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%.0f", MultiLayer.pInValue[i * 3 + j+1]);
		}
		printf("\n");
	}
	printf(" = ");
	for (p = 1; p <= NUM_OUTPUT; p++) {
		printf("%lf,", MultiLayer.pOutValue[p]);
	}

	return 0;
}