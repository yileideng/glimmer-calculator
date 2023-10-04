#include"head.c"
//初始化字符栈：
Status init_SQstack(SQstack* pstack)
{
    pstack->pbase = (StackElem*)malloc(sizeof(StackElem) * Stack_Size);//申请空间

    if (!pstack->pbase)//判断初始化是否成功
        return ERROR;
    pstack->ptop = pstack->pbase;
    pstack->size = Stack_Size;
    return OK;
}

//初始化数字栈：
Status init_NSstack(NSstack* pstack)
{
    pstack->pbase = (StackElem2*)malloc(sizeof(StackElem2) * Stack_Size);//申请空间

    if (!pstack->pbase)//判断初始化是否成功
        return ERROR;
    pstack->ptop = pstack->pbase;
    pstack->size = Stack_Size;
    return OK;
}

//释放栈的内存：
void stack_free(SQstack* pstack, NSstack* pstack2)
{

    free(pstack->pbase);
    pstack->ptop = pstack->pbase = NULL;
    pstack->size = 0;
    free(pstack2->pbase);
    pstack2->ptop = pstack2->pbase = NULL;
    pstack2->size = 0;
}

//清空栈：
void stack_clear(NSstack* pstack, SQstack* pstack2)
{
    while (pstack->ptop != NULL)
    {
        pstack->ptop--;
    }
    while (pstack2->ptop != NULL)
    {
        pstack2->ptop--;
    }

}

//判断栈是否为空:
Bool is_empty(SQstack* pstack)
{
    return(pstack->ptop == pstack->pbase) ? 1 : 0;
}

//求栈的长度：
int stack_length(SQstack* pstack)
{
    int i = 0;
    while ((pstack->ptop--) != NULL)
    {
        i++;
    }
    return i;
}

//取栈顶元素:
Status stack_get_top(SQstack* pstack, StackElem* pElem)
{
    *pElem = *(pstack->ptop);//将栈顶元素存入*pElem
    if (pElem == NULL)//判断是否成功
        return ERROR;
    return OK;
}

//字符入栈：
Status SQstack_push(SQstack* pstack, StackElem* pElem)
{
    if (pstack->ptop - pstack->pbase >= pstack->size)//判断栈内内存是否充足，否则重新分配内存
    {
        pstack->pbase = (StackElem*)realloc(pstack->pbase, (pstack->size + Add_Size) * sizeof(StackElem));

        if (pstack->pbase == NULL)
            return ERROR;
        pstack->ptop = pstack->pbase + pstack->size;
        pstack->size += Stack_Size;
    }
    *pstack->ptop++ = *pElem;
    return OK;
}
//数字入栈：
Status NSstack_push(NSstack* pstack, StackElem2 pElem)
{
    if (pstack->ptop - pstack->pbase >= pstack->size)//判断栈内内存是否充足，否则重新分配内存
    {
        pstack->pbase = (StackElem2*)realloc(pstack->pbase, (pstack->size + Add_Size) * sizeof(StackElem));

        if (pstack->pbase == NULL)
            return ERROR;
        pstack->ptop = pstack->pbase + pstack->size;
        pstack->size += Stack_Size;
    }
    *pstack->ptop++ = pElem;

    return OK;
}



//字符出栈：
Status SQstack_pop(SQstack* pstack, StackElem* pElem)
{
    if (pstack->ptop == pstack->pbase)
        return ERROR;
    *pElem = *(--pstack->ptop);
    return OK;
}
//数字出栈：
Status NSstack_pop(NSstack* pstack, StackElem2* pElem)
{
    if (pstack->ptop == pstack->pbase)
        return ERROR;
    *pElem = *(--pstack->ptop);
    return OK;
}



//定义visit函数
Status visit(StackElem* pElem)
{
    if (!pElem) return ERROR;
    printf("%s", pElem);
    return 0;
}
//遍历栈：
Status stack_traverse(SQstack* pstack, Status(*visit)(StackElem*))
{
    if (pstack->ptop == pstack->pbase) return 0;
    StackElem* p = pstack->pbase;
    while (p != pstack->ptop)
    {
        visit(p);
        p++;
    }
    if (pstack->ptop != NULL)//判断是否成功
        return ERROR;
    return OK;

}

