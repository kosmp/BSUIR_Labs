using SQLite;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator.Entities
{
    [Table("Cocktails")]
    public class Cocktail
    {
        [PrimaryKey, AutoIncrement, Indexed]
        public int Id { get; set; }

        [MaxLength(15)]
        public string Name { get; set; }
    }
}
