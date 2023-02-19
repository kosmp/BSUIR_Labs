using System.Text.RegularExpressions;

namespace Lab1;

public partial class MainPage : ContentPage
{
    double memory = 0;
    string first = "0";
    string second = "0";
    char op;

    public MainPage()
    {
        InitializeComponent();
    }

    private void processing(char _op)
    {
        if (label.Text.Last() == '-' || label.Text.Last() == '+' || label.Text.Last() == '*' || label.Text.Last() == '÷')
        {
            if (_op == '=')
            {
                func(_op);
                return;
            }
            else
            {
                op = _op;
                label.Text = label.Text.Substring(0, label.Text.Length - 1);
            }
        }

        Regex regex = new Regex(@".*[0-9](\+|\*|÷|-)-?[0-9].*");
        MatchCollection matches = regex.Matches(label.Text);

        if (matches.Count > 0)
        {
            if (label.Text.Contains('+'))
            {
                for (int i = 1; i < label.Text.Length; i++)
                {
                    if (i == label.Text.Length - 1)
                        continue;

                    int indPrev = i - 1;
                    int indNext = i + 1;

                    if ((label.Text[i] == '+' || label.Text[i] == '-' || label.Text[i] == '*' || label.Text[i] == '÷')
                        && (label.Text[indPrev] >= '0' && label.Text[indPrev] <= '9' && ((label.Text[indNext] >= '0' && label.Text[indNext] <= '9') || label.Text[indNext] == '-')))
                    {
                        second = label.Text.Substring(i + 1);
                        break;
                    }
                }
            }
            else if (label.Text.Contains("*"))
            {
                second = label.Text.Substring(label.Text.IndexOf("*") + 1);
            }
            else if (label.Text.Contains("÷"))
            {
                second = label.Text.Substring(label.Text.IndexOf("÷") + 1);
                if (Convert.ToDouble(second) == 0)
                    return;
            }
            else if (label.Text.Contains('-'))
            {
                for (int i = 1; i < label.Text.Length; i++)
                {
                    if (i + 1 == label.Text.Length)
                        continue;

                    int indPrev = i - 1;
                    int indNext = i + 1;

                    if ((label.Text[i] == '+' || label.Text[i] == '-' || label.Text[i] == '*' || label.Text[i] == '÷')
                        && (label.Text[indPrev] >= '0' && label.Text[indPrev] <= '9' && ((label.Text[indNext] >= '0' && label.Text[indNext] <= '9') || label.Text[indNext] == '-')))
                    {
                        second = label.Text.Substring(i);
                        break;
                    }
                }
            }
            else
            {
                func(_op);
                return;
            }

            switch (op)
            {
                case '-':
                    memory = Convert.ToDouble(first) - Convert.ToDouble(second);
                    break;
                case '+':
                    memory = Convert.ToDouble(first) + Convert.ToDouble(second);
                    break;
                case '*':
                    memory = Convert.ToDouble(first) * Convert.ToDouble(second);
                    break;
                case '÷':
                    memory = Convert.ToDouble(first) / Convert.ToDouble(second);
                    break;
                default: throw new NotImplementedException();
            }

            op = _op;
            if (memory == 0)
                memory = 0;
            first = memory.ToString();
            second = "0";
            if (_op != '=')
                label.Text = first + _op;
            else
                label.Text = first;
        }
        else
        {
            func(_op);
        }
    }

    private void func(char _op)
    {
        if (_op == '=')
        {
            op = _op;
            if (label.Text.Last() == '+')
            {
                first = (Convert.ToDouble(first) + Convert.ToDouble(first)).ToString();
                second = "0";
                memory = Convert.ToDouble(first);
                label.Text = first;
            }
            else if (label.Text.Last() == '-')
            {
                first = (Convert.ToDouble(first) - Convert.ToDouble(first)).ToString();
                second = "0";
                memory = Convert.ToDouble(first);
                label.Text = first;
            }
            else if (label.Text.Last() == '*')
            {
                first = (Convert.ToDouble(first) * Convert.ToDouble(first)).ToString();
                second = "0";
                memory = Convert.ToDouble(first);
                label.Text = first;
            }
            else if (label.Text.Last() == '÷')
            {
                if (first != "0")
                {
                    first = (Convert.ToDouble(first) / Convert.ToDouble(first)).ToString();
                    second = "0";
                    memory = Convert.ToDouble(first);
                    label.Text = first;
                }
                else
                {
                    first = "0";
                    second = "0";
                    memory = 0;
                    label.Text = "0";
                }
            }
        }
        else
        {
            op = _op;
            label.Text += _op;
            if (label.Text.Length >= 2)
                first = label.Text.Substring(0, label.Text.Length - 1);
            else
                first = "0";
        }
    }

