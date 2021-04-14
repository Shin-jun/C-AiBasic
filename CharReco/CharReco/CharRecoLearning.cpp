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


	// �Ű�� ��Ʈ��ũ ����
	int HiddenNodes[1] = { 2 };	// [1] �̶� 1�� ���ƾ���
	int numofHiddenLayer = 1;
	MultiLayer.Create(NUM_INPUT, HiddenNodes, NUM_OUTPUT, numofHiddenLayer);

	// �н� ������ �غ�
	double x[NUM_TRAINING_SET][NUM_INPUT] = { {1, 1, 1,			// ��
											   0, 0, 1,
											   0, 0, 1},
											  {1, 0, 0,			// ��
											   1, 0, 0,
											   1, 1, 1},
											  {1, 1, 1,			// ��
											   1, 0, 0,
											   1, 1, 1} };

	// ����
	double d[NUM_TRAINING_SET][NUM_OUTPUT] = { {1,0,0}, {0,1,0}, {0,0,1} };

	// ����ġ �ҷ�����
	if (MultiLayer.LoadWeight((char*)"..\\Weight\\weight.txt"))
	{
		printf("������ ����ġ�κ��� �н��� �����մϴ�.\n");
	}
	else
	{
		printf("���� ����ġ�κ��� ó������ �����մϴ�.\n");
	}


	// ��� ���
	for (n = 0; n < NUM_TRAINING_SET; n++)
	{
		for (p = 0; p < NUM_INPUT; p++)
		{
			MultiLayer.pInValue[p + 1] = x[n][p];
		}
		// ��°�
		MultiLayer.Forward();

		for (p = 1; p <= NUM_INPUT; p++)
			printf("%.0f", MultiLayer.pInValue[p]);
		printf(" = ");
		for (p = 1; p <= NUM_OUTPUT; p++)
			printf("%lf,", MultiLayer.pOutValue[p]);
		printf("\n");
	}

	getchar();

	// �н�����
	double MSE;
	for (epoch = 0; epoch < MAX_EPOCH; epoch++)
	{
		MSE = 0.0;
		// �Է°� ������ ����
		for (n = 0; n < NUM_TRAINING_SET; n++)
		{
			// �Է� ����
			for (p = 0; p < NUM_INPUT; p++)
			{
				MultiLayer.pInValue[p + 1] = x[n][p];
			}
			// ���� ����
			for (p = 0; p < NUM_OUTPUT; p++)
				MultiLayer.pCorrectOutValue[p + 1] = d[n][p];

			// ��°� ���
			MultiLayer.Forward();
			// ������ �н�
			MultiLayer.BackPropagationLearning();


			// �����Ŀ� ��°� �������� ���
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

	// ��� ���
	for (n = 0; n < NUM_TRAINING_SET; n++)
	{
		for (p = 0; p < NUM_INPUT; p++)
		{
			MultiLayer.pInValue[p + 1] = x[n][p];
		}
		// ��°�
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