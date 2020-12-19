#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
�밴�մ˱��޸�N��ri
N   1  2  3     4     5     6     7     8     9     10    11    12    13    14
ri  0  0  0.52  0.89  1.12  1.26  1.36  1.41  1.46  1.49  1.49  1.52  1.56  1.58
*/
extern int ahp() {
    system("cls"); /*����Ϊ������ؽ���*/
    printf("********************************************************\n");
    printf("**************ϵͳ�����۲�η������������**************\n");
    printf("*T.L.saaty����20��������ʮ�������˲�η�����(Analytic*\n");
    printf("*Hierarchy  Process, AHP),����һ�ֶ��ԺͶ������ϵ�,ϵ*\n");
    printf("*ͳ����,��λ��ķ�������,��һ�ֲ��Ȩ�ؾ��߷�������.   *\n");
    printf("********************************************************\n");
    int N = 0;
    double ri = 0;
    for (N = 0; !(N >= 3 && N <= 14);) {
        printf("���������Ľ�����������֧�ּ���3��14�׵ľ��󣩣�");
        scanf("%d", &N);
        if (!(N >= 3 && N <= 14)) printf("��������һ�������������.���������롣");
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
    printf("�˳�����������ƽ��������ϵͳ�����۲�η�����%d�׾���.\n", N);
    printf("�ؼ�����:N=%d,r.i.=%4.3f\n�������������ĸ���෴��.\n", N, ri);
    printf("��:Ҫ����1/6,��ʵ������-6\n\n");
    double a[N][N] /*����*/, sum[N] /*�������*/, w[N] /*���й�һ���������*/, w0[N] /*Ȩ������*/, la[N] /*����ֵ����*/;
    int i, j;
    printf("ע��!��ֻ������������.\n");

    for (i = 0; i < N; i++) {
        a[i][i] = 1;
        for (j = 0; j < i; j++) {
            printf("���������������е�[%d,%d]Ԫ��:", i + 1, j + 1);
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
                    printf("��������һ�������������.���������룺");
                    continue;
                }
            }

            //printf("%d,%d:%lf\n",i,j,a[i][j]);
            //printf("%d,%d:%lf\n",j,i,a[j][i]);
        }
    }

    printf("����Ϊ��������:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (floor(a[i][j]) != 0)
                printf("%3.0lf\t", a[i][j]);
            else
                printf("1/%1.0lf\t", 1 / a[i][j]);
        }
        printf("\n");
    }

    printf("����Ϊ�������:\n");
    for (i = 0; i < N; i++) {
        sum[i] = 0;
        for (j = 0; j < N; j++) {
            sum[i] = sum[i] + a[j][i];
        }
        printf("sum%d:%lf\n", i + 1, sum[i]);
    }

    printf("����Ϊwi:\n");
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

    printf("����Ϊw0i:\n");
    for (i = 0; i < N; i++) {
        w0[i] = 0;
        w0[i] = w[i] / sum_w;
        printf("w0_%d:%lf\n", i + 1, w0[i]);
    }

    for (i = 0; i < N; i++) {
        sum_w0 = sum_w0 + w0[i];
    }
    printf("sum_w0:%lf\n", sum_w0);

    printf("����Ϊlamda:\n");
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
        printf("������пɽ��ܵ�һ����.\n");
        for (i = 0; i < N; i++)
            printf("��%d��Ҫ�ص�Ȩ��Ϊ:%lf\n", i + 1, w0[i]);
    } else
        printf("���󲻾��пɽ��ܵ�һ����.������жϾ���,ʹ������пɽ��ܵ�һ����.\n");
    printf("�������,�밴������˳�.\n");
    getchar();
}