    private void OnBtnZeroClicked(object sender, EventArgs e)
    {
        if (label.Text.Length > 307)
            return;

        if (op == '=')
        {
            op = ' ';
            label.Text = "0";
            return;
        }

        if (label.Text != "0")
        {
            Regex regex1 = new Regex(@"[0-9](\+|-|\*|÷)-?0\.");
            MatchCollection matches1 = regex1.Matches(label.Text);
            if (matches1.Count == 0)
            {
                Regex regex2 = new Regex(@"[0-9](\+|-|\*|÷)-?0");
                MatchCollection matches2 = regex2.Matches(label.Text);
                if (matches2.Count > 0)
                    return;
            }

            label.Text += "0";
        }
    }

    private bool zeroInSecondHandler(char num)
    {
        Regex regex = new Regex(@".?[0-9]?(\+|-|\*|÷)0$");
        MatchCollection matches = regex.Matches(label.Text);

        if (matches.Count > 0)
        {
            label.Text = label.Text.Substring(0, label.Text.Length - 1) + num;
            return true;
        }
        else
        {
            return false;
        }
    }

    private void OnBtnOneClicked(object sender, EventArgs e)
	{
        if (label.Text.Length > 306 || zeroInSecondHandler('1'))
            return;

        if (label.Text == "0" || op == '=')
        {
            op = ' ';
            label.Text = "1";
        }
        else
        {
            label.Text += "1";
        }
    }

    private void OnBtnTwoClicked(object sender, EventArgs e)
    {
        if (label.Text.Length > 306 || zeroInSecondHandler('2'))
            return;

        if (label.Text == "0" || op == '=')
        {
            op = ' ';
            label.Text = "2";
        }
        else
        {
            label.Text += "2";
        }
    }

    private void OnBtnThreeClicked(object sender, EventArgs e)
    {
        if (label.Text.Length > 306 || zeroInSecondHandler('3'))
            return;

        if (label.Text == "0" || op == '=')
        {
            op = ' ';
            label.Text = "3";
        }
        else
        {
            label.Text += "3";
        }

    }

    private void OnBtnFourClicked(object sender, EventArgs e)
    {
        if (label.Text.Length > 306 || zeroInSecondHandler('4'))
            return;

        if (label.Text == "0" || op == '=')
        {
            op = ' ';
            label.Text = "4";
        }
        else
        {
            label.Text += "4";
        }

    }

    private void OnBtnFiveClicked(object sender, EventArgs e)
    {
        if (label.Text.Length > 306 || zeroInSecondHandler('5'))
            return;

        if (label.Text == "0" || op == '=')
        {
            op = ' ';
            label.Text = "5";
        }
        else
        {
            label.Text += "5";
        }
    }

    private void OnBtnSixClicked(object sender, EventArgs e)
    {
        if (label.Text.Length > 306 || zeroInSecondHandler('6'))
            return;

        if (label.Text == "0" || op == '=')
        {
            op = ' ';
            label.Text = "6";
        }
        else
        {
            label.Text += "6";
        }
    }

    private void OnBtnSevenClicked(object sender, EventArgs e)
    {
        if (label.Text.Length > 306 || zeroInSecondHandler('7'))
            return;

        if (label.Text == "0" || op == '=')
        {
            op = ' ';
            label.Text = "7";
        }
        else
        {
            label.Text += "7";
        }
    }

    private void OnBtnEightClicked(object sender, EventArgs e)
    {
        if (label.Text.Length > 306 || zeroInSecondHandler('8'))
            return;

        if (label.Text == "0" || op == '=')
        {
            op = ' ';
            label.Text = "8";
        }
        else
        {
            label.Text += "8";
        }

    }

    private void OnBtnNineClicked(object sender, EventArgs e)
    {
        if (label.Text.Length > 306 || zeroInSecondHandler('9'))
            return;

        if (label.Text == "0" || op == '=')
        {
            op = ' ';
            label.Text = "9";
        }
        else
        {
            label.Text += "9";
        }
    }

    private void OnBtnPlusClicked(object sender, EventArgs e)
    {
        processing('+');
    }

