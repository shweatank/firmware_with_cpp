#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define LOG_INFO(format, ...)  printf("[INFO] " format "\n", ##__VA_ARGS__)
#define LOG_WARN(format, ...)  printf("[WARN] " format "\n", ##__VA_ARGS__)
#define LOG_ERROR(format, ...) printf("[ERROR] " format "\n", ##__VA_ARGS__)
#define LOG_DEBUG(format, ...) printf("[DEBUG] " format "\n", ##__VA_ARGS__)

#endif // LOG_H
