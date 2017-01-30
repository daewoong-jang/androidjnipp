/*
 * Copyright (C) 2017 Daewoong Jang.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <functional>

template <typename C, typename R, typename... P>
std::function<R (P...)> lambda_function_type(R (C::*)(P...) const)
{
    return {};
}

template <typename C, typename R, typename... P>
std::function<R (P...)> lambda_function(C&& c, R (C::*)(P...) const)
{
    return std::function<R (P...)>(std::forward<C>(c));
}

template<typename F> decltype(lambda_function_type<F>(&F::operator())) lambda(F&& f)
{
    return lambda_function<F>(std::forward<F>(f), &F::operator());
}

template<typename T, typename Enable = void>
struct normalize_creation_param;

template<typename T>
struct normalize_creation_param<T,
    typename std::enable_if<std::is_pod<typename std::decay<T>::type>::value>::type> {
    typedef typename std::decay<T>::type type;
};

template<typename T>
struct normalize_creation_param<T,
    typename std::enable_if<!std::is_pod<typename std::decay<T>::type>::value>::type> {
    typedef typename std::conditional<std::is_rvalue_reference<T>::value,
        typename std::decay<T>::type&&,
        const typename std::decay<T>::type&>::type type;
};
