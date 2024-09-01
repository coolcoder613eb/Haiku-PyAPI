#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/LocaleStrings.h>

namespace py = pybind11;


void define_LocaleStrings(py::module_& m)
{
py::enum_<country_strings>(m, "country_strings", "")
.value("B_COUNTRY_STRINGS_BASE", country_strings::B_COUNTRY_STRINGS_BASE, "")
.value("B_DATE_TIME_FORMAT", country_strings::B_DATE_TIME_FORMAT, "")
.value("B_TIME_AM_PM_FORMAT", country_strings::B_TIME_AM_PM_FORMAT, "")
.value("B_SHORT_DATE_TIME_FORMAT", country_strings::B_SHORT_DATE_TIME_FORMAT, "")
.value("B_SHORT_TIME_AM_PM_FORMAT", country_strings::B_SHORT_TIME_AM_PM_FORMAT, "")
.value("B_AM_STRING", country_strings::B_AM_STRING, "")
.value("B_PM_STRING", country_strings::B_PM_STRING, "")
.value("B_DATE_SEPARATOR", country_strings::B_DATE_SEPARATOR, "")
.value("B_TIME_SEPARATOR", country_strings::B_TIME_SEPARATOR, "")
.value("B_NUM_COUNTRY_STRINGS", country_strings::B_NUM_COUNTRY_STRINGS, "")
.export_values();

py::enum_<language_strings>(m, "language_strings", "")
.value("B_LANGUAGE_STRINGS_BASE", language_strings::B_LANGUAGE_STRINGS_BASE, "")
.value("B_YESTERDAY_STRING", language_strings::B_YESTERDAY_STRING, "")
.value("B_TODAY_STRING", language_strings::B_TODAY_STRING, "")
.value("B_TOMORROW_STRING", language_strings::B_TOMORROW_STRING, "")
.value("B_FUTURE_STRING", language_strings::B_FUTURE_STRING, "")
.value("B_DAY_1", language_strings::B_DAY_1, "")
.value("B_DAY_2", language_strings::B_DAY_2, "")
.value("B_DAY_3", language_strings::B_DAY_3, "")
.value("B_DAY_4", language_strings::B_DAY_4, "")
.value("B_DAY_5", language_strings::B_DAY_5, "")
.value("B_DAY_6", language_strings::B_DAY_6, "")
.value("B_DAY_7", language_strings::B_DAY_7, "")
.value("B_AB_DAY_1", language_strings::B_AB_DAY_1, "")
.value("B_AB_DAY_2", language_strings::B_AB_DAY_2, "")
.value("B_AB_DAY_3", language_strings::B_AB_DAY_3, "")
.value("B_AB_DAY_4", language_strings::B_AB_DAY_4, "")
.value("B_AB_DAY_5", language_strings::B_AB_DAY_5, "")
.value("B_AB_DAY_6", language_strings::B_AB_DAY_6, "")
.value("B_AB_DAY_7", language_strings::B_AB_DAY_7, "")
.value("B_MON_1", language_strings::B_MON_1, "")
.value("B_MON_2", language_strings::B_MON_2, "")
.value("B_MON_3", language_strings::B_MON_3, "")
.value("B_MON_4", language_strings::B_MON_4, "")
.value("B_MON_5", language_strings::B_MON_5, "")
.value("B_MON_6", language_strings::B_MON_6, "")
.value("B_MON_7", language_strings::B_MON_7, "")
.value("B_MON_8", language_strings::B_MON_8, "")
.value("B_MON_9", language_strings::B_MON_9, "")
.value("B_MON_10", language_strings::B_MON_10, "")
.value("B_MON_11", language_strings::B_MON_11, "")
.value("B_MON_12", language_strings::B_MON_12, "")
.value("B_AB_MON_1", language_strings::B_AB_MON_1, "")
.value("B_AB_MON_2", language_strings::B_AB_MON_2, "")
.value("B_AB_MON_3", language_strings::B_AB_MON_3, "")
.value("B_AB_MON_4", language_strings::B_AB_MON_4, "")
.value("B_AB_MON_5", language_strings::B_AB_MON_5, "")
.value("B_AB_MON_6", language_strings::B_AB_MON_6, "")
.value("B_AB_MON_7", language_strings::B_AB_MON_7, "")
.value("B_AB_MON_8", language_strings::B_AB_MON_8, "")
.value("B_AB_MON_9", language_strings::B_AB_MON_9, "")
.value("B_AB_MON_10", language_strings::B_AB_MON_10, "")
.value("B_AB_MON_11", language_strings::B_AB_MON_11, "")
.value("B_AB_MON_12", language_strings::B_AB_MON_12, "")
.value("B_YES_EXPRESSION", language_strings::B_YES_EXPRESSION, "")
.value("B_NO_EXPRESSION", language_strings::B_NO_EXPRESSION, "")
.value("B_YES_STRING", language_strings::B_YES_STRING, "")
.value("B_NO_STRING", language_strings::B_NO_STRING, "")
.value("B_NUM_LANGUAGE_STRINGS", language_strings::B_NUM_LANGUAGE_STRINGS, "")
.export_values();

py::enum_<other_locale_strings>(m, "other_locale_strings", "")
.value("B_OTHER_STRINGS_BASE", other_locale_strings::B_OTHER_STRINGS_BASE, "")
.value("B_CODESET", other_locale_strings::B_CODESET, "")
.value("B_ERA", other_locale_strings::B_ERA, "")
.value("B_ERA_DATE_FORMAT", other_locale_strings::B_ERA_DATE_FORMAT, "")
.value("B_ERA_DATE_TIME_FORMAT", other_locale_strings::B_ERA_DATE_TIME_FORMAT, "")
.value("B_ERA_TIME_FORMAT", other_locale_strings::B_ERA_TIME_FORMAT, "")
.value("B_ALT_DIGITS", other_locale_strings::B_ALT_DIGITS, "")
.export_values();


}
