#include "AudioPlay.h"
#include <QtMultimedia/QAudioOutput>
#include <QtCore/QMutex>


void AudioPlay::Stop()
{
	mutex.lock();
	if (m_AudioOutput)
	{
		m_AudioOutput->stop();
		delete m_AudioOutput;
		m_AudioOutput = NULL;
		io = NULL;
	}

	mutex.unlock();
}

bool AudioPlay::Start()
{
	Stop();
	mutex.lock();
	QAudioFormat fmt; //Qt音频的格式
	fmt.setSampleRate(this->sampleRate); //1秒采集48000个声音
	fmt.setSampleSize(this->sampleSize); //16位
	fmt.setChannelCount(this->channel);  //声道2双声道
	fmt.setCodec("audio/pcm"); //音频的格式
	fmt.setByteOrder(QAudioFormat::LittleEndian); //次序
	fmt.setSampleType(QAudioFormat::UnSignedInt); //样本的类别

	m_AudioOutput = new QAudioOutput(fmt);
	io = m_AudioOutput->start();
	mutex.unlock();
	return true;
}

void AudioPlay::Play(bool isPlay)
{
	mutex.lock();
	if (!m_AudioOutput)
	{
		mutex.unlock();
		return;
	}

	if (isPlay)
	{
		m_AudioOutput->resume();
	}
	else
	{
		m_AudioOutput->suspend();
	}

	mutex.unlock();
}

bool AudioPlay::Write(const char *data, int datasize)
{
	if (!data || datasize <= 0)
		return false;
	mutex.lock();
	if (io)
	{
		mutex.unlock();
		io->write(data, datasize);
		return true;
	}

	mutex.unlock();
}

int AudioPlay::GetFree()
{
	mutex.lock();
	if (!m_AudioOutput)
	{
		mutex.unlock();
		return 0;
	}
		
	int free = m_AudioOutput->bytesFree();
	mutex.unlock();

	return free;
}

//设置音量
void AudioPlay::SetVolume(int value)
{
	mutex.lock();
	m_AudioOutput->setVolume(value);
	mutex.unlock();
}

AudioPlay* AudioPlay::Get()
{
	static AudioPlay ap;
	return &ap;
}

