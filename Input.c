#include "Input.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"

void getInput(char *str, ...)
{
    va_list ap;
    va_start(ap, str);

    char identifier;
    char *separator = NULL;
    long char_num = 0;
    for (int i = 1; i < strlen(str); i++)
    {
        int malloc_check = 0;
        free(separator);
        char_num = 0;
        separator = NULL;
        // to get identifier
        identifier = str[i];
        // to get char_num
        char *s = NULL;
        int j = 0; // size
        i++;
        while (str[i] != '}')
        {
            char* temporary = realloc(s, j + 2);
            if (temporary == NULL)
            {
                printf("Couldn't allocate memory 1\n");
                free(s);
                return;
            }
            s = temporary;
            s[j] = str[i];
            i++;
            j++;
        }
        if (j > 0) // to make sure that there is a string for char_num, because
                   // if there is no char_num entered no point doing this
        {
            s[j] = '\0';
            char *tail;
            char_num = strtol(s, &tail, 10);
            if (*tail != '\0')
            {
                printf("The char_num has to be integers\n");
                free(s);
                return;
            }
        }
        free(s);
        s = NULL;

        // for separator
        j = 0;
        i++;
        while (str[i - 1] == '\\' || i < strlen(str) && str[i] != '{')
        {
            char* temporary = realloc(separator, j + 2);
            if (temporary == NULL)
            {
                printf("Couldn't allocate memory 2\n");
                free(separator);
                return;
            }
            separator = temporary;
            separator[j] = str[i];
            i++;
            j++;
        }
        if (j > 0) // to make sure that separator isn't nothing(if nothing: go to
                   // next pointer) (if nothing on last {} keep going until EOF)
        {
            separator[j] = '\0';
        }
        int len = 0;
        if (separator != NULL) // initialize string to compare with separator
        {
            len = strlen(separator) - 1;
            s = malloc(len + 2); // len + 2 = strlen(separator) + 1( +1 for '\0')
            if (s == NULL)
            {
                printf("could not allocate memory 3\n");
                free(s);
                return;
            }
            s[len + 1] = '\0';
        }
        char *tail; // used to check if user inputs correct digits
        // Now doing the strings part etc
        char *get = NULL;
        if (identifier != 's')
        {
            get = malloc(char_num + 1);
            int k = 0;
            char c;
            while ((c = fgetc(stdin)) != EOF && c != '\n' && c != '\r' /*'/r' for MacOS*/)
            {
                if (separator != NULL)
                {
                    for (int l = len; l >= 1; l--)
                    {
                        s[l - 1] = s[l];
                    }
                    s[len] = c;
                }
                if (separator != NULL && !strcmp(separator, s))
                {
                    break;
                }
                if (char_num == 0)
                {
                    char* temporary = realloc(get, k + 2);
                    if (temporary == NULL)
                    {
                        printf("Couldn't allocate memory 5\n");
                        free(get);
                        return;
                    }
                    get = temporary;
                    get[k] = c;
                    k++;
                }
                else if (char_num != 0) // not "else" for clarity and choice ;)
                {
                    get[k] = c;
                    k++;
                    if (k >= char_num)
                    {
                        break;
                    }
                }
            }
            get[k] = '\0';
        }
        if (identifier == 's')
        {
            char *temp = NULL;
            char **value = va_arg(ap, char **);

            int k = 0;
            char c;
            while ((c = fgetc(stdin)) != EOF && c != '\n' && c != '\r' /*'/r' for MacOS*/)
            {
                if (separator != NULL)
                {
                    for (int l = 1; l <= len; l++)
                    {
                        s[l - 1] = s[l];
                    }
                    s[len] = c;
                }
                if (separator != NULL && !strcmp(separator, s))
                {
                    break;
                }
                if (char_num != 0 && k < char_num)
                {
                    // value = (char*)value; // so no warnings
                    ((char *)value)[k] = c;
                }
                if (char_num == 0)
                {
                    char* temporary = realloc(temp, k + 2);
                    if (temporary == NULL)
                    {
                        printf("Couldn't allocate memory 5\n");
                        free(temp);
                        return;
                    }
                    temp = temporary;
                    temp[k] = c;
                }
                k++;
            }
            if (char_num == 0)
            {
                temp[k] = '\0';
                if (c == '\n' || c == '\r' || c == EOF)
                {
                    *value = temp;
                    malloc_check = 1;
                    free(s);
                    continue;
                }
                int length = strlen(temp) - strlen(separator) + 1 + 1;
                char* temporary = realloc(temp, length);
                if(!temporary){
                    printf("Couldn't allocate memory 6\n");
                    free(temp);
                    return;
                }
                temp = temporary;
                temp[length - 1] = '\0';
                *value = temp;
            }
            else
            {
                if (c == '\n' || c == '\r' || c == EOF)
                {
                    ((char *)value)[k] = '\0';
                    malloc_check = 1;
                    free(s);
                    continue;
                }
                ((char *)value)[k - strlen(separator) + 1] = '\0';
            }
        }
        else if (identifier == 'c')
        {
            char *value = va_arg(ap, char *);
            *value = get[0];
        }
        else if (identifier == 'l')
        {
            long *value = va_arg(ap, long *);
            *value = strtol(get, &tail, 10);
        }
        else if (identifier == 'L')
        {
            long long *value = va_arg(ap, long long *);
            *value = strtoll(get, &tail, 10);
        }
        else if (identifier == 'i')
        {
            int *value = va_arg(ap, int *);
            *value = strtol(get, &tail, 10);
        }
        else if (identifier == 'f')
        {
            float *value = va_arg(ap, float *);
            *value = strtof(get, &tail);
        }
        else if (identifier == 'd')
        {
            double *value = va_arg(ap, double *);
            *value = strtod(get, &tail);
        }
        else
        {
            printf("Invalid identifier\n");
            break;
        }
        if (identifier != 's' && identifier != 'c' && *tail != '\0')
        {
            printf("Enter correct digit\n");
            return;
        }
        if (identifier != 's')
        {
            free(get);
        }
        if (malloc_check == 0)
        {
            free(s);
        }
    }
    free(separator);
    va_end(ap);
}

#pragma GCC diagnostic pop