using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _153505_Kosmin._Application.Abstractions;
using _153505_Kosmin.Domain.Abstractions;
using _153505_Kosmin.Domain.Entitites;

namespace _153505_Kosmin._Application.Services;

public class IngredientService : IIngredientsSerivce
{
    IUnitofWork unitOfWork;
    public IngredientService(IUnitofWork unitOfWork)
    {
        this.unitOfWork = unitOfWork;
    }
    public Task<IEnumerable<Ingredient>> GetAllAsync()
    {
        return Task.Run(() => unitOfWork.IngredientRepository.ListAllAsync().Result.ToList().AsEnumerable());
    }
    public Task<Ingredient> GetByIdAsync(int id)
    {
        return unitOfWork.IngredientRepository.FirstOrDefaultAsync(x => x.Id == id);
    }
    public Task AddAsync(Ingredient ingredient)
    {
        return unitOfWork.IngredientRepository.AddAsync(ingredient);
    }
    public Task UpdateAsync(Ingredient ingredient)
    {
        return unitOfWork.IngredientRepository.UpdateAsync(ingredient);
    }
    public Task<Ingredient> DeleteAsync(int Id)
    {
        var ingredient = GetByIdAsync(Id).Result;
        return unitOfWork.IngredientRepository.DeleteAsync(ingredient).ContinueWith(x => ingredient);
    }
    public Task AddPicById(int Id, string path)
    {
        var ingredient = GetByIdAsync(Id).Result;
        ingredient.PicPath = path;
        return UpdateAsync(ingredient);
    }

    public Task ChangeRemainNum(int Id, int new_num)
    {
        var ingredient = GetByIdAsync(Id).Result;
        ingredient.RemainNum = new_num;
        return UpdateAsync(ingredient);
    }
    public Task AddToCocktail(int Id, int CocktailId)
    {
        var ingredient = GetByIdAsync(Id).Result;
        ingredient.CocktailId = CocktailId;
        return UpdateAsync(ingredient);
    }
}
