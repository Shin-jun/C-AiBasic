#include "MLP.h"

#include <malloc.h>		// malloc()�� ���� �߰�
#include <time.h>		// time()�� ���� �߰�
#include <stdlib.h>		// srand()�� ���� �߰�
#include <math.h>		// exp()�� ���� �߰�

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
	m_iNumHiddenLayer = numHiddenLayer;		// �Է�, ����� ����
	m_iNumTotalLayer = numHiddenLayer + 2;	// ���� + �Է� + ���

	// m_iNumNodes�� ���� �޸��Ҵ�
	m_NumNodes = (int*)malloc((m_iNumTotalLayer + 1) * sizeof(int));	// ����(+1)

	m_NumNodes[0] = m_iNumInNodes;
	for (layer = 0; layer < m_iNumHiddenLayer; layer++)
		m_NumNodes[1 + layer] = pHiddenNode[layer];
	m_NumNodes[m_iNumTotalLayer - 1] = m_iNumOutNodes;	// ����� ����
	m_NumNodes[m_iNumTotalLayer] = m_iNumOutNodes;		// ���� ����

	// �� ��庰 ��¸޸��Ҵ�=[layerNo][nodeNo]
	// �Է� : m_NodeOut[0][], ��� : m_NodeOut[m_iNumTotalLayer-1][]
	// ���� : m_NodeOut[m_iNumTotalLayer][]
	m_NodeOut = (double**)malloc((m_iNumTotalLayer + 1) * sizeof(double*));	// ����(+1)
	for (layer = 0; layer < m_iNumTotalLayer; layer++)
		m_NodeOut[layer] = (double*)malloc((m_NumNodes[layer] + 1) * sizeof(double));	// ���̾�� ���� +1
	// ����(��� ���� ���� ����, ���̾�� �ʿ������ ÷�ڴ� 1���� n����)
	m_NodeOut[m_iNumTotalLayer] = (double*)malloc((m_NumNodes[m_iNumTotalLayer - 1] + 1) * sizeof(double));


	// ����ġ �޸� �Ҵ� m_Weight[����layer][���۳��][������]
	m_Weight = (double***)malloc((m_iNumTotalLayer - 1) * sizeof(double**));
	for (layer = 0; layer < m_iNumTotalLayer - 1; layer++)
	{
		m_Weight[layer] = (double**)malloc((m_NumNodes[layer] + 1) * sizeof(double*));	// ���̾(+1)
		for (snode = 0; snode < m_NumNodes[layer] + 1; snode++)
			m_Weight[layer][snode] = (double*)malloc((m_NumNodes[layer + 1] + 1) * sizeof(double));	// �������̾��� ����+1 , ���̾ ��(+1)
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

	for (layer = 0; layer < m_iNumTotalLayer - 1; layer++)		// ��������
	{
		for (snode = 0; snode <= m_NumNodes[layer]; snode++)	// for ���̾�� ���� 0����
		{
			for (enode = 1; enode <= m_NumNodes[layer + 1]; enode++)	// ���� ���̾��� ����
			{
				m_Weight[layer][snode][enode] = (double)rand() / RAND_MAX - 0.5;	// -0.5~0.5
			}
		}
	}
}


void CMLP::Forward()
{
	int layer, snode, enode;
	double wsum;	// ������

	for (layer = 0; layer < m_iNumTotalLayer - 1; layer++)
	{
		for (enode = 1; enode <= m_NumNodes[layer + 1]; enode++)
		{
			wsum = 0.0;	// ��庰 ������
			wsum += m_Weight[layer][0][enode] * 1;	// ���̾
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
