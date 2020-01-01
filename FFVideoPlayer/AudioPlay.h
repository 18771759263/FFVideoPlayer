/*

“Ù∆µ≤•∑≈

*/

#pragma once
#include <QtMultimedia/QAudioOutput>
#include <QtCore/QMutex>


class AudioPlay
{
public:
	static AudioPlay* Get();

	QAudioOutput *m_AudioOutput = NULL;
	QIODevice *io = NULL;
	QMutex mutex;

	int sampleRate = 48000;
	int sampleSize = 16;
	int channel = 2;

public:
	void Stop();
	bool Start();
	void Play(bool isPlay);
	bool Write(const char *data, int datasize);
	int GetFree();
	void SetVolume(int value);

private:
	AudioPlay() {}
};

