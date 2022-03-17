#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <QDebug>

class Date
{
public:
    Date();
    Date NextDay();
    Date PreviousDay();
    short WeekNumber();
    int DaysTillYourBirthday(Date birthdaydate);
    int Duration(Date date);
    bool IsLeap();
    void realDate();
    void calculateMonths();
    int months[13];
    int day;
    int month;
    int year;
};

#endif // DATE_H
