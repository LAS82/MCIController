// --------------------------------------------------------------------------------------------------------------------
// Copyright (C) 2017 L.A.S - LAS Soft
//
// This program is free software: you can redistribute it and/or modify
// it under the +terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/. 
//
// Controller.h - Contains the definition of all MCI controller methods.
// 
// Email: lealves_82@yahoo.com.br
// --------------------------------------------------------------------------------------------------------------------

#include <Windows.h>
#include <stdio.h>

#pragma comment(lib, "winmm.lib")

//***************************************
// Constants that helps controlling
// the currently player status.
// Very used with the PlayAudioFacade 
// method.
//****************************************
const int STOPPED_STATUS = 0x00;
const int PAUSED_STATUS = 0x01;
const int PLAYING_STATUS = 0x02;


//****************************************
// Internal method.
// Calculates the size of the open file
// command.
//****************************************
size_t CalcTotalOpenCommandSize(LPSTR lpStrCommand, LPSTR lpEndCommand, LPSTR filename);

//****************************************
// Internal method.
// Opens the file.
//****************************************
void OpenAudioFile(LPSTR lpFilename);

//****************************************
// Internal method.
// Closes the file.
//****************************************
void CloseAudioFile();

//****************************************
// Executes the audio file.
// lpFilename: the filename of the file
// to be playing.
//****************************************
__declspec(dllexport) int ExecAudioFile(LPSTR lpFilename);

//****************************************
// Stops the audio file execution.
//****************************************
__declspec(dllexport) int StopAudioFileExecution();

//****************************************
// Controls the reproduction volume.
// volume: A value between 0 (low) 
// and 1000 (high)
//****************************************
__declspec(dllexport) void AdjustVolume(int volume);

//****************************************
// Pause the audio file execution.
//****************************************
__declspec(dllexport) int PauseAudioFileExec();

//****************************************
// Resumes the audio file execution.
//****************************************
__declspec(dllexport) int ResumeAudioFileExec();

//****************************************
// Returns the current execution time
// in milliseconds
//****************************************
__declspec(dllexport) long GetCurrentPosition();

//****************************************
// Returns the full length in milliseconds
//****************************************
__declspec(dllexport) long GetTotalLength();

//****************************************
// Method created to use with a Play/Pause
// button. That method verifies the 
// current status of the audio and 
// according to this, executes, pause or 
// resumes the audio.
//****************************************
__declspec(dllexport) int PlayAudioFacade(LPSTR lpFilename, int intCurrentlyStatus);
