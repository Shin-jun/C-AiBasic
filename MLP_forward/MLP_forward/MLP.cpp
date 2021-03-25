#include "MLP.h"

#include <malloc.h>		// malloc()를 위해 추가
#include <time.h>		// time()을 위해 추가
#include <stdlib.h>		// srand()을 위해 추가
#include <math.h>		// exp()를 위해 추가

CMLP::CMLP()
{
	int layer;

	m_iNumInNodes = 0;
	m_iNumOutNodes = 0;

	m_NumNodes = NULL;
	m_NodeOut = NULL;

	m_Weight = NULL;

	pInValue = NULL;
	pOutValue = NULL;
	pCorrectOutValue = NULL;
}

CMLP::~CMLP()
{
	int layer, snode, enode;

	if (m_NodeOut != NULL)
	{
		for (layer = 0; layer < (m_iNumTotalLayer + 1); layer++)
			free(m_NodeOut[layer]);
		free(m_NodeOut);
	}

	if (m_Weight != NULL)
	{
		for (layer = 0; layer < (m_iNumTotalLayer - 1); layer++)
		{
			if (m_Weight[layer] != NULL)
			{
				for (snode = 0; snode < m_NumNodes[layer] + 1; snode++)
					free(m_Weight[layer][snode]);
				free(m_Weight[layer]);
			}
		}
	}
	if (m_NumNodes != NULL)
		free(m_NumNodes);
}


bool CMLP::Create(int InNode, int* pHiddenNode, int OutNode, int numHiddenLayer)
{
	int layer, snode, enode;

	m_iNumInNodes = InNode;
	m_iNumOutNodes = OutNode;
	m_iNumHiddenLayer = numHiddenLayer;		// 입력, 출력층 제외
	m_iNumTotalLayer = numHiddenLayer + 2;	// 히든 + 입력 + 출력

	// m_iNumNodes를 위한 메모리할당
	m_NumNodes = (int*)malloc((m_iNumTotalLayer + 1) * sizeof(int));	// 정답(+1)

	m_NumNodes[0] = m_iNumInNodes;
	for (layer = 0; layer < m_iNumHiddenLayer; layer++)
		m_NumNodes[1 + layer] = pHiddenNode[layer];
	m_NumNodes[m_iNumTotalLayer - 1] = m_iNumOutNodes;	// 출력층 노드수
	m_NumNodes[m_iNumTotalLayer] = m_iNumOutNodes;		// 정답 노드수

	// 각 노드별 출력메모리할당=[layerNo][nodeNo]
	// 입력 : m_NodeOut[0][], 출력 : m_NodeOut[m_iNumTotalLayer-1][]
	// 정답 : m_NodeOut[m_iNumTotalLayer][]
	m_NodeOut = (double**)malloc((m_iNumTotalLayer + 1) * sizeof(double*));	// 정답(+1)
	for (layer = 0; layer < m_iNumTotalLayer; layer++)
		m_NodeOut[layer] = (double*)malloc((m_NumNodes[layer] + 1) * sizeof(double));	// 바이어스를 위해 +1
	// 정답(출력 노드와 같은 개수, 바이어스가 필요없지만 첨자는 1에서 n까지)
	m_NodeOut[m_iNumTotalLayer] = (double*)malloc((m_NumNodes[m_iNumTotalLayer - 1] + 1) * sizeof(double));


	// 가중치 메모리 할당 m_Weight[시작layer][시작노드][연결노드]
	m_Weight = (double***)malloc((m_iNumTotalLayer - 1) * sizeof(double**));
	for (layer = 0; layer < m_iNumTotalLayer - 1; layer++)
	{
		m_Weight[layer] = (double**)malloc((m_NumNodes[layer] + 1) * sizeof(double*));	// 바이어스(+1)
		for (snode = 0; snode < m_NumNodes[layer] + 1; snode++)
			m_Weight[layer][snode] = (double*)malloc((m_NumNodes[layer + 1] + 1) * sizeof(double));	// 다음레이어의 노드수+1 , 바이어스 수(+1)
	}

	pInValue = m_NodeOut[0];
	pOutValue = m_NodeOut[m_iNumTotalLayer - 1];
	pCorrectOutValue = m_NodeOut[m_iNumTotalLayer];

	InitW();

	return false;
}


void CMLP::InitW()
{
	int layer, snode, enode;

	srand(time(NULL));

	for (layer = 0; layer < m_iNumTotalLayer - 1; layer++)		// 정답제외
	{
		for (snode = 0; snode <= m_NumNodes[layer]; snode++)	// for 바이어스를 위해 0부터
		{
			for (enode = 1; enode <= m_NumNodes[layer + 1]; enode++)	// 다음 레이어의 노드수
			{
				m_Weight[layer][snode][enode] = (double)rand() / RAND_MAX - 0.5;	// -0.5~0.5
			}
		}
	}
}


void CMLP::Forward()
{
	int layer, snode, enode;
	double wsum;	// 가중합

	for (layer = 0; layer < m_iNumTotalLayer - 1; layer++)
	{
		for (enode = 1; enode <= m_NumNodes[layer + 1]; enode++)
		{
			wsum = 0.0;	// 노드별 가중합
			wsum += m_Weight[layer][0][enode] * 1;	// 바이어스
			for (snode = 1; snode < m_NumNodes[layer]; snode++)
			{
				wsum += (m_Weight[layer][snode][enode] * m_NodeOut[layer][snode]);
			}

			m_NodeOut[layer + 1][enode] = ActivationFunc(wsum);
		}
	}
}

double CMLP::ActivationFunc(double weightsum)
{
	// step func
	if (weightsum > 0) return 1.0;
	else return 0.0;

	// sigmoid
	// return 1 / (1 + exp(-weightsum));
	
}
