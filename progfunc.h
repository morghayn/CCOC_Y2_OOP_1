#ifndef PROGFUNC_H
#define PROGFUNC_H

class ProgFunc {
    public:
        void Draw(int style, int col, int row, int length,int amount);
        void gotoXY(int x, int y);
        void gotoXY(int x, int y, string text, bool highlight);
        void ShowConsoleCursor(bool showFlag);
};

ProgFunc MyFunction;
    void Draw(int a, int b, int c, int d,int e) {MyFunction.Draw(a,b,c,d,e);}
    void gotoXY(int x, int y) {MyFunction.gotoXY(x,y);}
    void gotoXY(int x, int y, string a, bool b) {MyFunction.gotoXY(x,y,a,b);}
    void ShowConsoleCursor(bool showFlag) {MyFunction.ShowConsoleCursor(showFlag);}

#endif // PROGFUNC_H
