using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Threading.Tasks;
using _153505_Kosmin._Application.Abstractions;
using _153505_Kosmin.Domain.Entitites;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using _153505_Kosmin.Pages;

namespace _153505_Kosmin.ViewModels;

public partial class CocktailPageViewModel : ObservableObject
{
    public readonly ICocktailService _cocktailService;
    public readonly IIngredientsSerivce _ingredientService;

    public CocktailPageViewModel(ICocktailService cocktailService, IIngredientsSerivce ingredientSerivce)
    {
        Debug.WriteLine("qweqweqweqweqweqweqweqweqweqweqweqwe");
        _cocktailService = cocktailService;
        _ingredientService = ingredientSerivce;
        Cocktails = new();
        Ingredients = new();
    }
    /*public CocktailPageViewModel()
    {
        Debug.WriteLine("asdasdasdasdasdasdasdasdadasd");
    }*/
    ObservableCollection<Cocktail> cocktails;
    ObservableCollection<Ingredient> ingredients;
    public ObservableCollection<Cocktail> Cocktails { get => cocktails; set=>SetProperty(ref cocktails, value); }
    public ObservableCollection<Ingredient> Ingredients { get => ingredients; set => SetProperty(ref ingredients, value); }

    [ObservableProperty]
    public Cocktail selectedCocktail;

    [RelayCommand]
    async void Ingr() => await AddIngredient();
    private async Task AddIngredient()
    {
        await Shell.Current.GoToAsync($"{nameof(AddIngredientPage)}");
    }

    [RelayCommand]
    async void Cockt() => await AddCocktail();
    private async Task AddCocktail()
    {
        await Shell.Current.GoToAsync($"{nameof(AddCocktailPage)}");
    }

    [RelayCommand]
    async void ShowDetails(Ingredient ingredient) => await GotoDetailsPage(ingredient);
    private async Task GotoDetailsPage(Ingredient ingredient)
    {
        IDictionary<string, object> parameters = new Dictionary<string, object>()
        {
            {"Ingredient", ingredient }
        };
        await Shell.Current.GoToAsync($"{nameof(IngredientDetails)}", parameters);
    }


    [RelayCommand]
    public async void UpdateCocktailList() => await GetCocktails();
    [RelayCommand]
    public async void UpdateIngredientList() => await GetIngredients();

    //public async Task SetCocktails()
    //public async Task SetIngredients()

    public async Task GetCocktails()
    {
        var cocktails = await _cocktailService.GetAllAsync();
        await MainThread.InvokeOnMainThreadAsync(() =>
        {
            Cocktails.Clear();
            foreach (var cocktail in cocktails)
                Cocktails.Add(cocktail);
        });
    }
    public async Task GetIngredients()
    {
        Debug.WriteLine(SelectedCocktail.Id);
        Debug.WriteLine("qwert");
        var ingredients = await _cocktailService.GetIngredientsAsync(selectedCocktail.Id);
        await MainThread.InvokeOnMainThreadAsync(() =>
        {
            Ingredients.Clear();
            foreach (var ingredient in ingredients)
            {

                Ingredients.Add(ingredient);
                Debug.WriteLine(ingredient.Name);
            }
        });
        OnPropertyChanged();
        Ingredients = Ingredients;
    }


}

