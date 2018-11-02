# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include <time.h>

// 难度
int complexity;
// 是否带负数
int has_negative;
// 是否带小数
int has_double;
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
    char text[100];
    // 用户答案
    char user_input[20];
    // 正确答案
    char ans[20];
    // 选项记录
    char choices[100];
    int index;
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
void get_has_double();

// 获得运算数个数
void get_operator_num();

// 获得题型
void get_problem_type();

// 获得题量
void get_problem_num();

// 生成题目和正确答案
void generate_title_and_res(char *text, char *res);

// 输入出错
void input_error();

// 获得是否带括号
void get_has_brace();

void display_choice(struct TestRecord *pRecord);

// 生成单个题目，并保存测试结果到参数record中
void test_single_problem(struct TestRecord *record);

// 保存记录
void save_record();

// 开始测试
void start_test();

// 分析用户输入
void analysis_res(struct TestRecord *pRecord);

// 展示题目给用户
void display_problem(struct TestRecord *pRecord);

// 交换两个浮点数
void swap(double *pA, double *pB);

// 随机声称用于运算的数字
void generate_number(char text[20]);

// 随机生成a~b之间的随机数
int random_int_range(int a, int b);

// 生成min～max之间的随机小数
double random_double_range(double min, double max);

// 去除小数末尾的0
void remove_last_zeros(char *text);

// 生成运算符+-*/
void generate_operator(char text[20]);

// 给计算式分配括号
void allocate_brace(int left_brace[20], int right_brace[20]);

// 生成题目
void evaluate_title(char text[100], char number[20][20], char ops[20][20], int left_brace[20], int right_brace[20]);

// 生成结果
void evaluate_res(char *res, char number[20][20], char ops[20][20], int left_brace[20], int right_brace[20]);

// 返回运算符优先级
int precedence(char op);

// 进行一次运算
double double_operation(double num1, double num2, char op);

// 生成选择题的选项
void generate_random_choice(double pChoices[4], double res);

// 展示判断题
void display_judge(struct TestRecord *pRecord);

// 将答题记录转换成字符串
void record_to_str(struct TestRecord record, char str[100]);

// 展示系统介绍
void show_introduction();

int main() {
    // 初始化随机数
    srand((unsigned int) time(NULL));
    // 获取用户选择
    get_options();

    // 展示系统介绍
    show_introduction();

    // 生成测试记录数组
    record = (struct TestRecord *) malloc(problem_num * sizeof(struct TestRecord));

    // 开始测试
    start_test();

    // 保存测试记录
    save_record();

    // 释放内存
    free(record);
    return 0;
}

void show_introduction() {
    char *msg[3];
    msg[CHOOSE] = strdup("选择题，请输入正确的选项");
    msg[JUDGE] = strdup("判断题，请输入T（正确）或F（错误）");
    msg[FILL] = strdup("填空题，请输入正确的答案，误差小于0.01");
    printf("\n%s\n\n", msg[type]);
}

void get_options() {
    // 获得复杂度
    get_complexity();
    // 获得是否有负数
    get_has_negative();
    // 获得是否有小数
    get_has_double();
    // 是否有括号
    get_has_brace();
    // 问题的类型（填空，判断，选择）
    get_problem_type();
    // 运算数的个数
    get_operator_num();
    // 题目个数
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
    scanf("%s", t);
    if (t[0] == 'Y' || t[0] == 'y') {
        has_negative = 1;
    } else if (t[0] == 'N' || t[0] == 'n') {
        has_negative = 0;
    } else {
        input_error();
    }
    printf("\n");
}

void get_has_double() {
    printf("是否带小数(Y/N)：");
    char t[2];
    scanf("%s", t);
    if (t[0] == 'Y' || t[0] == 'y') {
        has_double = 1;
    } else if (t[0] == 'N' || t[0] == 'n') {
        has_double = 0;
    } else {
        input_error();
    }
    printf("\n");
}

void get_has_brace() {
    printf("是否带括号(Y/N): ");
    char t[2];
    scanf("%s", t);
    if (t[0] == 'Y' || t[0] == 'y') {
        has_brace = 1;
    } else if (t[0] == 'N' || t[0] == 'n') {
        has_brace = 0;
    } else {
        input_error();
    }
    printf("\n");
}

