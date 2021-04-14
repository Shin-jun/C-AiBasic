#include <stdio.h>
#include "MLP.h"
CMLP	MultiLayer;

int main() 
{
    printf("학번 : 20151186\n이름 : 신용준\n과제 : 전방향 다층신경망 학습\n\n");

    int HiddenNodes[1] = { 2 };
    int numofHiddenLayer = 1;
    MultiLayer.Create(2, HiddenNodes, 1, numofHiddenLayer);

    double x[4][2] = { {0,0},{ 0,1 },{ 1,0 },{ 1,1 } };

    MultiLayer.m_Weight[0][0][1] = -0.8;
    MultiLayer.m_Weight[0][1][1] = 0.5;
    MultiLayer.m_Weight[0][2][1] = 0.4;

    MultiLayer.m_Weight[0][0][2] = 0.1;
    MultiLayer.m_Weight[0][1][2] = 0.9;
    MultiLayer.m_Weight[0][2][2] = 1.0;

    MultiLayer.m_Weight[1][0][1] = -0.3;
    MultiLayer.m_Weight[1][1][1] = -1.2;
    MultiLayer.m_Weight[1][2][1] = 1.1;

    MultiLayer.pInValue[1] = 1;
    MultiLayer.pInValue[2] = 1;

    MultiLayer.pCorrectOutValue[1] = 0;

    MultiLayer.Forward();
    MultiLayer.BackPropagationLearning();

    int layer, snode, enode, node;
    printf("학습 전 가중치\n");
    for (layer = 0; layer < MultiLayer.m_iNumTotalLayer - 1; layer++)
    {
        printf("\nlayer=%d: ", layer);
        for (enode = 1; enode <= MultiLayer.m_NumNodes[layer + 1]; enode++)
        {
            printf("[%d]", enode);
            printf("bias=%7.4lf", MultiLayer.m_Weight[layer][0][enode]);
            for (snode = 1; snode <= MultiLayer.m_NumNodes[layer]; snode++)
            {
                printf("%7.4lf", MultiLayer.m_Weight[layer][snode][enode]);
            }
        }

    }
    printf("\n\n%lf %lf=%lf\n", MultiLayer.pInValue[1],
        MultiLayer.pInValue[1], MultiLayer.pOutValue[1]);

    printf("\n\n노드별 출력값");
    for (layer = 0; layer < MultiLayer.m_iNumTotalLayer; layer++)
    {
        printf("\nlayer=%d: ", layer);
        for (node = 1; node <= MultiLayer.m_NumNodes[layer]; node++)
        {
            printf("%lf ", MultiLayer.m_NodeOut[layer][node]);
        }
    }

    printf("\n\n에러 경사값");
    for (layer = 0; layer <= MultiLayer.m_iNumTotalLayer-1; layer++)
    {
        printf("\nlayer=%d: ", layer);
        for (node = 1; node <= MultiLayer.m_NumNodes[layer]; node++)
        {
            printf("%lf ", MultiLayer.m_ErrorGradient[layer][node]);
        }
    }

    printf("\n\n학습 후 가중치");
    for (layer = 0; layer < MultiLayer.m_iNumTotalLayer - 1; layer++)
    {
        printf("\nlayer=%d: ", layer);
        for (enode = 1; enode <= MultiLayer.m_NumNodes[layer + 1]; enode++)
        {
            printf("[%d]", enode);
            printf("bias=%7.4lf", MultiLayer.m_Weight[layer][0][enode]);
            for (snode = 1; snode <= MultiLayer.m_NumNodes[layer]; snode++)
            {
                printf("%7.4lf", MultiLayer.m_Weight[layer][snode][enode]);
            }
        }

    }
    printf("\n\n");
}
