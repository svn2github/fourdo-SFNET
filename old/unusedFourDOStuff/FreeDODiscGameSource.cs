using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using FourDO.Utilities;
using System.Windows.Forms;
using CDLib;
using System.Runtime.InteropServices;

namespace FourDO.Emulation.GameSource
{
    internal class FreeDODiscGameSource : DiscGameSource
    {
        [DllImport(@"discreader.dll", EntryPoint = "__drc_Interface")]
        private static extern IntPtr DiscInterface(int procedure, IntPtr datum);

        public FreeDODiscGameSource(char driveLetter)
            : base(driveLetter)
        {
        }

        #region IGameSource Implementation

        protected override unsafe void OnOpen()
        {
            base.Open();
            
            byte[] buffer = new byte[256];
            fixed (byte* tempPtr = buffer)
            {
                DiscInterface(5, new IntPtr((int)tempPtr));
                DiscInterface(1, new IntPtr((int)tempPtr));
            }
        }

        protected override void OnClose()
        {
        }

        /*
        protected override int OnGetSectorCount()
        {
            int badcount = base.GetSectorCount();

            int goodcount = (int)DiscInterface(3, new IntPtr(0));

            if (badcount != goodcount)
                Console.WriteLine("difference!");

            return goodcount;
        }
         * */

        private byte[] badbuffer = new byte[2048];
        protected override unsafe void OnReadSector(IntPtr destinationBuffer, int sectorNumber)
        {
            // old style
            fixed (byte* badPtr = badbuffer)
            {
                base.ReadSector(destinationBuffer, sectorNumber);
            
                // New working style.
                //DiscInterface(4, new IntPtr(sectorNumber));
                //DiscInterface(2, new IntPtr(badPtr));

                /*
                int* srcBad = (int*)badPtr;
                int* srcGood = (int*)destinationBuffer.ToPointer();
                for (int x = 0; x < 2048 / 4; x++)
                {
                    if (*srcBad != *srcGood)
                    {
                        Console.WriteLine("difference!");
                    }
                    srcBad++;
                    srcGood++;
                }
                 * */
            }
        }

        #endregion // IGameSource Implementation
    }
}
