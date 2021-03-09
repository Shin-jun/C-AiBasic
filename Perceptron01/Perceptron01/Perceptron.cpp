#include <iostream>

#define NUM_INPUT_NODE 2
#define NUM_DATA_SET 5

void initw(double weight[NUM_INPUT_NODE + 1]);
int getdata(double e[][NUM_INPUT_NODE + 1]);
double forward(double input[NUM_INPUT_NODE + 1], double weight[NUM_INPUT_NODE + 1]);
double ActivationFunc(double sum);

void main() 
{
	double x[NUM_DATA_SET][NUM_INPUT_NODE + 1]; // �����ͼ�Ʈ
	double w[NUM_INPUT_NODE + 1]; // ����ġ�� ���̾
	double o; // ���
	int n_of_set; // �Էµ� �����ͼ�Ʈ ����

	// ����ġ �ʱ�ȭ
	initw(w);

	// �Է� ������ �о���̱�
	n_of_set = getdata(x);
	printf("�����ͼ�Ʈ ���� : %d\n", n_of_set);

	// ���
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

// ����ġ �ʱ�ȭ
void initw(double weight[NUM_INPUT_NODE + 1])
{
	// ����� ����ġ�� �Ҵ�
	weight[0] = -0.5;
	weight[1] = 1;
	weight[2] = 1;
}

// ������ �Է�
int getdata(double e[][NUM_INPUT_NODE + 1])
{
	int nset_of_x = 0; // �����ͼ�Ʈ ����
	int j = 1; // �ݺ� �����

	// ������ �Է�
	while (scanf("%lf", &e[nset_of_x][j]) != EOF)
	{
		++j;
		if (j > NUM_INPUT_NODE)
		{	// ���� ������
			j = 1; 
			++nset_of_x;
		}
		if (nset_of_x == NUM_DATA_SET)
			break;
	}
	return nset_of_x;
}

// ������ ���
double forward(double input[NUM_INPUT_NODE + 1], double weight[NUM_INPUT_NODE + 1])
{
	int i; // �ݺ�����
	double weightsum, o; // �����հ� ���
	// ���
	weightsum = 0;
	weightsum = weight[0] * 1; // ���̾ ó��
	for (i = 1; i <= NUM_INPUT_NODE; ++i)
		weightsum += input[i] * weight[i];

	// ��°� ���
	o = ActivationFunc(weightsum);
	return o;
}

// Ȱ���Լ�
double ActivationFunc(double sum)
{
	// ��� �Լ� ���
	if (sum >= 0) return 1.0;
	else          return -1.0;

	// �ñ׸��̵� �Լ�
	// return 1.0/(1.0+exp(-u));
}