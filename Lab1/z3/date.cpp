#include "date.h"

Date::Date()
{
   calculateMonths();
}

void Date::calculateMonths()
{
    if(IsLeap() == true)
        months[2] = 29;
    else
        months[2] = 28;
    months[1] = 31;
    months[3] = 31;
    months[4] = 30;
    months[5] = 31;
    months[6] = 30;
    months[7] = 31;
    months[8] = 31;
    months[9] = 30;
    months[10] = 31;
    months[11] = 30;
    months[12] = 31;
}

void Date::realDate()
{
    char * ctime (const time_t * time);
    const time_t tm = time(nullptr);
    char dayCh[3];
    char monthCh[3];
    char yearCh[5];
    strftime(dayCh, 3, "%d", localtime(&tm));
    strftime(monthCh, 3, "%m", localtime(&tm));
    strftime(yearCh, 5, "%Y", localtime(&tm));
    day = (dayCh[0] - '0') * 10 + (dayCh[1] - '0');
    month = (monthCh[0] - '0') * 10 + (monthCh[1] - '0');
    year = (yearCh[0] - '0') * 1000 + (yearCh[1] - '0') * 100 + (yearCh[2] - '0') * 10 + (yearCh[3] - '0');
}

bool Date::IsLeap()
{
    if (!(year % 4))
    {
        if (!(year % 100))
        {
            if (!(year % 400))
                return true;
            else
                return false;
        }
        else
            return true;
     }
     else
        return false;
}

Date Date::NextDay()
{
    Date nextDate;
    if (day < months[month])
    {
        nextDate.day = day + 1;
        nextDate.month = month;
        nextDate.year = year;
    }
    else
    {
        nextDate.day = 1;
        if (month < 12)
        {
            nextDate.month = month + 1;
            nextDate.year = year;
        }
        else
        {
            nextDate.month = 1;
            nextDate.year = year + 1;
        }
    }
    return nextDate;
}

Date Date::PreviousDay()
{
    Date prevDate;
    if (day > 1)
    {
        prevDate.day = day - 1;
        prevDate.month = month;
        prevDate.year = year;
    }
    else
    {
        if (month > 1)
        {
            prevDate.day = months[month - 1];
            prevDate.month = month - 1;
            prevDate.year = year;
        }
        else
        {
            prevDate.day = months[12];
            prevDate.month = 12;
            prevDate.year = year - 1;
        }
    }
    return prevDate;
}

short Date::WeekNumber()
{
    short days = 0;
    for(int i = 1; i <= month; i++)
    {
        if (i != month)
        {
            days += months[i];
        }
        else
        {
            days += day;
        }
    }
    if (days % 7 == 0)
        return days / 7;
    else
        return days / 7 + 1;
}

int Date::DaysTillYourBirthday(Date birthdaydate)
{
    int days = 0;
    if (birthdaydate.month == month && birthdaydate.day >= day)
    {
        return birthdaydate.day - day;
    }
    if (birthdaydate.month > month)
    {
        for (int i = month; i <= birthdaydate.month; i++)
        {
            if (i == month)
            {
                days = months[month] - day;
            }
            else
            {
                if (i != birthdaydate.month)
                {
                    days += months[i];
                }
                else
                {
                    days += birthdaydate.day;
                    return days;
                }
            }
        }
    }
    else
    {
        for (int i = month; i <= 12; i++)
        {
            if (i == month)
            {
                days = months[month] - day;
            }
            else
            {
                days += months[i];
            }
        }
        year++;
        calculateMonths();
        for (int i = 1; i <= birthdaydate.month; i++)
        {
            if (i != birthdaydate.month)
            {
                days += months[i];
            }
            else
            {
                days += birthdaydate.day;
            }
        }
        year--;
        calculateMonths();
    }
    return days;
}

int Date::Duration(Date date)
{
    int days = 0;
    if (date.year == year && date.month == month && date.day == day) return 0;
    if (date.year > year || (date.year == year && date.month > month) || (date.month == month && date.day > day))
    {
        bool startMonth = true;
        int j = month;
        int buf = year;
        if (date.year > year)
        {
            for (int i = year; i <= date.year; i++)
            {
                for (; j <= 12; j++)
                {
                    if (j == month && startMonth)
                    {
                        startMonth = false;
                        days += months[month] - day;
                    }
                    else if (year == date.year && j == date.month)
                    {
                        days += date.day;
                        break;
                    }
                    else
                    {
                        days += months[j];
                    }
                }
                year++;
                calculateMonths();
                j = 1;
            }
            year = buf;
            calculateMonths();
            return days;
        }
        else if (date.year == year && date.month > month)
        {
            for (; j <= date.month; j++)
            {
                 if (j == month)
                 {
                     days += months[month] - day;
                 }
                 else if (j == date.month)
                 {
                     days += date.day;
                     break;
                 }
                 else
                 {
                     days += months[j];
                 }
            }
            return days;
        }
        else if (date.month == month && date.day > day)
        {
            return date.day - day;
        }
    }
    else
    {
        bool startMonth = true;
        int j = date.month;
        int buf = date.year;
        if (year > date.year)
        {
            for (int i = date.year; i <= year; i++)
            {
                for (; j <= 12; j++)
                {
                    if (j == date.month && startMonth)
                    {
                        startMonth = false;
                        days += date.months[date.month] - date.day;
                    }
                    else if (date.year == year && j == month)
                    {
                        days += day;
                        break;
                    }
                    else
                    {
                        days += date.months[j];
                    }
                }
                date.year++;
                date.calculateMonths();
                j = 1;
            }
            date.year = buf;
            date.calculateMonths();
            return days;
        }
        else if (year == date.year && month > date.month)
        {
            for (; j <= month; j++)
            {
                 if (j == date.month)
                 {
                     days += date.months[date.month] - date.day;
                 }
                 else if (j == month)
                 {
                     days += day;
                     break;
                 }
                 else
                 {
                     days += date.months[j];
                 }
            }
            return days;
        }
        else if (month == date.month && day > date.day)
        {
            return day - date.day;
        }
    }
}
