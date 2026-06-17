#if 1
// double linked list
// 호텔 객실 관리 프로그램

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ============================================================
// 자료 define
// ============================================================
typedef struct {
    int  year;
    int  month;
    int  day;
    int  hour;
    int  minute;
} _stDate;

typedef struct _node {
    int    roomno;          // 객실번호
    char   name[20];        // 예약자 정보 ...
    char   phone[40];       
    double price;   
    char   address[40];
    _stDate enter_date;     // 입실 시간
    _stDate exit_date;      // 퇴실 시간
    struct _node* prev;     // 앞 노드
    struct _node* next;     // 뒤 노드
} t_node;

typedef struct {
    t_node* head;           // 첫 예약
    t_node* tail;           // 마지막 예약
    int     num_of_data;    // 예약 건수
} t_list;

// ============================================================
// 전역 변수
// ============================================================
FILE* filep;
t_list room_list = { NULL, NULL, 0 };

#define FILENAME "reservation.txt"

// ============================================================
// 함수 선언
// ============================================================
void   read_line(char* buf, int size);
void   room_manager(void);
void   room_reserve(void);
void   room_exit_proc(void);
void   room_modify(void);
void   room_lookup(void);
void   room_lookup_all(void);
void   save_to_file(void);
void   load_from_file(void);
t_node* find_room(int roomno);
void   list_add_back(t_node* newnode);
void   list_delete(t_node* target);
void   print_date(const char* label, _stDate* d);
void   input_date(const char* prompt, _stDate* d);
void   print_separator(void);
void   print_all_header(void);
void   print_node_row(t_node* tp);
void   print_node_detail(t_node* tp);

// ============================================================
// main
// ============================================================
int main(void)
{
    int choice;

    // 파일에서 기존 예약 데이터 로드
    load_from_file();

    while (1)
    {
        room_manager();
        printf("Select: ");
        { char _b[32]; read_line(_b, sizeof(_b)); sscanf(_b, "%d", &choice); }
        printf("\n");

        switch (choice)
        {
        case 1: room_reserve();    break;
        case 2: room_exit_proc();  break;
        case 3: room_modify();     break;
        case 4: room_lookup();     break;
        case 5: room_lookup_all(); break;
        case 9:
        {
            char yn;
            printf("--------------< 종료 >---------------------\n");
            printf("  메뉴를 종료합니다.\n");
            printf("  확인 (y/n): ");
            { char _b[4]; read_line(_b, sizeof(_b)); yn = _b[0]; }
            if (yn == 'y' || yn == 'Y')
            {
                save_to_file();
                printf("  예약 정보가 %s 에 저장되었습니다.\n", FILENAME);

                // 저장된 내용 화면 출력
                room_lookup_all();

                // 메모리 해제
                t_node* tp = room_list.head;
                while (tp)
                {
                    t_node* next = tp->next;
                    free(tp);
                    tp = next;
                }
                return 0;
            }
            break;
        }
        default:
            printf("  잘못된 선택입니다.\n\n");
        }
    }
    return 0;
}

// ============================================================
// 메뉴 출력
// ============================================================
void room_manager(void)
{
    printf("------------------ < 객실 관리 >----------------------\n");
    printf("  1. 입력(예약)\n");
    printf("  2. 삭제(퇴실)\n");
    printf("  3. 수정(예약내역수정)\n");
    printf("  4. 조회(개별조회)\n");
    printf("  5. 전체조회(예약자 전체조회)\n\n");
    printf("  9. 종료\n");
    printf("------------------------------------------------------\n");
}

// ============================================================
// 1. 입력(예약)
// ============================================================
void room_reserve(void)
{
    int    roomno;
    char   name[20], phone[40], address[40];
    double price;
    _stDate enter, exit_d;
    char   yn;

    printf("--------------< 입력 예약 >---------------------\n");
    printf("  roomno  : "); { char _b[32]; read_line(_b, sizeof(_b)); sscanf(_b, "%d", &roomno); }
    printf("  name    : "); read_line(name, sizeof(name));
    printf("  phoneno : "); read_line(phone, sizeof(phone));
    printf("  요금    : "); { char _b[32]; read_line(_b, sizeof(_b)); sscanf(_b, "%lf", &price); }
    printf("  주소    : "); read_line(address, sizeof(address));
    input_date("  입실예정시각", &enter);
    input_date("  퇴실예정시각", &exit_d);

    printf("  확인 (y/n) : "); { char _b[4]; read_line(_b, sizeof(_b)); yn = _b[0]; }

    if (yn != 'y' && yn != 'Y')
    {
        printf("  예약이 취소되었습니다.\n\n");
        return;
    }

    // 중복 체크
    if (find_room(roomno))                                  // find_room 함수로 같은 객실 번호 탐색
    {
        printf("  이미 예약된 객실 입니다.\n\n");           
        return;                                              
    }

    // 노드 생성
    t_node* newnode = (t_node*)malloc(sizeof(t_node));
    if (!newnode) { printf("  메모리 할당 실패\n"); return; }

    newnode->roomno = roomno;
    newnode->price = price;
    newnode->enter_date = enter;
    newnode->exit_date = exit_d;
    newnode->prev = newnode->next = NULL;
    strcpy(newnode->name, name);
    strcpy(newnode->phone, phone);
    strcpy(newnode->address, address);

    list_add_back(newnode);
    printf("  정상 예약 되었습니다.\n\n");
}

