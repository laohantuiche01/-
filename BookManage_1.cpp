#include <bits/stdc++.h>
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class BookData;//创建类

class Node;//用链表储存

Node *CreatHead();//采用单链表，创建头节点

Node *CreatNode(BookData data);//创建节点

void insertNode(Node *headNode, BookData data);//插入数据/节点

void printNode(Node *headNode);//打印链表内容

void deleyeByName(Node *headNode, char *bookName);//按照书名删除指定内容

Node *searchByName(struct Node *headNode, char *bookName);//按照名字寻找书籍

void bubbleSortList(Node *headNode);//按照价格冒泡排序输出

void mainmenu();//主菜单

void saveInfoToFile(const char *fileName, Node *headNode);//文件操作，保存

void readInfoFromFile(const char *fileName);//文件操作，读取

void fixData(Node *headNode, int bookISBN);//修改数据

//数据的储存方式及操作

class BookData                            //定义数据类型，存储书籍信息
{
public:
    char bookTitle[20];                   //书名
    int bookISBN;                         //书的编号
    int num;                              //库存
    float price;                          //价格
    int cashiernum = 0;                       //要卖出的数量
    BookData() = default;//创建类

    ~BookData() = default;

    void inputData()//输入数据（用于修改）
    {
        cout << "请输入书的剩余库存：\n";
        cin >> num;
        cout << "请输入书的ISBN：\n";
        cin >> bookISBN;
        cout << "请输入书的名字：\n";
        cin >> bookTitle;
        cout << "请输入书的单价：\n";
        cin >> price;
    }

    void dataInitialize()//初始化类
    {
        num = 0;
        bookISBN = 0;
        price = 0.0;
    }


};

class Node //用单项链表储存
{
public:
    BookData data;
    Node *next;
};

Node *list_head = NULL;//创建全局变量来储存头节点

Node *CreatHead()//创建头链表
{
    Node *headNode = (Node *) malloc(sizeof(Node *));//开辟动态内存
    headNode->next = NULL;
    return headNode;
}

Node *CreatNode(BookData data)//创建节点
{
    Node *newNode = (Node *) malloc((sizeof(Node *)));
    newNode->next = NULL;
    newNode->data = data;
    return newNode;
}

void insertNode(Node *headNode, BookData data)//从头部插入链表
{
    Node *newNode = CreatNode(data);
    newNode->next = headNode->next;
    headNode->next = newNode;
}

void printNode(Node *headNode)//打印出链表
{
    Node *pMove = headNode->next;//用一个移动的指针输出
    cout << "\t前台销售模块\n";
    cout << "日期：\n";
    cout << "ISBN号\t书名\t数量\t单价\n";
    while (pMove != NULL)//移动输出
    {
        cout << pMove->data.bookISBN << "\t" << pMove->data.bookTitle << "\t" << pMove->data.num << "\t"
             << pMove->data.price << "\n";
        pMove = pMove->next;
    }
}

void deleyeByName(Node *headNode, char *bookName)//通过书名删除图书
{
    Node *posLeftNode = headNode;//左边一位指针
    Node *posNode = headNode->next;//指针
    while (posNode != NULL && strcmp(posNode->data.bookTitle, bookName)) //指针不为空并且没找到特定书籍
    {
        posLeftNode = posNode;
        posNode = posNode->next;
    }
    if (posNode == NULL) //处理空指针的情况
    {
        cout << "未找到相关书籍！\n";
        return;
    } else {
        std::cout << "删除成功!!!\n";
        posLeftNode->next = posNode->next;
        posNode = NULL;
        free(posNode);    //释放内存
    }
    //saveInfoToFile("bookinfo.txt", list_head);
}

Node *searchByName(struct Node *headNode, char *bookName) //寻找相关书籍
{
    Node *posNode = headNode->next;//头节点未储存信息
    while (posNode != NULL && strcmp(posNode->data.bookTitle, bookName)) {
        posNode = posNode->next;
    }
    return posNode;
}

