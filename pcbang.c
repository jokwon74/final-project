//PC 관리 프로그램 

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME    20 //최대 이름 길이
#define MAX_FOOD_NUM 5//pc 수
typedef struct {//pc 구조체 정의
    char name[MAX_NAME + 1];//이름
    int num; //번호
    int charge; // 요금
    int sale[MAX_FOOD_NUM];// 음식 가격
}PC;

const char* food[MAX_FOOD_NUM] = { "라면", "떡꼬치", "볶음밥", "콜라", "커피" }; // 음식 리스트

#define MAX_PC_NUM 10// 최대 PC 수

PC users[MAX_PC_NUM];

void clear();
void Run();
int main(void)
{

    clear();//데이터 초기화
    Run();

    return 0;
}


void clear()
{
    int i = 0;
    int s = 0;

    for (i = 0; i < MAX_PC_NUM; i++)
    {
        for (s = 0; s < MAX_FOOD_NUM; s++)
        {
            users[i].sale[s] = -1;
        }
    }
}

int SelectMenu();//메뉴 출력 및 선택
void PC_SELECT();//pc선택(PC정보입력
void TURNOFF_PC();//pc 강제종료(데이터삭제)
void FindPC();// pc검색
void MONEY();//판매관리
void ADD_TIME();//시간추가
void ListPC();//Pc목록

void Run()
{
    int key = 0;
    while ((key = SelectMenu()) != 0)//선택한 메뉴가 0이 아니면 반복
    {
        switch (key)//선택한 키에 따라 기능 수행
        {
        case 1: PC_SELECT(); break;
        case 2: TURNOFF_PC(); break;
        case 3: FindPC(); break;
        case 4: MONEY(); break;
        case 5: ListPC(); break;
        default: printf("잘못 선택하였습니다.\n"); break;
        }
    }
    printf("프로그램 종료\n");
}

int SelectMenu()
{
    int key = 0;
    printf("PC 관리 프로그램 0:종료\n");
    printf("1: PC 정보 입력 2: PC종료 3: PC검색 4: 판매관리 5: 사용중인 PC \n");
    scanf_s("%d", &key);
    return key;
}

int IsAvailNum(int num);//유효한 번호인지 판별
void PC_SELECT()
{
    printf("마스크를 착용해주세요.\n");
    printf("-------------------------\n");

    int num = 0;
    PC* user = 0;
    int s = 0;

    printf("선택할 PC 번호(1~%d):", MAX_PC_NUM);
    scanf_s("%d", &num);

    if (IsAvailNum(num) == 0)//유효한 번호가 아닐 때
    {
        printf("없는 PC번호입니다.\n");
        return;
    }

    if (users[num - 1].num)//이미 번호를 설정한 상태일 때
    {
        printf("이미 사용중입니다.\n");
        return;
    }

    user = users + (num - 1);
    user->num = num;
    printf("이름: ");
    scanf_s("%s", user->name, sizeof(user->name));

    user = users + (num - 1);
    user->num = num;
    printf("1000원단위로 입력해주세요.1000원당 1시간입니다   요금: ");
    scanf_s("%d", &user->charge, sizeof(user->charge));

    printf("주문하실 음식에 맞는 가격을 입력해주세요.\n");
    printf("주문하지 않으실 음식에는 0을 입력해주세요.\n");
    printf("라면 : 3000원\n");
    printf("떡꼬치 : 2000원\n");
    printf("볶음밥 : 4500원\n");
    printf("콜라 : 1500원\n");
    printf("커피 : 1800원\n");
    printf("-------------------------\n");
    for (s = 0; s < MAX_FOOD_NUM; s++)
    {
        printf("%s 가격:", food[s]);
        scanf_s("%d", user->sale + s);
    }
}
int IsAvailNum(int num)
{
    return (num >= 1) && (num <= MAX_PC_NUM);
}
void TURNOFF_PC()
{
    int num = 0;
    PC* user = 0;
    int s = 0;

    printf("종료할 PC번호(1~%d): ", MAX_PC_NUM);
    scanf_s("%d", &num);

    if (IsAvailNum(num) == 0)//유효한 번호가 아닐 때
    {
        printf("유효하지 않은 PC번호입니다.\n");
        return;
    }

    if (users[num - 1].num == 0)//번호를 설정한 상태가 아닐 때
    {
        printf("사용하지 않는 PC입니다.\n");
        return;
    }

    user = users + (num - 1);
    strcpy_s(user->name, sizeof(user->name), "");
    user->num = 0;

    for (s = 0; s < MAX_FOOD_NUM; s++)
    {
        user->sale[s] = -1;
    }

    printf("종료하였습니다.\n");
}
void ViewPCData(PC* user);
void FindPC()
{
    int num = 0;
    PC* user = 0;
    int s = 0;

    printf("검색할 PC 번호(1~%d): ", MAX_PC_NUM);
    scanf_s("%d", &num);

    if (IsAvailNum(num) == 0)//유효한 번호가 아닐 때
    {
        printf("유효하지 않은 PC번호입니다.\n");
        return;
    }

    if (users[num - 1].num == 0)//번호를 설정한 상태가 아닐 때
    {
        printf("사용하지 않는 PC입니다.\n");
        return;
    }

    user = users + (num - 1);
    ViewPCData(user);
}
void ViewPCData(PC* user)
{
    int time = (user->charge) / 1000;

    printf("%4d %10s %d시간\n", user->num, user->name, time);
}
void ViewPCsale(PC* user);
void MONEY()
{
    int num = 0;
    PC* user = 0;
    int s = 0;

    printf("검색할 PC 번호(1~%d): ", MAX_PC_NUM);
    scanf_s("%d", &num);

    if (IsAvailNum(num) == 0)//유효한 번호가 아닐 때
    {
        printf("유효하지 않은 PC번호입니다.\n");
        return;
    }

    if (users[num - 1].num == 0)//번호를 설정한 상태가 아닐 때
    {
        printf("사용하지 않는 PC입니다.\n");
        return;
    }

    user = users + (num - 1);
    ViewPCsale(user);
}
void ViewPCsale(PC* user)
{
    int s = 0;
    int sum = 0;

    for (s = 0; s < MAX_FOOD_NUM; s++)
    {
        sum = sum + user->sale[s];
    }
    printf("총 금액은 %d입니다.\n ", sum + user->charge);

}
void ListPC()
{
    int i = 0;
    int s = 0;

    for (i = 0; i < MAX_PC_NUM; i++)
    {
        if (users[i].num)
        {
            ViewPCData(users + i);
            printf("\n");
            ViewPCsale(users + i);
        }
    }
}
