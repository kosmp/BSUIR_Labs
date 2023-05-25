using _153505_Kosmin.Pages;

namespace _153505_Kosmin;

public partial class AppShell : Shell
{
	public AppShell()
	{
		InitializeComponent();
		Routing.RegisterRoute(nameof(IngredientDetails),
							  typeof(IngredientDetails));
		Routing.RegisterRoute(nameof(AddCocktailPage),
							  typeof(AddCocktailPage));
		Routing.RegisterRoute(nameof(AddIngredientPage),
							  typeof(AddIngredientPage));
		Routing.RegisterRoute(nameof(EditIngredient),
							  typeof(EditIngredient));
	}
}