    private void OnBtnMinusClicked(object sender, EventArgs e)
    {
        processing('-');
    }

    private void OnBtnCommaClicked(object sender, EventArgs e)
    {
        Regex regex = new Regex(@".+\.[0-9]*$");
        MatchCollection matches = regex.Matches(label.Text);

        if (matches.Count > 0)
            return;

        if (op == '=')
        {
            op = ' ';
            label.Text = "0.";
            first = "0.";
        }
        else
        {
            if (label.Text.Last() == '+' || label.Text.Last() == '-' || label.Text.Last() == '*' || label.Text.Last() == '÷')
                label.Text += "0.";
            else
                label.Text += ".";
        }
    }
    
    private void OnBtnEqualClicked(object sender, EventArgs e)
    {
        processing('=');
    }

    private void OnBtnMultiplyClicked(object sender, EventArgs e)
    {
        processing('*');
    }

    private void OnBtnPlusMinusClicked(object sender, EventArgs e)
    {
        if (label.Text == "0")
            return;

        Regex regex = new Regex(@".*[0-9](\+|\*|÷|-)-?[0-9].*");
        MatchCollection matches = regex.Matches(label.Text);

        Regex checkFractional = new Regex(@"-?0\.0*$");
        MatchCollection matchesFractional = checkFractional.Matches(first);

        Regex zeroInteger = new Regex(@"^-?0$");
        MatchCollection matchZeroInteger = zeroInteger.Matches(first);

        if (label.Text.Length > 1 && (label.Text.Last() == '+' || label.Text.Last() == '-' || label.Text.Last() == '*' || label.Text.Last() == '÷'))
        {
            if ((matchesFractional.Count > 0 || matchZeroInteger.Count > 0) && label.Text.Last() == '÷')
                return;
            second = (-Convert.ToDouble(first)).ToString();
            label.Text += second;
        }
        else if (matches.Count > 0)
        {
            if (label.Text.Contains('+'))
            {
                for (int i = 1; i < label.Text.Length; i++)
                {
                    if (i == label.Text.Length - 1)
                        continue;

                    int indPrev = i - 1;
                    int indNext = i + 1;
                    if (label.Text[i] == '+' && label.Text[indPrev] >= '0' && label.Text[indPrev] <= '9' && label.Text[indNext] >= '0' && label.Text[indNext] <= '9')
                    {
                        second = label.Text.Substring(i + 1);
                        break;
                    }
                }

                if (second != "0")
                {
                    if (second[0] != '-')
                        second = second.Insert(0, "-");
                    else
                        second = second.Remove(0, 1);
                }
                label.Text = first + "+" + second;
            }
            else if (label.Text.Contains("*"))
            {
                second = label.Text.Substring(label.Text.IndexOf('*') + 1);
                if (second != "0")
                {
                    if (second[0] != '-')
                        second = second.Insert(0, "-");
                    else
                        second = second.Remove(0, 1);
                }
                label.Text = first + "*" + second;
            }
            else if (label.Text.Contains("÷"))
            {
                second = label.Text.Substring(label.Text.IndexOf('÷') + 1);
                if (second != "0")
                {
                    if (second[0] != '-')
                        second = second.Insert(0, "-");
                    else
                        second = second.Remove(0, 1);
                }
                label.Text = first + "÷" + second;
            }
            else if (label.Text.Contains('-'))
            {
                for (int i = 1; i < label.Text.Length; i++)
                {
                    if (i == label.Text.Length - 1)
                        continue;

                    int indPrev = i - 1;
                    int indNext = i + 1;
                    if (label.Text[i] == '-' && label.Text[indPrev] >= '0' && label.Text[indPrev] <= '9' && label.Text[indNext] >= '0' && label.Text[indNext] <= '9')
                    {
                        second = label.Text.Substring(i + 1);
                        break;
                    }
                }

                if (second[0] != '-')
                    second = second.Insert(0, "-");
                else
                    second = second.Remove(0, 1);
                label.Text = first + "-" + second;
            }
        }
        else
        {
            if (label.Text[0] == '-')
            {
                first = label.Text.Remove(0, 1);
                label.Text = first;
            }
            else
            {
                first = label.Text.Insert(0, "-");
                label.Text = first;
            }
        }
    }

    private void OnBtnDivideClicked(object sender, EventArgs e)
    {
        processing('÷');
    }

