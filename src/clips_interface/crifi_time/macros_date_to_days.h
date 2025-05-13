#pragma once

#define LEAPYEAR(dts) (((dts->year % 100 != 0) || (dts->year % 400 == 0)) && (dts->year % 4 == 0))
#define MONTH31(dts) ((dts->month == 1) || (dts->month == 3) || (dts->month == 5) || (dts->month == 7) || (dts->month == 8) || (dts->month == 10) || (dts->month == 12))
#define MONTH29(dts) ((dts->month == 2) && LEAPYEAR(dts))
#define MONTH28(dts) ((dts->month == 2) && !LEAPYEAR(dts))
#define MONTH30(dts) ((dts->month == 4) || (dts->month == 6) || (dts->month == 9) || (dts->month == 11))

//length of month before
#define MONTH31L(dts) ((dts->month == 2) || (dts->month == 4) || (dts->month == 6) || (dts->month == 8) || (dts->month == 9) || (dts->month == 11) || (dts->month == 1))
#define MONTH29L(dts) ((dts->month == 3) && LEAPYEAR(dts))
#define MONTH28L(dts) ((dts->month == 3) && !LEAPYEAR(dts))
#define MONTH30L(dts) ((dts->month == 5) || (dts->month == 7) || (dts->month == 10) || (dts->month == 12))

