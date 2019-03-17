/*************************************************************************
	> File Name: Unionset.cpp
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年03月17日 星期日 10时18分28秒
 ************************************************************************/

#include <iostream>
#include <ctime>
using namespace std;

struct Unionset {
    int *father;
    int *size;
    int n;
    Unionset (int n) {
        this->n = n;
        this->father = (int *)malloc(sizeof(int) * n);
        this->size = (int *)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) {
            this->father[i] = i;
            this->size[i] = 1;
        }
    }
    int find(int x) {
        if (this->father[x] != x) {
            return (this->father[x] = this->find(this->father[x]));
        }
        return x;
    }
    int merge(int a, int b) {
        int fa = this->find(a), fb = this->find(b);
        if (fa == fb) return 0;
        if (this->size[fa] < this->size[fb]) {
            fa ^= fb, fb ^= fa, fa ^= fb;
        }
        this->father[fb] = fa;
        this->size[fa] += this->size[fb];
        return 1;
    }
    void output() {
        for (int i = 0; i < this->n; i++) {
            cout << "(" << i << ", " << this->father[i] << ")\t";
            if (i + 1 < this->n && i + 1 % 5 == 0) cout << endl;
        }
        cout << endl;
        return ;
    }
    ~Unionset() {
        free(this->father);
        free(this->size);
    }
};

int main() {
    srand(time(0));
    int op, a, b;
    #define MAX_OP 20
    #define MAX_N 10
    Unionset u(MAX_N);
    for(int i = 0; i < MAX_OP; i++) {
        op = rand() % 4;
        a = rand() % MAX_N;
        b = rand() % MAX_N;
        switch (op) {
            case 0: {
                cout << "find " << a << " <-> " << b << " = " << (u.find(a) == u.find(b)) << endl;
            } break;
            default: {
                cout << "union " << a << " <-> " << b << " = " << u.merge(a, b) << endl;
            } break;
        }
        u.output();
    } 
    return 0;
}
