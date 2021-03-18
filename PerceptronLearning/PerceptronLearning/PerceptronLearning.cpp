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
	double x[MAXNUM_NUM_DATA_SET][NUM_INPUT_NODE + 1]; // �Էµ����ͼ�Ʈ
	double w[NUM_INPUT_NODE + 1]; // ����ġ�� ���̾
	double desired[MAXNUM_NUM_DATA_SET];	// ����
	double output[MAXNUM_NUM_DATA_SET];		// ��°�

	double o; // ���
	int n_of_set; // �Էµ� �����ͼ�Ʈ ����
	double err;
	int i, j;	// ���
	
	double error_epoch = 0.0;
	int epoch = 0;

	// ����ġ �ʱ�ȭ
	initw(w);

	// �Է� ������ �о���̱�
	n_of_set = getdata(x, desired);
	printf("�����ͼ�Ʈ ���� : %d\n", n_of_set);

	// ������ ��°� ���, ���
	neural_forward(x, w, n_of_set, output);
	for (i = 0; i < n_of_set; ++i)
	{
		printf("%d", i);
		for (j = 1; j <= NUM_INPUT_NODE; ++j)
			printf("%lf ", x[i][j]);
		printf(" =%lf\n", output[i]);
	}

	// �н� ����
	printf("\n ------�н�����-------\n");
	for (epoch = 0; epoch < MAX_EPOCH; epoch++)
	{
		err = neural_learning(x, w, n_of_set, desired);
		printf("epoch=%d avg err=%lf\n", epoch, err);
		if (err == 0.0)
			break;
	}
	printf("-----�н�����-----\n");
	
	// �н��Ϸ��� ��°� ���, ���
	neural_forward(x, w, n_of_set, output);
	for (i = 0; i < n_of_set; ++i)
	{
		printf("%d", i);
		for (j = 1; j <= NUM_INPUT_NODE; ++j)
			printf("%lf ", x[i][j]);
		printf(" =%lf\n", output[i]);
	}

	// �н��Ϸ�� ����ġ
	printf("bais_weight=%lf\n", w[0]);
	for (j = 1; j <= NUM_INPUT_NODE; ++j)
		printf("weight%d=%lf", j, w[j]);
	printf("\n");

	return 0;
}

// ����ġ �ʱ�ȭ
void initw(double weight[NUM_INPUT_NODE + 1])
{
	srand(time(NULL));
	for (int i = 0; i < NUM_INPUT_NODE + 1; i++)
		weight[i] = (double)rand() / RAND_MAX - 0.5;	// -0.5 ~ 0.5

}

// ������ �Է�
int getdata(double in[][NUM_INPUT_NODE + 1], double desired[])
{
	int n_of_x = 0; // �����ͼ�Ʈ ����
	int j = 0; // �ݺ� �����

	// ���̾
	in[0][0] = 1; in[0][1] = 0; in[0][2] = 0; desired[0] = 1;
	in[1][0] = 1; in[1][1] = 0; in[1][2] = 1; desired[1] = 1;
	in[2][0] = 1; in[2][1] = 1; in[2][2] = 0; desired[2] = 0;
	in[3][0] = 1; in[3][1] = 1; in[3][2] = 1; desired[3] = 0;
	n_of_x = 4;

	return n_of_x;
}

// ������ ���
double forward(double input[NUM_INPUT_NODE + 1], double weight[NUM_INPUT_NODE + 1])
{
	int i; // �ݺ�����
	double weightsum;	// ������
	double result;		// ���

	// ���
	weightsum = 0.0;
	weightsum += (1 * weight[0]); // ���̾ ó��
	for (i = 1; i <= NUM_INPUT_NODE; ++i)
		weightsum += (input[i] * weight[i]);

	// ��°� ���
	result = ActivationFunc(weightsum);
	return result;
}

// Ȱ���Լ�
double ActivationFunc(double sum)
{
	// ��� �Լ� ���
	if (sum >= 0) return 1.0;
	else          return 0.0;

	// return (sum >=0)? 1.0:0.0;

	// �ñ׸��̵� �Լ�
	// return 1.0/(1.0+exp(-u));
}

void neural_forward(double in[][NUM_INPUT_NODE + 1], double w[NUM_INPUT_NODE + 1], int n_of_set, double out[MAXNUM_NUM_DATA_SET])
{
	int i;

	// ��� ��ü
	for (i = 0; i < n_of_set; i++)
		out[i] = forward(in[i], w);
}

// ��ü ������ �н� ���� 
double neural_learning(double in[][NUM_INPUT_NODE + 1], double w[NUM_INPUT_NODE + 1], int n_of_set, double dout[MAXNUM_NUM_DATA_SET])	// ��Ʈ ���� , ����
{
	int i, j;
	double out;
	double err;
	double error_sum;

	for (j = 0; j < n_of_set; j++)
	{
		out = forward(in[j], w);
		err = dout[j] - out;
		w[0] = w[0] + LEARNING_RATE * 1 * err;	// ���̾
		for (i = 1; i <= NUM_INPUT_NODE; i++)
			w[i] = w[i] + LEARNING_RATE * in[j][i] * err;
	}

	// ��� ������ ���
	error_sum = 0.0;
	for (j = 0; j < n_of_set; j++)
	{
		out = forward(in[j], w);
		err = (dout[j] - out) * (dout[j] - out);
		error_sum += fabs(err);
	}

	return error_sum / n_of_set;

}