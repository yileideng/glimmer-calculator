#include"head.c"
Status init_SQstack(SQstack* pstack);
//初始化数字栈：
Status init_NSstack(NSstack* pstack);
//释放栈的内存：
void stack_free(SQstack* pstack, NSstack* pstack2);
//清空栈：
void stack_clear(NSstack* pstack, SQstack* pstack2);
//判断栈是否为空:
Bool is_empty(SQstack* pstack);
//求栈的长度：
int stack_length(SQstack* pstack);
//取栈顶元素:
Status stack_get_top(SQstack* pstack, StackElem* pElem);
//字符入栈：
Status SQstack_push(SQstack* pstack, StackElem* pElem);
//数字入栈：
Status NSstack_push(NSstack* pstack, StackElem2 pElem);
//字符出栈：
Status SQstack_pop(SQstack* pstack, StackElem* pElem);
//数字出栈：
Status NSstack_pop(NSstack* pstack, StackElem2* pElem);
//定义visit函数
Status visit(StackElem* pElem);
//遍历栈：
Status stack_traverse(SQstack* pstack, Status(*visit)(StackElem*));
//计算后缀表达式的结果:
double cal_post(StackElem* str); //计算后缀表达式
//将中缀表达式转化为后缀表达式,并计算返回结果：
double transform(StackElem* str, StackElem* p) ;//str为中缀表达式字符串，p为后缀表达式字符串
void clear_input_buffer() ;
void save_result(const char* file, double result) ;

int main(int argc, char* argv[])
{

    // 判断是否指定了保存结果的文件
    FILE* file = NULL;
    if (argc == 3 && strcmp(argv[1], "-t") == 0) {
        file = fopen(argv[2], "w");
        if (file == NULL) {
            fprintf(stderr, "Failed to open file.\n");
            return 1;
        }
    }

    
    char* input;
    while (1) {
        input = readline("\033[33minteraction> \033[00m");

        // 用户输入
        if (input != NULL) {
            if (strcmp(input, "quit") == 0) {
                free(input);
                break;
            }
            //输入help时提示，并使用红色字体
            else if (strcmp(input, "help") == 0) {
                printf("\033[31mOperation commands:\n");
                printf("- Enter an expression to calculate.\n");
                printf("- Type 'quit' to exit the program.\033[00m\n");
            }
            else {
                //保存到历史
                add_history(input);

                char post[50];
                printf("\033[33mresult> \033[00m%lf\n", transform(input, post));

                // 将结果保存到文件
                if (file != NULL) {
                    save_result(argv[2], transform(input, post));
                }
            }
            free(input);
        }
    }

    // 关闭保存结果的文件
    if (file != NULL) {
        fclose(file);
    }
return 0;
}