Node *searchByISBN(struct Node *headNode, int bookISBN) //根据ISBN值寻找相关书籍
{
    Node *posNode = headNode->next;
    while (posNode != NULL && posNode->data.bookISBN != bookISBN) {
        posNode = posNode->next;
    }
    return posNode;
}

void changeData() //进行改变书籍内容的操作
{
    int tempDataNum = 0;//储存输入的值
    cout << "\n请输入要改的ISBN号\n";
    cin >> tempDataNum;
    fixData(list_head, tempDataNum);
}

void bubbleSortList(Node *headNode) //按价格进行冒泡排序
{
    for (Node *p = headNode->next; p != NULL; p = p->next) {
        for (Node *q = headNode->next; q->next != NULL; q = q->next) {
            if (q->data.price > q->next->data.price) {
                BookData tempData = q->data;
                q->data = q->next->data;
                q->next->data = tempData;
            }
        }
    }
    printNode(headNode);
}

//文件操作
void saveInfoToFile(const char *fileName, Node *headNode)//写入
{
    FILE *fp = fopen(fileName, "w");
    Node *pMove = headNode->next;
    while (pMove != NULL) //储存内容
    {
        fprintf(fp, "%d\t%d\t%s\t%.1f\n", pMove->data.num, pMove->data.bookISBN, pMove->data.bookTitle,
                pMove->data.price);
        pMove = pMove->next;
    }
    fclose(fp);//关闭文件
}

void readInfoFromFile(const char *fileName)//文件读操作
{
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) //如果没有的话创建文件
    {
        fp = fopen(fileName, "w+");
    }
    BookData tempData;//用一个容器来读取文件内容
    tempData.dataInitialize();
    while (fscanf(fp, "%d\t%d\t%s\t%f\n", &tempData.num, &tempData.bookISBN, tempData.bookTitle, &tempData.price) !=
           EOF) //读文件操作，读入指针
    {
        insertNode(list_head, tempData);
    }
    fclose(fp);
}

void fixData(Node *headNode, int bookISBN)//根据ISBN修改内容
{
    Node *posNode = searchByISBN(headNode, bookISBN);
    int tempnum = 0;
    cout << "\n1.书名\n";
    cout << "2.书的数量\n";
    cout << "3.书的单价\n";
    cout << "请输入想要修改的内容：\n";
    cin >> tempnum;
    if (tempnum == 1) //switch会出BUG，用了if语句
    {
        cout << "请输入修改后的书名：\n";
        char tempTitle[20];
        cin >> tempTitle;
        memcpy(tempTitle, posNode->data.bookTitle, sizeof(tempTitle));
    } else if (tempnum == 2) {
        cout << "请输入修改后的数量：\n";
        int tempDataNum = 0;
        cin >> tempDataNum;
        posNode->data.num = tempDataNum;
    } else if (tempnum = 3) {
        cout << "请输入修改后的单价：\n";
        int tempPrice = 0;
        cin >> tempPrice;
        posNode->data.price = tempPrice;
    } else {
        cout << "输入内容无效！\n";
    }

    //saveInfoToFile("bookinfo.txt", list_head);
}

//int readInfoFromFile(const char *fileName) {
//    FILE *fp = fopen(fileName, "r");
//    if (fp == NULL) {
//        // 文件不存在，尝试创建文件
//        fp = fopen(fileName, "w+");
//        if (fp == NULL) {
//            perror("Failed to open file");
//            return -1; // 返回错误代码
//        }
//        fclose(fp); // 关闭文件，因为我们只是想要创建它
//        fp = fopen(fileName, "r"); // 重新以读取模式打开
//        if (fp == NULL) {
//            perror("Failed to reopen file");
//            return -1; // 返回错误代码
//        }
//    }
//
//    BookData tempData;
//    tempData.dataInitialize();
//    while (fscanf(fp, "%d\t%d\t%s\t%f\n", &tempData.num, &tempData.bookISBN, tempData.bookTitle, &tempData.price) == 4) {
//        insertNode(list_head, tempData);
//    }
//
//    fclose(fp);
//    return 0; // 成功
//}




