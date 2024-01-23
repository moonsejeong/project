#ifndef JOBIN_H
#define JOBIN_H

class JobIn
{
private:
    void Page_Logo(void);
    int Page_Home(void);
    int Page_Login(void);
    int Page_Create(void);
    int Page_Search(void);
    int Page_Basic(void);
    int Page_Detail(void);
    int getch(void);

public:
    void Page_Run(void);
};

#endif