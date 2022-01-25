// RUN: %empty-directory(%t)

// RUN: %target-swift-frontend %S/swift-functions.swift -typecheck -module-name Functions -emit-cxx-header-path %t/functions.h

// RUN: %target-clangxx -c %s -I %t -o %t/swift-functions-execution.o
// RUN: %target-build-swift %S/swift-functions.swift -o %t/swift-functions-execution %t/swift-functions-execution.o -module-name Functions -Xfrontend -entry-point-function-name -Xfrontend swiftMain -Xfrontend -enable-cxx-interop

// RUN: %target-codesign %t/swift-functions-execution
// RUN: %target-run %t/swift-functions-execution | %FileCheck %s

// REQUIRES: executable_test

#include <cassert>
#include "functions.h"

int main() {
  Functions::passVoidReturnVoid();
  Functions::passIntReturnVoid(-1);
  assert(Functions::passTwoIntReturnIntNoArgLabel(1, 2) == 42);
  assert(Functions::passTwoIntReturnInt(1, 2) == 3);
  assert(Functions::passTwoIntReturnIntNoArgLabelParamName(1, 4) == 5);
  return 0;
}

// CHECK: passVoidReturnVoid
// CHECK-NEXT: passIntReturnVoid -1
// CHECK-NEXT: passTwoIntReturnIntNoArgLabel
