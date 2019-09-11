#include"my_INTERPOLATION.h"
BEGIN_MAVER_EMG_NAMESPACE
std::string float2str2(float x)
{
	std::stringstream ss;
	ss << x;
	return ss.str();
}
std::string float_list_2_str(const std::vector<float>& srcx)
{
	std::string benginindex = "[";
	std::string endindex = "]";
	std::string val;
	for (size_t i = 0; i < srcx.size(); i++)
	{
		val += float2str2(srcx[i]) + std::string(",");
	}
	val = val.substr(0, val.size() - 1);
	return benginindex + val + endindex;
}
void interpolate(const std::vector<float> & srcx, const std::vector<float> & srcy, const std::vector<float> & dstx, std::vector<float> & dsty)
{
	if (srcx.empty() || srcy.empty() || srcx.empty())
	{
		dsty = srcy;
		return;
	}
	std::string srcxstr = float_list_2_str(srcx);
	std::string srcystr = float_list_2_str(srcy);
	alglib::real_1d_array xreal = srcxstr.c_str();
	alglib::real_1d_array yreal = srcystr.c_str();
	alglib::spline1dinterpolant spline;
	alglib::spline1dbuildcubic(xreal, yreal, spline);
	dsty.resize(dstx.size());
	for (size_t i = 0; i < dstx.size(); i++)
	{
		dsty[i] = static_cast<float>(alglib::spline1dcalc(spline, static_cast<double>(dstx[i])));
	}
}
END_MAVER_EMG_NAMESPACE