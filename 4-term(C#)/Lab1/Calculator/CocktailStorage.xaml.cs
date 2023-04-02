using Calculator.Entities;
using Calculator.Services;
using System.Collections.ObjectModel;

namespace Calculator;

public partial class CocktailStorage : ContentPage
{
	private readonly SQLiteService db;

	public ObservableCollection<Ingredient> Ingredients { get; set; }
	public ObservableCollection<Cocktail> Cocktails { get; set; }

	public CocktailStorage(IDbService dbService)
	{
        InitializeComponent();

        db = dbService as SQLiteService;
        db.Init();
        BindingContext = this;
    }

	public CocktailStorage()
	{
		InitializeComponent();
	}

    private void PickerSelectedIndexChanged(object sender, EventArgs e)
    {
        Ingredients = new ObservableCollection<Ingredient>(db.GetCocktailIngredients((picker.SelectedItem as Cocktail).Id));
        IngredientListView.ItemsSource = Ingredients;
    }

    private void OnPage_Loaded(object sender, EventArgs e)  
    {
        Cocktails = new ObservableCollection<Cocktail>(db.GetAllCocktails());
        picker.ItemsSource = null;
        picker.ItemsSource = Cocktails;
    }
}