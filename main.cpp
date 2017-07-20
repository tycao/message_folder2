#include "message.h"

int main(int argc, char *argv[])
{
    Folder f;
    Message m1("hello from tycao...");
    Message m2(m1);
    Message m3;
    m3 = m1;
    m1.save(f);
    m2.save(f);
    m3.save(f);
    cout << "f.show() : ";
    f.show();

    Folder ff(f);
    cout << "ff.show() : ";
    ff.show();
    ff.remMsg(&m1);
    ff.remMsg(&m2);
    cout << "ff.show() after remMsg(m1), remMsg(m2) : ";
    ff.show();
/*    swap(ff, f);
    cout << "ff.show() after swap(ff, f) : ";
    ff.show();
    cout << "f.show() after swap(ff, f) : ";
    f.show();
*/
    Message m4("Hi Mom!");
    m4.save(ff);
    swap(m1, m4);
    ff.show();
    f.show();
    m1.show();
    m4.show();
}
