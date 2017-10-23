// asctime.cpp
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include <ctime>
#include "time.h"

using namespace xll;
using namespace xml;

static AddInX xai_asctime(
	FunctionX(XLL_CSTRINGX, _T("?xll_asctime"), PREFIX _T("ASCTIME"))
	.Arg(XLL_FPX, _T("tm"), IS_TM)
	.Category(CATEGORY)
	.FunctionHelp(_T("Convert a tm time structure to a character string."))
	.Documentation(
		_T("The character string has the form \"Ddd Mmm dd hh:mm:ss yyyy\", ")
		_T("e.g., \"Wed Jan 01 01:23:45 2011\". ")
		_T("The converted character string is adjusted according to the local time zone settings and a 24 hour clock is used. ")
		,
		xlink(PREFIX _T("CTIME"))
	)
);
xcstr WINAPI
xll_asctime(const xfp* ptm)
{
#pragma XLLEXPORT
	static TCHAR buf[26];

	try {
		CHECK_FP(ptm);

		if (0 != _tasctime_s(buf, fp2tm(ptm))) {
			XLL_ERROR("ASCTIME: failed");

			return 0;
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return buf;
}

static AddInX xai_ctime(
	FunctionX(XLL_CSTRINGX, _T("?xll_ctime"), PREFIX _T("CTIME"))
	.Arg(XLL_DOUBLEX, _T("time_t"), IS_TM)
	.Category(CATEGORY)
	.FunctionHelp(_T("Convert a UTC time_t to a character string."))
	.Documentation(
		_T("The character string has the form \"Ddd Mmm dd hh:mm:ss yyyy\", ")
		_T("e.g., \"Wed Jan 01 01:23:45 2011\". ")
		_T("The converted character string is adjusted according to the local time zone settings and a 24 hour clock is used. ")
		,
		xlink(PREFIX _T("ASCTIME"))
	)
);
xcstr WINAPI
xll_ctime(double t)
{
#pragma XLLEXPORT
	static TCHAR buf[26];

	time_t u = static_cast<time_t>(t);
	if (0 != _tctime_s(buf, 26, &u)) { 
		XLL_ERROR("CTIME: failed");

		return 0;
	}

	return buf;
}