// ============================================================
// 2. 삭제(퇴실)
// ============================================================
void room_exit_proc(void)
{
    int  roomno;
    char name[20], phone[40], yn;

    printf("--------------< 삭제(퇴실) >---------------------\n");
    printf("  roomno  : "); { char _b[32]; read_line(_b, sizeof(_b)); sscanf(_b, "%d", &roomno); }
    printf("  name    : "); read_line(name, sizeof(name));
    printf("  phoneno : "); read_line(phone, sizeof(phone));
    printf("  확인 (y/n) : "); { char _b[4]; read_line(_b, sizeof(_b)); yn = _b[0]; }

    if (yn != 'y' && yn != 'Y')
    {
        printf("  퇴실이 취소되었습니다.\n\n");
        return;
    }

    t_node* tp = find_room(roomno);
    if (!tp)
    {
        printf("  없는 객실 입니다.\n\n");
        return;
    }

    // 이름 + 전화번호도 일치 확인
    if (strcmp(tp->name, name) || strcmp(tp->phone, phone))
    {
        printf("  예약자 정보가 일치하지 않습니다.\n\n");
        return;
    }

    list_delete(tp);
    free(tp);
    printf("  퇴실처리 되었습니다.\n\n");
}

// ============================================================
// 3. 수정(예약내역수정)
// ============================================================
void room_modify(void)
{
    int    roomno;
    char   name[20], phone[40], address[40];
    double price;
    _stDate enter, exit_d;
    char   yn;

    printf("--------------< 수정 예약 >---------------------\n");
    printf("  roomno  : "); { char _b[32]; read_line(_b, sizeof(_b)); sscanf(_b, "%d", &roomno); }
        
    t_node* tp = find_room(roomno);           
    if (!tp)
    {
        printf("  없는 객실 입니다.\n\n");
        return;
    }

    printf("  name    : "); read_line(name, sizeof(name));
    printf("  phoneno : "); read_line(phone, sizeof(phone));
    printf("  요금    : "); { char _b[32]; read_line(_b, sizeof(_b)); sscanf(_b, "%lf", &price); }
    printf("  주소    : "); read_line(address, sizeof(address));
    input_date("  입실예정시각", &enter);
    input_date("  퇴실예정시각", &exit_d);

    printf("  확인 (y/n) : "); { char _b[4]; read_line(_b, sizeof(_b)); yn = _b[0]; }

    if (yn != 'y' && yn != 'Y')
    {
        printf("  수정이 취소되었습니다.\n\n");
        return;
    }

    tp->price = price;
    tp->enter_date = enter;
    tp->exit_date = exit_d;
    strcpy(tp->name, name);
    strcpy(tp->phone, phone);
    strcpy(tp->address, address);

    printf("  정상 수정 되었습니다.\n\n");
}

// ============================================================
// 4. 조회(개별조회)
// ============================================================
void room_lookup(void)
{
    int roomno;
    printf("--------------< 조회(개별조회) >---------------------\n");
    printf("  roomno 입력: "); { char _b[32]; read_line(_b, sizeof(_b)); sscanf(_b, "%d", &roomno); }

    t_node* tp = find_room(roomno);
    if (!tp)
    {
        printf("  없는 객실 번호 입니다.\n\n");
        return;
    }

    print_node_detail(tp);
}

// ============================================================
// 5. 전체조회
// ============================================================
void room_lookup_all(void)
{
    if (room_list.num_of_data == 0)
    {
        printf("  예약된 객실이 없습니다.\n\n");
        return;
    }

    print_all_header();

    t_node* tp = room_list.head;
    while (tp)
    {
        print_node_row(tp);
        tp = tp->next;
    }
    printf("===================================================\n\n");
}

// ============================================================
// 파일 저장
// ============================================================
void save_to_file(void)
{
    filep = fopen(FILENAME, "wb");
    if (!filep) { fprintf(stderr, "파일 저장 실패!\n"); return; }

    // 노드 수 먼저 저장
    fwrite(&room_list.num_of_data, sizeof(int), 1, filep);

    t_node* tp = room_list.head;
    while (tp)
    {
        // prev/next 포인터 제외한 데이터만 저장
        // roomno ~ exit_date 까지만 쓴다
        size_t data_size = sizeof(t_node) - sizeof(struct _node*) * 2;
        fwrite(tp, 1, data_size, filep);
        tp = tp->next;
    }
    fclose(filep);
}

