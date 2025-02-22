// ******************************************************************
// File:    audio_out.h
// Descr:   wrapper to BASS audio library (v0.41)
// Author:  Novoselov Anton @ 2017-2018
// URL:     https://github.com/ans-hub/audio_out
// ******************************************************************

// BASS Library docs placed here: https://www.un4seen.com/doc/
#include "stdafx.h"
#include <tga2d/audio/audio_out.h>
#ifdef _RETAIL
#pragma warning( push )
#pragma warning( disable : 4390 )
#pragma warning( disable : 4100 )
#endif
namespace Tga2D {

	AudioOut::AudioOut()
		: inited_{ false }
		, loaded_{ }
		, channels_cnt_{ audio_helpers::kChannelsCount }
	{
		if (BASS_Init(-1, 44100, BASS_DEVICE_8BITS, 0, NULL))
			inited_ = true;
		else
			audio_helpers::PrintBassError("Bass_Init", "");
	}

	AudioOut::~AudioOut()
	{
		for (auto& a : loaded_)
			BASS_SampleFree(a.second);
		if (inited_)
			BASS_Free();
	}

	// Plays the sample (with loading its before)


	bool AudioOut::Play(Handle hndl, Handle& outChannel, float aVolume)
	{
		if (!hndl)
			return false;

		// Try to get channel

		hndl = BASS_SampleGetChannel(hndl, FALSE);
		if (!hndl)
			return audio_helpers::PrintBassError("BASS_SampleGetChannel", "");
		BASS_ChannelSetAttribute(hndl, BASS_ATTRIB_VOL, aVolume);
		outChannel = hndl;

		// Try to play channel

		if (BASS_ChannelPlay(hndl, FALSE))
			return true;
		else
			return audio_helpers::PrintBassError("BASS_ChannelPlay", "");
	}

	bool AudioOut::Play(const std::string& fname, bool repeat, Handle& outChannel)
	{
		// Try to load stream (may be loaded already)

		Handle hndl = FindLoaded(fname);

		if (!hndl)
		{
			hndl = Load(fname, repeat);
			if (!hndl)
			{
				return false;
			}
		}


		// Try to get channel

		hndl = BASS_SampleGetChannel(hndl, FALSE);
		if (!hndl)
			return audio_helpers::PrintBassError("BASS_SampleGetChannel", fname);
		BASS_ChannelSetAttribute(hndl, BASS_ATTRIB_VOL, 1.0f);
		outChannel = hndl;
		// Try to play channel

		if (BASS_ChannelPlay(hndl, FALSE))
			return true;
		else
			return audio_helpers::PrintBassError("BASS_ChannelPlay", fname);
	}

	bool AudioOut::PlayMusic(const FileName& fname, bool repeat, Handle& outChannel)
	{
		// If we want to remove old music files
		
		//if (myFileName.size() != 0 && myFileName != fname)
		//{
		//	//Stop(myFileName, true);
		//	//BASS_SampleFree(FindLoaded(myFileName));
		//	//RemoveSample(FindLoaded(myFileName));
		//}

		myFileName = fname;

		// Try to load stream (may be loaded already)
		
		Handle hndl = FindLoaded(fname);

		if (!hndl)
		{
			hndl = Load(fname, repeat);
			if (!hndl)
			{
				return false;
			}
		}

		// Try to get channel

		hndl = BASS_SampleGetChannel(hndl, FALSE);
		if (!hndl)
			return audio_helpers::PrintBassError("BASS_SampleGetChannel", fname);
		BASS_ChannelSetAttribute(hndl, BASS_ATTRIB_VOL, 1.0f);
		// Try to play channel
		outChannel = hndl;

		if (BASS_ChannelPlay(hndl, FALSE))
			return true;
		else
			return audio_helpers::PrintBassError("BASS_ChannelPlay", fname);




	}

	// Stops playing the sample in two ways - by immediately and by
	// set loop flag to 0, therefore next loop is not come

