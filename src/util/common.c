//
// Created by vitalijbukatkin on 06.06.2020.
//

#include "stdio.h"

char *Common_StringConcat(char *buff, char *str1, char *str2) {
    sprintf(buff, "%s%s", str1, str2);
    return buff;
}