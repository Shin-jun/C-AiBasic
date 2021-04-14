#include <stdio.h>

#include "MLP.h"
CMLP MultiLayer;

#define NUM_TRAINING_SET	3
#define NUM_INPUT			9
#define NUM_OUTPUT			3


int main() {

	int p;


	// �Ű�� ��Ʈ��ũ ����
	int HiddenNodes[1] = { 2 };	// [1] �̶� 1�� ���ƾ���
	int numofHiddenLayer = 1;
	MultiLayer.Create(NUM_INPUT, HiddenNodes, NUM_OUTPUT, numofHiddenLayer);


	// ����ġ �ҷ�����
	if (MultiLayer.LoadWeight((char*)"..\\Weight\\weight.txt"))
	{
		printf("������ ����ġ�κ��� �н��� �����մϴ�.\n");
	}
	else
	{
		printf("���� ����ġ�κ��� ó������ �����մϴ�.\n");
	}

	// �׽�Ʈ �Է�
	int test_input[NUM_INPUT] = { 1,0,1,
								 1,1,0,
								 0,1,1 };

	// �Է�����
	for (p = 0; p < NUM_INPUT; p++)
	{
		MultiLayer.pInValue[p + 1] = test_input[p];
	}

	// ��� ���
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