    private void OnBtnSquareRootClicked(object sender, EventArgs e)
    {
        Regex regex = new Regex(@".*[0-9](\+|\*|÷|-)-?[0-9].*");
        MatchCollection matches = regex.Matches(label.Text);

        if (!label.Text.Contains('+') && !label.Text.Contains('-') && !label.Text.Contains('*') && !label.Text.Contains('÷') && Convert.ToDouble(label.Text) == 0)
        {
            label.Text = "0";
            first = "0";
            memory = 0;
        }
        else if (matches.Count > 0)
        {
            if (label.Text.Contains('+'))
            {
                for (int i = 1; i < label.Text.Length; i++)
                {
                    if (i == label.Text.Length - 1)
                        continue;

                    int indPrev = i - 1;
                    int indNext = i + 1;

                    if ((label.Text[i] == '+' || label.Text[i] == '-' || label.Text[i] == '*' || label.Text[i] == '÷')
                        && (label.Text[indPrev] >= '0' && label.Text[indPrev] <= '9' && ((label.Text[indNext] >= '0' && label.Text[indNext] <= '9') || label.Text[indNext] == '-')))
                    {
                        second = label.Text.Substring(i + 1);
                        if (Convert.ToDouble(second) < 0)
                            return;
                        second = Math.Sqrt(Convert.ToDouble(second)).ToString();
                        memory = Convert.ToDouble(second);
                        label.Text = first + "+" + second;
                        break;
                    }
                }
            }
            else if (label.Text.Contains("*"))
            {
                second = label.Text.Substring(label.Text.IndexOf("*") + 1);
                if (Convert.ToDouble(second) < 0)
                    return;
                second = Math.Sqrt(Convert.ToDouble(second)).ToString();
                memory = Convert.ToDouble(second);
                label.Text = first + "*" + second;
            }
            else if (label.Text.Contains("÷"))
            {
                second = label.Text.Substring(label.Text.IndexOf("÷") + 1);
                if (Convert.ToDouble(second) < 0)
                    return;
                second = Math.Sqrt(Convert.ToDouble(second)).ToString();
                memory = Convert.ToDouble(second);
                label.Text = first + "÷" + second;
                if (Convert.ToDouble(second) == 0)
                    return;
            }
            else if (label.Text.Contains('-'))
            {
                for (int i = 1; i < label.Text.Length; i++)
                {
                    if (i + 1 == label.Text.Length)
                        continue;

                    int indPrev = i - 1;
                    int indNext = i + 1;

                    if ((label.Text[i] == '+' || label.Text[i] == '-' || label.Text[i] == '*' || label.Text[i] == '÷')
                        && (label.Text[indPrev] >= '0' && label.Text[indPrev] <= '9' && ((label.Text[indNext] >= '0' && label.Text[indNext] <= '9') || label.Text[indNext] == '-')))
                    {
                        second = label.Text.Substring(i + 1);
                        if (Convert.ToDouble(second) < 0)
                            return;
                        second = Math.Sqrt(Convert.ToDouble(second)).ToString();
                        memory = Convert.ToDouble(second);
                        label.Text = first + "-" + second;
                        break;
                    }
                }
            }
        }
        else if (label.Text.Length > 1 && (label.Text.Last() == '+' || label.Text.Last() == '-' || label.Text.Last() == '*' || label.Text.Last() == '÷'))
        {
            if (label.Text.Last() == '+' || label.Text.Last() == '-')
            {
                if (Convert.ToDouble(first) < 0)
                    return;
                second = Math.Sqrt(Convert.ToDouble(first)).ToString();
                memory = Convert.ToDouble(second);
                label.Text += second;
            }
            else if (label.Text.Last() == '*' || label.Text.Last() == '÷')
            {
                if (Convert.ToDouble(first) < 0)
                    return;
                second = Math.Sqrt(Convert.ToDouble(first)).ToString();
                memory = Convert.ToDouble(second);
                label.Text += second;
            }
        }
        else
        {
            if (Convert.ToDouble(label.Text) < 0)
                return;
            label.Text = Math.Sqrt(Convert.ToDouble(label.Text)).ToString();
            memory = Convert.ToDouble(label.Text);
        }
        op = '=';
    }
    
