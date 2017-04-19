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
// Controller.c - Contains the implementation of all MCI controller methods.
// 
// Email: lealves_82@yahoo.com.br
// --------------------------------------------------------------------------------------------------------------------

#include "Controller.h"

size_t CalcTotalOpenCommandSize(LPSTR lpStrCommand, LPSTR lpEndCommand, LPSTR filename)
{
	size_t sizeFilename = strlen(filename);
	size_t sizeStrCommand = strlen(lpStrCommand);
	size_t sizeEndCommand = strlen(lpEndCommand);

	return sizeFilename + sizeStrCommand + sizeEndCommand;
}

void OpenAudioFile(LPSTR lpFilename)
{
	LPSTR command;

	LPSTR lpOpenFileStrCommand = "Open \"";
	LPSTR lpOpenFileEndCommand = "\" alias MediaFile";

	size_t totalSize = CalcTotalOpenCommandSize(lpOpenFileStrCommand, lpOpenFileEndCommand, lpFilename);

	command = (LPSTR)calloc(totalSize, sizeof(LPSTR));

	strcat(command, lpOpenFileStrCommand);
	strcat(command, lpFilename);
	strcat(command, lpOpenFileEndCommand);

	mciSendStringA(command, NULL, 0, NULL);

	free(command);
}

void CloseAudioFile()
{
	mciSendStringA("close MediaFile", NULL, 0, NULL);
}

__declspec(dllexport) int ExecAudioFile(LPSTR lpFilename)
{
	OpenAudioFile(lpFilename);

	mciSendStringA("Play MediaFile", NULL, 0, NULL);

	return PLAYING_STATUS;
}

__declspec(dllexport) void AdjustVolume(int volume)
{
	char charVolume[5];
    int i = sprintf(charVolume, "%d", volume);

	LPSTR lpCommand = "setaudio MediaFile volume to ";

	size_t commandSize = strlen(lpCommand);
	
	LPSTR lpFullCommand;

	lpFullCommand = (LPSTR)calloc((commandSize + 0x05), sizeof(LPSTR));

	strcat(lpFullCommand, lpCommand);
	strcat(lpFullCommand, charVolume);

	mciSendStringA(lpFullCommand, NULL, 0, NULL);

	free(lpFullCommand);
}

__declspec(dllexport) int StopAudioFileExecution()
{
	mciSendStringA("stop MediaFile", NULL, 0, NULL);
	
	CloseAudioFile();

	return STOPPED_STATUS;
}

__declspec(dllexport) int PauseAudioFileExec()
{ 
	mciSendStringA("pause MediaFile", NULL, 0, NULL);

	return PAUSED_STATUS;
}

__declspec(dllexport) int ResumeAudioFileExec()
{
	mciSendStringA("resume MediaFile", NULL, 0, NULL);

	return PLAYING_STATUS;
}

__declspec(dllexport) long GetCurrentPosition()
{
	LPSTR lpRet;
	long milliseconds;

	lpRet = (LPSTR)calloc(128, sizeof(LPSTR));

	mciSendStringA("status MediaFile position", lpRet, 128, NULL);
	
	milliseconds = atol(lpRet);

	free(lpRet);

	return milliseconds;
}

__declspec(dllexport) long GetTotalLength()
{
	LPSTR lpRet;
	long milliseconds;

	lpRet = (LPSTR)calloc(128, sizeof(LPSTR));

	mciSendStringA("status MediaFile length", lpRet, 128, NULL);

	milliseconds = atol(lpRet);

	free(lpRet);

	return milliseconds;
}

__declspec(dllexport) int PlayPauseAudioFacade(LPSTR lpFilename, int intCurrentlyStatus)
{
	int newStatus;

	switch (intCurrentlyStatus)
	{
	case 0x00:
		newStatus = ExecAudioFile(lpFilename);
		break;
	case 0x01:
		newStatus = ResumeAudioFileExec();
		break;
	case 0x02:
		newStatus = PauseAudioFileExec();
		break;
	}

	return newStatus;
}