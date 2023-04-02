using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MauiApp1.Services;
using MauiApp1.Entities;
using SQLite;

namespace MauiApp1.Services
{
    public class SQLiteService : IDbService
    {
        private SQLiteConnection database;

        public IEnumerable<Cocktail> GetAllCocktails()
        {
            Init();
            List<Cocktail> cocktails = database.Table<Cocktail>().ToList();
            return cocktails;
        }

        public IEnumerable<Ingredient> GetCocktailIngredients(int id)
        {
            Init();
            return from ingrid in database.Table<Ingredient>()
                   where ingrid.CocktailId == id
                   select ingrid;
        }

        public void Init()
        {
            if (database is not null)
                return;

            database = new SQLiteConnection(Constants.DatabasePath, Constants.Flags);
            database.DropTable<Cocktail>();
            database.DropTable<Ingredient>();
            database.CreateTables<Cocktail, Ingredient>();

            List<Cocktail> cocktails = new List<Cocktail>
            {
                new Cocktail{Name = "Mojito"},
                new Cocktail{Name = "Pina Colada"},
                new Cocktail{Name = "Tropical"}
            };

            List<Ingredient> ingredients = new List<Ingredient>
            {
                new Ingredient{Name = "lime", CocktailId = 1},
                new Ingredient{Name = "mint", CocktailId = 1},
                new Ingredient{Name = "sugar syrup", CocktailId = 1},
                new Ingredient{Name = "soda water", CocktailId = 1},
                new Ingredient{Name = "ice", CocktailId = 1},
                new Ingredient{Name = "pineapple juice", CocktailId = 2},
                new Ingredient{Name = "coconut milk", CocktailId = 2},
                new Ingredient{Name = "ice", CocktailId = 2},
                new Ingredient{Name = "milk", CocktailId = 3},
                new Ingredient{Name = "bananas", CocktailId = 3},
                new Ingredient{Name = "orange juice", CocktailId = 3},
                new Ingredient{Name = "sugar", CocktailId = 3},
                new Ingredient{Name = "ice", CocktailId = 3}
            };

            database.InsertAll(cocktails);
            database.InsertAll(ingredients);;
        }
    }
}
