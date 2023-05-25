using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _153505_Kosmin.ViewModels;
using System.Diagnostics;
using CommunityToolkit.Mvvm.Input;
using System.Collections.ObjectModel;
using CommunityToolkit.Maui.Core.Extensions;
using _153505_Kosmin.Domain.Entitites;
using _153505_Kosmin.ValueConverter;

namespace _153505_Kosmin.Pages;

[XamlCompilation(XamlCompilationOptions.Compile)]
public partial class CocktailPage : ContentPage
{
    public CocktailPageViewModel ViewModel { get; set; }
    ObservableCollection<string> cocktails_name;
    
    public CocktailPage(CocktailPageViewModel ViewModel)
    //public CocktailPage()
    {
        InitializeComponent();
        BindingContext = ViewModel;
        this.ViewModel = ViewModel;
        var rate = new RateToColorValueConverter();
        this.ViewModel.selectedCocktail = this.CocktailPicker.SelectedItem as Cocktail;

    }
}