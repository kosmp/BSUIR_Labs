using System;

namespace task3
{
    public class DateService
    {
        public static string GetDay(string date)
        {
            try { DateTime.Parse(date); }
            catch(Exception) { return "err"; }

            if (date != null && date.Length == 10)
            {
                DateTime dt = new DateTime(int.Parse(date.Substring(6, 4)), int.Parse(date.Substring(3, 2)), int.Parse(date.Substring(0, 2)));
                if (dt.DayOfWeek == DayOfWeek.Monday)
                    return "Monday";
                else if (dt.DayOfWeek == DayOfWeek.Tuesday)
                    return "Tuesday";
                else if (dt.DayOfWeek == DayOfWeek.Wednesday)
                    return "Wednesday";
                else if (dt.DayOfWeek == DayOfWeek.Thursday)
                    return "Thursday";
                else if (dt.DayOfWeek == DayOfWeek.Friday)
                    return "Friday";
                else if (dt.DayOfWeek == DayOfWeek.Saturday)
                    return "Saturday";
                else if (dt.DayOfWeek == DayOfWeek.Sunday)
                    return "Sunday";
            }
            return "err";
        }

        public static string GetDaysSpan(int day, int month, int year)
        {
            try
            {
                DateTime thisDate = DateTime.Today;
                DateTime date = new DateTime(year, month, day);
                if (thisDate >= date)
                    return thisDate.Subtract(date).Days.ToString();
                else
                    return date.Subtract(thisDate).Days.ToString();
            }
            catch (Exception)
            {
                return "err";
            }
        }
    }
}

