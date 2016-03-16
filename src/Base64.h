/*
 * Base64.h
 *
 *  Created on: Mar 16, 2016
 *      Author: fred
 */

#ifndef BASE64_H_
#define BASE64_H_
#include <string>
#include <vector>

namespace Quadcopter {
#define TCHAR char    //Not unicode
#define TEXT(x) x     //Not unicode
#define BYTE unsigned char
#define DWORD long
class Base64 {
public:
	Base64();
	std::basic_string<TCHAR> base64Encode(std::vector<BYTE> inputBuffer);
	std::vector<BYTE> base64Decode(const std::basic_string<TCHAR>& input);
	virtual ~Base64();
};
}
#endif /* BASE64_H_ */
