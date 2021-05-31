/*
 * Copyright (C) 2013-2017 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#pragma once

#include "JSCJSValue.h"

namespace JSC {

class CodeBlock;
class FunctionExecutable;

JS_EXPORT_PRIVATE FunctionExecutable* getExecutableForFunction(JSValue theFunctionValue);
JS_EXPORT_PRIVATE CodeBlock* getSomeBaselineCodeBlockForFunction(JSValue theFunctionValue);

JS_EXPORT_PRIVATE JSValue numberOfDFGCompiles(JSValue function);
JS_EXPORT_PRIVATE JSValue setNeverInline(JSValue function);
JS_EXPORT_PRIVATE JSValue setNeverOptimize(JSValue function);
JS_EXPORT_PRIVATE JSValue optimizeNextInvocation(JSValue function);

JS_EXPORT_PRIVATE JSValue failNextNewCodeBlock(ExecState*);
JS_EXPORT_PRIVATE JSValue numberOfDFGCompiles(ExecState*);
JS_EXPORT_PRIVATE JSValue setNeverInline(ExecState*);
JS_EXPORT_PRIVATE JSValue setNeverOptimize(ExecState*);
JS_EXPORT_PRIVATE JSValue setCannotUseOSRExitFuzzing(ExecState*);
JS_EXPORT_PRIVATE JSValue optimizeNextInvocation(ExecState*);

JS_EXPORT_PRIVATE unsigned numberOfExceptionFuzzChecks();
JS_EXPORT_PRIVATE unsigned numberOfExecutableAllocationFuzzChecks();
JS_EXPORT_PRIVATE unsigned numberOfStaticOSRExitFuzzChecks();
JS_EXPORT_PRIVATE unsigned numberOfOSRExitFuzzChecks();

JS_EXPORT_PRIVATE void finalizeStatsAtEndOfTesting();

JS_EXPORT_PRIVATE void waitForVMDestruction();

} // namespace JSC
