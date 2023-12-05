#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/DateTime.h>
#include <Message.h>

namespace py = pybind11;
using namespace BPrivate;

PYBIND11_MODULE(DateTime, m)
{
py::enum_<time_type>(m, "time_type", "")
.value("B_GMT_TIME", time_type::B_GMT_TIME, "")
.value("B_LOCAL_TIME", time_type::B_LOCAL_TIME, "")
.export_values();

py::enum_<diff_type>(m, "diff_type", "")
.value("B_HOURS_DIFF", diff_type::B_HOURS_DIFF, "")
.value("B_MINUTES_DIFF", diff_type::B_MINUTES_DIFF, "")
.value("B_SECONDS_DIFF", diff_type::B_SECONDS_DIFF, "")
.value("B_MILLISECONDS_DIFF", diff_type::B_MILLISECONDS_DIFF, "")
.value("B_MICROSECONDS_DIFF", diff_type::B_MICROSECONDS_DIFF, "")
.export_values();

py::class_<BTime>(m, "BTime")
.def(py::init(), "")
.def(py::init<const BTime &>(), "", py::arg("other"))
.def(py::init<int, int, int, int>(), "", py::arg("hour"), py::arg("minute"), py::arg("second"), py::arg("microsecond")=0)
.def(py::init<const BMessage *>(), "", py::arg("archive"))
.def("Archive", &BTime::Archive, "", py::arg("into"))
//.def("IsValid", py::overload_cast<>(&BTime::IsValid, py::const_), "") // overloading a method with both static and instance methods is not supported;
.def_static("IsValid", py::overload_cast<const BTime &>(&BTime::IsValid), "", py::arg("time"))
.def_static("IsValid", py::overload_cast<int, int, int, int>(&BTime::IsValid), "", py::arg("hour"), py::arg("minute"), py::arg("second"), py::arg("microsecond")=0)
.def_static("CurrentTime", &BTime::CurrentTime, "", py::arg("type"))
.def("Time", &BTime::Time, "")
.def("SetTime", py::overload_cast<const BTime &>(&BTime::SetTime), "", py::arg("time"))
.def("SetTime", py::overload_cast<int, int, int, int>(&BTime::SetTime), "", py::arg("hour"), py::arg("minute"), py::arg("second"), py::arg("microsecond")=0)
.def("AddHours", &BTime::AddHours, "", py::arg("hours"))
.def("AddMinutes", &BTime::AddMinutes, "", py::arg("minutes"))
.def("AddSeconds", &BTime::AddSeconds, "", py::arg("seconds"))
.def("AddMilliseconds", &BTime::AddMilliseconds, "", py::arg("milliseconds"))
.def("AddMicroseconds", &BTime::AddMicroseconds, "", py::arg("microseconds"))
.def("Hour", &BTime::Hour, "")
.def("Minute", &BTime::Minute, "")
.def("Second", &BTime::Second, "")
.def("Millisecond", &BTime::Millisecond, "")
.def("Microsecond", &BTime::Microsecond, "")
.def("Difference", &BTime::Difference, "", py::arg("time"), py::arg("type"))
.def("__ne__", &BTime::operator!=, "", py::arg("time"))
.def("__eq__", &BTime::operator==, "", py::arg("time"))
.def("__lt__", &BTime::operator<, "", py::arg("time"))
.def("__le__", &BTime::operator<=, "", py::arg("time"))
.def("__gt__", &BTime::operator>, "", py::arg("time"))
.def("__ge__", &BTime::operator>=, "", py::arg("time"))
;

py::class_<BDate>(m, "BDate")
.def(py::init(), "")
.def(py::init<const BDate &>(), "", py::arg("other"))
.def(py::init<int, int, int>(), "", py::arg("year"), py::arg("month"), py::arg("day"))
.def(py::init<time_t, time_type>(), "", py::arg("time"), py::arg("type")=B_LOCAL_TIME)
.def(py::init<const BMessage *>(), "", py::arg("archive"))
.def("Archive", &BDate::Archive, "", py::arg("into"))
//.def("IsValid", py::overload_cast<>(&BDate::IsValid, py::const_), "") // overloading a method with both static and instance methods is not supported;
.def_static("IsValid", py::overload_cast<const BDate &>(&BDate::IsValid), "", py::arg("date"))
.def_static("IsValid", py::overload_cast<int, int, int>(&BDate::IsValid), "", py::arg("year"), py::arg("month"), py::arg("day"))
.def_static("CurrentDate", &BDate::CurrentDate, "", py::arg("type"))
.def("Date", &BDate::Date, "")
.def("SetDate", py::overload_cast<const BDate &>(&BDate::SetDate), "", py::arg("date"))
.def("SetDate", py::overload_cast<int, int, int>(&BDate::SetDate), "", py::arg("year"), py::arg("month"), py::arg("day"))
.def("GetDate", &BDate::GetDate, "", py::arg("year"), py::arg("month"), py::arg("day"))
.def("AddDays", &BDate::AddDays, "", py::arg("days"))
.def("AddYears", &BDate::AddYears, "", py::arg("years"))
.def("AddMonths", &BDate::AddMonths, "", py::arg("months"))
.def("Day", &BDate::Day, "")
.def("Year", &BDate::Year, "")
.def("Month", &BDate::Month, "")
.def("Difference", &BDate::Difference, "", py::arg("date"))
.def("SetDay", &BDate::SetDay, "", py::arg("day"))
.def("SetMonth", &BDate::SetMonth, "", py::arg("month"))
.def("SetYear", &BDate::SetYear, "", py::arg("year"))
.def("DayOfWeek", &BDate::DayOfWeek, "")
.def("DayOfYear", &BDate::DayOfYear, "")
.def("WeekNumber", &BDate::WeekNumber, "")
//.def("IsLeapYear", py::overload_cast<>(&BDate::IsLeapYear, py::const_), "")
.def_static("IsLeapYear", py::overload_cast<int>(&BDate::IsLeapYear), "", py::arg("year"))
.def("DaysInYear", &BDate::DaysInYear, "")
.def("DaysInMonth", &BDate::DaysInMonth, "")
//.def("ShortDayName", py::overload_cast<>(&BDate::ShortDayName, py::const_), "")
.def_static("ShortDayName", py::overload_cast<int>(&BDate::ShortDayName), "", py::arg("day"))
//.def("ShortMonthName", py::overload_cast<>(&BDate::ShortMonthName, py::const_), "")
.def_static("ShortMonthName", py::overload_cast<int>(&BDate::ShortMonthName), "", py::arg("month"))
//.def("LongDayName", py::overload_cast<>(&BDate::LongDayName, py::const_), "")
.def_static("LongDayName", py::overload_cast<int>(&BDate::LongDayName), "", py::arg("day"))
//.def("LongMonthName", py::overload_cast<>(&BDate::LongMonthName, py::const_), "")
.def_static("LongMonthName", py::overload_cast<int>(&BDate::LongMonthName), "", py::arg("month"))
//.def("DateToJulianDay", &BDate::DateToJulianDay, "")
.def_static("JulianDayToDate", &BDate::JulianDayToDate, "", py::arg("julianDay"))
.def("__ne__", &BDate::operator!=, "", py::arg("date"))
.def("__eq__", &BDate::operator==, "", py::arg("date"))
.def("__lt__", &BDate::operator<, "", py::arg("date"))
.def("__le__", &BDate::operator<=, "", py::arg("date"))
.def("__gt__", &BDate::operator>, "", py::arg("date"))
.def("__ge__", &BDate::operator>=, "", py::arg("date"))
;

py::class_<BDateTime>(m, "BDateTime")
.def(py::init(), "")
.def(py::init<const BDate &, const BTime &>(), "", py::arg("date"), py::arg("time"))
.def(py::init<const BMessage *>(), "", py::arg("archive"))
.def("Archive", &BDateTime::Archive, "", py::arg("into"))
.def("IsValid", &BDateTime::IsValid, "")
.def_static("CurrentDateTime", &BDateTime::CurrentDateTime, "", py::arg("type"))
.def("SetDateTime", &BDateTime::SetDateTime, "", py::arg("date"), py::arg("time"))
.def("Date", py::overload_cast<>(&BDateTime::Date), "")
.def("Date", py::overload_cast<>(&BDateTime::Date), "")
.def("SetDate", &BDateTime::SetDate, "", py::arg("date"))
.def("Time", py::overload_cast<>(&BDateTime::Time), "")
.def("Time", py::overload_cast<>(&BDateTime::Time), "")
.def("SetTime", &BDateTime::SetTime, "", py::arg("time"))
.def("Time_t", &BDateTime::Time_t, "")
.def("SetTime_t", &BDateTime::SetTime_t, "", py::arg("seconds"))
.def("__ne__", &BDateTime::operator!=, "", py::arg("dateTime"))
.def("__eq__", &BDateTime::operator==, "", py::arg("dateTime"))
.def("__lt__", &BDateTime::operator<, "", py::arg("dateTime"))
.def("__le__", &BDateTime::operator<=, "", py::arg("dateTime"))
.def("__gt__", &BDateTime::operator>, "", py::arg("dateTime"))
.def("__ge__", &BDateTime::operator>=, "", py::arg("dateTime"))
;

/*
m.attr("time_type") = py::cast(time_type);

m.attr("B_GMT_TIME") = py::cast(B_GMT_TIME);

m.attr("B_LOCAL_TIME") = py::cast(B_LOCAL_TIME);

m.attr("diff_type") = py::cast(diff_type);

m.attr("B_HOURS_DIFF") = py::cast(B_HOURS_DIFF);

m.attr("B_MINUTES_DIFF") = py::cast(B_MINUTES_DIFF);

m.attr("B_SECONDS_DIFF") = py::cast(B_SECONDS_DIFF);

m.attr("B_MILLISECONDS_DIFF") = py::cast(B_MILLISECONDS_DIFF);

m.attr("B_MICROSECONDS_DIFF") = py::cast(B_MICROSECONDS_DIFF);

m.attr("BTime") = py::cast(BTime);

m.attr("BDate") = py::cast(BDate);

m.attr("BDateTime") = py::cast(BDateTime);
*/
}
