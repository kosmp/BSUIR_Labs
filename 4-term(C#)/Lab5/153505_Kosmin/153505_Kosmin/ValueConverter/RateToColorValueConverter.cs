using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Globalization;

namespace _153505_Kosmin.ValueConverter;

public class RateToColorValueConverter:IValueConverter
{
    public object Convert(object value, Type targetType, object parameter,
                            CultureInfo culture)
    {
        if ((int)value < 22)
            return Colors.LightPink;
        return Colors.WhiteSmoke;
    }
    public object ConvertBack(object value, Type targetTyp, object parameter,
                                CultureInfo culture)
    {
        throw new NotImplementedException();
    }
}
