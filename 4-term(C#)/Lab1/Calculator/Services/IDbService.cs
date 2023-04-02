using Calculator.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator.Services
{
    public interface IDbService
    {
        IEnumerable<Cocktail> GetAllCocktails();
        IEnumerable<Ingredient> GetCocktailIngredients(int id);
        void Init();
    }
}
