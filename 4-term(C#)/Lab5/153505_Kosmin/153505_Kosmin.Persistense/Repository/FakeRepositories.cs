using _153505_Kosmin.Domain.Abstractions;
using _153505_Kosmin.Domain.Entitites;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Xml.Linq;

namespace _153505_Kosmin.Persistense.Repository;

public class FakeIngredientRepository : IRepository<Ingredient>
{
    List<Ingredient> _ingredients = new List<Ingredient>();
    private readonly DbContext _dbContext;
    public FakeIngredientRepository(DbContext dbContext)
    {
        Random rand = new Random();
        int k = 1;
        for (int i = 1; i <= 2; i++)
            for (int j = 0; j < 10; j++)
                _ingredients.Add(new Ingredient()
                {
                    Id = k,
                    Name = $"Trainee {k++}",
                    CocktailId = i,
                    RemainNum = rand.Next(0, 10)
                });
        _dbContext = dbContext;
    }
    public async Task<IReadOnlyList<Ingredient>> ListAsync(Expression<Func<Ingredient, bool>> filter, CancellationToken
cancellationToken = default, params Expression<Func<Ingredient, object>>[]?
includesProperties)
    {
        var data = _ingredients.AsQueryable();
        return data.Where(filter).ToList();
    }
    public Task<IReadOnlyList<Ingredient>> ListAllAsync(CancellationToken cancellationToken = default)
    {
        throw new NotImplementedException();
    }
    public Task AddAsync(Ingredient entity, CancellationToken cancellationToken = default)
    {
        throw new NotImplementedException();
    }
    public Task UpdateAsync(Ingredient entity, CancellationToken cancellationToken = default)
    {
        throw new NotImplementedException();
    }
    public Task DeleteAsync(Ingredient entity, CancellationToken cancellationToken = default)
    {
        throw new NotImplementedException();
    }
    public Task<Ingredient> FirstOrDefaultAsync(Expression<Func<Ingredient, bool>> filter, CancellationToken
                                cancellationToken = default)
    {
        throw new NotImplementedException();
    }
    public Task<Ingredient> GetByIdAsync(int id, CancellationToken cancellationToken = default,
                       params Expression<Func<Ingredient, object>>[]? includeProperties)
    {
        throw new NotImplementedException();
    }

}


public class FakeCocktailRepository : IRepository<Cocktail>
{
    public List<Cocktail> _cocktails;
    private readonly DbContext _dbContext;

    public FakeCocktailRepository(DbContext dbContext)
    {
        _cocktails = new List<Cocktail>()
        {
            //new Cocktail() { Id = 1, Name = "Cocktail 1", Strength = 10.5, Price = 1000, Ingredients = new List<Ingredient>(){ new Ingredient() { Id = 1,Name= "qwe", RemainNum = 40, CocktailId = 1 }, new Ingredient(2, "ads", 20, 1) } },
            //new Cocktail() { Id = 2, Name = "Cocktail 2", Strength = 35, Price = 2000, Ingredients = new List<Ingredient>() {new Ingredient(1, "zxc", 20, 1), new Ingredient(2, "asd", 400, 1) }}
        };
        _dbContext = dbContext;
    }
    public List<Cocktail> GetGet()
    {
        return _cocktails;
    }
    public async Task<IReadOnlyList<Cocktail>> ListAllAsync(CancellationToken cancellationToken = default)
    {
        return await Task.Run(() => _cocktails);
    }

    public Task<IReadOnlyList<Cocktail>> ListAsync(Expression<Func<Cocktail, bool>> filter,
                                     CancellationToken cancellationToken = default,
                                     params Expression<Func<Cocktail, object>>[]? includesProperties)
    {
        throw new NotImplementedException();
    }
    public Task AddAsync(Cocktail entity, CancellationToken cancellationToken = default)
    {
        throw new NotImplementedException();
    }
    public Task UpdateAsync(Cocktail entity, CancellationToken cancellationToken = default)
    {
        throw new NotImplementedException();
    }
    public Task DeleteAsync(Cocktail entity, CancellationToken cancellationToken = default)
    {
        throw new NotImplementedException();
    }
    public Task<Cocktail> FirstOrDefaultAsync(Expression<Func<Cocktail, bool>> filter, CancellationToken
                                cancellationToken = default)
    {
        throw new NotImplementedException();
    }
    public Task<Cocktail> GetByIdAsync(int id, CancellationToken cancellationToken = default,
                       params Expression<Func<Cocktail, object>>[]? includeProperties)
    {
        Debug.WriteLine(id);
        return Task.Run(() => _cocktails[id - 1]);
    }
}
