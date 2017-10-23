// ymdhms.cpp - break down Excel time
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "time.h"

using namespace xll;
using namespace xml;

static AddInX xai_ymdhms(
	FunctionX(XLL_FPX XLL_UNCALCEDX, _T("?xll_ymdhms"), PREFIX _T("YMDHMS"))
	.Arg(XLL_DOUBLEX, _T("Date"), _T("is an Excel Julian date"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Break down an Excel date into an array of year, month, day, hours, minutes, and seconds. "))
	.Documentation(
		_T("The data are returned in an array having six elements. ")
		,
		element()
		._(xlink(PREFIX _T("MKTIME")))
		._(xlink(PREFIX _T("MKGMTIME")))
	)
);
xfp* WINAPI
xll_ymdhms(double d)
{
#pragma XLLEXPORT
	static FPX e(6, 1);

	e[0] = ExcelX(xlfYear, NumX(d));
	e[1] = ExcelX(xlfMonth, NumX(d));
	e[2] = ExcelX(xlfDay, NumX(d));
	e[3] = ExcelX(xlfHour, NumX(d));
	e[4] = ExcelX(xlfMinute, NumX(d));
	e[5] = ExcelX(xlfSecond, NumX(d));

	if (columns<XLOPERX>(ExcelX(xlfCaller)) > 1)
		e.reshape(1, 6);

	return e.get();
}
