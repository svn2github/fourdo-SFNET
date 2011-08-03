﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace FourDO.Emulation.Plugins
{
    public interface IAudioPlugin
    {
        void Destroy();

        bool GetHasSettings();
        void ShowSettings(IWin32Window owner);

        void PushSample(uint dspSample);
    }
}
