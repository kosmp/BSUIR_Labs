using MauiApp1.Entities;
using MauiApp1.Services;
using System.Collections.ObjectModel;
using System.Net.NetworkInformation;

namespace MauiApp1;

public partial class CocktailStorage : ContentPage
{
    private readonly IDbService db;

    public ObservableCollection<Ingredient> Ingredients { get; set; } = new();
    public ObservableCollection<Cocktail> Cocktails { get; set; } = new();

    public CocktailStorage(IDbService dbService)
    {
        InitializeComponent();

        db = dbService;

        db.Init();
        BindingContext = this;
    }

    private void PickerSelectedIndexChanged(object sender, EventArgs e)
    {
        Ingredients.Clear();
        var ing = db.GetCocktailIngredients((picker.SelectedItem as Cocktail).Id);
        foreach(var item in ing)
        {
            Ingredients.Add(item);
        };
    }

    private void OnPage_Loaded(object sender, EventArgs e)
    {
        Cocktails.Clear();
        foreach (var item in db.GetAllCocktails())
        {
            Cocktails.Add(item);
        };
    }
}