	bool AudioOut::Stop(Handle hndl, bool immediately)
	{
		if (!hndl)
			return false;

		if (immediately)
			return StopPlayingImmediately(hndl);
		else
			return RemoveLoopFromSample(hndl);
	}

	bool AudioOut::Stop(const std::string& fname, bool immediately)
	{
		Handle hndl = FindLoaded(fname);

		if (!hndl)
			return audio_helpers::PrintGeneralError(fname + String(" not loaded"));

		if (immediately)
			return StopPlayingImmediately(hndl);
		else
			return RemoveLoopFromSample(hndl);
	}

	// Returns filename of first finded sample which currently is playing

	AudioOut::VStrings AudioOut::NowPlaying(bool only_repeated) const
	{
		VStrings res{};

		for (const auto& l : loaded_)
		{
			auto sample_hndl = l.second;
			auto channels_hndls = GetLoadedChannels(sample_hndl);

			if (IsChannelsPlayingNow(channels_hndls)) {
				if (!only_repeated)
					res.push_back(l.first);
				else
					if (audio_helpers::IsRepeatedSample(sample_hndl)) res.push_back(l.first);
			}
		}
		return res;
	}

	void AudioOut::SetVolume(const Handle& hndl, float aVolume)
	{
		//HCHANNEL ch = BASS_SampleGetChannel(hndl, FALSE);
		BASS_ChannelSetAttribute(hndl, BASS_ATTRIB_VOL, aVolume);

	}

	void AudioOut::SetPosition(const Handle& hndl, VECTOR2F aPosition)
	{
		BASS_ChannelSetAttribute(hndl, BASS_ATTRIB_PAN, aPosition.x);
	}

	void AudioOut::StopMusic(bool immediately)
	{
		if (myFileName != "")
		{
			Handle hndl = FindLoaded(myFileName);

			if (!hndl)
				audio_helpers::PrintGeneralError(myFileName + String(" not loaded"));

			if (immediately)
				StopPlayingImmediately(hndl);
			else
				RemoveLoopFromSample(hndl);
		}
	}

	void AudioOut::RemoveSample(const Handle& aHNDL)
	{
		for (int i = 0; i < loaded_.size(); i++)
			if (loaded_[i].second == aHNDL)
			{
				loaded_.erase(loaded_.begin() + i);
				break;
			}
	}

	// Loads sample by filename, saves to loaded_ vector and return its handle

	long AudioOut::Load(const std::string& fname, bool repeat)
	{
		// Check if already loaded

		Handle hndl = FindLoaded(fname);
		if (hndl)
			return audio_helpers::PrintGeneralError(fname + String(" already loaded"));

		// Create new sample

		DWORD flags{};
		if (repeat)
			flags = BASS_SAMPLE_LOOP;
		else
			flags = BASS_SAMPLE_8BITS + BASS_SAMPLE_OVER_POS;
		hndl = BASS_SampleLoad(FALSE, fname.c_str(), 0, 0, 3, flags);

		// Add sample to container

		if (!hndl)
		{
			return -1;
		}
		else
		{
			loaded_.push_back(std::make_pair(fname, hndl));
			return hndl;
		}
	}

	// Returns handle of sample if its were been loaded early

	AudioOut::Handle AudioOut::FindLoaded(const std::string& fname) const
	{
		for (auto& l : loaded_)
			if (l.first == fname) return l.second;
		return 0;
	}

	// Gets vector of handles to all loaded channels of sample

	AudioOut::VHandles AudioOut::GetLoadedChannels(const Handle& hndl) const
	{
		// Create struct to save channels list

		auto  nfo = audio_helpers::GetSampleInfo(hndl);
		auto  ch_list_ptr = std::unique_ptr<HCHANNEL>{ new HCHANNEL[nfo.max] };
		auto* ch_list = ch_list_ptr.get();

		// Get channels list

		DWORD ch_count{ 0 };
		ch_count = BASS_SampleGetChannels(hndl, ch_list);

		// Save channels to vector

		VHandles res{};
		for (DWORD i = 0; i < ch_count; ++i) {
			res.push_back(ch_list[i]);
		}
		return res;
	}

