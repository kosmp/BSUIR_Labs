using SQLite;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator.Entities
{
    [Table("Ingredients")]
    public class Ingredient
    {
        [PrimaryKey, AutoIncrement, Indexed]
        public int IngredientId { get; set; }
        public string Name { get; set; }

        [Indexed]
        public int CocktailId { get; set; }
    }
}
