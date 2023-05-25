using SQLite;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153505_Kosmin.Domain.Entitites;

[Table("Ingredients")]
public class Ingredient: Entity
{
    
    /*public Ingredient(int id, string name, int remainNum, int cocktailiId) 
    {
        base.Id = id;
        this.Name = name;
        RemainNum = remainNum;
        CocktailId = cocktailiId;
    }
    public Ingredient() { }*/
    public int RemainNum { get; set; }
    public string? PicPath { get; set; } = "default.png";
    //[Indexed]
    public int CocktailId { get; set; }
}
