
// Copyright (c) 2010-2019 niXman (i dot nixman dog gmail dot com). All
// rights reserved.
//
// This file is part of YAS(https://github.com/niXman/yas) project.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef __yas__version_hpp
#define __yas__version_hpp

// YAS_VERSION / 100000 is the major version
// YAS_VERSION / 100 % 1000 is the minor version
// YAS_VERSION % 100 is the bugfix level

#define YAS_VERSION_MAJOR 7
#define YAS_VERSION_MINOR 0
#define YAS_VERSION_BUGFIX 4

#define YAS_VERSION \
     YAS_VERSION_MAJOR*100000 \
    +YAS_VERSION_MINOR*1000 \
    +YAS_VERSION_BUGFIX*10

#define __YAS_STRINGIZE_I(x) #x
#define __YAS_STRINGIZE(x) __YAS_STRINGIZE_I(x)

#define YAS_VERSION_STRING \
        __YAS_STRINGIZE(YAS_VERSION_MAJOR) \
    "." __YAS_STRINGIZE(YAS_VERSION_MINOR) \
    "." __YAS_STRINGIZE(YAS_VERSION_BUGFIX)

namespace yas {
namespace detail {

/**************************************************************************/

enum yas_version {
     binary_archive_version = 7
    ,text_archive_version = 3
    ,json_archive_version = 1
};

/**************************************************************************/

} // namespace detail
} // namespace yas

#endif // __yas__version_hpp