/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   enumclasshash.h
 * Author: Alexey
 *
 * Created on 19 октября 2016 г., 19:24
 */

#ifndef ENUMCLASSHASH_H
#define ENUMCLASSHASH_H

/* для хеша enum class */
struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

#endif /* ENUMCLASSHASH_H */

