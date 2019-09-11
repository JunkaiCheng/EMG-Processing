//hebaoxiang 2019-04-16
#ifndef _MARVER_INTERPOLATOPN_H
#define _MAVER_INTERPOLATOPN_H


#include "algorithm.h"
#include<sstream>
#include <ap.h>
#include <interpolation.h>
#include<stdafx.h>
BEGIN_MAVER_EMG_NAMESPACE
std::string float2str2(float x);
std::string float_list_2_str(const std::vector<float>& srcx);
void interpolate(const std::vector<float> & srcx, const std::vector<float> & srcy, const std::vector<float> & dstx, std::vector<float> & dsty);

END_MAVER_EMG_NAMESPACE
#endif // !INTERPOLATOPN_H