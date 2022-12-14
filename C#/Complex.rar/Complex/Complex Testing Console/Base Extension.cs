/* ============= */
/*               */
/*   Extension   */
/*               */
/* ============= */
using System;
namespace ComplexTestingConsole
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
        public static void Main()
        {
            Base.Main();
            Release();
        }
    }
}
