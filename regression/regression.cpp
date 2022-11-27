#include<stdio.h>
#include<math.h>
#include<string.h>
float data[10][2] =
{
    {1,2},
    {2,4},
    {1.5,3},
    {3,6},
    {4,8},
    {1.1,2.2},
    {2.3,4.6},
    {0.5,1},
    {3.2,6.4},
    {3.3,6.6},


};
float W[2] = { 1,3 };


void grad_des(float* data, float learning_rate)
{
    float x[10][2] = { 0 };
    int i = 0;
    int j = 0;
    float loss = 0;
    float grad[2] = { 0 };
    int m, n = 0;
    int echo = 0;
    float y_true[10] = { 0 };
    float y_pre[10] = { 0 };
    memcpy(x, data, sizeof(x));

    //将x转换为[1,x]形式
    for (i = 0; i < 10; i++)
    {
        y_true[i] = *(*(x)+i * 2 + 1);
        //x1=[1,x1]
        *(*(x)+i * 2 + 1) = *(*(x)+i * 2 + 0);
        *(*(x)+i * 2) = 1;
    }
    //cal grid
    for (echo = 0; echo < 100; echo++)
    {
        loss = 0;
        for (i = 0; i < 10; i++)
        {
            y_pre[i] = 0;
            for (m = 0; m < 2; m++)
            {
                y_pre[i] += (float)*(*(x)+i * 2 + m) * W[m];
            }
            loss += (float)(y_pre[i] - y_true[i]) * (float)(y_pre[i] - y_true[i]) / 2;
        }
        printf("loss=%f  \r\n", loss);
        if (loss < 0.001)
            break;
        //        单个数据梯度下降
        for (i = 0; i < 10; i++)
        {

            for (j = 0; j < 2; j++)
            {
                grad[j] = (y_pre[i] - y_true[i]) * (*(*(x)+i * 2 + j));
                W[j] = W[j] - learning_rate * grad[j];
            }

            printf("grad1=%f,grad2=%f,", grad[0], grad[1]);
            printf("W1=%f,W2=%f,", W[0], W[1]);
            printf("y_pre=%f", y_pre[0]);
            printf("\r\n ");
        }

        //批量梯度下降
//        for(j=0;j<2;j++)
//            grad[j]=0;
//        for(i=0; i<10; i++)
//        {
//
//            for(j=0; j<2; j++)
//            {
//                grad[j]+=(y_pre[i]-y_true[i])*(*(*(x)+i*2+j));
//            }
//        }
//        for(j=0; j<2; j++)
//        {
//            W[j]=W[j]-learning_rate*grad[j];
//        }
//        printf("grad1=%f,grad2=%f,",grad[0],grad[1]);
//        printf("W1=%f,W2=%f,",W[0],W[1]);
//        printf("y_pre=%f",y_pre[0]);
//        printf("\r\n ");

//  //随机数据梯度下降
//    int k1=0;
//    int k2=3;
//        for(i=k1; i<k2&&(k2<10); i++)
//        {
//
//            for(j=0; j<2; j++)
//            {
//                grad[j]=(y_pre[i]-y_true[i])*(*(*(x)+i*2+j));
//                W[j]=W[j]-learning_rate*grad[j];
//            }
//
//            printf("grad1=%f,grad2=%f,",grad[0],grad[1]);
//            printf("W1=%f,W2=%f,",W[0],W[1]);
//            printf("y_pre=%f",y_pre[0]);
//            printf("\r\n ");
//            k1++;
//            k2++;
//        }

    }
}

int main()
{
    grad_des(*data, 0.01);
    return 0;
}