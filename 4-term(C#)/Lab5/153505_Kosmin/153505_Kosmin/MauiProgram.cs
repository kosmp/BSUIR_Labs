using CommunityToolkit.Maui;
using _153505_Kosmin.Domain.Abstractions;
using _153505_Kosmin.Domain.Entitites;
using _153505_Kosmin.Persistense;
using _153505_Kosmin.Persistense.Repository;
using _153505_Kosmin._Application.Abstractions;
using _153505_Kosmin._Application.Services;
using _153505_Kosmin.ViewModels;
using _153505_Kosmin.Pages;
using Microsoft.EntityFrameworkCore;
using _153505_Kosmin.Persistense.Data;
using SQLite;
using _153505_Kosmin.ValueConverter;
using System.Reflection;
using Microsoft.Extensions.Configuration;
using System;

namespace _153505_Kosmin;

public static class MauiProgram
{
	public static MauiApp CreateMauiApp()
	{
		string settingsStream = "_153505_Kosmin.appsettings.json";

		var builder = MauiApp.CreateBuilder();

		var a = Assembly.GetExecutingAssembly();
		using var stream = a.GetManifestResourceStream(settingsStream);
		builder.Configuration.AddJsonStream(stream);

		builder
			.UseMauiApp<App>()
			.ConfigureFonts(fonts =>
			{
				fonts.AddFont("OpenSans-Regular.ttf", "OpenSansRegular");
				fonts.AddFont("OpenSans-Semibold.ttf", "OpenSansSemibold");
			});
		builder.UseMauiApp<App>().UseMauiCommunityToolkit();

		AddDbContext(builder);
		SetupServices(builder.Services);
		SeedData(builder.Services);


		return builder.Build();
	}

	public static void SetupServices(IServiceCollection services)
	{
		//Services
		services.AddSingleton<IUnitofWork, EfUnitOfWork>();
		services.AddSingleton<ICocktailService, CocktailService>();
		services.AddTransient<IIngredientsSerivce, IngredientService>();

		services.AddSingleton<RateToColorValueConverter>();
		var dataPath = Path.Combine(FileSystem.Current.AppDataDirectory, "Cocktails.db");
		services.AddDbContext<AppDbContext>(opt => opt.UseSqlite($"Data Source = {dataPath}"));

		//pages
		services.AddTransient<CocktailPage>();
		services.AddTransient<IngredientDetails>();
		services.AddTransient<AddCocktailPage>();
		services.AddTransient<AddIngredientPage>();
		services.AddScoped<EditIngredient>();

		//ViewModels
		services.AddSingleton<CocktailPageViewModel>();
		services.AddTransient<IngredientDetailsViewModel>();
	}

	private static void AddDbContext(MauiAppBuilder builder)
	{
		var connStr = builder.Configuration
		 .GetConnectionString("SqliteConnection");
		string dataDirectory = String.Empty;
		connStr = String.Format(connStr, dataDirectory);
		var options = new DbContextOptionsBuilder<AppDbContext>()
	   .UseSqlite(connStr)
	   .Options;
		builder.Services.AddSingleton<AppDbContext>((s) =>
		 new AppDbContext(options));
	}

	public async static void SeedData(IServiceCollection services)
	{
		using var provider = services.BuildServiceProvider();
		var unitOfWork = provider.GetService<IUnitofWork>();
		await unitOfWork.RemoveDatbaseAsync();
		await unitOfWork.CreateDatabaseAsync();
		// Add cources
		IReadOnlyList<Cocktail> cocktails = new List<Cocktail>()
		 {
			 new Cocktail(){Name="Cocktail name 1", Strength=10,
							Price=1000},
			 new Cocktail(){Name="Cocktail name 2", Strength=40,
							Price=2000}
		 };
		foreach (var cocktail in cocktails)
			await unitOfWork.CocktailRepository.AddAsync(cocktail);
		await unitOfWork.SaveAllAsync();
		//Add trainees
		Random rand = new Random();
		int k = 1;
		foreach (var cocktail in cocktails)
			for (int j = 0; j < 10; j++)
				await unitOfWork.IngredientRepository.AddAsync(new Ingredient()
				{
					Name = $"Ingredient {k++}",
					RemainNum = (int)rand.NextInt64(0, 30),
					CocktailId = cocktail.Id,
					PicPath = $"pic{k - 1}.jpg"
				});
		//Debug.WriteLine(unitOfWork.IngredientRepository.ListAllAsync().Result.Count);
		await unitOfWork.SaveAllAsync();
	}


}