void mainmenu()                           //主菜单界面设计
{
    cout << "----------------------------\n";
    cout << "\t图书管理系统\n";
    cout << "\t  主菜单\n";
    cout << "   1.收银模块\n";
    cout << "   2.书库管理模块\n";
    cout << "   3.报表模块\n";
    cout << "   4.退出系统\n\n";
    cout << "   输入选择:\n";
    cout << "   请输入1~4之间的数。\n";
    cout << "----------------------------\n";
}

//书库操作菜单
void bookstore_menu() {
    cout << "\t书库管理模块\n\n";
    cout << "1.查找某本书的信息\n";
    cout << "2.增加书\n";
    cout << "3.修改书的信息\n";
    cout << "4.删除书\n";
    cout << "5.返回到主菜单\n\n";
    cout << "输入选择\n";
    int key_num = 0;//输入数字储存
    cin >> key_num;
    //switch语句会出BUG
    if (key_num == 1) //查找图书信息
    {
        char tempTitle_search[20];//新建临时的储存点储存名称
        Node *tempNode_search;
        cout << "请输入查询书籍名称：\n";
        cin >> tempTitle_search;
        tempNode_search = searchByName(list_head, tempTitle_search);
        system("cls");
        if (tempNode_search == NULL) {
            cout << "未查询到该书籍！\n";
        } else {
            cout << "\t图书管理系统\n";
            cout << "\t 书的资料\n";
            cout << "ISBN号:\t" << tempNode_search->data.bookISBN << "\n";
            cout << "书名:\t" << tempNode_search->data.bookTitle << "\n";
            cout << "库存量:\t" << tempNode_search->data.num << "\n";
            cout << "零售价:\t" << tempNode_search->data.price << "\n";
        }
    } else if (key_num == 2) //增加书
    {
        BookData tempdata;
        tempdata.inputData();
        insertNode(list_head, tempdata);
        saveInfoToFile("bookinfo.txt", list_head);
        cout << "输入成功！\n";

    } else if (key_num == 3) //修改属的信息
    {
        changeData();
    } else if (key_num == 4) //删除书
    {
        char tempTitle_delete[20];//新建临时的储存点储存名称
        cout << "请输入删除书籍名称：\n";
        cin >> tempTitle_delete;
        deleyeByName(list_head, tempTitle_delete);
    } else if (key_num == 5) //返回到主菜单
    {
        return;
    } else //处理异常情况
    {
        cout << "ERROR!!!\n请重新输入！";
        system("pause");
        system("cls");
        bookstore_menu();
    }


}

void report_menu() //报表的菜单
{
    cout << "\t图书管理系统\n";
    cout << "\t  报表模块\n";
    cout << "1.书库列表\n";
    cout << "2.零售价列表\n";
    cout << "3.书价格排序列表\n";
    cout << "4.返回到主菜单\n\n";
    cout << "输入选择：";
    int tempnum = 0;
    cin >> tempnum;
    switch (tempnum) {
        case 1://书库列表
            system("cls");
            printNode(list_head);
            break;
        case 3://书库按价格排序
            system("cls");
            bubbleSortList(list_head);
            break;
        case 4://返回主菜单
            return;
        case 2://零售价列表
            system("cls");
            Node *pMove = list_head->next;//用一个移动的指针输出
            cout << "\t前台销售模块\n";
            cout << "日期：\n";
            cout << "ISBN号\t书名\t单价\t\n";
            while (pMove != NULL)//移动输出
            {
                cout << pMove->data.bookISBN << "\t" << pMove->data.bookTitle << "\t"
                     << pMove->data.price << "\n";
                pMove = pMove->next;
            }
            break;
    }
}


