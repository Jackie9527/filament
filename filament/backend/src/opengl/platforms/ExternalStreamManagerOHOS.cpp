/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ExternalStreamManagerOHOS.h"

#include <utils/api_level.h>
#include <utils/compiler.h>
#include <utils/Log.h>

#include <dlfcn.h>

#include <chrono>

using namespace utils;

namespace filament::backend {

using namespace backend;
using Stream = Platform::Stream;


template <typename T>
static void loadSymbol(T*& pfn, const char *symbol) noexcept {
    pfn = (T*)dlsym(RTLD_DEFAULT, symbol);
}

ExternalStreamManagerOHOS& ExternalStreamManagerOHOS::create() noexcept {
    return *(new ExternalStreamManagerOHOS{});
}

void ExternalStreamManagerOHOS::destroy(ExternalStreamManagerOHOS* pExternalStreamManagerOHOS) noexcept {
    delete pExternalStreamManagerOHOS;
}

ExternalStreamManagerOHOS::ExternalStreamManagerOHOS() noexcept
{

}

ExternalStreamManagerOHOS::~ExternalStreamManagerOHOS() noexcept = default;


#if 0
Stream* ExternalStreamManagerOHOS::acquire(jobject surfaceTexture) noexcept {
    return nullptr;
}
#endif

void ExternalStreamManagerOHOS::release(Stream* handle) noexcept {
}

void ExternalStreamManagerOHOS::attach(Stream* handle, intptr_t tname) noexcept {
    
}

void ExternalStreamManagerOHOS::detach(Stream* handle) noexcept {
    
}

void ExternalStreamManagerOHOS::updateTexImage(Stream* handle, int64_t* timestamp) noexcept {
    
}

} // namespace filament::backend
