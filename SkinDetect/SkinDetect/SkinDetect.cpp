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

	while ((ch = getche()) != EOF)	// conio.h �߰� 
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
		case '5':	// ����
			return 0;
			break;
		}
		DisplayMenu();
	}

}

void DisplayMenu()	// ���� �޴� �ۼ�
{
	char menu[5][64] = { {"[1]�н�"},		// 64����� 5���� �޴�
						 {"[2]weight ����"},
						 {"[3]weight �б�"},
						 {"[4]test"},
						 {"[5]����"} };
	printf("\n9��������_20151186_�ſ���\n");
	for (int i = 0; i < 5; i++)
	{
		printf("\n%s", menu[i]);
	}
	printf("\n���ø޴�:");
}

void LearningStart()
{
	int i, j;

	int x[NUM_TRAINING_SET][NUM_INPUT];
	int d[NUM_TRAINING_SET][NUM_OUTPUT];

	// �н������� ���Ͽ��� �б�
	FILE* fp = fopen("learningdata.txt", "rt");
	if (fp == NULL)
	{
		printf("\n=>�н������͸� ���� �� �����ϴ�.");
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

	// �н�����
	printf("\n=>�н��� �����մϴ�.");
	int epoch, n, p;
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
				MultiLayer.pInValue[p + 1] = x[n][p] / 256.0;	// ==> 0...1�����ǰ� �н��ӵ��� ����(������)
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
		if (MSE < 0.000001)
			break;
	}

	printf("\n=>�н��� �Ϸ�Ǿ����ϴ�.");
}

void SaveWeight()
{
	MultiLayer.SaveWeight((char*)"weight.txt");
	printf("\n=>����ġ�� �����߽��ϴ�.");
}

void LoadWeight()
{
	if (MultiLayer.LoadWeight((char*)"weight.txt"))
	{
		printf("\n=>����ġ�� �о����ϴ�.");
	}
	else
	{
		printf("\n==>����ġ ������ ���� ���� �����ϴ�.");
	}
}

void test()
{
	int i;
	int rgb[3];

	printf("\n=>rgb���� �Է�:");
	for (i = 0; i < NUM_INPUT; i++)
		scanf("%d", &rgb[i]);

	// �Է�
	for (i = 0; i < NUM_INPUT; i++)
		MultiLayer.pInValue[i + 1] = rgb[i] / 256.0;

	MultiLayer.Forward();

	printf("\n[���]%lf,%lf,%lf=%lf,%lf", MultiLayer.pInValue[1], MultiLayer.pInValue[2], MultiLayer.pInValue[3],		// RGB��
		MultiLayer.pOutValue[1], MultiLayer.pOutValue[2]);	// ��� 1, 0
}