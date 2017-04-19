# MCI Controller for audio

---

The MCI (Media Control Interface) for audio contains a set of exposed methods
that may be used to play audio files in Microsoft Windows without any Windows Media Player
library.

---

Here are some samples on how to use it with .NET Framework:


###### Executing an audio file
```

[DllImport("MCI_Controller.dll", CallingConvention = CallingConvention.Cdecl)]
static extern int ExecAudioFile(String filename);

int playStatus = 0;

private void btnOpenAndPlayFile_Click(object sender, EventArgs e)
{
	playStatus = ExecAudioFile(filename);
}

```


###### Controlling Play/Pause button

```

[DllImport("MCI_Controller.dll", CallingConvention = CallingConvention.Cdecl)]
static extern int PlayPauseAudioFacade(String filename, int currentPlayStatus);

int playStatus = 0;

private void btnPlayPauseResume_Click(object sender, EventArgs e)
{
	playStatus = PlayPauseAudioFacade(filename, playStatus);
}

```