#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <ctype.h>  
  
// 函数声明  
void count_chars_words(const char *filename, int *char_count, int *word_count);  
  
int main(int argc, char *argv[]) {  
    if (argc != 3) {  
        fprintf(stderr, "Usage: %s [-c|-w] [input_file_name]\n", argv[0]);  
        return 1;  
    }  
  
    int char_count = 0;  
    int word_count = 0;  
    char *param = argv[1];  
    char *filename = argv[2];  
  
    if (strcmp(param, "-c") == 0) {  
        // 统计字符数  
        count_chars_words(filename, &char_count, NULL);  
        printf("字符数：%d\n", char_count);  
    } else if (strcmp(param, "-w") == 0) {  
        // 统计单词数  
        count_chars_words(filename, NULL, &word_count);  
        printf("单词数：%d\n", word_count);  
    } else {  
        fprintf(stderr, "Invalid parameter: %s\n", param);  
        return 1;  
    }  
  
    return 0;  
}  
  
// 统计字符数和单词数  
void count_chars_words(const char *filename, int *char_count, int *word_count) {  
    FILE *file = fopen(filename, "r");  
    if (file == NULL) {  
        perror("Error opening file");  
        exit(EXIT_FAILURE);  
    }  
  
    int in_word = 0; // 标记是否在当前单词内  
    while (!feof(file)) {  
        char ch = fgetc(file);  
        if (!feof(file)) {  
            if (char_count) (*char_count)++; // 统计字符数  
            if (isspace(ch)) { // 遇到空格、制表符或换行符  
                in_word = 0;  
            } else if (!in_word) { // 遇到一个单词的起始  
                if (word_count) (*word_count)++; // 统计单词数  
                in_word = 1;  
            }  
        }  
    }  
  
    fclose(file);  
}