using System.Collections.Generic;
using System.IO;
using System;


namespace CSVImporter {
    public class CSVParser {
        
        public PLCDatabase Parse(string file) {

            PLCDatabase plc = new();

            using (StreamReader sr = new StreamReader(file)) {
                string currentLine;
                while ((currentLine = sr.ReadLine()) != null) {
                    CheckContainsPLC(currentLine, plc);
                    CheckContainsModbusAdr(currentLine, plc);
                    CheckContainsDBBlock(currentLine, plc);
                    CheckContainsOffset(currentLine, plc);
                    CheckContainsPlus(currentLine, plc);
                }
            }

            return plc;
        }

        private void CheckContainsPLC(string line, PLCDatabase p) {
            if (line.Contains("PLC number")) {
                string[] subs = line.Split(';');
                p.PLCNumber = Int32.Parse(subs[1]);
            }
        }

        private void CheckContainsModbusAdr(string line, PLCDatabase p) {
            if (line.Contains("Modbus Adr")) {
                string[] subs = line.Split(';');
                p.ModbusAdr = Int32.Parse(subs[1]); 
            }
        }

        private void CheckContainsDBBlock(string line, PLCDatabase p) {
            if (line.Contains("DB Block")) {
                string[] subs = line.Split(';');
                p.DBBlock = Int32.Parse(subs[1]);
            }
        }

        private void CheckContainsOffset(string line, PLCDatabase p) {
            if (line.Contains("Offset DB Channel")) {
                string[] subs = line.Split(';');
                p.OffsetDBChannel = Int32.Parse(subs[1]);
            }
        }

        private void CheckContainsPlus(string line, PLCDatabase p) {
            if (line.Contains("+")) {
                string[] subs = line.Split(';');
                p.AddNewLineAddr(subs);
            }
        }
    }
}
