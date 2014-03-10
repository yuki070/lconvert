/*
 * stringutil.h
 *
 *  Created on: 2014��3��10��
 *      Author: liangjianqiang
 */

#ifndef STRINGUTIL_H_
#define STRINGUTIL_H_

#include <vector>
#include <string>

namespace stringutil {

    std::vector<std::string> split(const std::string& sep, const std::string& str);

} /* namespace stringutil */
#endif /* STRINGUTIL_H_ */
