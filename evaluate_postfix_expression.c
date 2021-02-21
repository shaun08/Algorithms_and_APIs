// 2021-02-21: SHAUN08 --> C Program to evaluate postfix algebraic expression on a given set of strings
//                         NOTE: Supported algebraic operators: only +, -, * and /

#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_SIZE 16
#define BOOL uint8_t
#define FALSE 0
#define TRUE 1
#define INT_POS_MAX_64B_STR "2147483647"
#define INT_NEG_MAX_64B_STR "-2147483646"

typedef enum
{
    STATUS_SUCCESS,
    STATUS_INVALID,
    STATUS_DIVIDE_BY_ZERO,
    STATUS_RESULT_OVERFLOW,
    STATUS_EXTRA_NUMBERS_PASSED,
    STATUS_EXTRS_OPERATORS_PASSED
} FuncState_t ;

BOOL isNumber(char* str)
{
    BOOL ret_val = FALSE;

    if(str)
    {
        // Check string for negative numbers
        if(*str == '-')
        {
            // Return FALSE if there is only "-" in string
            if(*(str+1) == '\0')
                return FALSE;
            else
                str++;
        }

        while(*str)
        {
            if( !isdigit(*str) )
                return ret_val;
            str++;
        }
        ret_val = TRUE;
    }

    return ret_val;
}

BOOL isOperator(char *str)
{
    BOOL ret_val = FALSE;

    if(str)
    {
        while(*str)
        {
            switch(*str)
            {
            case '+':
            case '-':
            case '*':
            case '/':
                break;
            default:
                return ret_val;
            }
            str++;
        }
        ret_val = TRUE;
    }

    return ret_val;
}

BOOL checkAddOverflow(int result, int num1, int num2)
{
    // If the 2 numbers are negative and the result is positive
    if( (num1 < 0) && (num2 < 0) && (result > 0) )
        return TRUE;

    // If the 2 numbers are positive and the result is negative
    if( (num1 > 0) && (num2 > 0) && (result < 0) )
        return TRUE;

    return FALSE;
}

BOOL checkMultiplyOverflow(int result, int num1, int num2)
{
    // If either of the numbers is 0, result would never overflow
    if( (num1 == 0) || (num2 == 0) )
        return FALSE;

    // If first number is equal to (result divided by second number)
    if( num1 == (result / num2) )
        return FALSE;

    return TRUE;
}

FuncState_t evaluatePostfix(const uint8_t postfix_size, char* postfix[], int* result)
{
    if( (postfix == NULL) || (result == NULL) || (postfix_size < 3) )
        return STATUS_INVALID;

    // Stack to store all integers present in post fix
    // NOTE: Using an array here as C does not have built-in stack data type
    //       like std::stack in C++
    int num_stack[MAX_STR_SIZE] = {0};
    int num_stack_top = -1; // Index to track top of stack

    int index = 0;
    while( index < postfix_size )
    {
        // Check if the first 2 strings are numbers in postfix
        if( (index == 0) && isNumber(postfix[index]) && isNumber(postfix[index+1]) )
        {
            num_stack[++num_stack_top] = atoi(postfix[index]);
            num_stack[++num_stack_top] = atoi(postfix[++index]);
        }
        // If string at current index of postfix is a number
        else if( isNumber(postfix[index]) )
        {
            num_stack[++num_stack_top] = atoi(postfix[index]);
        }
        // If string at current index of postfix is an operator
        else if( isOperator(postfix[index]) )
        {
            if(num_stack_top < 1)
                return STATUS_EXTRS_OPERATORS_PASSED;

            int val2 = num_stack[num_stack_top--];
            int val1 = num_stack[num_stack_top];

            switch( *postfix[index] )
            {
                case '+':
                {
                    num_stack[num_stack_top] = val1 + val2;

                    if( checkAddOverflow(num_stack[num_stack_top], val1, val2) )
                        return STATUS_RESULT_OVERFLOW;

                    break;
                }
                case '-':
                {
                    num_stack[num_stack_top] = val1 - val2;

                    break;
                }
                case '*':
                {
                    num_stack[num_stack_top] = val1 * val2;

                    if( checkMultiplyOverflow(num_stack[num_stack_top], val1, val2) )
                        return STATUS_RESULT_OVERFLOW;

                    break;
                }
                case '/':
                {
                    if(val2 == 0)
                        return STATUS_DIVIDE_BY_ZERO;

                    num_stack[num_stack_top] = val1 / val2;

                    break;
                }
            }
        }
        // INVALID string passed
        else
        {
            return STATUS_INVALID;
        }

        index++;
    }

    if(num_stack_top != 0)
        return STATUS_EXTRA_NUMBERS_PASSED;

    *result = num_stack[num_stack_top];
    return STATUS_SUCCESS;
}

int main()
{
    int result = 0;
    char **null_ptr = NULL;
    FuncState_t status = STATUS_SUCCESS;

    // Str1 passed
    char *str1[3] = {"44", "-7", "*"};
    status = evaluatePostfix(3, str1, &result);
    printf("Status: %d, Result: %d\n\n", status, result);

    // Str2 passed
    char *str2[5] = {"100", "10", "/", "5", "-"};
    status = evaluatePostfix(5, str2, &result);
    printf("Status: %d, Result: %d\n\n", status, result);

    // Str3 passed
    char *str3[7] = {"100", "10", "/", "-44", "6", "-", "+"};
    status = evaluatePostfix(7, str3, &result);
    printf("Status: %d, Result: %d\n\n", status, result);

    // Char array passed as NULL
    status = evaluatePostfix(1, null_ptr, &result);
    printf("Status: %d, Result: %d\n\n", status, result);

    // Result pointer passed as NULL
    status = evaluatePostfix(sizeof(str1), str1, NULL);
    printf("Status: %d, Result: %d\n\n", status, result);

    // Size of strings passed as 0
    status = evaluatePostfix(0, str1, &result);
    printf("Status: %d, Result: %d\n\n", status, result);

    // Str4 passed, divide by 0 error
    char *str4[3] = {"44", "0", "/"};
    status = evaluatePostfix(3, str4, &result);
    printf("Status: %d, Result: %d\n\n", status, result);

    // Str5 passed, add overflow error
    char *str5[7] = {"100", "2", "/", INT_POS_MAX_64B_STR, "6", "-", "+"};
    status = evaluatePostfix(7, str5, &result);
    printf("Status: %d, Result: %d\n\n", status, result);

    // Str6 passed, multiply overflow error
    char *str6[7] = {"100", "10", "/", INT_NEG_MAX_64B_STR, "10", "+", "*"};
    status = evaluatePostfix(7, str6, &result);
    printf("Status: %d, Result: %d\n\n", status, result);

    // Str7 passed, extra numbers error
    char *str7[6] = {"100", "10", "/", "5", "6", "-"};
    status = evaluatePostfix(6, str7, &result);
    printf("Status: %d, Result: %d\n\n", status, result);

    // Str8 passed, extra operators error
    char *str8[7] = {"100", "10", "/", "5", "*", "-", "+"};
    status = evaluatePostfix(7, str8, &result);
    printf("Status: %d, Result: %d\n\n", status, result);

    return 0;
}
