using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _153505_Kosmin.ViewModels;
using System.Diagnostics;
using _153505_Kosmin.Domain.Entitites;
using CommunityToolkit.Mvvm.Input;

namespace _153505_Kosmin.Pages;

[XamlCompilation(XamlCompilationOptions.Compile)]
public partial class IngredientDetails : ContentPage, IQueryAttributable
{
    IngredientDetailsViewModel ViewModel;


    public Ingredient cur { get; set; }
    public IngredientDetails(IngredientDetailsViewModel ViewModel)
    {
        InitializeComponent();

        this.ViewModel = ViewModel;
        //BindingContext = ViewModel;

        //this.lbl.Text = ViewModel.cur.Name;
    }
    public void ApplyQueryAttributes(IDictionary<string, object> query)
    {
        cur = (Ingredient)query["Ingredient"];

        this.NameLabel.Text = "Ingredient name: " + cur.Name;
        this.IngrImg.Source = cur.PicPath;
        this.RemainNum.Text = "Remain num: " + cur.RemainNum;


    }

    async void EditEvent(object sender, EventArgs e)
    {
        IDictionary<string, object> parameters = new Dictionary<string, object>()
        {
            {"Ingredient", cur }
        };
        await Shell.Current.GoToAsync($"{nameof(EditIngredient)}", parameters);
    }

    //Command="{Binding Source={RelativeSource AncestorType={x:Type models:IngredientDetailsViewModel}}, Path=EditIngrCommand}" CommandParameter="{Binding cur}"

}