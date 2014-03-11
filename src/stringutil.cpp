/*
 * stringutil.cpp
 *
 *  Created on: 2014Äê3ÔÂ10ÈÕ
 *      Author: liangjianqiang
 */

#include "stringutil.h"

namespace stringutil {

    std::vector<std::string> Split(const std::string& sep, const std::string& str) {
        std::vector<std::string> v;
        size_t sep_len = sep.length();
        size_t p1 = 0;
        size_t p2 = 0;
        do {
            p2 = str.find(sep, p1);
            v.push_back(str.substr(p1, p2 - p1));
            p1 = p2 + sep_len;
        } while (p2 != std::string::npos);
        return v;
    }

} /* namespace stringutil */
