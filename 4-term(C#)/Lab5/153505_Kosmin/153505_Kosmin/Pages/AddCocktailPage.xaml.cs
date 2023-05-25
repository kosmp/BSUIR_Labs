using _153505_Kosmin.Domain.Entitites;
using _153505_Kosmin.ViewModels;
using System.Diagnostics;

namespace _153505_Kosmin.Pages;

public partial class AddCocktailPage : ContentPage
{
	CocktailPageViewModel ViewModel;
	public AddCocktailPage(CocktailPageViewModel ViewModel)
	{
		InitializeComponent();

		this.ViewModel = ViewModel;
	}

	 async void AddCocktailEvent(object sender, EventArgs e)
	{
		var name = this.CocktailName.Text;
		var price = Convert.ToInt32(this.CocktailPrice.Text);
		var strength = Convert.ToDouble(this.CocktailStrength.Text);
		var id = ViewModel._cocktailService.GetAllAsync().Result.ToList().Count + 1;
		var ckct = new Cocktail();
		ckct.Name = name;
		ckct.Price = price;
		ckct.Strength = strength;
		var tmp = ViewModel.SelectedCocktail;
		ViewModel._cocktailService.AddAsync(ckct);
		ViewModel.SelectedCocktail = new Cocktail();
		ViewModel.UpdateCocktailList();
        //ViewModel.SelectedCocktail = ViewModel.Cocktails.ToList()[0];
        await Shell.Current.GoToAsync("..");
    }
}