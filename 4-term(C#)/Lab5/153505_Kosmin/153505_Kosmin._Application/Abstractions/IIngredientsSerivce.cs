using _153505_Kosmin.Domain.Entitites;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153505_Kosmin._Application.Abstractions;

public interface IIngredientsSerivce: IBaseService<Ingredient>
{
    public Task AddPicById(int Id, string path);
}
