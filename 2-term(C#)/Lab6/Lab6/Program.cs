using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab6
{
    public abstract class Figure
    {
        public Figure()
        {
            Console.WriteLine("Constructing figure");
        }

        public abstract double GetPerimeter();
        public abstract double GetArea();

        public virtual string info()
        {
            return "Figure";
        }

        public string testOverload()
        {
            return "Figure overload function";
        }
    }

    public class Rectangle : Figure
    {
        public Rectangle()
        {
            Console.WriteLine("Constructing rectangle");
        }

        public override double GetPerimeter()
        {
            return Width * 2 + Height * 2;
        }

        public override double GetArea()
        {
            return Width * Height;
        }

        public float Width { get; set; }
        public float Height { get; set; }

        public override string info()
        {
            return "Rectangle";
        }

        public string testOverload()
        {
            return "Rectangle overload function";
        }

        public string demOverloadFuncFromBase()
        {
            return base.testOverload();
        }
    }

    public class Circle : Figure
    {
        public Circle()
        {
            Console.WriteLine("Constructing circle");
        }

        public double Radius { get; set; }

        public override double GetPerimeter()
        {
            return Radius * 2 * 3.14;
        }

        public override double GetArea()
        {
            return Radius * Radius * 3.14;
        }
    }

    sealed class TestClass
    {

    }

    public class Program
    {
        static void Main(string[] args)
        {
            Rectangle rect = new Rectangle();
            rect.Width = 5;
            rect.Height = 3;
            Console.WriteLine("Rectangle Perimetr: " + rect.GetPerimeter());
            Console.WriteLine("Rectangle Area: " + rect.GetArea());
            Console.WriteLine("Info from rectangle: " + rect.info() + '\n');
            Console.WriteLine(rect.testOverload());
            Console.WriteLine(rect.demOverloadFuncFromBase() + '\n');

            Circle c = new Circle();
            c.Radius = 5;
            Console.WriteLine("Circle Perimetr: " + c.GetPerimeter());
            Console.WriteLine("Circle Area: " + c.GetArea());
            Console.WriteLine("Try to get info() from circle: " + c.info());
        }
    }
}
