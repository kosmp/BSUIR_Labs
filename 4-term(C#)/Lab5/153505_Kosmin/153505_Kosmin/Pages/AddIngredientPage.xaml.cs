namespace _153505_Kosmin.Pages;
using _153505_Kosmin.ViewModels;
using _153505_Kosmin.Domain.Entitites;
using System.Windows.Input;
using System.Diagnostics;

public partial class AddIngredientPage : ContentPage
{
    Ingredient elToAdd = new Ingredient();

    CocktailPageViewModel ViewModel;
    public AddIngredientPage(CocktailPageViewModel ViewModel)
	{
		InitializeComponent();
        this.ViewModel = ViewModel;
	}

    public async void AddEvent(object sender, EventArgs e)
    {
        elToAdd.Name = this.name.Text;
        elToAdd.RemainNum = Convert.ToInt32(this.num.Text);
        elToAdd.PicPath = this.img.Source.ToString().Remove(0, 6);
        elToAdd.CocktailId = ViewModel.SelectedCocktail.Id;
        ViewModel._cocktailService.GetByIdAsync(ViewModel.SelectedCocktail.Id).Result.Ingredients.Add(elToAdd);
        ViewModel._ingredientService.AddAsync(elToAdd);
        ViewModel.UpdateIngredientList();
        await Shell.Current.GoToAsync("..");
    }

    public async void AddImage(object sender, EventArgs e)
    {
        var result = await FilePicker.Default.PickAsync();
        if (result != null)
        {
            if (result.FileName.EndsWith("jpg", StringComparison.OrdinalIgnoreCase) ||
                result.FileName.EndsWith("png", StringComparison.OrdinalIgnoreCase))
            {
                var tmp = result.FileName;
                this.img.Source = tmp;
                Debug.WriteLine(tmp);
            }
        }
    }
}