#include "jobin.h"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <unistd.h>
#include <sqlite3.h>
#include <termios.h>

void JobIn::Page_Logo(void)
{
    std::cout << std::endl;
    std::cout << "⠀⠀⠛⠛⠛⠀⠀⣿⠀⠀⠀⣤⠛⠛⠛⣤⠀⠀⣿⠀⠀⠀⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
    std::cout << "⠛⠛⣿⠛⣿⠛⠀⣿⠀⠀⠀⣿⠀⠀⠀⣿⠛⠛⣿⠀⠀⠀⣤⠀⠀⣤⣤⣤⣤⠀⠀⠀" << std::endl;
    std::cout << "⠛⠛⠀⠀⠀⠛⠀⣿⠀⠀⠀⠀⠛⠛⠛⠀⠀⠀⠛⠀⠀⠀⣿⠀⠀⣿⠀⠀⠀⣿⠀⠀" << std::endl;
    std::cout << "⠛⠛⣿⠛⠛⠛⠀⣿⠀⠀⠀⠀⣿⣤⣤⣤⣤⣤⣿⠀⠀⠀⣿⠀⠀⣿⠀⠀⠀⣿⠀⠀" << std::endl;
    std::cout << "⠀⣤⠛⠀⠀⠀⠀⣿⠀⠀⠀⠀⠛⣤⣤⣤⣤⣤⠛⠀⠀⠀⠛⠀⠀⠛⠀⠀⠀⠛⠀⠀" << std::endl;
    std::cout << std::endl;
}

