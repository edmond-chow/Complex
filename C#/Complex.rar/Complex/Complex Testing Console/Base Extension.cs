/* ============= */
/*               */
/*   Extension   */
/*               */
/* ============= */
using System;
namespace CmplxConExt
{
    internal class Original
    {
        private static readonly ConsoleColor ForegroundColor;
        private static readonly ConsoleColor BackgroundColor;
        private static readonly string Title;
        static Original()
        {
            ForegroundColor = Console.ForegroundColor;
            BackgroundColor = Console.BackgroundColor;
            Title = Console.Title;
        }
        private static void Release()
        {
            Console.ForegroundColor = ForegroundColor;
            Console.BackgroundColor = BackgroundColor;
            Console.Title = Title;
        }
        private static void Main()
        {
            ComplexTestingConsole.Base.Main();
            Release();
        }
    }
}