void get_operator_num() {
    printf("请输入运算数个数：");
    scanf("%d", &operator_num);
    printf("\n");
}

void get_problem_type() {
    printf("请输入题目类型(0:填写结果, 1:对错判断 ,2: 选择题): ");
    int t;
    scanf("%d", &t);
    switch (t) {
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

void get_problem_num() {
    printf("输入题目数量: ");
    scanf("%d", &problem_num);
}

// 输入出错
void input_error() {
    fprintf(stderr, "input error");
    exit(1);
}

void test_single_problem(struct TestRecord *record) {
    // 生成测试题目和正确答案，保存在record中
    generate_title_and_res(record->text, record->ans);
    // 把问题展示给用户
    display_problem(record);
    // 获得用户的答案
    scanf("%s", record->user_input);
    // 分析用户回答是否正确
    analysis_res(record);
}

// 展示题目给用户
void display_problem(struct TestRecord *pRecord) {
    printf("%d. %s = ", pRecord->index, pRecord->text);
    if (type == CHOOSE) {
        printf("\n");
        display_choice(pRecord);
    } else if (type == JUDGE) {
        display_judge(pRecord);
    } else {
        printf("\n");
    }
    printf("Answer: ");
}

void display_judge(struct TestRecord *pRecord) {
    double choices[4];
    double res;
    sscanf(pRecord->ans, "%lf", &res);
    generate_random_choice(choices, res);
    int is_right_ans = rand() % 2;
    double display_choices = is_right_ans == 0 ? res : choices[rand() % 4];
    printf("%.2f\n", display_choices);
    memset(pRecord->choices, 0, 100);
    char text[40];
    sprintf(text, "%.2f\n", display_choices);
    strcat(pRecord->choices, text);
    *pRecord->ans = (is_right_ans == 0 ? 'T' : 'F');
    pRecord->ans[1] = '\0';
}

// 分析用户输入
void analysis_res(struct TestRecord *pRecord) {
    if (type == CHOOSE || type == JUDGE) {
        pRecord->is_correct = (strcmp(pRecord->user_input, pRecord->ans) == 0);
    } else {
        double a, b;
        sscanf(pRecord->user_input, "%lf", &a);
        sscanf(pRecord->ans, "%lf", &b);
        pRecord->is_correct = ((a - b) * (a - b) <= 0.0001);
    }

    if (pRecord->is_correct) {
        printf("Accept\n");
    } else {
        printf("Wrong\n");
    }
    printf("\n");
}

// 开始测试
void start_test() {
    for (int i = 0; i < problem_num; i++) {
        record[i].index = i + 1;
        test_single_problem(record + i);
    }
}

// 展示选择题的选项
void display_choice(struct TestRecord *pRecord) {
    /*
     * 随机生成4个选项，其中一个是正确答案
     */
    double res;
    sscanf(pRecord->ans, "%lf", &res);

    double choices[4];
    generate_random_choice(choices, res);
    int index = rand() % 4;
    choices[index] = res;

    /*
     * 打乱四个选项的顺序
     */
    int sw[4];
    for (int i = 0; i < 4; i++) {
        sw[i] = rand() % 4;
    }
    swap(&choices[sw[0]], &choices[sw[1]]);
    swap(&choices[sw[2]], &choices[sw[3]]);

    for (int i = 0; i < 4; i++) {
        if (choices[i] == res) {
            *pRecord->ans = 'A' + i;
            pRecord->ans[1] = '\0';
            break;
        }
    }

    /*
     * 按选择题的格式输出并把选项保存到record->choices中
     */
    memset(pRecord->choices, 0, 100);
    char text[50];
    strcat(pRecord->choices, "\n");
    for (int i = 0; i < 4; i++) {
        printf("%c. %.2f", 'A' + i, choices[i]);
        sprintf(text, "%c. %.2f", 'A' + i, choices[i]);
        strcat(pRecord->choices, text);
        if (i != 3) {
            printf("    ");
            strcat(pRecord->choices, "    ");
        } else {
            printf("\n");
            strcat(pRecord->choices, "\n");
        }
    }
}

// 生成4个选项
void generate_random_choice(double pChoices[4], double res) {
    pChoices[0] = res + (rand() % 5) + 1;
    pChoices[1] = res - (rand() % 5) - 1;
    pChoices[2] = res + (rand() % 10 + 1) * 1.0 / 10.0;
    pChoices[3] = res - (rand() % 10 + 1) * 1.0 / 10.0;
}

void swap(double *pA, double *pB) {
    double t = *pA;
    *pA = *pB;
    *pB = t;
}

// 生成题目和正确答案
void generate_title_and_res(char *text, char *res) {
    memset(text, 0, 100);
    memset(res, 0, 20);

    // 运算数
    char number[20][20];
    // 运算符
    char ops[20][20];
    // 每个运算符的左括号数量（一个数字可以有多个左括号）
    int left_brace[20];
    // 每个运算符的右括号数量（一个数字可以有多个右括号）
    int right_brace[20];

    // 生成operator_num个云算数和operator_num-1个运算符
    for (int i = 0; i < operator_num; i++) {
        generate_number(number[i]);
        if (i != operator_num - 1) generate_operator(ops[i]);
    }

    memset(left_brace, 0, sizeof(left_brace));
    memset(right_brace, 0, sizeof(right_brace));

    if (has_brace) {
        // 添加括号
        allocate_brace(left_brace, right_brace);
    }

    // 将题目转换为字符串
    evaluate_title(text, number, ops, left_brace, right_brace);
    // 计算出正确结果并保存在res中
    evaluate_res(res, number, ops, left_brace, right_brace);
}

// 生成结果
/*
 * 维护一个运算数栈和一个运算符栈，通过入栈和出栈操作分析出运算顺序并计算出结果
 */
void evaluate_res(char *res, char number[20][20], char ops[20][20], int left_brace[20], int right_brace[20]) {
    double num_stack[20];
    char op_stack[20];
    int op_top_pointer = 0;
    int num_top_pointer = 0;

    for (int i = 0; i < operator_num; i++) {
        // 特殊处理负数
        sscanf(number[i], number[i][1] == '-' ? "(%lf)" : "%lf", &num_stack[++num_top_pointer]);
        // 数字直接压进数字栈
        for (int j = 0; j < left_brace[i]; j++) {
            op_stack[++op_top_pointer] = '(';
        }
        // 处理右括号
        // 有右括号则从符号栈中弹出运算符并且从数字栈中弹出运算数进行计算直到遇到左括号
        for (int j = 0; j < right_brace[i]; j++) {
            while (op_stack[op_top_pointer] != '(') {
                double num = num_stack[num_top_pointer--];
                num_stack[num_top_pointer] = double_operation(num_stack[num_top_pointer], num,
                                                              op_stack[op_top_pointer--]);
            }
            // 弹出左括号
            --op_top_pointer;
        }

        /*
         * 处理运算符
         * 如果当前运算符的优先级小于栈顶运算符的优先级，则弹出栈顶的运算符和数字栈中的运算数进行计算直到栈顶运算符的优先级小于当前运算符
         * 最后将当前运算符压入栈中
         */
        if (i != operator_num - 1) {
            char tmp_op = ops[i][1];
            while (op_top_pointer != 0 && precedence(op_stack[op_top_pointer]) >= precedence(tmp_op) &&
                   op_stack[op_top_pointer] != '(') {
                double num = num_stack[num_top_pointer--];
                num_stack[num_top_pointer] = double_operation(num_stack[num_top_pointer], num,
                                                              op_stack[op_top_pointer--]);
            }
            // 压入当前运算符
            op_stack[++op_top_pointer] = tmp_op;
        }
    }

    // 如果符号栈中还有剩余的运算符，则则弹出栈顶的运算符和数字栈中的运算数进行计算直到符号栈为空
    while (op_top_pointer > 0) {
        double num = num_stack[num_top_pointer--];
        num_stack[num_top_pointer] = double_operation(num_stack[num_top_pointer], num,
                                                      op_stack[op_top_pointer--]);
    }
    sprintf(res, "%.2f", num_stack[1]);
}

// 进行一次运算
double double_operation(double num1, double num2, char op) {
    switch (op) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            return num1 / num2;
        default:
            fprintf(stderr, "Invalid op %c\n", op);
            exit(1);
    }
}

// 返回运算符优先级
int precedence(char op) {
    switch (op) {
        case ')':
            return 0;
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 3;
        case '(':
            return 4;
        default:
            fprintf(stderr, "Invalid operator %c\n", op);
            exit(1);
    }
}

// 生成题目
void evaluate_title(char text[100], char number[20][20], char ops[20][20], int left_brace[20], int right_brace[20]) {
    for (int i = 0; i < operator_num; i++) {
        for (int j = 0; j < left_brace[i]; j++) {
            strcat(text, "(");
        }
        strcat(text, number[i]);
        for (int j = 0; j < right_brace[i]; j++) {
            strcat(text, ")");
        }
        if (i != operator_num - 1)strcat(text, ops[i]);
    }
}

// 给计算式分配括号
/*
 * 先生成左括号数量，在分配到适合的位置上，并在适合位置上放上相匹配的右括号
 */
void allocate_brace(int left_brace[20], int right_brace[20]) {
    if (operator_num < 3) return;
    int total_brace = rand() % (operator_num / 3) + 1;
    int min_left_index = rand() % (operator_num - total_brace);
    int index = min_left_index;
    for (int i = 0; i < total_brace; i++) {
        left_brace[index]++;
        index++;
    }

    index = min_left_index + 1;
    for (int i = 0; i < total_brace;) {
        if (left_brace[index] > 0) {
            index++;
            continue;
        }
        right_brace[index]++;
        i++;
        if (index < operator_num - 1) index += rand() % 2;
    }
}

// 生成运算符+-*/
void generate_operator(char text[20]) {
    memset(text, 0, 20);
    static const char *ops = "+-*/";
    sprintf(text, " %c ", ops[rand() % 4]);
}

// 随机声称用于运算的数字
void generate_number(char text[20]) {
    memset(text, 0, 20);
    int min = has_negative ? -complexity : 1;
    if (has_double) {
        // 生成随机的浮点数
        double tmp = random_double_range(min, complexity);
        sprintf(text, tmp < 0 ? "(%.2f)" : "%.2f", tmp);
        remove_last_zeros(text);
    } else {
        int tmp = random_int_range(min, complexity);
        sprintf(text, tmp < 0 ? "(%d)" : "%d", tmp);
    }
}

// 去除小数末尾的0
void remove_last_zeros(char *text) {
    int len = (int) strlen(text);
    for (int i = len - 1; i > 0; i--) {
        if (text[i] != '0') {
            text[i + 1] = '\0';
            break;
        }
    }
}

// 生成min～max之间的随机小数
double random_double_range(double min, double max) {
    return (rand() / (double) RAND_MAX) * (max - min) + min;
}

// 随机生成a~b之间的随机数
int random_int_range(int a, int b) {
    int res = rand() % (b - a + 1) + a;
    return res == 0 ? 1 : res;
}


// 保存记录
void save_record() {
    // 取当前时间作为文件名的一部分
    time_t rawtime;
    time(&rawtime);
    struct tm *now = gmtime(&rawtime);
    char pathname[50];
    char record_str[100];
    sprintf(pathname, "record-%d%d%d_%d_%d", now->tm_year, now->tm_mon, now->tm_yday, now->tm_hour, now->tm_min);
    FILE *fp = fopen(pathname, "w");

    int score = 0;
    for (int i = 0; i < problem_num; i++) {
        record_to_str(record[i], record_str);
        if (record[i].is_correct == 1)score += 10;
        fprintf(fp, record_str);
    }
    fprintf(fp, "总分：%d      满分: %d\n", score, problem_num * 10);
    fclose(fp);
}

// 将答题记录转换为字符串
void record_to_str(struct TestRecord record, char str[100]) {
    // 填空题和其他类型题目的展示方式有些不同
    if (type != FILL) {
        sprintf(str, "%d. %s = %s用户输入: %s\n正确答案: %s\n得分: %s\n\n", record.index, record.text, record.choices,
                record.user_input, record.ans, record.is_correct == 1 ? "10" : "0");
    } else {
        sprintf(str, "%d. %s = \n用户输入: %s\n正确答案: %s\n分析: %s\n\n", record.index, record.text,
                record.user_input, record.ans, record.is_correct == 1 ? "10" : "0");
    }
}