int JobIn::Page_Home(void)
{
    std::string arr[3][2] =
    {
        {"▸ ", "로그인"},
        {"  ", "회원가입"},
        {"  ", "종료"}
    };
    int ypos = 0;

    while(1)
    {
        system("clear");
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        Page_Logo();
        for (int i = 0; i < 3; i++)
        {
            std::cout << std::endl;
            for (int j = 0; j < 2; j++)
            {
                std::cout << arr[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;

        int key = getch();
        if (key == 10) // 엔터
        {
            if (ypos == 0)
            {
                return 1;
            }
            else if (ypos == 1)
            {
                return 2;
            }
            else if (ypos == 2)
            {
                return 3;
            }
        }
        else if (key == 65 && ypos > 0) // 위
        {
            arr[ypos][0] = "  ";
            arr[ypos - 1][0] = "▸ ";
            ypos--;
        }
        else if (key == 66 && ypos < 2) // 아래
        {
            arr[ypos][0] = "  ";
            arr[ypos + 1][0] = "▸ ";
            ypos++;
        }
    }
}

int JobIn::Page_Login(void)
{
    sqlite3* db;
    sqlite3_stmt* stmt;
    char* err_msg = 0;

    int rc = sqlite3_open("userinfo.db", &db);
    if (rc != SQLITE_OK)
    {
        std::cout << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }
    
    while(1)
    {
        std::string id, pw;
        std::string arr[2][2] =
        {
            {"▸ ", "아이디: "},
            {"  ", "비밀번호: "}
        };
        system("clear");
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        Page_Logo();
        std::cout << std::endl;
        for (int i = 0; i < 2; i++)
        {
            std::cout << std::endl;
            for (int j = 0; j < 2; j++)
            {
                std::cout << arr[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << "아이디 입력\n\n>> ";
        std::cin >> id;
        system("clear");
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        Page_Logo();
        std::cout << std::endl;
        arr[0][0] = "  ";
        arr[0][1] = "아이디: " + id;
        arr[1][0] = "▸ ";
        for (int i = 0; i < 2; i++)
        {
            std::cout << std::endl;
            for (int j = 0; j < 2; j++)
            {
                std::cout << arr[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << "비밀번호 입력\n\n>> ";
        std::cin >> pw;
        system("clear");
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        Page_Logo();
        std::cout << std::endl;
        arr[1][1] = "비밀번호: " + std::string(pw.length(), '*');
        for (int i = 0; i < 2; i++)
        {
            std::cout << std::endl;
            for (int j = 0; j < 2; j++)
            {
                std::cout << arr[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;

        std::string sql = "SELECT pw FROM utable WHERE id = '" + id + "';";
        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
        if (rc != SQLITE_OK)
        {
            std::cerr << "로그인 실패" << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return rc;
        }

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW)
        {
            std::string dbpw(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));

            if (pw == dbpw)
            {
                std::cout << "로그인 성공" << std::endl;
                sleep(1);
                std::cin.ignore();
                break;
            }
            else
            {
                std::cout << "로그인 실패" << std::endl;
                sleep(1);
                continue;
            }
        }
        else
        {
            std::cout << "로그인 실패" << std::endl;
            sleep(1);
            continue;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

int JobIn::Page_Create(void)
{
    sqlite3* db;
    char* err_msg = 0;

    int rc = sqlite3_open("userinfo.db", &db);
    if (rc != SQLITE_OK)
    {
        std::cout << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }
    std::string arr[4][2] =
    {
        {"▸ ", "아이디: "},
        {"  ", "비밀번호: "},
        {"  ", "메일주소: "},
        {"  ", "휴대폰번호: "}
    };
    std::string id, pw, mail, phone;
    while(1)
    {
        system("clear");
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        Page_Logo();
        for (int i = 0; i < 4; i++)
        {
            if (i != 0)
            {
                std::cout << std::endl;
            }
            for (int j = 0; j < 2; j++)
            {
                std::cout << arr[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << "아이디 입력: ";
        std::cin >> id;
        std::string sql = "INSERT INTO utable (id) VALUES ('" + id + "');";
        rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err_msg);
        if (rc != SQLITE_OK)
        {
            std::cout << "중복된 아이디" << std::endl;
            sleep(1);
            continue;
        }
        else
        {
            break;
        }
    }
    while(1)
    {
        int error = 0;
        system("clear");
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        Page_Logo();
        arr[0][0] = "  ";
        arr[0][1] = "아이디: " + id;
        arr[1][0] = "▸ ";
        for (int i = 0; i < 4; i++)
        {
            if (i != 0)
            {
                std::cout << std::endl;
            }
            for (int j = 0; j < 2; j++)
            {
                std::cout << arr[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << "비밀번호 입력(4자리 숫자): ";
        std::cin >> pw;
        for (int i = 0; i < pw.length(); i++)
        {
            if (isdigit(pw[i]) == 0)
            {
                std::cout << "잘못된 비밀번호" << std::endl;
                error = 1;
                sleep(1);
                break;
            }
        }
        if (error == 1)
        {
            continue;
        }
        std::string sql = "UPDATE utable SET pw = '" + pw + "' WHERE id = '" + id + "';";
        rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err_msg);
        if (rc != SQLITE_OK)
        {
            std::cout << "잘못된 비밀번호" << std::endl;
            sleep(1);
            continue;
        }
        else
        {
            break;
        }
    }
    while(1)
    {
        system("clear");
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        Page_Logo();
        arr[1][0] = "  ";
        arr[1][1] = "비밀번호: " + pw;
        arr[2][0] = "▸ ";
        for (int i = 0; i < 4; i++)
        {
            if (i != 0)
            {
                std::cout << std::endl;
            }
            for (int j = 0; j < 2; j++)
            {
                std::cout << arr[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << "메일주소 입력: ";
        std::cin >> mail;
        std::string sql = "UPDATE utable SET mail = '" + mail + "' WHERE id = '" + id + "';";
        rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err_msg);
        if (rc != SQLITE_OK)
        {
            std::cout << "중복된 메일주소" << std::endl;
            sleep(1);
            continue;
        }
        else
        {
            break;
        }
    }
    while(1)
    {
        system("clear");
        int error = 0;
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        Page_Logo();
        arr[2][0] = "  ";
        arr[2][1] = "메일주소: " + mail;
        arr[3][0] = "▸ ";
        for (int i = 0; i < 4; i++)
        {
            if (i != 0)
            {
                std::cout << std::endl;
            }
            for (int j = 0; j < 2; j++)
            {
                std::cout << arr[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << "휴대폰번호 입력: ";
        std::cin >> phone;
        for (int i = 0; i < phone.length(); i++)
        {
            if (isdigit(phone[i]) == 0)
            {
                std::cout << "잘못된 휴대폰번호" << std::endl;
                error = 1;
                sleep(1);
                break;
            }
        }
        if (error == 1)
        {
            continue;
        }
        std::string sql = "UPDATE utable SET phone = '" + phone + "' WHERE id = '" + id + "';";
        rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err_msg);
        if (rc != SQLITE_OK)
        {
            std::cout << "잘못된 휴대폰번호" << std::endl;
            sleep(1);
            continue;
        }
        else
        {
            break;
        }
    }
    while(1)
    {
        system("clear");
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        Page_Logo();
        arr[3][1] = "휴대폰번호: " + phone;
        for (int i = 0; i < 4; i++)
        {
            if (i != 0)
            {
                std::cout << std::endl;
            }
            for (int j = 0; j < 2; j++)
            {
                std::cout << arr[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << "회원가입 완료" << std::endl;
        sleep(1);
        break;
    }
    std::cin.ignore();
    sqlite3_close(db);
    return 0;
}

int JobIn::Page_Search(void)
{
    std::string arr[3][2] =
    {
        {"▸ ", "기본 검색"},
        {"  ", "상세 검색"},
        {"  ", "로그아웃"}
    };
    int ypos = 0;

    while(1)
    {
        system("clear");
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        Page_Logo();
        for (int i = 0; i < 3; i++)
        {
            std::cout << std::endl;
            for (int j = 0; j < 2; j++)
            {
                std::cout << arr[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;

        int key = getch();
        if (key == 10) // 엔터
        {
            if (ypos == 0)
            {
                return 1;
            }
            else if (ypos == 1)
            {
                return 2;
            }
            else if (ypos == 2)
            {
                return 3;
            }
        }
        else if (key == 65 && ypos > 0) // 위
        {
            arr[ypos][0] = "  ";
            arr[ypos - 1][0] = "▸ ";
            ypos--;
        }
        else if (key == 66 && ypos < 2) // 아래
        {
            arr[ypos][0] = "  ";
            arr[ypos + 1][0] = "▸ ";
            ypos++;
        }
    }
}

int JobIn::Page_Basic(void)
{
    sqlite3* db;
    sqlite3_stmt* stmt;
    char* err_msg = 0;

    int rc = sqlite3_open("companyinfo.db", &db);
    if (rc != SQLITE_OK)
    {
        std::cout << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }
    system("clear");
    std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    std::cout << "\n기본 검색\t" << "\n\n검색 건수\t" << "건\n\n";
    std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    std::string word;
    std::cout << "검색어 입력\n\n>> ";
    std::cin >> word;

    std::string sql = "SELECT * FROM ctable WHERE co_title LIKE '\%" + word + "\%';";

    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        std::cerr << "검색 실패" << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return rc;
    }

    // rc = sqlite3_step(stmt);
    int count = 0;
    while(sqlite3_step(stmt) == SQLITE_ROW)
    {
        count++;
    }
    if (count == 0)
    {
        std::cout << "검색 결과 없음" << std::endl;
        sleep(1);
        return 1;
    }
    std::vector<std::vector<std::string>> arrv(count, std::vector<std::string>(17));
    int a = 1;

    system("clear");
    std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    std::cout << "\n기본 검색\t" << word << "\n\n검색 건수\t" << count << "건\n\n";
    while((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        std::string co_num(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        std::string co_name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string co_title(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        std::string co_region(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        std::string co_career(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        std::string co_education(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        std::string co_salary(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        std::string co_skill(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        std::string co_work(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        std::string co_prefer(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        std::string co_dday(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
        std::string co_ceo(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11)));
        std::string co_establish(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 12)));
        std::string co_type(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 13)));
        std::string co_employee(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 14)));
        std::string co_sector(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 15)));
        std::string co_website(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 16)));
        arrv[a-1][0] = co_num;
        arrv[a-1][1] = co_name;
        arrv[a-1][2] = co_title;
        arrv[a-1][3] = co_region;
        arrv[a-1][4] = co_career;
        arrv[a-1][5] = co_education;
        arrv[a-1][6] = co_salary;
        arrv[a-1][7] = co_skill;
        arrv[a-1][8] = co_work;
        arrv[a-1][9] = co_prefer;
        arrv[a-1][10] = co_dday;
        arrv[a-1][11] = co_ceo;
        arrv[a-1][12] = co_establish;
        arrv[a-1][13] = co_type;
        arrv[a-1][14] = co_employee;
        arrv[a-1][15] = co_sector;
        arrv[a-1][16] = co_website;

        std::cout << "    " << a << ".\t" << co_name << std::endl;
        std::cout << "\t" << co_title << std::endl;
        std::cout << "\t" << co_region << "\t" << co_career << "\t" << co_education << "\n\n";
        a++;
    }
    std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    std::string num;
    while(1)
    {
        std::cout << "공고 번호 선택\n\n>> ";
        std::cin >> num;
        if (stoi(num) -1 < count && stoi(num) - 1 >= 0)
        {
            std::cin.ignore();
            break;
        }
        else
        {  
            std::cout << "잘못된 입력\n\n";
            sleep(1);
            continue;
        }
    }

    std::string arr[2][2] =
    {
        {"▸ ", "회사 정보"},
        {"  ", "다시 검색"}
    };
    int ypos = 0;
    int b;
    while(1)
    {
        system("clear");
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << std::endl;
        std::cout  << arrv[stoi(num) - 1][1] << "\n\n" << arrv[stoi(num) - 1][2] << "\n\n지역: " << arrv[stoi(num) - 1][3] << "\n경력: " << arrv[stoi(num) - 1][4];
        std::cout << "\n학력: " << arrv[stoi(num) - 1][5] << "\n급여: " << arrv[stoi(num) - 1][6] << "\n\n주요스킬: " << arrv[stoi(num) - 1][7];
        std::cout << "\n\n담당업무\n- " << arrv[stoi(num) - 1][8] << "\n우대조건\n- " << arrv[stoi(num) - 1][9] << "\n\n공고 마감일: " << arrv[stoi(num) - 1][10] << "\n";
        std::cout << std::endl;
        for (int i = 0; i < 2; i++)
        {
            std::cout << std::endl;
            for (int j = 0; j < 2; j++)
            {
                std::cout << arr[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        int key = getch();
        if (key == 10) // 엔터
        {
            if (ypos == 0)
            {
                b = 1;
                break;
            }
            else if (ypos == 1)
            {
                b = 2;
                break;
            }
        }
        else if (key == 65 && ypos > 0) // 위
        {
            arr[ypos][0] = "  ";
            arr[ypos - 1][0] = "▸ ";
            ypos--;
        }
        else if (key == 66 && ypos < 1) // 아래
        {
            arr[ypos][0] = "  ";
            arr[ypos + 1][0] = "▸ ";
            ypos++;
        }
    }
    if (b == 1)
    {
        system("clear");
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << std::endl;
        std::cout  << arrv[stoi(num) - 1][1] << "\n\n" << arrv[stoi(num) - 1][2] << "\n\n지역: " << arrv[stoi(num) - 1][3] << "\n경력: " << arrv[stoi(num) - 1][4];
        std::cout << "\n학력: " << arrv[stoi(num) - 1][5] << "\n급여: " << arrv[stoi(num) - 1][6] << "\n\n주요스킬: " << arrv[stoi(num) - 1][7];
        std::cout << "\n\n담당업무\n- " << arrv[stoi(num) - 1][8] << "\n우대조건\n- " << arrv[stoi(num) - 1][9] << "\n\n공고 마감일: " << arrv[stoi(num) - 1][10] << "\n";
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "대표자: " << arrv[stoi(num) - 1][11] << "\n\n설립일: " << arrv[stoi(num) - 1][12] <<"\n\n기업형태: " << arrv[stoi(num) - 1][13];
        std::cout << "\n\n사원수: " << arrv[stoi(num) - 1][14] << "\n\n업종: " << arrv[stoi(num) - 1][15] << "\n\n홈페이지: " << arrv[stoi(num) - 1][16];
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "▸  다시 검색";
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        while(1)
        {
            int key = getch();
            if (key == 10)
            {
                return 1;
            }
            else
            {
                continue;
            }
        }
    }
    else if (b == 2)
    {
        return 1;
    }

    return 0;
}

int JobIn::Page_Detail(void)
{
    std::string region, career, education, skill;

    sqlite3* db;
    sqlite3_stmt* stmt;
    char* err_msg = 0;

    int rc = sqlite3_open("companyinfo.db", &db);
    if (rc != SQLITE_OK)
    {
        std::cout << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }
    while(1)
    {
        system("clear");
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << "\n상세 검색\t지역: \n\t\t경력: \n\t\t학력: \n\t\t스킬: " << "\n\n검색 건수\t" << "건\n\n";
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << "지역 입력(전체, 경기, 경남, 경북, 광주, 대전, 부산, 서울, 세종, 인천, 전북, 충남, 충북)\n\n>> ";
        std::cin >> region;
        if (region == "전체" || region == "경기" || region == "경남" || region == "경북" || region == "광주" || region == "대전" || region == "부산" || region == "서울" || region == "세종" || region == "인천" || region == "전북" || region == "충남" || region == "충북")
        {
            break;
        }
        else
        {
            continue;
        }
    }
    while(1)
    {
        system("clear");
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << "\n상세 검색\t지역: " << region << "\n\t\t경력: \n\t\t학력: \n\t\t스킬: " << "\n\n검색 건수\t" << "건\n\n";
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << "경력 입력(전체, 신입, 경력)\n\n>> ";
        std::cin >> career;
        if (career == "전체" || career == "신입" || career == "경력")
        {
            break;
        }
        else
        {
            continue;
        }
    }
    while(1)
    {
        system("clear");
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << "\n상세 검색\t지역: " << region << "\n\t\t경력: " << career << "\n\t\t학력: \n\t\t스킬: " << "\n\n검색 건수\t" << "건\n\n";
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << "학력 입력(전체, 학력무관, 고졸이상, 대졸(2,3년제)이상, 대졸(4년제)이상, 석사졸업이상)\n\n>> ";
        std::cin >> education;
        if (education == "전체" || education == "학력무관" || education == "고졸이상" || education == "대졸(2,3년제)이상" || education == "대졸(4년제)이상" || education == "석사졸업이상")
        {
            break;
        }
        else
        {
            continue;
        }
    }
    while(1)
    {
        system("clear");
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << "\n상세 검색\t지역: " << region << "\n\t\t경력: " << career << "\n\t\t학력: " << education << "\n\t\t스킬: " << "\n\n검색 건수\t" << "건\n\n";
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << "스킬 입력(전체, c, c++, c#, python)\n\n>> ";
        std::cin >> skill;
        if (skill == "전체" || skill == "c" || skill == "c++" || skill == "c#" || skill == "python")
        {
            break;
        }
        else
        {
            continue;
        }
    }

    std::string tempregion, tempcareer, tempeducation, tempskill;
    tempregion = region;
    tempcareer = career;
    tempeducation = education;
    tempskill = skill;
    
    if (region == "전체")
    {
        region = "";
    }
    if (career == "전체")
    {
        career = "";
    }
    if (education == "전체")
    {
        education = "";
    }
    if (skill == "전체")
    {
        skill = "";
    }
    std::string sql = "SELECT * FROM ctable WHERE (co_region LIKE '\%" + region + "\%' AND co_career LIKE '\%"+ career + "\%' AND co_education LIKE '\%"+ education + "\%' AND co_skill LIKE '\%"+ skill + "\%');";
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        std::cerr << "검색 실패" << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return rc;
    }

    // rc = sqlite3_step(stmt);
    int count = 0;
    while(sqlite3_step(stmt) == SQLITE_ROW)
    {
        count++;
    }
    if (count == 0)
    {
        std::cout << "검색 결과 없음" << std::endl;
        std::cin.ignore();
        sleep(1);
        return 1;
    }

    std::vector<std::vector<std::string>> arrv(count, std::vector<std::string>(17));
    int a = 1;
    system("clear");
    std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    std::cout << "\n상세 검색\t지역: " << tempregion << "\n\t\t경력: " << tempcareer << "\n\t\t학력: " << tempeducation << "\n\t\t스킬: " << tempskill << "\n\n검색 건수\t" << count << "건\n\n";
    while((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        std::string co_num(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        std::string co_name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string co_title(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        std::string co_region(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        std::string co_career(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        std::string co_education(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        std::string co_salary(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        std::string co_skill(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        std::string co_work(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        std::string co_prefer(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        std::string co_dday(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
        std::string co_ceo(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11)));
        std::string co_establish(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 12)));
        std::string co_type(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 13)));
        std::string co_employee(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 14)));
        std::string co_sector(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 15)));
        std::string co_website(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 16)));
        arrv[a-1][0] = co_num;
        arrv[a-1][1] = co_name;
        arrv[a-1][2] = co_title;
        arrv[a-1][3] = co_region;
        arrv[a-1][4] = co_career;
        arrv[a-1][5] = co_education;
        arrv[a-1][6] = co_salary;
        arrv[a-1][7] = co_skill;
        arrv[a-1][8] = co_work;
        arrv[a-1][9] = co_prefer;
        arrv[a-1][10] = co_dday;
        arrv[a-1][11] = co_ceo;
        arrv[a-1][12] = co_establish;
        arrv[a-1][13] = co_type;
        arrv[a-1][14] = co_employee;
        arrv[a-1][15] = co_sector;
        arrv[a-1][16] = co_website;

        std::cout << "    " << a << ".\t" << co_name << std::endl;
        std::cout << "\t" << co_title << std::endl;
        std::cout << "\t" << co_region << "\t" << co_career << "\t" << co_education << "\n\n";
        a++;
    }
    std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    std::string num;
    while(1)
    {
        std::cout << "공고 번호 선택\n\n>> ";
        std::cin >> num;
        if (stoi(num) -1 < count && stoi(num) - 1 >= 0)
        {
            std::cin.ignore();
            break;
        }
        else
        {  
            std::cout << "잘못된 입력\n\n";
            sleep(1);
            continue;
        }
    }

    std::string arr[2][2] =
    {
        {"▸ ", "회사 정보"},
        {"  ", "다시 검색"}
    };
    int ypos = 0;
    int b;
    while(1)
    {
        system("clear");
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << std::endl;
        std::cout  << arrv[stoi(num) - 1][1] << "\n\n" << arrv[stoi(num) - 1][2] << "\n\n지역: " << arrv[stoi(num) - 1][3] << "\n경력: " << arrv[stoi(num) - 1][4];
        std::cout << "\n학력: " << arrv[stoi(num) - 1][5] << "\n급여: " << arrv[stoi(num) - 1][6] << "\n\n주요스킬: " << arrv[stoi(num) - 1][7];
        std::cout << "\n\n담당업무\n- " << arrv[stoi(num) - 1][8] << "\n우대조건\n- " << arrv[stoi(num) - 1][9] << "\n\n공고 마감일: " << arrv[stoi(num) - 1][10] << "\n";
        std::cout << std::endl;
        for (int i = 0; i < 2; i++)
        {
            std::cout << std::endl;
            for (int j = 0; j < 2; j++)
            {
                std::cout << arr[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        int key = getch();
        if (key == 10) // 엔터
        {
            if (ypos == 0)
            {
                b = 1;
                break;
            }
            else if (ypos == 1)
            {
                b = 2;
                break;
            }
        }
        else if (key == 65 && ypos > 0) // 위
        {
            arr[ypos][0] = "  ";
            arr[ypos - 1][0] = "▸ ";
            ypos--;
        }
        else if (key == 66 && ypos < 1) // 아래
        {
            arr[ypos][0] = "  ";
            arr[ypos + 1][0] = "▸ ";
            ypos++;
        }
    }
    if (b == 1)
    {
        system("clear");
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        std::cout << std::endl;
        std::cout  << arrv[stoi(num) - 1][1] << "\n\n" << arrv[stoi(num) - 1][2] << "\n\n지역: " << arrv[stoi(num) - 1][3] << "\n경력: " << arrv[stoi(num) - 1][4];
        std::cout << "\n학력: " << arrv[stoi(num) - 1][5] << "\n급여: " << arrv[stoi(num) - 1][6] << "\n\n주요스킬: " << arrv[stoi(num) - 1][7];
        std::cout << "\n\n담당업무\n- " << arrv[stoi(num) - 1][8] << "\n우대조건\n- " << arrv[stoi(num) - 1][9] << "\n\n공고 마감일: " << arrv[stoi(num) - 1][10] << "\n";
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "대표자: " << arrv[stoi(num) - 1][11] << "\n\n설립일: " << arrv[stoi(num) - 1][12] <<"\n\n기업형태: " << arrv[stoi(num) - 1][13];
        std::cout << "\n\n사원수: " << arrv[stoi(num) - 1][14] << "\n\n업종: " << arrv[stoi(num) - 1][15] << "\n\n홈페이지: " << arrv[stoi(num) - 1][16];
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "▸  다시 검색";
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "──────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
        while(1)
        {
            int key = getch();
            if (key == 10)
            {
                return 2;
            }
            else
            {
                continue;
            }
        }
    }
    else if (b == 2)
    {
        return 2;
    }
    return 0;
}

void JobIn::Page_Run(void)
{
    while(1)
    {
        int page_home = Page_Home();
        if (page_home == 1)
        {
            int page_login = Page_Login();
            if (page_login == 0)
            {
                while(1)
                {
                    int page_search = Page_Search();
                    if (page_search == 1)
                    {
                        int page_basic = Page_Basic();
                        if (page_basic == 1)
                        {
                            continue;
                        }
                    }
                    else if (page_search == 2)
                    {
                        while(1)
                        {
                            int page_detail = Page_Detail();
                            if (page_detail == 1)
                            {
                                continue;
                            }
                            else if (page_detail == 2)
                            {
                                break;
                            }
                        }
                    }
                    else if (page_search == 3)
                    {
                        break;
                    }
                }
            }
        }
        else if (page_home == 2)
        {
            while(1)
            {
                int page_create = Page_Create();
                if (page_create == 0)
                {
                    break;
                }
            }
        }
        else if (page_home == 3)
        {
            break;
        }
    }
}

int JobIn::getch(void)
{
    int c;
    struct termios oldattr, newattr;

    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    newattr.c_cc[VMIN] = 1;
    newattr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return c;
}