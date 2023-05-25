using _153505_Kosmin.Persistense.Data;
using _153505_Kosmin.Domain.Abstractions;
using _153505_Kosmin.Domain.Entitites;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace _153505_Kosmin.Persistense.Repository;

public class FakeUnitOfWork: IUnitofWork
{
    private readonly AppDbContext _context;
    private readonly Lazy<IRepository<Cocktail>> _cocktailRepository;
    private readonly Lazy<IRepository<Ingredient>> _ingredientRepository;

    IRepository<Cocktail> IUnitofWork.CocktailRepository => _cocktailRepository.Value;
    IRepository<Ingredient> IUnitofWork.IngredientRepository => _ingredientRepository.Value;
    public FakeUnitOfWork(AppDbContext context)
    {

        //_context = new AppDbContext(new Microsoft.EntityFrameworkCore.DbContextOptions<AppDbContext>());
        _context = context;
        _cocktailRepository = new Lazy<IRepository<Cocktail>>(() => new FakeCocktailRepository(_context));
        _ingredientRepository = new Lazy<IRepository<Ingredient>>(() => new FakeIngredientRepository(_context));
    }

    public async Task CreateDatabaseAsync()
    {
        await _context.Database.EnsureCreatedAsync();
    }

    public async Task RemoveDatbaseAsync()
    {
        await _context.Database.EnsureDeletedAsync();
    }

    public async Task SaveAllAsync()
    {
        await _context.SaveChangesAsync();
    }
}
