using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _153505_Kosmin.Pages;
using System.Diagnostics;
using _153505_Kosmin.Domain.Entitites;
using System.Web;
using _153505_Kosmin._Application.Abstractions;

namespace _153505_Kosmin.ViewModels;
public partial class IngredientDetailsViewModel : ObservableObject
{
    public readonly ICocktailService _cocktailService;
    public readonly IIngredientsSerivce _ingredientService;
    public IngredientDetailsViewModel(ICocktailService cocktailService, IIngredientsSerivce ingredientSerivce) 
    {
        Debug.WriteLine("qweqweqweqweqweqweqweqweqweqweqweqwe");
        _cocktailService = cocktailService;
        _ingredientService = ingredientSerivce;
    }

    public Ingredient cur { get; set; }

    /*[RelayCommand]
    public async void EditIngr(Ingredient ingredient) => await Edit(ingredient);

    public async Task Edit(Ingredient ingredient)
    {
        IDictionary<string, object> parameters = new Dictionary<string, object>()
        {
            {"Ingredient", ingredient }
        };
        Debug.WriteLine("zxczxczxc");
        await Shell.Current.GoToAsync($"{nameof(EditIngredient)}", parameters);
    }*/


}
