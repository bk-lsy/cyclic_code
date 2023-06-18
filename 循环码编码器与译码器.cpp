

#include <iostream>
#include <string>
using namespace std;

const int EXP = 13;//�����������λ��
const int INTER = 4;//��Ϣ�볤��
const int CY = 7;//ѭ���볤��

const int IN_N = 3;//���������Ϣ��Ԫ��
const int OUT_N = 3;//�������ѭ��������


struct Poly {
    int mexp;
    int coef[EXP] = { 0 };//ϵ����С��������
};


const Poly y_1 = { 3,{1,1,0,1} };
const Poly y_2 = { 3,{1,0,1,1} };//����74ѭ�������ɶ���ʽ

//��������ƶ���ʽ
Poly input(int n) {
    Poly p;
    
    int max_exp = 0;
    bool set_max = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        char a;
        int x =0;
        cin >> a;
        x = a - '0';
        if (!set_max && x) {
            max_exp = i;
            set_max = 1;
        }
        p.coef[i] = x;
    }
    p.mexp = max_exp;
    return p;
}

//��������ƶ���ʽ
void output(Poly p,int n) {

    for (int i = n-1; i >= 0; i--) {
        cout << p.coef[i];
    }
    cout << endl;
}
//��λ����

Poly shift_poly(const Poly x, int xn,int ym)
{
    Poly y;
    y.mexp = ym;
    if (xn > ym) {
        for (int i = 0; i <= ym; i++) {

            y.coef[i] = x.coef[i + xn - ym];
        }
    }
    else {
        for (int i = 0; i <= ym; i++) {
            y.coef[i+ym-xn] = x.coef[i];
        }

    }
    return y;
}


//�����ƶ���ʽ���
Poly xor_poly(Poly a, Poly b) {

    Poly p;
    p.mexp = max(a.mexp, b.mexp);

    bool mcoef = 0;
    for (int i = p.mexp ; i >= 0; i--)
    {
        int s = a.coef[i] + b.coef[i];
        p.coef[i] = s%2;
        if (p.coef[i]) {
            mcoef = 1;
        }
        if (!p.coef[i] && !mcoef) {
            p.mexp--;
        }
    }
    return p;
}
//�����ƶ���ʽ����
Poly div_poly(Poly x, const Poly y) {
    Poly out;
    Poly remain = x;
   

    if (x.mexp < y.mexp) {
        out.mexp = 0;       
    }
    else {

        out.mexp = x.mexp - y.mexp;
        
        while (remain.mexp >= y.mexp) {
            Poly res;
           res = shift_poly(y,y.mexp,remain.mexp);
            remain = xor_poly(res,remain );
            out.coef[remain.mexp - y.mexp] = 1;
        }
    }
    return remain;
}



//��Ϣ��תΪѭ����
Poly inTocy(Poly x,const Poly y) {
    Poly s,  remain;
    s.mexp = 6;
    Poly xmx;
    xmx =shift_poly(x,3,6);

     remain=div_poly(xmx, y);

     

    for (int i = 0; i <= s.mexp; i++) {
        if (i <= 2) {
            s.coef[i] = remain.coef[i];

        }
        else {
            s.coef[i] = xmx.coef[i];

        }
    }
    return s;
}
//ѭ����תΪ��Ϣ��
Poly cyToin(Poly x,Poly y) {
    
    Poly remain;

    remain = div_poly(x, y);

    Poly cyout = shift_poly(x,6,3);

    int fall = 0;
    for (int i = 0; i < 3; i++) {
        if (remain.coef[i]) {
            fall++;
        }
    }
    if (fall == 3) {
        cyout.coef[4] = abs(cyout.coef[4] - 1);
    }
    else if (fall == 2) {
        
            if (!remain.coef[0]) {
                cyout.coef[6] = abs(cyout.coef[6] - 1);
            }          
            else if (!remain.coef[1]) {
                cyout.coef[3] = abs(cyout.coef[3] - 1);
            }
            else {
                cyout.coef[5] = abs(cyout.coef[5] - 1);
            }
        
    }

    return cyout;

}
//������ 
int main() {


    const Poly y = y_1;

    cout << "��ǰ���ɶ���ʽ:";
    output(y,4);
    cout << "������" << IN_N << "����Ϣ����б������:" << endl;
    Poly x_1[IN_N], out_1[IN_N];

    for (int i = 0; i < IN_N; i++) {
      x_1[i] = input(INTER);
        out_1[i] = inTocy(x_1[i], y);
    }
    cout << "������:" << endl;
    for (int i = 0; i < IN_N; i++) {
        output(out_1[i],7);
    }

    cout << "������" << OUT_N << "��ѭ��������������:" << endl;

    Poly x_2[OUT_N ], out_2[OUT_N ];

    for (int i = 0; i < OUT_N; i++) {
        x_2[i] = input(CY);
       out_2[i] = cyToin(x_2[i], y);
    }
    cout << "������:" << endl;
    for (int i = 0; i < OUT_N; i++) {
        output(out_2[i],4);
    }

    return 0;
}

/*
* 
�޲��
0001
1110
1000
0001011
1110100
1000101

�޲����һλ��Ԫ�����λ
0001
1110
1000
0001011
1100100
1011101


0001 1110 1000
0001011
0101011
1001010

*/