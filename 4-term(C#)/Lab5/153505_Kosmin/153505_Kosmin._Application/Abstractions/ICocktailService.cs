using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _153505_Kosmin.Domain.Entitites;

namespace _153505_Kosmin._Application.Abstractions;

public interface ICocktailService: IBaseService<Cocktail>
{
    public Task<IReadOnlyList<Ingredient>> GetIngredientsAsync(int cocktailId);
}
