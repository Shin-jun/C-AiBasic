#include <stdio.h>
#include <conio.h>

#include "MLP.h"
CMLP MultiLayer;

#define NUM_INPUT 3
#define NUM_OUTPUT 2
#define NUM_TRAINING_SET 20

#define MAX_EPOCH 10000000

void DisplayMenu();
void LearningStart();
void SaveWeight();
void LoadWeight();
void test();


int main() 
{
	int HiddenNodes[2] = { 5,3 };
	int numofHiddenLayer = 2;
	MultiLayer.Create(NUM_INPUT, HiddenNodes, NUM_OUTPUT, numofHiddenLayer);


	char ch;
	DisplayMenu();

	while ((ch = getche()) != EOF)	// conio.h 추가 
	{
		switch (ch)
		{
		case '1':
			LearningStart();
			break;
		case '2':
			SaveWeight();
			break;
		case '3':
			LoadWeight();
			break;
		case '4':
			test();
			break;
		case '5':	// 종료
			return 0;
			break;
		}
		DisplayMenu();
	}

}

void DisplayMenu()	// 선택 메뉴 작성
{
	char menu[5][64] = { {"[1]학습"},		// 64개출력 5개의 메뉴
						 {"[2]weight 저장"},
						 {"[3]weight 읽기"},
						 {"[4]test"},
						 {"[5]종료"} };
	printf("\n9주차과제_20151186_신용준\n");
	for (int i = 0; i < 5; i++)
	{
		printf("\n%s", menu[i]);
	}
	printf("\n선택메뉴:");
}

void LearningStart()
{
	int i, j;

	int x[NUM_TRAINING_SET][NUM_INPUT];
	int d[NUM_TRAINING_SET][NUM_OUTPUT];

	// 학습데이터 파일에서 읽기
	FILE* fp = fopen("learningdata.txt", "rt");
	if (fp == NULL)
	{
		printf("\n=>학습데이터를 읽을 수 없습니다.");
		return;
	}

	for (i = 0; i < NUM_TRAINING_SET; i++)
	{
		for (j = 0; j < NUM_INPUT; j++)
		{
			fscanf(fp, "%d", &x[i][j]);
		}
		for (j = 0; j < NUM_OUTPUT; j++)
		{
			fscanf(fp, "%d", &d[i][j]);
		}
	}
	fclose(fp);

	// 학습진행
	printf("\n=>학습을 시작합니다.");
	int epoch, n, p;
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
				MultiLayer.pInValue[p + 1] = x[n][p] / 256.0;	// ==> 0...1사이의값 학습속도를 낮춤(스케일)
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
		if (MSE < 0.000001)
			break;
	}

	printf("\n=>학습이 완료되었습니다.");
}

void SaveWeight()
{
	MultiLayer.SaveWeight((char*)"weight.txt");
	printf("\n=>가중치를 저장했습니다.");
}

void LoadWeight()
{
	if (MultiLayer.LoadWeight((char*)"weight.txt"))
	{
		printf("\n=>가중치를 읽었습니다.");
	}
	else
	{
		printf("\n==>가중치 파일을 읽을 수가 없습니다.");
	}
}

void test()
{
	int i;
	int rgb[3];

	printf("\n=>rgb값을 입력:");
	for (i = 0; i < NUM_INPUT; i++)
		scanf("%d", &rgb[i]);

	// 입력
	for (i = 0; i < NUM_INPUT; i++)
		MultiLayer.pInValue[i + 1] = rgb[i] / 256.0;

	MultiLayer.Forward();

	printf("\n[출력]%lf,%lf,%lf=%lf,%lf", MultiLayer.pInValue[1], MultiLayer.pInValue[2], MultiLayer.pInValue[3],		// RGB값
		MultiLayer.pOutValue[1], MultiLayer.pOutValue[2]);	// 결과 1, 0
}