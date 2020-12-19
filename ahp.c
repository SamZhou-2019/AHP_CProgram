#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
请按照此表修改N及ri
N   1  2  3     4     5     6     7     8     9     10    11    12    13    14
ri  0  0  0.52  0.89  1.12  1.26  1.36  1.41  1.46  1.49  1.49  1.52  1.56  1.58
*/
extern int ahp() {
    system("cls"); /*以下为程序相关介绍*/
    printf("********************************************************\n");
    printf("**************系统方法论层次分析法计算程序**************\n");
    printf("*T.L.saaty等人20世纪在七十年代提出了层次分析法(Analytic*\n");
    printf("*Hierarchy  Process, AHP),它是一种定性和定量相结合的,系*\n");
    printf("*统化的,层次化的分析方法,是一种层次权重决策分析方法.   *\n");
    printf("********************************************************\n");
    int N = 0;
    double ri = 0;
    for (N = 0; !(N >= 3 && N <= 14);) {
        printf("请输入矩阵的阶数（本程序支持计算3至14阶的矩阵）：");
        scanf("%d", &N);
        if (!(N >= 3 && N <= 14)) printf("你输入了一个不合理的数据.请重新输入。");
    }
    switch (N) {
        case 3:
            ri = 0.52;
            break;
        case 4:
            ri = 0.89;
            break;
        case 5:
            ri = 1.12;
            break;
        case 6:
            ri = 1.26;
            break;
        case 7:
            ri = 1.36;
            break;
        case 8:
            ri = 1.41;
            break;
        case 9:
            ri = 1.46;
            break;
        case 10:
        case 11:
            ri = 1.49;
            break;
        case 12:
            ri = 1.52;
            break;
        case 13:
            ri = 1.56;
            break;
        case 14:
            ri = 1.58;
            break;
    }
    printf("此程序利用算术平均法计算系统方法论层次分析法%d阶矩阵.\n", N);
    printf("关键数据:N=%d,r.i.=%4.3f\n分数·请输入分母的相反数.\n", N, ri);
    printf("如:要输入1/6,请实际输入-6\n\n");
    double a[N][N] /*矩阵*/, sum[N] /*按列求和*/, w[N] /*按列归一化后按行求和*/, w0[N] /*权重向量*/, la[N] /*特征值向量*/;
    int i, j;
    printf("注意!请只输入下三角阵.\n");

    for (i = 0; i < N; i++) {
        a[i][i] = 1;
        for (j = 0; j < i; j++) {
            printf("请输入下三角阵中的[%d,%d]元素:", i + 1, j + 1);
            for (;;) {
                scanf("%lf", &a[i][j]);
                if (a[i][j] >= 1 && a[i][j] <= 10 && a[i][j] == (int) a[i][j]) {
                    a[i][j] = floor(a[i][j]);
                    a[j][i] = 1.0 / a[i][j];
                    break;
                } else if (a[i][j] >= -10 && a[i][j] <= -1 && a[i][j] == (int) a[i][j]) {
                    a[j][i] = (-1) * ceil(a[i][j]);
                    a[i][j] = 1.0 / a[j][i];
                    break;
                } else {
                    printf("你输入了一个不合理的数据.请重新输入：");
                    continue;
                }
            }

            //printf("%d,%d:%lf\n",i,j,a[i][j]);
            //printf("%d,%d:%lf\n",j,i,a[j][i]);
        }
    }

    printf("以下为完整矩阵:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (floor(a[i][j]) != 0)
                printf("%3.0lf\t", a[i][j]);
            else
                printf("1/%1.0lf\t", 1 / a[i][j]);
        }
        printf("\n");
    }

    printf("以下为按列求和:\n");
    for (i = 0; i < N; i++) {
        sum[i] = 0;
        for (j = 0; j < N; j++) {
            sum[i] = sum[i] + a[j][i];
        }
        printf("sum%d:%lf\n", i + 1, sum[i]);
    }

    printf("以下为wi:\n");
    for (i = 0; i < N; i++) {
        w[i] = 0;
        for (j = 0; j < N; j++) {
            w[i] = w[i] + a[i][j] / sum[j];
        }
        printf("w%d:%lf\n", i + 1, w[i]);
    }

    double sum_w = 0, avg_la = 0, sum_w0 = 0;
    for (i = 0; i < N; i++) {
        sum_w = sum_w + w[i];
    }
    printf("sum_w:%lf\n", sum_w);

    printf("以下为w0i:\n");
    for (i = 0; i < N; i++) {
        w0[i] = 0;
        w0[i] = w[i] / sum_w;
        printf("w0_%d:%lf\n", i + 1, w0[i]);
    }

    for (i = 0; i < N; i++) {
        sum_w0 = sum_w0 + w0[i];
    }
    printf("sum_w0:%lf\n", sum_w0);

    printf("以下为lamda:\n");
    for (i = 0; i < N; i++) {
        la[i] = 0;
        for (j = 0; j < N; j++) {
            la[i] = la[i] + a[i][j] * w0[j];
        }
        la[i] = la[i] / w0[i];
        printf("lamda%d:%lf\n", i + 1, la[i]);
        avg_la = avg_la + la[i];
    }
    double douN = (double) N;
    printf("sum_lamda:%lf\n", avg_la);
    printf("max=avg_lamda:%lf\n", avg_la / douN);
    printf("c.i.:%lf\n", (avg_la / douN - N) / 4.0);
    double cr = ((avg_la / douN - N) / 4) / ri /*r.i.*/;
    printf("c.r.:%lf\n", cr);
    if (cr < 0.1) {
        printf("矩阵具有可接受的一致性.\n");
        for (i = 0; i < N; i++)
            printf("第%d个要素的权重为:%lf\n", i + 1, w0[i]);
    } else
        printf("矩阵不具有可接受的一致性.请调整判断矩阵,使矩阵具有可接受的一致性.\n");
    printf("程序完成,请按任意键退出.\n");
    getchar();
}