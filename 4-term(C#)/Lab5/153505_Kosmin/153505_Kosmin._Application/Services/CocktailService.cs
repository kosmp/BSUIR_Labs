using _153505_Kosmin._Application.Abstractions;
using _153505_Kosmin.Domain.Abstractions;
using _153505_Kosmin.Domain.Entitites;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Threading.Tasks;

namespace _153505_Kosmin._Application.Services;

public class CocktailService: ICocktailService
{
    IUnitofWork unitOfWork;
    //CocktailService() { }
    public CocktailService(IUnitofWork unitOfWork)
    {
        this.unitOfWork = unitOfWork;
    }
    public async Task<IEnumerable<Cocktail>> GetAllAsync()
    {
        return await unitOfWork.CocktailRepository.ListAllAsync();
    }
    public Task<IReadOnlyList<Ingredient>> GetIngredientsAsync(int cocktailId) 
    {
        return unitOfWork.IngredientRepository.ListAsync(el => el.CocktailId == cocktailId);
    }
    public Task<Cocktail> GetByIdAsync(int id)
    {
        return unitOfWork.CocktailRepository.GetByIdAsync(id);
    }
    public Task AddAsync(Cocktail cocktail) 
    {
        return unitOfWork.CocktailRepository.AddAsync(cocktail);
    }
    public Task UpdateAsync(Cocktail cocktail) 
    {
        return unitOfWork.CocktailRepository.UpdateAsync(cocktail);
    }
    public Task<Cocktail> DeleteAsync(int Id)
    {
        var cocktail = GetByIdAsync(Id).Result;
        return unitOfWork.CocktailRepository.DeleteAsync(cocktail).ContinueWith(x => cocktail);
    }

}
