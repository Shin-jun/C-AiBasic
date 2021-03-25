#include <stdio.h>

#include "MLP.h"
CMLP MultiLayer;

int main()
{
	int HiddenNodes[1] = { 2 };		// 은닉노드 2개 , 은닉 레이어 1개
	int numofHiddenLayer = 1;

	MultiLayer.Create(2, HiddenNodes, 1, numofHiddenLayer);

	double x[4][2] = { {0,0}, {0,1}, {1,0},{1,1} };

	MultiLayer.m_Weight[0][0][1] = -7.3061;
	MultiLayer.m_Weight[0][1][1] = 4.7621;
	MultiLayer.m_Weight[0][2][1] = 4.7618;

	MultiLayer.m_Weight[0][0][2] = -2.8441;
	MultiLayer.m_Weight[0][1][2] = 6.3917;
	MultiLayer.m_Weight[0][2][2] = 6.3917;

	MultiLayer.m_Weight[1][0][1] = -4.5589;
	MultiLayer.m_Weight[1][1][1] = -10.3788;
	MultiLayer.m_Weight[1][2][1] = 9.7691;

	int n;
	for (n = 0; n < 4; n++)
	{
		// MultiLayer.pInValue[0] = 1;		// 바이어스
		MultiLayer.pInValue[1] = x[n][0];
		MultiLayer.pInValue[2] = x[n][1];

		MultiLayer.Forward();

		printf("%lf %lf=%lf\n", MultiLayer.pInValue[1], MultiLayer.pInValue[2], MultiLayer.pOutValue[1]);
	}
	printf("\n");

	int layer, snode, enode, node;
	// 가중치 출력(layer=0...multiLayer.miNumTotalLayer-1)
	for (layer = 0; layer < MultiLayer.m_iNumTotalLayer - 1; layer++)
	{
		for (snode = 0; snode <= MultiLayer.m_NumNodes[layer]; snode++)
		{
			for (enode = 1; enode <= MultiLayer.m_NumNodes[layer + 1]; enode++)
			{
				printf("w[%d][%d][%d] = %lf, ", layer, snode, enode, MultiLayer.m_Weight[layer][snode][enode]);
			}
			printf("\n");
		}
		printf("\n");
	}

	return 0;
}