	// Returns true if at least one channel is playing now

	bool AudioOut::IsChannelsPlayingNow(const VHandles& handles) const
	{
		for (const auto& h : handles) {
			auto active = BASS_ChannelIsActive(h);
			if (active) return true;
		}
		return false;
	}

	// Stop playback of given sample immediately

	bool AudioOut::StopPlayingImmediately(const Handle& hndl)
	{
		HCHANNEL ch = BASS_SampleGetChannel(hndl, FALSE);
		BASS_ChannelSetPosition(ch, 0, BASS_POS_BYTE);
		return BASS_SampleStop(hndl);
	}

	// Stop playback after end of playing sample and change loop flag 

	bool AudioOut::RemoveLoopFromSample(const Handle& hndl)
	{
		if (!audio_helpers::IsRepeatedSample(hndl))
			// return StopPlayingImmediately(hndl);
			return false;

		auto channels_hndls = GetLoadedChannels(hndl);
		for (auto& ch : channels_hndls) {
			if (BASS_ChannelFlags(ch, 0, 0) & BASS_SAMPLE_LOOP) {
				BASS_ChannelFlags(ch, 0, BASS_SAMPLE_LOOP);
				return true;
			}
		}
		return false;
	}

	// HELPERS

	bool audio_helpers::IsNowPlaying(const AudioOut& audio, const std::string& fname)
	{
		auto now_playing = audio.NowPlaying(false);

		for (const auto& sound : now_playing) {
			if (sound == fname) return true;
		}
		return false;
	}

	bool audio_helpers::StopAllNowPlaying(AudioOut& audio, bool only_repeated)
	{
		bool result{ true };
		auto sounds = audio.NowPlaying(only_repeated);

		for (const auto& sound : sounds) {
			if (!audio.Stop(sound)) result = false;
		}
		return result;
	}

	// Returns true if given sample is looped

	bool audio_helpers::IsRepeatedSample(const Handle& hndl)
	{
		auto info = audio_helpers::GetSampleInfo(hndl);
		if (info.flags == BASS_SAMPLE_LOOP + BASS_SAMPLE_SOFTWARE)
			return true;
		else
			return false;
	}

	audio_helpers::SampleNfo audio_helpers::GetSampleInfo(const Handle& hndl)
	{
		BASS_SAMPLE nfo;
		BASS_SampleGetInfo(hndl, &nfo);
		return nfo;
	}

	bool audio_helpers::SetSampleInfo(const Handle& hndl, SampleNfo& nfo)
	{
		return BASS_SampleSetInfo(hndl, &nfo);
	}

	const char* GetStringFromError(int aCode)
	{
		switch (aCode)
		{
		case 1:
			return "Memory error";
			break;
		case 2:
			return "Can't open the file";
			break;
		case 3:
			return "Can't find a free/valid driver";
			break;
		case 6:
			return "Unsupported sample format";
			break;
		case 18:
			return "Can't get a free channel";
			break;
		default:
			break;
		}

		return "N/A";
	}

	bool audio_helpers::PrintBassError(const std::string& func_name, const std::string& aExtra)
	{
		func_name;
		auto err = BASS_ErrorGetCode();
		if (err)
			ERROR_PRINT("%s%s %s", "Audio error: ", GetStringFromError(err), aExtra.c_str());

		return err ? false : true;
	}

	bool audio_helpers::PrintGeneralError(const std::string& msg)
	{
		std::cerr << "Audio error: " << msg << '\n';
		return false;
	}

}  // namespace anshub

#ifdef _RETAIL
#pragma warning( pop  )
#endif