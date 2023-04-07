using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSVImporter {
    public class PLCDatabase {

        private List<PLCAddress> AddrList = new List<PLCAddress>();
        public int PLCNumber;
        public int ModbusAdr;
        public int DBBlock;
        public int OffsetDBChannel;

        public void AddNewLineAddr(string[] subs) {
            PLCAddress addr = new();

            addr.Address = subs[0].Trim('+');
            addr.Name = subs[1];
            addr.ChannelType = subs[2];
            addr.NoOfBits = Int32.Parse(subs[3]);
            addr.Type = subs[4];
            addr.InitialValue = subs[5];
            addr.Comment = subs[6];
            addr.ChannelName = subs[7];
            addr.ChannelReference = subs[8];


            AddrList.Add(addr);

            Console.WriteLine(String.Format("Address = {0}, Name = {1}, ChannelType = {2}, NoOfBits = {3}, Type = {4}, InitValue = {5}, Comment = {6}, ChannelName = {7}, ChannelRef = {8}",
                addr.Address, addr.Name, addr.ChannelType, addr.NoOfBits, addr.Type, addr.InitialValue, addr.Comment, addr.ChannelName, addr.ChannelReference));
        }
    }
}
