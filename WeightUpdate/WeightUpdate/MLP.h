#pragma once

#define LEARNING_RATE 0.1

class CMLP
{
public:
	CMLP();
	~CMLP();

private:

public:
	// 신경망 구조선언을 위한 변수
	int m_iNumInNodes;		// 입력노드
	int m_iNumOutNodes;		// 출력노드
	int m_iNumHiddenLayer;	// 히든레이어 수
	int m_iNumTotalLayer;	// 전체레이어수(inputlayer + hiddenlayer + outputlayer)
	int* m_NumNodes;		// [0]: input node, [1..]: hidden layer, [m_iNumHiddenLayer+1], output layer, 정답

	double*** m_Weight;		// [시작layer][시작노드][연결노드]
	double** m_NodeOut;		// [layer][node]

	double** m_ErrorGradient;

	double* pInValue, * pOutValue;	// 입력레이어, 출력레이어
	double* pCorrectOutValue;		// 정답레이어

	bool Create(int inNode, int* pHiddenNode, int OutNode, int HiddenLayer);
private:
	void InitW();
	double ActivationFunc(double u);
public:
	void Forward();
	void BackPropagationLearning();
};