//计算后缀表达式的结果:
double cal_post(StackElem* str) //计算后缀表达式
{
    int i;
    StackElem2 e, a, b;
    char d[50];
    NSstack n;
    init_NSstack(&n);   //初始化一个运算数栈保存运算数
    for (i = 0; i < strlen(str); i++)
    {
        int j = 0;
        while (isdigit(str[i]) || '.' == str[i])
        {
            d[j++] = str[i++];
            d[j] = '\0';
            if (!isdigit(str[i]) && '.' != str[i])
            {
                e = atof(d);   //使用atof()将字符串形式的运算数转换为double型数据
                NSstack_push(&n, e);   //运算数入栈
            }
        }
        switch (str[i])
        {
        case '+':
            NSstack_pop(&n, &b);
            NSstack_pop(&n, &a);
            NSstack_push(&n, a + b);
            break;
        case '-':
            NSstack_pop(&n, &b);
            NSstack_pop(&n, &a);
            NSstack_push(&n, a - b);
            break;
        case '*':
            NSstack_pop(&n, &b);
            NSstack_pop(&n, &a);
            NSstack_push(&n, a * b);
            break;
        case '/':
            NSstack_pop(&n, &b);
            NSstack_pop(&n, &a);
            if (b == 0)
            {
                printf("ERROR：分母不能为0");//分母为0时：ERROR
                exit(-1);
            }
            NSstack_push(&n, a / b);
            break;
        }
    }
    NSstack_pop(&n, &e);
    return e;
}



//将中缀表达式转化为后缀表达式,并计算返回结果：
double transform(StackElem* str, StackElem* p) //str为中缀表达式字符串，p为后缀表达式字符串
{
    SQstack s;
    init_SQstack(&s);   //初始化一个空字符栈
    StackElem e;
    int i;
    int j = 0;
    for (i = 0; i < strlen(str); i++)  //遍历中缀表达式
    {
        //遇到数字和小数点直接输出
        while (isdigit(str[i]) || '.' == str[i])
        {
            p[j++] = str[i++];
            if (!isdigit(str[i]) && '.' != str[i])
                p[j++] = ' ';   //一个数字输出后使用空格与其它运算符分隔开
        }

        //遇到左括号直接入栈
        if ('(' == str[i])
            SQstack_push(&s, &str[i]);

        //遇到右括号直接出栈，直到栈顶为左括号
        if (')' == str[i])
        {
            while ('(' != *(s.ptop - 1))
            {
                SQstack_pop(&s, &e);
                p[j++] = e;
                p[j++] = ' ';
            }
            SQstack_pop(&s, &e);  //左括号出栈但不输出
        }

        //遇到+或—
        if ('+' == str[i] || '-' == str[i])
        {
            while (!is_empty(&s) && '(' != *(s.ptop - 1))
            {
                SQstack_pop(&s, &e);//中缀表达式中+-优先级最低，直接把字符栈中运算符出栈
                p[j++] = e;
                p[j++] = ' ';
            }
            SQstack_push(&s, &str[i]);//把+-入栈
        }

        //遇到*或/
        if ('*' == str[i] || '/' == str[i] || '%' == str[i])
        {
            while (!is_empty(&s) && '(' != *(s.ptop - 1) && '+' != *(s.ptop - 1) && '-' != *(s.ptop - 1))
            {
                SQstack_pop(&s, &e);//栈中除了+-，其它运算符优先级更高，将其出栈
                p[j++] = e;
                p[j++] = ' ';
            }
            SQstack_push(&s, &str[i]);//将*/入栈
        }
    }

    //判断栈空,非空则直接出栈并输出
    while (!is_empty(&s)) {
        SQstack_pop(&s, &e);
        if ('(' != e)
        {
            p[j++] = e;
            p[j++] = ' ';
        }
    }
    p[--j] = '\0';
    double result = cal_post(p);
    return result;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != EOF && c != '\n');
}

//将结果写入文件
void save_result(const char* file, double result) {
    FILE* fp = fopen(file, "a");
    if (fp != NULL) {
        fprintf(fp, "%lf\n", result);
        fclose(fp);
    }
}
