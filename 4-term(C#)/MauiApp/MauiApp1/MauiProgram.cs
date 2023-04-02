using MauiApp1.Entities;
using MauiApp1.Services;
using Microsoft.Extensions.Logging;

namespace MauiApp1;

public static class MauiProgram
{
    public static MauiApp CreateMauiApp()
    {
        var builder = MauiApp.CreateBuilder();
        builder
            .UseMauiApp<App>()
            .ConfigureFonts(fonts =>
            {
                fonts.AddFont("OpenSans-Regular.ttf", "OpenSansRegular");
                fonts.AddFont("OpenSans-Semibold.ttf", "OpenSansSemibold");
            });

        builder.Services.AddTransient<IDbService, SQLiteService>();
        builder.Services.AddSingleton<CocktailStorage>();

#if DEBUG
        builder.Logging.AddDebug();
#endif

        return builder.Build();
    }
}
