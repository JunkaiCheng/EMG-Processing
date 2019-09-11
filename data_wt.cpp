#include "data_wt.h"

using namespace std;

BEGIN_MAVER_EMG_NAMESPACE

CDataWT::CDataWT() :CData("CDataWT")
{}

CDataWT::~CDataWT()
{}

CDataWT::CDataWT(const CDataWT& rhs) :CData(rhs) {
	longs	= rhs.longs;
	//type		= rhs.type;
}

CDataWT::CDataWT(const std::string& classname) : CData(classname)
{}

CDataWT& CDataWT::operator= (const CDataWT& rhs)
{
	CData::operator=(rhs);
	longs = rhs.longs;
	//type = rhs.type;
	return *this;
}

CObject* CDataWT::clone() const
{
	return new CDataWT(*this);
}

std::shared_ptr<CObject> CDataWT::clone_shared() const
{
	return std::make_shared<CDataWT>(*this);
}

bool CDataWT::isSameKindAs(const CObject* ptr)
{
	return dynamic_cast<const CDataWT*>(ptr) != nullptr;
}

bool CDataWT::isSameKindAs(const std::shared_ptr<CObject> ptr)
{
	return std::dynamic_pointer_cast<const CDataWT, const CObject>(ptr) != nullptr;
}

vector<vector<int>>& CDataWT::getLongs() {
	return longs;
}

bool CDataWT::getDataSeriesLongs(size_t idx, std::vector<int>&data_series) {
	if (idx >= longs.size())
		return false;
	data_series = longs[idx];
	return true;
}

void CDataWT::setLongs(std::vector<std::vector<int>>& new_longs) {
	longs = new_longs;
}

void CDataWT::resizeLongs(size_t resize_datasize) {
	longs.resize(resize_datasize);
}

bool CDataWT::setDataSeriesLongs(size_t idx, std::vector<int>&data_series) {
	if (idx >= longs.size())
		return false;
	longs[idx] = data_series;
	return true;
}

//void CDataWT::setType(string & s)
//{
//	type = s;
//}
//
//string & CDataWT::getType()
//{
//	return type;
//}

END_MAVER_EMG_NAMESPACE