    private void OnBtnSquareClicked(object sender, EventArgs e)
    {
        Regex regex = new Regex(@".*[0-9](\+|\*|÷|-)-?[0-9].*");
        MatchCollection matches = regex.Matches(label.Text);

        if (!label.Text.Contains('+') && !label.Text.Contains('-') && !label.Text.Contains('*') && !label.Text.Contains('÷') && Convert.ToDouble(label.Text) == 0)
        {
            label.Text = "0";
            first = "0";
            memory = 0;
        }
        else if (matches.Count > 0)
        {
            if (label.Text.Contains('+'))
            {
                for (int i = 1; i < label.Text.Length; i++)
                {
                    if (i == label.Text.Length - 1)
                        continue;

                    int indPrev = i - 1;
                    int indNext = i + 1;

                    if ((label.Text[i] == '+' || label.Text[i] == '-' || label.Text[i] == '*' || label.Text[i] == '÷')
                        && (label.Text[indPrev] >= '0' && label.Text[indPrev] <= '9' && ((label.Text[indNext] >= '0' && label.Text[indNext] <= '9') || label.Text[indNext] == '-')))
                    {
                        second = (Convert.ToDouble(label.Text.Substring(i + 1)) * Convert.ToDouble(label.Text.Substring(i + 1))).ToString();
                        memory = Convert.ToDouble(second);
                        label.Text = first + "+" + second;
                        break;
                    }
                }
            }
            else if (label.Text.Contains("*"))
            {
                second = (Convert.ToDouble(label.Text.Substring(label.Text.IndexOf("*") + 1)) * Convert.ToDouble(label.Text.Substring(label.Text.IndexOf("*") + 1))).ToString();
                memory = Convert.ToDouble(second);
                label.Text = first + "*" + second;
            }
            else if (label.Text.Contains("÷"))
            {
                second = (Convert.ToDouble(label.Text.Substring(label.Text.IndexOf("÷") + 1)) * Convert.ToDouble(label.Text.Substring(label.Text.IndexOf("÷") + 1))).ToString();
                memory = Convert.ToDouble(second);
                label.Text = first + "÷" + second;
                if (Convert.ToDouble(second) == 0)
                    return;
            }
            else if (label.Text.Contains('-'))
            {
                for (int i = 1; i < label.Text.Length; i++)
                {
                    if (i + 1 == label.Text.Length)
                        continue;

                    int indPrev = i - 1;
                    int indNext = i + 1;

                    if ((label.Text[i] == '+' || label.Text[i] == '-' || label.Text[i] == '*' || label.Text[i] == '÷')
                        && (label.Text[indPrev] >= '0' && label.Text[indPrev] <= '9' && ((label.Text[indNext] >= '0' && label.Text[indNext] <= '9') || label.Text[indNext] == '-')))
                    {
                        second = (Convert.ToDouble(label.Text.Substring(i+1)) * Convert.ToDouble(label.Text.Substring(i + 1))).ToString();
                        memory = Convert.ToDouble(second);
                        label.Text = first + "-" + second;
                        break;
                    }
                }
            }
        }
        else if (label.Text.Length > 1 && (label.Text.Last() == '+' || label.Text.Last() == '-' || label.Text.Last() == '*' || label.Text.Last() == '÷'))
        {
            if (label.Text.Last() == '+' || label.Text.Last() == '-')
            {
                second = (Convert.ToDouble(first) * Convert.ToDouble(first)).ToString();
                memory = Convert.ToDouble(second);
                label.Text += second;
            }
            else if (label.Text.Last() == '*' || label.Text.Last() == '÷')
            {
                second = (Convert.ToDouble(first) * Convert.ToDouble(first)).ToString();
                memory = Convert.ToDouble(second);
                label.Text += second;
            }
        }
        else
        {
            label.Text = (Convert.ToDouble(label.Text) * Convert.ToDouble(label.Text)).ToString();
            memory = Convert.ToDouble(label.Text);
        }
        op = '=';
    }
    
