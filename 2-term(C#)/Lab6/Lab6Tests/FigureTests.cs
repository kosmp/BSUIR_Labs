using Microsoft.VisualStudio.TestTools.UnitTesting;
using Lab6;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab6.Tests
{
    [TestClass()]
    public class FigureTest
    {
        [TestMethod()]
        public void infoFigure_test()
        {
            Circle c = new Circle();
            if (c.info() != "Figure")
                Assert.Fail();
        }

        [TestMethod()]
        public void testOverload_test()
        {
            Rectangle rect = new Rectangle();
            if (rect.demOverloadFuncFromBase() != "Figure overload function")
                Assert.Fail();
        }
    }

    [TestClass()]
    public class RectangleTest
    {
        [TestMethod()]
        public void GetPerimeter_test()
        {
            Rectangle rect = new Rectangle();
            rect.Width = 5;
            rect.Height = 3;
            if (rect.GetPerimeter() != 16)
                Assert.Fail();
        }

        [TestMethod()]
        public void GetArea_test()
        {
            Rectangle rect = new Rectangle();
            rect.Width = 5;
            rect.Height = 3;
            if (rect.GetArea() != 15)
                Assert.Fail();
        }

        [TestMethod()]
        public void infoRectangle_test()
        {
            Rectangle rect = new Rectangle();
            rect.Width = 5;
            rect.Height = 3;
            if (rect.info() != "Rectangle")
                Assert.Fail();
        }

        [TestMethod()]
        public void overload_test()
        {
            Rectangle rect = new Rectangle();
            rect.Width = 5;
            rect.Height = 3;
            if (rect.testOverload() != "Rectangle overload function")
                Assert.Fail();
        }
    }

    [TestClass()]
    public class CircleTest
    {
        [TestMethod()]
        public void GetPerimeter_test()
        {
            Circle c = new Circle();
            c.Radius = 2;
            if (c.GetPerimeter() != 12.56)
                Assert.Fail();
        }

        [TestMethod()]
        public void GetArea_test()
        {
            Circle c = new Circle();
            c.Radius = 3;
            if (c.GetArea() != 28.26)
                Assert.Fail();
        }
    }
}