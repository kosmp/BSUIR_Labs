using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _153505_Kosmin.Domain.Entitites;

namespace _153505_Kosmin._Application;
public interface IBaseService<T> where T : Entity
{
    Task<IEnumerable<T>> GetAllAsync();
    Task<T> GetByIdAsync(int id);
    Task AddAsync(T item);
    Task UpdateAsync(T item);
    Task<T> DeleteAsync(int id);
}
