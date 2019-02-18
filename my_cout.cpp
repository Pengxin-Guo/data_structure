/*************************************************************************
	> File Name: my_cout.cpp
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年02月17日 星期日 20时45分06秒
 ************************************************************************/

#include <iostream>

namespace mylib {

    class Charactor {
    private :
        char c;
    public :
        Charactor(char c) : c(c) {}
        char get() const { return this->c; }
    };

    class file {
    private :
        FILE *f;
    public :
        file(FILE *f) : f(f) {}
        file(const char *s) {
            this->f = fopen(s, "w");
        }
        FILE *get() const { return this->f; }
        ~file() {
            if (this->f != NULL) fclose(this->f);
        }
    };

    class ostream {
    private :
        FILE *fout;
    public :
        ostream() {
            this->fout = stdout;
        }
        ostream &operator<<(const int &x) {
            fprintf(this->fout, "%d", x);
            return *this;
        }
        ostream &operator<<(const double &x) {
            fprintf(this->fout, "lf", x);
            return *this;
        }
        ostream &operator<<(const char *x) {
            fprintf(this->fout, "%s", x);
            return *this;
        }
        ostream &operator<<(const char x) {
            fprintf(this->fout, "%c", x);
            return *this;
        }
        ostream &operator<<(const Charactor &x) {
            (*this) << x.get();
            return *this;
        }
        ostream &operator<<(const file &x) {
            this->fout = x.get();
            return *this;
        }
    };

    file STDIN(stdin), STDOUT(stdout), STDERR(stderr);
    Charactor endl('\n');
    ostream cout;
}

int main() {
    mylib::file fout("output");
    mylib::cout << 123 << fout << 456 << mylib::STDOUT << 789 << mylib::endl;
    return 0;
}
