#ifndef FOTRIC_TEST_H_
#define FOTRIC_TEST_H_
#include <string>
#include <functional>
#include <vector>

#if defined(WIN32)
#if defined(HELLO_SHARED_IMPLEMENTATION)
#define IR_TEST_EXPORTS __declspec(dllexport)
#define IR_TEST_EXPORTS_PRIVATE __declspec(dllexport)
#else
#define IR_TEST_EXPORTS __declspec(dllimport)
#define IR_TEST_EXPORTS_PRIVATE __declspec(dllimport)
#endif  // defined(HELLO_SHARED_IMPLEMENTATION)
#else
#if defined(HELLO_SHARED_IMPLEMENTATION)
#define IR_TEST_EXPORTS __attribute__((visibility("default")))
#define IR_TEST_EXPORTS_PRIVATE __attribute__((visibility("default")))
#else
#define IR_TEST_EXPORTS
#define IR_TEST_EXPORTS_PRIVATE
#endif  // defined(HELLO_SHARED_IMPLEMENTATION)
#endif


IR_TEST_EXPORTS void ir_test_init();

#endif // !FOTRIC_TEST_H_