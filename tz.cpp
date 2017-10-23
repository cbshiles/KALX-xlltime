// tz.cpp - Time zone related functions
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include <ctime>
#include "time.h"

using namespace xll;
using namespace xml;

static AddInX xai_tzset(
	FunctionX(XLL_CSTRINGX, _T("?xll_tzset"), PREFIX _T("TZSET"))
	.Arg(XLL_CSTRINGX, _T("TZ?"), _T("is the optional time zone environment variable"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Use TZ to assign values to three global variables: _daylight, _timezone, and _tzname."))
	.Documentation(
		_T("Sets the corresponding environment variable if <codeInline>TZ</codeInline> is not missing and returns the current value. ")
		_T("The format of <codeInline>TZ</codeInline> is tzn[") ENT_plusmn _T("]hh[:mm[:ss] ][dzn] where")
		_T("<defintionTable>")
		_T("<definedTerm>tzn</definedTerm>")
		_T("<definition><para>is a three-letter time-zone name, such as PST. You must specify the correct offset from local time to UTC.</para></definition>")
		_T("<definedTerm>hh</definedTerm>")
		_T("<definition><para>is the difference in hours between UTC and local time with optional sign.</para></definition>")
		_T("<definedTerm>mm</definedTerm>")
		_T("<definition><para>are the minutes, separated from <replaceable>hh</replaceable> by a colon (:).</para></definition>")
		_T("<definedTerm>ss</definedTerm>")
		_T("<definition><para>are the seconds, separated from <replaceable>mm</replaceable> by a colon (:).</para></definition>")
		_T("<definedTerm>dzn</definedTerm>")
		_T("<definition><para>is a three-letter daylight-saving-time zone such as PDT. ")
		_T("If daylight saving time is never in effect in the locality, set TZ without a value for dzn. </para></definition>")
		_T("</defintionTable>")
		,
		element()
		._(xlink(PREFIX _T("DAYLIGHT")))
		._(xlink(PREFIX _T("TIMEZONE")))
		._(xlink(PREFIX _T("TZNAME")))
	)
);
xcstr WINAPI
xll_tzset(xcstr tz)
{
#pragma XLLEXPORT
	static xcstr tz_;

	if (tz && *tz) {

		if (0 != _tputenv_s(_T("TZ"), tz)) {
			XLL_ERROR("TZSET: putenv failed");

			tz_ = 0;
		}

		_tzset();
	}

	tz_ = _tgetenv(_T("TZ"));
	
	return tz_;
}

static AddInX xai_daylight(
	FunctionX(XLL_DOUBLEX, _T("?xll_daylight"), PREFIX _T("DAYLIGHT"))
	.Arg(XLL_CSTRINGX, _T("tzset"), _T("is the output from ") PREFIX _T("TZSET"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Nonzero value if a daylight-saving-time zone is specified in TZ setting; otherwise, 0."))
	.Documentation(
		_T("Use the return value from <codeInline>TZSET</codeInline> to have Excel update when ")
		_T("<environmentVariable>TZ</environmentVariable> is changed. ")
		,
		xlink(PREFIX _T("TZSET"))
	)
);
double WINAPI
xll_daylight(xcstr tzset)
{
#pragma XLLEXPORT

	if (!tzset || !*tzset) {
		XLL_WARNING("DAYLIGHT: missing argument. F2-Enter to get current value");
	}

	return _daylight;
}

static AddInX xai_timezone(
	FunctionX(XLL_DOUBLEX, _T("?xll_timezone"), PREFIX _T("TIMEZONE"))
	.Arg(XLL_CSTRINGX, _T("tzset"), _T("is the output from ") PREFIX _T("TZSET"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Difference in seconds between local time and UTC."))
	.Documentation(
		_T("Use the return value from <codeInline>TZSET</codeInline> to have Excel update when ")
		_T("<environmentVariable>TZ</environmentVariable> is changed. ")
		,
		xlink(PREFIX _T("TZSET"))
	)
);
double WINAPI
xll_timezone(xcstr tzset)
{
#pragma XLLEXPORT

	if (!tzset || !*tzset) {
		XLL_WARNING("TIMEZONE: missing argument. F2-Enter to get current value");
	}

	return _timezone;
}

#ifndef EXCEL12

static AddInX xai_tzname(
	FunctionX(XLL_LPOPERX, _T("?xll_tzname"), PREFIX _T("TZNAME"))
	.Arg(XLL_CSTRINGX, _T("tzset"), _T("is the output from ") PREFIX _T("TZSET"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Two row array of time-zone name and daylight-saving-time zone."))
	.Documentation(
		_T("Returns the string value of time-zone name from TZ environmental variable; empty if TZ has not been set ")
		_T("and the string value of daylight-saving-time zone; empty if daylight-saving-time zone is omitted from TZ environmental variable. ")
		,
		xlink(PREFIX _T("TZSET"))
	)
);
LPOPERX WINAPI
xll_tzname(xcstr tzset)
{
#pragma XLLEXPORT
	static OPERX tzname(2, 1);

	if (!tzset || !*tzset) {
		XLL_WARNING("TZNAME: missing argument. F2-Enter to get current value");
	}

	tzname[0] = _tzname[0]; //!!! not working with EXCEL12
	tzname[1] = _tzname[1];

	return &tzname;
}

#endif // EXCEL12
