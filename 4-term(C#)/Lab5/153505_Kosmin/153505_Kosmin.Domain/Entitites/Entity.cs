using SQLite;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153505_Kosmin.Domain.Entitites;

public class Entity
{
    public Entity() { }
    public Entity(int id, string name)
    {
        Id = id;
        Name = name;
    }

    [PrimaryKey, AutoIncrement, Indexed]
    public int Id { get; set; }
    public string Name { get; set; }
}
