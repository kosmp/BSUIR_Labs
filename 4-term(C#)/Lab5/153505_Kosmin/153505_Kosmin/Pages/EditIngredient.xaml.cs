namespace _153505_Kosmin.Pages;
using _153505_Kosmin.ViewModels;
using _153505_Kosmin.Domain.Entitites;
using System.Diagnostics;
using System.Linq;

public partial class EditIngredient : ContentPage, IQueryAttributable
{

    CocktailPageViewModel ViewModel;
	public EditIngredient(CocktailPageViewModel ViewModel)
	{
		InitializeComponent();
        this.ViewModel = ViewModel;
        this.pick.ItemsSource = this.ViewModel.Cocktails.Select(x => x.Name).ToList();
        this.pick.SelectedIndex = this.ViewModel.SelectedCocktail.Id - 1;
        //this.pick.ItemDisplayBinding = this.ViewModel.SelectedCocktail;
	}

    Ingredient cur;

    public void ApplyQueryAttributes(IDictionary<string, object> query)
    {

        cur = (Ingredient)query["Ingredient"];
        Debug.WriteLine(cur.Name);
        Debug.WriteLine(cur.CocktailId);

        this.name.Text = cur.Name;
        this.num.Text = cur.RemainNum.ToString();
        this.img.Source = cur.PicPath;
        this.pick.SelectedIndex = cur.CocktailId - 1;
    }

    public async void ApplyChanges(object sender, EventArgs e)
    {
        cur.Name = this.name.Text;
        cur.RemainNum = Convert.ToInt32(this.num.Text);
        cur.PicPath = this.img.Source.ToString().Remove(0, 6);
        cur.CocktailId = this.pick.SelectedIndex + 1;
        await ViewModel._ingredientService.UpdateAsync(cur);
        Debug.WriteLine(ViewModel._ingredientService.GetByIdAsync(11).Result.CocktailId);
        Debug.WriteLine(ViewModel.Ingredients[0].Name);
        ViewModel.UpdateIngredientListCommand.Execute(null);
        ViewModel.GetIngredients();
        await Shell.Current.GoToAsync("..");
    }

    public async void ChangeImage(object sender, EventArgs e)
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