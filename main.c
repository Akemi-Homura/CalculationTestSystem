# include <stdio.h>
# include <stdlib.h>
# include <curses.h>
# include <string.h>

# define MAX(a,b) ((a>b?a:b))

// 难度
int complexity;
// 是否带负数
int has_negative;
// 是否带小数
int has_float;
// 运算数个数
int operator_num;
// 是否带括号
int has_brace;
// 题型 -- 填空，判断，选择
enum problem_type {
    FILL, JUDGE, CHOOSE
};

// 题型
int type;
// 题量
int problem_num;

// 记录结果的结构体
struct TestRecord {
    // 题目
    char text[20];
    // 用户答案
    char user_input[20];
    // 正确答案
    char ans[20];
    // 分析
    int is_correct;
};

// 测试记录数组
struct TestRecord *record;

// 显示游戏开始信息
void display_gamestart();

// 用户选择
void get_options();

// 获得难度
void get_complexity();

// 获得是否带负数
void get_has_negative();

// 获得是否带小数
void get_has_float();

// 获得运算数个数
void get_operator_num();

// 获得题型
void get_problem_type();

// 获得题量
void get_problem_num();

void input_error();

// 获得是否带括号
void get_has_brace();

void display_choice(const char** choices,int num);

// 生成单个题目，并保存测试结果到参数record中
void test_single_problem(struct TestRecord *record);

// 保存记录
void save_record();

void start_test();

int main() {
    // 获取用户选择
    get_options();

    // 生成测试记录数组
    record = (struct TestRecord *) malloc(problem_num * sizeof(struct TestRecord));

    // 开始测试
    /*  start_test(); */

    // 保存测试记录
    /*  save_record(); */

    // 释放内存
    /*  free(record); */
    return 0;
}

void get_options() {
    get_complexity();
    get_has_negative();
    get_has_float();
    get_has_brace();
    get_problem_type();
    get_operator_num();
    get_problem_num();
}

void get_complexity() {
    printf("请输入难度(10, 100, 1000): ");
    scanf("%d", &complexity);
    printf("\n");
}

void get_has_negative() {
    printf("是否带负数(Y/N)：");
    char t[2];
    scanf("%s",t);
    if(t[0] == 'Y' || t[0] == 'y'){
        has_negative = 1;
    }else if (t[0] == 'N' || t[0] == 'n'){
        has_negative = 0;
    }else{
        input_error();
    }
    printf("\n");
}

void get_has_float() {
    printf("是否带小数(Y/N)：");
    char t[2];
    scanf("%s",t);
    if(t[0] == 'Y'){
        has_float = 1;
    }else if (t[0] == 'N'){
        has_float = 0;
    }else{
        input_error();
    }
    printf("\n");
}

void get_has_brace(){
    printf("是否带括号(Y/N): ");
    char t[2];
    scanf("%s",t);
    if(t[0] == 'Y' || t[0] == 'y'){
        has_brace = 1;
    }else if (t[0] == 'N' || t[0] == 'n'){
        has_brace = 0;
    }else{
        input_error();
    }
    printf("\n");
}

void get_operator_num() {
    printf("请输入运算数个数：");
    scanf("%d",&operator_num);
    printf("\n");
}

void get_problem_type() {
    printf("请输入题目类型(0:填写结果, 1:对错判断 ,2: 选择题): ");
    int t;
    scanf("%d\n",&t);
    switch(t){
        case 0:
            type = FILL;
            break;
        case 1:
            type = JUDGE;
            break;
        case 2:
            type = CHOOSE;
            break;
        default:
            input_error();
    }
    printf("\n");
}

void get_problem_num(){
    printf("输入题目数量: ");
    scanf("%d", &problem_num);
    system("clear");
}

void input_error() {
    fprintf(stderr, "input error");
    exit(1);
}

void test_single_problem(struct TestRecord* record){
}

void start_test() {
    for(int i=0;i<problem_num;i++){
        test_single_problem(record + i);
    }
}
