using _153505_Kosmin.Domain.Entitites;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153505_Kosmin.Domain.Abstractions;

public interface IUnitofWork
{
    IRepository<Cocktail> CocktailRepository { get; }
    IRepository<Ingredient> IngredientRepository { get; }
    public Task RemoveDatbaseAsync();
    public Task CreateDatabaseAsync();
    public Task SaveAllAsync();
}
