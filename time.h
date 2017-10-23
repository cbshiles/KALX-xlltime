// time.h - header file for <ctime> function wrappers
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
//#define EXCEL12
#include "xll/xll.h"

#ifndef CATEGORY
#define CATEGORY _T("Time")
#endif
#define PREFIX _T("TIME.")

#define IS_TM _T("is an array of year, month, day, and optional hour, minute, second, dst")
#define IS_TIME_T _T("is a UTC time_t")

#define CHECK_FP(pf) ensure (size(*pf) >= 3 && 1970 <= pf->array[0] && pf->array[0] <= 3000)

typedef xll::traits<XLOPERX>::xcstr xcstr;
typedef xll::traits<XLOPERX>::xfp xfp;
typedef xll::traits<XLOPERX>::xword xword;

inline struct tm* fp2tm(const xfp* ptm)
{
	xword n;
	static struct tm tm;

	ensure (xll::size(*ptm) >= 3);
	n = xll::size(*ptm);

	tm.tm_year  = static_cast<int>(ptm->array[0] - 1900);
	tm.tm_mon   = static_cast<int>(ptm->array[1] - 1);
	tm.tm_mday  = static_cast<int>(ptm->array[2]);
	tm.tm_hour  = n > 3 ? static_cast<int>(ptm->array[3]) : 0;
	tm.tm_min   = n > 4 ? static_cast<int>(ptm->array[4]) : 0;
	tm.tm_sec   = n > 5 ? static_cast<int>(ptm->array[5]) : 0;
	tm.tm_isdst = n > 6 ? static_cast<int>(ptm->array[6]) : -1; // detect DST
	tm.tm_wday  = n > 7 ? static_cast<int>(ptm->array[7]) : 0;
	tm.tm_yday  = n > 8 ? static_cast<int>(ptm->array[8]) : 0;

	return &tm;
}

inline xfp* tm2fp(const struct tm* ptm)
{
	static char buf[sizeof(xfp) + 9*sizeof(double)];
	xfp* fp = reinterpret_cast<xfp*>(buf);
	fp->rows = 9;
	fp->columns = 1;

	fp->array[0] = ptm->tm_year + 1900;
	fp->array[1] = ptm->tm_mon + 1;
	fp->array[2] = ptm->tm_mday;
	fp->array[3] = ptm->tm_hour;
	fp->array[4] = ptm->tm_min;
	fp->array[5] = ptm->tm_sec;
	fp->array[6] = ptm->tm_isdst;
	fp->array[7] = ptm->tm_wday;
	fp->array[8] = ptm->tm_yday;

	return fp;
}