Node *cashierPrint() //对于多个数据储存于打印
{
    system("cls");
    cout << "请输入选购书籍的ISBN号：\n";
    Node *seachNode = NULL;//
    int tempBookISBN;
    int tempnum = 0;
    cin >> tempBookISBN;
    seachNode = searchByISBN(list_head, tempBookISBN);
    if (seachNode == NULL) {
        cout << "您输入了无效ISBN码！请再次输入！\n";
        cashierPrint();
    } else {
        cout << "请输入要购买的数量：";
        cin >> tempnum;
        cout << "\n";
        if (tempnum > seachNode->data.num) {
            cout << "没有这么多书！\n";
            system("pause");
            return cashierPrint();
        } else {
            seachNode->data.cashiernum = tempnum;
            return seachNode;
        }
    }
}

int cashierdecide() //此模块由于重复询问是否还买书
{
    cout << "\n您还要继续采购吗？[y/n] ";
    char temp_decide[10];//字符串储存输入的Y与N
    cin >> temp_decide;
    if (strcmp(temp_decide, "y")) {
        return 1;
    } else {
        return 0;
    }
}

void cashiermenu() //收银菜单
{
    Node *tempBox[10];//用数组储存购买多个书籍
    double priceSumPrice = 0;//总计的书的价格
    int tempRemem = 0;//计数器，第多少本书
    while (true) {
        tempBox[tempRemem] = cashierPrint();//传入书记的指针
        tempRemem++;
        if (cashierdecide()) {
            break;
        } else
            continue;
    }
    system("cls");
    cout << "\t前台销售模块\n";
    cout << "日期：\n";
    cout << "数量\tISBN号\t书名\t单价\t金额\n";
    for (int i = 0; i < tempRemem; i++) //输出以及出售完后书籍信息的更改
    {
        cout << tempBox[i]->data.cashiernum << "\t" << tempBox[i]->data.bookISBN << "\t" << tempBox[i]->data.bookTitle
             << "\t"<< tempBox[i]->data.price << "\t" << tempBox[i]->data.cashiernum * tempBox[i]->data.price << "\n";
        tempBox[i]->data.num = tempBox[i]->data.num - tempBox[i]->data.cashiernum;
        priceSumPrice = priceSumPrice + (double) tempBox[i]->data.price * (double) tempBox[i]->data.cashiernum;
        tempBox[i]->data.cashiernum = 0;
    }
    cout << "-------------------------------------\n";
    printf("销售合计：RMB %.2lf\n", priceSumPrice);//输出相关信息
    printf("零售税：RMB %.2lf\n", priceSumPrice * 0.06);
    printf("应付金额：RMB %.2lf\n\n", priceSumPrice * 1.06);

}


void keyDown_main()                       //用户在主界面输入数字后的反应
{
    int userKey = 0;
    cin >> userKey;                       //用户输入信息
    switch (userKey)                      //输入数字
    {
        case 1://收银模块
            system("cls");
            cashiermenu();
            break;
        case 2://图书操作模块
            system("cls");
            bookstore_menu();
            break;
        case 3://报表模块
            system("cls");
            report_menu();
            break;
        case 4:
            cout << "退出系统\n";
            cout << "退出系统成功！\n";
            system("pause");     //显示信息
            exit(0);                 //退出系统，返回值为0
            break;
        default:
            cout << "输入数字无效,请重新输入!\n";
            keyDown_main();                //再次输入
    }
}


int main() {
    list_head = CreatHead();//初始化头节点
    readInfoFromFile("bookinfo.txt");
    while (true) {
        mainmenu();
        keyDown_main();
        saveInfoToFile("bookinfo.txt", list_head);
        system("pause");
        system("cls");            //清空后在打印
    }
    system("pause");
    return 0;
}




