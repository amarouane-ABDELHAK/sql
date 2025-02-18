/*
 * Copyright OpenSearch Contributors
 * SPDX-License-Identifier: Apache-2.0
 */


#ifndef __MYLOG_H__
#define __MYLOG_H__

#undef DLL_DECLARE
#ifdef WIN32
#ifdef _MYLOG_FUNCS_IMPLEMENT_
#define DLL_DECLARE _declspec(dllexport)
#else
#ifdef _MYLOG_FUNCS_IMPORT_
#define DLL_DECLARE _declspec(dllimport)
#else
#define DLL_DECLARE
#endif /* _MYLOG_FUNCS_IMPORT_ */
#endif /* _MYLOG_FUNCS_IMPLEMENT_ */
#else
#define DLL_DECLARE
#endif /* WIN32 */

#include <stdio.h>
#ifndef WIN32
#include <unistd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __GNUC__
#define __attribute__(x)
#endif

DLL_DECLARE int mylog(const char *fmt, ...)
    __attribute__((format(OPENSEARCH_PRINTF_ATTRIBUTE, 1, 2)));
DLL_DECLARE int myprintf(const char *fmt, ...)
    __attribute__((format(OPENSEARCH_PRINTF_ATTRIBUTE, 1, 2)));

extern int qlog(const char *fmt, ...)
    __attribute__((format(OPENSEARCH_PRINTF_ATTRIBUTE, 1, 2)));
extern int qprintf(char *fmt, ...)
    __attribute__((format(OPENSEARCH_PRINTF_ATTRIBUTE, 1, 2)));

const char *po_basename(const char *path);

#define PREPEND_FMT "%10.10s[%s]%d: "
#define PREPEND_ITEMS , po_basename(__FILE__), __FUNCTION__, __LINE__
#define QLOG_MARK "[QLOG]"

#if defined(__GNUC__) && !defined(__APPLE__)
#define MYLOG(level, fmt, ...)                                                 \
    (level < get_mylog() ? mylog(PREPEND_FMT fmt PREPEND_ITEMS, ##__VA_ARGS__) \
                         : 0)
#define MYPRINTF(level, fmt, ...) \
    (level < get_mylog() ? myprintf((fmt), ##__VA_ARGS__) : 0)
#define QLOG(level, fmt, ...)                               \
    ((level < get_qlog() ? qlog((fmt), ##__VA_ARGS__) : 0), \
     MYLOG(level, QLOG_MARK fmt, ##__VA_ARGS__))
#define QPRINTF(level, fmt, ...)                               \
    ((level < get_qlog() ? qprintf((fmt), ##__VA_ARGS__) : 0), \
     MYPRINTF(level, (fmt), ##__VA_ARGS__))
#elif defined WIN32 /* && _MSC_VER > 1800 */
#define MYLOG(level, fmt, ...)                               \
    ((int)level <= get_mylog()                               \
         ? mylog(PREPEND_FMT fmt PREPEND_ITEMS, __VA_ARGS__) \
         : (printf || printf((fmt), __VA_ARGS__)))
#define MYPRINTF(level, fmt, ...)                           \
    ((int)level <= get_mylog() ? myprintf(fmt, __VA_ARGS__) \
                               : (printf || printf((fmt), __VA_ARGS__)))
#define QLOG(level, fmt, ...)                                           \
    (((int)level <= get_qlog() ? qlog((fmt), __VA_ARGS__)               \
                               : (printf || printf(fmt, __VA_ARGS__))), \
     MYLOG(level, QLOG_MARK fmt, __VA_ARGS__))
#define QPRINTF(level, fmt, ...)                                          \
    (((int)level <= get_qlog() ? qprintf(fmt, __VA_ARGS__)                \
                               : (printf || printf((fmt), __VA_ARGS__))), \
     MYPRINTF(level, (fmt), __VA_ARGS__))
#else
#define MYLOG(level, ...)                                                \
    do {                                                                 \
        _Pragma("clang diagnostic push");                                \
        _Pragma("clang diagnostic ignored \"-Wformat-pedantic\"");       \
        (level < get_mylog()                                             \
             ? (mylog(PREPEND_FMT PREPEND_ITEMS), myprintf(__VA_ARGS__)) \
             : 0);                                                       \
        _Pragma("clang diagnostic pop");                                 \
    } while (0)
#define MYPRINTF(level, ...)                                       \
    do {                                                           \
        _Pragma("clang diagnostic push");                          \
        _Pragma("clang diagnostic ignored \"-Wformat-pedantic\""); \
        (level < get_mylog() ? myprintf(__VA_ARGS__) : 0);         \
        _Pragma("clang diagnostic pop");                           \
    } while (0)
#define QLOG(level, ...)                                           \
    do {                                                           \
        _Pragma("clang diagnostic push");                          \
        _Pragma("clang diagnostic ignored \"-Wformat-pedantic\""); \
        (level < get_qlog() ? qlog(__VA_ARGS__) : 0);              \
        MYLOG(level, QLOG_MARK);                                   \
        MYPRINTF(level, __VA_ARGS__);                              \
        _Pragma("clang diagnostic pop");                           \
    } while (0)
#define QPRINTF(level, ...)                                        \
    do {                                                           \
        _Pragma("clang diagnostic push");                          \
        _Pragma("clang diagnostic ignored \"-Wformat-pedantic\""); \
        (level < get_qlog() ? qprintf(__VA_ARGS__) : 0);           \
        MYPRINTF(level, __VA_ARGS__);                              \
        _Pragma("clang diagnostic pop");                           \
    } while (0)
#endif /* __GNUC__ */

enum OpenSearchLogLevel {
    // Prefixing with OPENSEARCH_ because C does not support namespaces and we may get a
    // collision, given how common these names are
    OPENSEARCH_OFF,
    OPENSEARCH_FATAL,
    OPENSEARCH_ERROR,
    OPENSEARCH_WARNING,
    OPENSEARCH_INFO,
    OPENSEARCH_DEBUG,
    OPENSEARCH_TRACE,
    OPENSEARCH_ALL
};

int get_qlog(void);
int get_mylog(void);

int getGlobalDebug();
int setGlobalDebug(int val);
int getGlobalCommlog();
int setGlobalCommlog(int val);
int writeGlobalLogs();
int getLogDir(char *dir, int dirmax);
int setLogDir(const char *dir);

void InitializeLogging(void);
void FinalizeLogging(void);

#ifdef __cplusplus
}
#endif
#endif /* __MYLOG_H__ */