    private void OnBtnDivideByClicked(object sender, EventArgs e)
    {
        Regex regex = new Regex(@".*[0-9](\+|\*|÷|-)-?[0-9].*");
        MatchCollection matches = regex.Matches(label.Text);

        if (!label.Text.Contains('+') && !label.Text.Contains('-') && !label.Text.Contains('*') && !label.Text.Contains('÷') && Convert.ToDouble(label.Text) == 0)
        {
            label.Text = "0";
            first = "0";
            memory = 0;
        }
        else if (matches.Count > 0)
        {
            if (label.Text.Contains('+'))
            {
                for (int i = 1; i < label.Text.Length; i++)
                {
                    if (i == label.Text.Length - 1)
                        continue;

                    int indPrev = i - 1;
                    int indNext = i + 1;

                    if ((label.Text[i] == '+' || label.Text[i] == '-' || label.Text[i] == '*' || label.Text[i] == '÷')
                        && (label.Text[indPrev] >= '0' && label.Text[indPrev] <= '9' && ((label.Text[indNext] >= '0' && label.Text[indNext] <= '9') || label.Text[indNext] == '-')))
                    {
                        second = (1.0 / Convert.ToDouble(label.Text.Substring(i + 1))).ToString();
                        memory = Convert.ToDouble(second);
                        label.Text = first + "+" + second;
                        break;
                    }
                }
            }
            else if (label.Text.Contains("*"))
            {
                second = (1.0 / Convert.ToDouble(label.Text.Substring(label.Text.IndexOf("*") + 1))).ToString();
                memory = Convert.ToDouble(second);
                label.Text = first + "*" + second;
            }
            else if (label.Text.Contains("÷"))
            {
                second = (1.0 / Convert.ToDouble(label.Text.Substring(label.Text.IndexOf("÷") + 1))).ToString();
                memory = Convert.ToDouble(second);
                label.Text = first + "÷" + second;
                if (Convert.ToDouble(second) == 0)
                    return;
            }
            else if (label.Text.Contains('-'))
            {
                for (int i = 1; i < label.Text.Length; i++)
                {
                    if (i + 1 == label.Text.Length)
                        continue;

                    int indPrev = i - 1;
                    int indNext = i + 1;

                    if ((label.Text[i] == '+' || label.Text[i] == '-' || label.Text[i] == '*' || label.Text[i] == '÷')
                        && (label.Text[indPrev] >= '0' && label.Text[indPrev] <= '9' && ((label.Text[indNext] >= '0' && label.Text[indNext] <= '9') || label.Text[indNext] == '-')))
                    {
                        second = (1.0 / Convert.ToDouble(label.Text.Substring(i + 1))).ToString();
                        memory = Convert.ToDouble(second);
                        label.Text = first + "-" + second;
                        break;
                    }
                }
            }
        }
        else if (label.Text.Length > 1 && (label.Text.Last() == '+' || label.Text.Last() == '-' || label.Text.Last() == '*' || label.Text.Last() == '÷'))
        {
            if (label.Text.Last() == '+' || label.Text.Last() == '-')
            {
                second = (1.0 / Convert.ToDouble(first)).ToString();
                memory = Convert.ToDouble(second);
                label.Text += second;
            }
            else if (label.Text.Last() == '*' || label.Text.Last() == '÷')
            {
                second = (1.0 / Convert.ToDouble(first)).ToString();
                memory = Convert.ToDouble(second);
                label.Text += second;
            }
        }
        else
        {
            label.Text = (1.0 / Convert.ToDouble(label.Text)).ToString();
            memory = Convert.ToDouble(label.Text);
        }
        op = '=';
    }

