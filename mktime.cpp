// mktime.cpp - mktime, mkgmtime, localtime, gmtime
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include <ctime>
#include "time.h"

using namespace xll;
using namespace xml;

static AddInX xai_mktime(
	FunctionX(XLL_FPX XLL_UNCALCEDX, _T("?xll_mktime"), PREFIX _T("MKTIME"))
	.Arg(XLL_FPX, _T("tm"), IS_TM)
	.Category(CATEGORY)
	.FunctionHelp(_T("Convert broken down local time to UTC time_t. "))
	.Documentation(
		_T("If the output is an array then the members of the broken down time are returned instead of a time_t. ")
		_T("This is useful when converting the (possibly incomplete) fields into a fully defined structure with normalized values. ")
		,
		xlink(PREFIX _T("LOCALTIME"))
	)
);
xfp* WINAPI
xll_mktime(const xfp* fp)
{
#pragma XLLEXPORT
	static FPX t_(1, 1);
	xfp* pf;

	try {
		CHECK_FP(fp);

		tm* ptm = fp2tm(fp);
		time_t t = mktime(ptm);

		pf = tm2fp(ptm);
		if (columns<XLOPERX>(ExcelX(xlfCaller)) > 1) {
			pf->rows = 1;
			pf->columns = 9;
		}
		else {
			t_ = static_cast<double>(t);

			pf = t_.get();
		}
		pf = tm2fp(ptm);
		if (columns<XLOPERX>(ExcelX(xlfCaller)) > 1) {
			pf->rows = 1;
			pf->columns = 9;
		}
		else {
			t_ = static_cast<double>(t);

			pf = t_.get();
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return pf;
}

static AddInX xai_mkgmtime(
	FunctionX(XLL_FPX XLL_UNCALCEDX, _T("?xll_mkgmtime"), PREFIX _T("MKGMTIME"))
	.Arg(XLL_FPX, _T("tm"), IS_TM)
	.Category(CATEGORY)
	.FunctionHelp(_T("Convert broken down UTC time to UTC time_t. "))
	.Documentation(
		_T("If the output is an array then the members of the broken down time are returned instead of a time_t. ")
		_T("This is useful when converting the (possibly incomplete) fields into a fully defined structure with normalized values. ")
		,
		xlink(PREFIX _T("GMTIME"))
	)
);
xfp* WINAPI
xll_mkgmtime(const xfp* fp)
{
#pragma XLLEXPORT
	static FPX t_(1, 1);
	xfp* pf;

	try {
		CHECK_FP(fp);

		tm* ptm = fp2tm(fp);
		time_t t = _mkgmtime(ptm);

		LOPERX c(ExcelX(xlfCaller));
		if (size<XLOPERX>(c) > 1) {
			pf = tm2fp(ptm);
			if (columns<XLOPERX>(c) > 1) {
				pf->rows = 1;
				pf->columns = 9;
			}
		}
		else {
			t_ = static_cast<double>(t);

			pf = t_.get();
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return pf;
}

static AddInX xai_localtime(
	FunctionX(XLL_FPX XLL_UNCALCEDX, _T("?xll_localtime"), PREFIX _T("LOCALTIME"))
	.Arg(XLL_DOUBLEX, _T("time_t"), IS_TIME_T)
	.Category(CATEGORY)
	.FunctionHelp(_T("Convert UTC time_t to broken down local time. "))
	.Documentation(
		_T("The output array contains year, month, day, hour, minute, second, dst, day of week, and day of year. ")
		,
		xlink(PREFIX _T("MKTIME"))
	)
);
xfp* WINAPI
xll_localtime(double t)
{
#pragma XLLEXPORT
	time_t t_ = static_cast<time_t>(t);
	tm* ptm = localtime(&t_);
	xfp* pf = tm2fp(ptm);

	if (columns<XLOPERX>(ExcelX(xlfCaller)) > 1) {
		pf->rows = 1;
		pf->columns = 9;
	}

	return pf;
}

static AddInX xai_gmtime(
	FunctionX(XLL_FPX XLL_UNCALCEDX, _T("?xll_gmtime"), PREFIX _T("GMTIME"))
	.Arg(XLL_DOUBLEX, _T("time_t"), IS_TIME_T)
	.Category(CATEGORY)
	.FunctionHelp(_T("Convert UTC time_t to broken down UTC time. "))
	.Documentation(
		_T("The output array contains year, month, day, hour, minute, second, dst, day of week, and day of year. ")
		,
		xlink(PREFIX _T("MKGMTIME"))
	)
);
xfp* WINAPI
xll_gmtime(double t)
{
#pragma XLLEXPORT
	time_t t_ = static_cast<time_t>(t);
	tm* ptm = gmtime(&t_);
	xfp* pf = tm2fp(ptm);

	if (columns<XLOPERX>(ExcelX(xlfCaller)) > 1) {
		pf->rows = 1;
		pf->columns = 9;
	}

	return pf;
}


