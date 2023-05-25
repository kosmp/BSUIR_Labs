using SQLite;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153505_Kosmin.Domain.Entitites;

//[Table("Cocktails")]
public class Cocktail: Entity
{
    /*public Cocktail(string name, double strength, double price, List<Ingredient> ingredients)
    {
        base.Id = id;
        base.Name = name;
        Strength = strength;
        Price = price;
        Ingredients = ingredients;
    }
    public Cocktail(int id, string name, double strength, double price)
    {
        base.Id = id;
        base.Name = name;
        Strength = strength;
        Price = price;
        Ingredients = new List<Ingredient>();
    }
    public Cocktail() { }*/
    public double Strength { get; set; }
    public double Price { get; set; }
    public List<Ingredient> Ingredients { get; set; } = new List<Ingredient>();

}
