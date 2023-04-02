namespace MauiApp1;

public partial class ProgressBar : ContentPage
{
    double step = 0.0001;
    CancellationTokenSource cancelTokenSource = new CancellationTokenSource();
    bool isCounting = false;

    public ProgressBar()
    {
        InitializeComponent();
    }

    private async void OnStart(object sender, EventArgs e)
    {
        if (isCounting)
        {
            return;
        }
        isCounting = true;
        cancelTokenSource = new CancellationTokenSource();
        double currentValue = 0;
        double result = 0;
        StatusLabel.Text = "Вычисление";
        while (currentValue <= 1)
        {
            if (cancelTokenSource.Token.IsCancellationRequested)
            {
                StatusLabel.Text = "Задание отменено";
                cancelTokenSource = new CancellationTokenSource();
                return;
            }
            await Task.Run(() =>
            {
                result += step * Math.Sin(currentValue);
            });
            currentValue += step;
            CountingProgressBar.Progress = currentValue;
            ProgressPercentages.Text = Convert.ToString(Convert.ToInt32(currentValue * 100)) + "%";
        }
        StatusLabel.Text = "Результат: " + Convert.ToString(result);
        isCounting = false;
    }

    private void OnCancel(object sender, EventArgs e)
    {
        cancelTokenSource.Cancel();
        isCounting = false;
    }
}