// ============================================================
// 파일 로드
// ============================================================
void load_from_file(void)
{
    filep = fopen(FILENAME, "rb");
    if (!filep) return;   // 파일 없으면 그냥 통과

    int count = 0;
    if (!fread(&count, sizeof(int), 1, filep)) { fclose(filep); return; }

    size_t data_size = sizeof(t_node) - sizeof(struct _node*) * 2;

    for (int i = 0; i < count; i++)
    {
        t_node* newnode = (t_node*)malloc(sizeof(t_node));
        if (!newnode) break;

        newnode->prev = newnode->next = NULL;

        if (!fread(newnode, 1, data_size, filep))
        {
            free(newnode);
            break;
        }
        list_add_back(newnode);
    }
    fclose(filep);
    printf("  %d 건의 예약 정보를 불러왔습니다.\n\n", room_list.num_of_data);
}

// ============================================================
// 이중 연결 리스트 유틸
// ============================================================
void list_add_back(t_node* newnode)
{
    if (!room_list.head)
    {
        room_list.head = room_list.tail = newnode;
        newnode->prev = newnode->next = NULL;
    }
    else
    {
        room_list.tail->next = newnode;
        newnode->prev = room_list.tail;
        newnode->next = NULL;
        room_list.tail = newnode;
    }
    room_list.num_of_data++;
}

void list_delete(t_node* target)
{
    if (target->prev) target->prev->next = target->next;
    else              room_list.head = target->next;

    if (target->next) target->next->prev = target->prev;
    else              room_list.tail = target->prev;

    room_list.num_of_data--;
}

t_node* find_room(int roomno)
{
    t_node* tp = room_list.head;
    while (tp)
    {
        if (tp->roomno == roomno) return tp;
        tp = tp->next;
    }
    return NULL;
}

// ============================================================
// 한 줄 읽기 (fgets + sscanf 로 버퍼 문제 원천 차단)
// ============================================================
void read_line(char* buf, int size)
{
    if (fgets(buf, size, stdin))
    {
        // 끝에 붙은 '\n' 제거
        int len = (int)strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') buf[len - 1] = '\0';
    }
}

// ============================================================
// 출력 헬퍼
// ============================================================
void input_date(const char* prompt, _stDate* d)
{
    char buf[64];
    while (1)
    {
        printf("  %s (YYYY-MM-DD HH:MM): ", prompt);
        read_line(buf, sizeof(buf));
        if (sscanf(buf, "%d-%d-%d %d:%d",
            &d->year, &d->month, &d->day, &d->hour, &d->minute) == 5)
            break;
        printf("  형식이 맞지 않습니다. 예) 2026-06-05 18:00\n");
    }
}

void print_node_detail(t_node* tp)
{
    printf("  roomno  : %d\n", tp->roomno);
    printf("  name    : %s\n", tp->name);
    printf("  phoneno : %s\n", tp->phone);
    printf("  요금    : %.0f\n", tp->price);
    printf("  주소    : %s\n", tp->address);
    printf("  입실    : %04d-%02d-%02d %02d:%02d\n",
        tp->enter_date.year, tp->enter_date.month, tp->enter_date.day,
        tp->enter_date.hour, tp->enter_date.minute);
    printf("  퇴실예정: %04d-%02d-%02d %02d:%02d\n\n",
        tp->exit_date.year, tp->exit_date.month, tp->exit_date.day,
        tp->exit_date.hour, tp->exit_date.minute);
}

void print_all_header(void)
{
    printf("\n----------------------------------< 전체조회(예약자 전체조회) >--------------------------------\n");
    printf("  %-6s  %-10s  %-15s  %8s  %-12s  %-17s  %-17s\n",
        "roomno", "name", "phoneno", "요금", "주소", "입실", "퇴실");
    printf("  %-6s  %-10s  %-15s  %8s  %-12s  %-17s  %-17s\n",
        "------", "----------", "---------------", "--------", "------------",
        "-----------------", "-----------------");
}

void print_node_row(t_node* tp)
{
    char enter_buf[20], exit_buf[20];
    snprintf(enter_buf, sizeof(enter_buf), "%04d-%02d-%02d %02d:%02d",
        tp->enter_date.year, tp->enter_date.month, tp->enter_date.day,
        tp->enter_date.hour, tp->enter_date.minute);
    snprintf(exit_buf, sizeof(exit_buf), "%04d-%02d-%02d %02d:%02d",
        tp->exit_date.year, tp->exit_date.month, tp->exit_date.day,
        tp->exit_date.hour, tp->exit_date.minute);

    printf("  %-6d  %-10s  %-15s  %8.0f  %-12s  %-17s  %-17s\n",
        tp->roomno, tp->name, tp->phone, tp->price,
        tp->address, enter_buf, exit_buf);
}
#endif