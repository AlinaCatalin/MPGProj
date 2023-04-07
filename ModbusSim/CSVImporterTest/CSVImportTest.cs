using CSVImporter;

using System.Reflection;
using System.Resources;
using System;
using System.IO;
using System.Collections.Generic;

namespace CSVImporterTest {
    class CSVImportTest {

        public static ResourceManager rm = new ResourceManager("CSVImporterTest.Resources.MPGResources", Assembly.GetExecutingAssembly());
        private static String csvDirectoryPath = String.Format("{0}\\{1}",
            Directory.GetCurrentDirectory(), rm.GetString("CSVDirectory"));

        public static List<PLCDatabase> blockAddressList = new();
        public static CSVParser p = new();

        
        static void Main(string[] args) {

            string var = String.Format("{0}\\", csvDirectoryPath);
            var filePaths = Directory.GetFiles(var, "*.csv");

            foreach (string s in filePaths) {
                PLCDatabase plc = p.Parse(s);
                blockAddressList.Add(plc);
                Console.ReadLine();
            }
            
        }
    }
}