    private void OnBtnPercentClicked(object sender, EventArgs e)
    {
        Regex regex = new Regex(@".*[0-9](\+|\*|÷|-)-?[0-9].*");
        MatchCollection matches = regex.Matches(label.Text);

        if (matches.Count > 0)
        {
            if (label.Text.Contains('+'))
            {
                for (int i = 1; i < label.Text.Length; i++)
                {
                    if (i == label.Text.Length - 1)
                        continue;

                    int indPrev = i - 1;
                    int indNext = i + 1;

                    if ((label.Text[i] == '+' || label.Text[i] == '-' || label.Text[i] == '*' || label.Text[i] == '÷')
                        && (label.Text[indPrev] >= '0' && label.Text[indPrev] <= '9' && ((label.Text[indNext] >= '0' && label.Text[indNext] <= '9') || label.Text[indNext] == '-')))
                    {
                        second = label.Text.Substring(i + 1);
                        second = (Convert.ToDouble(second) / 100.0 * Convert.ToDouble(first)).ToString();
                        memory = Convert.ToDouble(second);
                        label.Text = first + "+" + second;
                        break;
                    }
                }
            }
            else if (label.Text.Contains("*"))
            {
                second = (Convert.ToDouble(label.Text.Substring(label.Text.IndexOf("*") + 1)) / 100.0).ToString();
                memory = Convert.ToDouble(second);
                label.Text = first + "*" + second;
            }
            else if (label.Text.Contains("÷"))
            {
                second = (Convert.ToDouble(label.Text.Substring(label.Text.IndexOf("÷") + 1)) / 100.0).ToString();
                memory = Convert.ToDouble(second);
                label.Text = first + "÷" + second;
                if (Convert.ToDouble(second) == 0)
                    return;
            }
            else if (label.Text.Contains('-'))
            {
                for (int i = 1; i < label.Text.Length; i++)
                {
                    if (i + 1 == label.Text.Length)
                        continue;

                    int indPrev = i - 1;
                    int indNext = i + 1;

                    if ((label.Text[i] == '+' || label.Text[i] == '-' || label.Text[i] == '*' || label.Text[i] == '÷')
                        && (label.Text[indPrev] >= '0' && label.Text[indPrev] <= '9' && ((label.Text[indNext] >= '0' && label.Text[indNext] <= '9') || label.Text[indNext] == '-')))
                    {
                        second = label.Text.Substring(i + 1);
                        second = (Convert.ToDouble(second) / 100.0 * Convert.ToDouble(first)).ToString();
                        memory = Convert.ToDouble(second);
                        label.Text = first + "-" + second;
                        break;
                    }
                }
            }
        }
        else if (label.Text.Length > 1 && (label.Text.Last() == '+' || label.Text.Last() == '-' || label.Text.Last() == '*' || label.Text.Last() == '÷'))
        {
            if (label.Text.Last() == '+' || label.Text.Last() == '-')
            {
                second = (Convert.ToDouble(first) * Convert.ToDouble(first) / 100.0).ToString();
                memory = Convert.ToDouble(second);
                label.Text += second;
            }
            else if (label.Text.Last() == '*' || label.Text.Last() == '÷')
            {
                second = (Convert.ToDouble(first) / 100.0).ToString();
                memory = Convert.ToDouble(second);
                label.Text += second;
            }
        }
        else
        {
            first = "0";
            label.Text = "0";
            memory = 0;
        }
    }
    
    private void OnBtnCEClicked(object sender, EventArgs e)
    {
        Regex regex = new Regex(@".*[0-9](\+|\*|÷|-)-?[0-9].*");
        MatchCollection matches = regex.Matches(label.Text);

        if (matches.Count > 0)
        {
            if (label.Text.Contains('+'))
            {
                second = "0";
                memory = 0;
                label.Text = first + "+" + second;
            }
            else if (label.Text.Contains("*"))
            {
                second = "0";
                memory = 0;
                label.Text = first + "*" + second;
            }
            else if (label.Text.Contains("÷"))
            {
                second = "0";
                memory = 0;
                label.Text = first + "÷" + second;
            }
            else if (label.Text.Contains('-'))
            {
                second = "0";
                memory = 0;
                label.Text = first + "-" + second;
            }
        }
        else if (label.Text.Length > 1 && (label.Text.Last() == '+' || label.Text.Last() == '-' || label.Text.Last() == '*' || label.Text.Last() == '÷'))
        {
            second = "0";
            memory = 0;
            label.Text += second;
        }
        else
        {
            label.Text = "0";
            memory = 0;
            first = second = "0";
        }
    }

    private void CBtn_Clicked(object sender, EventArgs e)
    {
        label.Text = "0";
        first = "0";
        second = "0";
        memory = 0;
    }

    private void OnBtnDeleteClicked(object sender, EventArgs e)
    {
        if (label.Text.Last() == '-' || label.Text.Last() == '+' || label.Text.Last() == '*' || label.Text.Last() == '÷')
        {
            return;
        }

        if (label.Text.Length == 1)
        {
            label.Text = "0";
            return;
        }    

        for (int i = 1; i < label.Text.Length; i++)
        {
            if (i == label.Text.Length - 1)
                continue;

            int indPrev = i - 1;
            int indNext = i + 1;

            if ((label.Text[i] == '+' || label.Text[i] == '-' || label.Text[i] == '*' || label.Text[i] == '÷')
                && (label.Text[indPrev] >= '0' && label.Text[indPrev] <= '9' && ((label.Text[indNext] >= '0' && label.Text[indNext] <= '9') || label.Text[indNext] == '-')))
            {
                second = label.Text.Substring(i + 1);

                if ((second.Length > 0 && second[0] != '-') && !second.Contains("E"))
                {
                    if (second.Length == 1)
                    {
                        second = "0";
                    }
                    else
                    {
                        second = second.Substring(0, second.Length - 1);
                    }
                    label.Text = first + label.Text[i] + second;
                }
                else if (second.Length > 0 && second[0] == '-')
                {
                    if (second.Length == 2)
                    {
                        second = "0";
                    }
                    else
                    {
                        second = second.Substring(0, second.Length - 1);
                    }
                    label.Text = first + label.Text[i] + second;
                }
                return;
            }
        }

        if (label.Text.Contains('E'))
            return;

        if (label.Text.Length == 2 && label.Text[0] == '-')
        {
            memory = 0;
            first = "0";
            label.Text = "0";
        }
        else
        {
            label.Text = label.Text.Substring(0, label.Text.Length - 1);
        }
    }

