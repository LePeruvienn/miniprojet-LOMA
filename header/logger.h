#ifndef LOG_H
#define LOG_H

#ifndef LOG_ENABLED
	#define LOG_ENABLED 1
#endif

#include <stdio.h>

#if LOG_ENABLED

	#define LOG_HEADER(fd, header, fmt, ...) fprintf(fd, "[%s]: " fmt "\n", header, ##__VA_ARGS__)
	#define LOG_HEADER_FILE(fd, header, fmt, ...) fprintf(fd, "[%s] %s:%d: " fmt "\n", header, __FILE__, __LINE__, ##__VA_ARGS__)

	#define LOG(fmt, ...) printf(fmt "\n", ##__VA_ARGS__)
	#define LOG_ERROR(fmt, ...) LOG_HEADER_FILE(stderr, "ERROR", fmt, ##__VA_ARGS__)
	#define LOG_INFO(fmt, ...) LOG_HEADER(stdout, "INFO", fmt, ##__VA_ARGS__)

#else

	#define LOG(fmt, ...)
	#define LOG_ERROR(fmt, ...)
	#define LOG_INFO(fmt, ...)

#endif

#define EXIT_PROGRAM(code) do { LOG("Program exited with code %d", code); exit(code); } while(0)
#define EXIT_ERROR(code, fmt, ...) do { LOG_ERROR(fmt, ##__VA_ARGS__); EXIT_PROGRAM(code); } while(0)

#endif // LOG_H
