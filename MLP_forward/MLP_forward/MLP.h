#pragma once

class CMLP
{
public:
	CMLP();
	~CMLP();

private:

public:
	// �Ű�� ���������� ���� ����
	int m_iNumInNodes;		// �Է³��
	int m_iNumOutNodes;		// ��³��
	int m_iNumHiddenLayer;	// ���緹�̾� ��
	int m_iNumTotalLayer;	// ��ü���̾��(inputlayer + hiddenlayer + outputlayer)
	int* m_NumNodes;		// [0]: input node, [1..]: hidden layer, [m_iNumHiddenLayer+1], output layer, ����

	double*** m_Weight;		// [����layer][���۳��][������]
	double** m_NodeOut;		// [layer][node]

	double* pInValue, * pOutValue;	// �Է·��̾�, ��·��̾�
	double* pCorrectOutValue;		// ���䷹�̾�

	bool Create(int inNode, int* pHiddenNode, int OutNode, int HiddenLayer);
private:
	void InitW();
public:
	void Forward();
	double ActivationFunc(double weightsum);
};

CMLP::CMLP()
{
}

CMLP::~CMLP()
{
}



bool CMLP::Create(int InNode, int* pHiddenNode, int OutNode, int numHiddenLayer)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	return false;
}


void CMLP::InitW()
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
}


void CMLP::Forward()
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
}


double CMLP::ActivationFunc(double weightsum)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	return 0.0;
}