    private void OnBtnRoundClicked(object sender, EventArgs e)
    {
        Regex regex = new Regex(@".*[0-9](\+|\*|÷|-)-?[0-9].*");
        MatchCollection matches = regex.Matches(label.Text);

        if (!label.Text.Contains('+') && !label.Text.Contains('-') && !label.Text.Contains('*') && !label.Text.Contains('÷') && Convert.ToDouble(label.Text) == 0)
        {
            label.Text = "0";
            first = "0";
            memory = 0;
        }
        else if (matches.Count > 0)
        {
            if (label.Text.Contains('+'))
            {
                for (int i = 1; i < label.Text.Length; i++)
                {
                    if (i == label.Text.Length - 1)
                        continue;

                    int indPrev = i - 1;
                    int indNext = i + 1;

                    if ((label.Text[i] == '+' || label.Text[i] == '-' || label.Text[i] == '*' || label.Text[i] == '÷')
                        && (label.Text[indPrev] >= '0' && label.Text[indPrev] <= '9' && ((label.Text[indNext] >= '0' && label.Text[indNext] <= '9') || label.Text[indNext] == '-')))
                    {
                        second = Math.Round(Convert.ToDouble(label.Text.Substring(i + 1))).ToString();
                        memory = Convert.ToDouble(second);
                        label.Text = first + "+" + second;
                        break;
                    }
                }
            }
            else if (label.Text.Contains("*"))
            {
                second = Math.Round(Convert.ToDouble(label.Text.Substring(label.Text.IndexOf("*") + 1))).ToString();
                memory = Convert.ToDouble(second);
                label.Text = first + "*" + second;
            }
            else if (label.Text.Contains("÷"))
            {
                second = Math.Round(Convert.ToDouble(label.Text.Substring(label.Text.IndexOf("÷") + 1))).ToString();
                memory = Convert.ToDouble(second);
                label.Text = first + "÷" + second;
                if (Convert.ToDouble(second) == 0)
                    return;
            }
            else if (label.Text.Contains('-'))
            {
                for (int i = 1; i < label.Text.Length; i++)
                {
                    if (i + 1 == label.Text.Length)
                        continue;

                    int indPrev = i - 1;
                    int indNext = i + 1;

                    if ((label.Text[i] == '+' || label.Text[i] == '-' || label.Text[i] == '*' || label.Text[i] == '÷')
                        && (label.Text[indPrev] >= '0' && label.Text[indPrev] <= '9' && ((label.Text[indNext] >= '0' && label.Text[indNext] <= '9') || label.Text[indNext] == '-')))
                    {
                        second = Math.Round(Convert.ToDouble(label.Text.Substring(i + 1))).ToString();
                        memory = Convert.ToDouble(second);
                        label.Text = first + "-" + second;
                        break;
                    }
                }
            }
        }
        else if (label.Text.Length > 1 && (label.Text.Last() == '+' || label.Text.Last() == '-' || label.Text.Last() == '*' || label.Text.Last() == '÷'))
        {
            if (label.Text.Last() == '+' || label.Text.Last() == '-')
            {
                second = Math.Round(Convert.ToDouble(first)).ToString();
                memory = Convert.ToDouble(second);
                label.Text += second;
            }
            else if (label.Text.Last() == '*' || label.Text.Last() == '÷')
            {
                second = Math.Round(Convert.ToDouble(first)).ToString();
                memory = Convert.ToDouble(second);
                label.Text += second;
            }
        }
        else
        {
            label.Text = Math.Round(Convert.ToDouble(label.Text)).ToString();
            memory = Convert.ToDouble(label.Text);
        }
        op = '=';
    }
}

