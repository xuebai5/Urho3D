//
// Copyright (c) 2008-2014 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "Precompiled.h"
#include "APITemplates.h"
#include "Audio.h"
#include "Sound.h"
#include "SoundListener.h"
#include "SoundSource3D.h"

namespace Urho3D
{

void RegisterSound(asIScriptEngine* engine)
{
    RegisterResource<Sound>(engine, "Sound");
    engine->RegisterObjectMethod("Sound", "float get_length() const", asMETHOD(Sound, GetLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "uint get_sampleSize() const", asMETHOD(Sound, GetSampleSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "float get_frequency() const", asMETHOD(Sound, GetFrequency), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "void set_looped(bool)", asMETHOD(Sound, SetLooped), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool get_looped() const", asMETHOD(Sound, IsLooped), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool get_sixteenBit() const", asMETHOD(Sound, IsSixteenBit), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool get_stereo() const", asMETHOD(Sound, IsStereo), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool get_compressed() const", asMETHOD(Sound, IsCompressed), asCALL_THISCALL);
}

void RegisterSoundSources(asIScriptEngine* engine)
{
    engine->RegisterEnum("SoundType");
    engine->RegisterEnumValue("SoundType", "SOUND_EFFECT", SOUND_EFFECT);
    engine->RegisterEnumValue("SoundType", "SOUND_AMBIENT", SOUND_AMBIENT);
    engine->RegisterEnumValue("SoundType", "SOUND_VOICE", SOUND_VOICE);
    engine->RegisterEnumValue("SoundType", "SOUND_MUSIC", SOUND_MUSIC);
    engine->RegisterEnumValue("SoundType", "SOUND_MASTER", SOUND_MASTER);
    
    RegisterSoundSource<SoundSource>(engine, "SoundSource");
    RegisterSoundSource<SoundSource3D>(engine, "SoundSource3D");
    // Allow creation of sound sources also outside scene
    RegisterObjectConstructor<SoundSource>(engine, "SoundSource");
    engine->RegisterObjectMethod("SoundSource3D", "void SetDistanceAttenuation(float, float, float)", asMETHOD(SoundSource3D, SetDistanceAttenuation), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void SetAngleAttenuation(float, float)", asMETHOD(SoundSource3D, SetAngleAttenuation), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_nearDistance(float)", asMETHOD(SoundSource3D, SetNearDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_nearDistance() const", asMETHOD(SoundSource3D, GetNearDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_farDistance(float)", asMETHOD(SoundSource3D, SetFarDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_farDistance() const", asMETHOD(SoundSource3D, GetFarDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_innerAngle(float)", asMETHOD(SoundSource3D, SetInnerAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_innerAngle() const", asMETHOD(SoundSource3D, GetInnerAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_outerAngle(float)", asMETHOD(SoundSource3D, SetOuterAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_outerAngle() const", asMETHOD(SoundSource3D, GetOuterAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_rolloffFactor(float)", asMETHOD(SoundSource3D, SetRolloffFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_rolloffFactor() const", asMETHOD(SoundSource3D, RollAngleoffFactor), asCALL_THISCALL);
}

void RegisterSoundListener(asIScriptEngine* engine)
{
    RegisterComponent<SoundListener>(engine, "SoundListener");
}

static Audio* GetAudio()
{
    return GetScriptContext()->GetSubsystem<Audio>();
}

static float GetMasterGainFromEnum(SoundType type, Audio* audio)
{
    return audio->GetMasterGain(type);
}

static float GetMasterGainFromHash(const StringHash& type, Audio* audio)
{
    return audio->GetMasterGain(type);
}

static StringHash GetHashFromType(SoundType type)
{
    return soundTypeHashes[type];
}

void RegisterAudio(asIScriptEngine* engine)
{
    RegisterObject<Audio>(engine, "Audio");
    engine->RegisterObjectMethod("Audio", "void SetMode(int, int, bool, bool interpolate = true)", asMETHOD(Audio, SetMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool Play()", asMETHOD(Audio, Play), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "void Stop()", asMETHOD(Audio, Stop), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "void SetMasterGain(SoundType, float)", asMETHODPR(Audio, SetMasterGain, (SoundType, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "float GetMasterGain(SoundType) const", asFUNCTION(GetMasterGainFromEnum), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Audio", "void SetMasterGain(const StringHash&in, float)", asMETHODPR(Audio, SetMasterGain, (const StringHash&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "float GetMasterGain(const StringHash&in) const", asFUNCTION(GetMasterGainFromHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Audio", "void set_masterGain(const StringHash&in, float)", asMETHODPR(Audio, SetMasterGain, (const StringHash&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "float get_masterGain(const StringHash&in) const", asFUNCTION(GetMasterGainFromHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Audio", "bool IsMasterGain(const StringHash&in) const", asMETHOD(Audio, IsMasterGain), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "void set_listener(SoundListener@+)", asMETHOD(Audio, SetListener), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "SoundListener@+ get_listener() const", asMETHOD(Audio, GetListener), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "uint get_sampleSize() const", asMETHOD(Audio, GetSampleSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "int get_mixRate() const", asMETHOD(Audio, GetMixRate), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool get_stereo() const", asMETHOD(Audio, IsStereo), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool get_interpolation() const", asMETHOD(Audio, GetInterpolation), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool get_playing() const", asMETHOD(Audio, IsPlaying), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool get_initialized() const", asMETHOD(Audio, IsInitialized), asCALL_THISCALL);
    engine->RegisterGlobalFunction("Audio@+ get_audio()", asFUNCTION(GetAudio), asCALL_CDECL);
    engine->RegisterGlobalFunction("StringHash GetHashFromSoundType(SoundType type)", asFUNCTION(GetHashFromType), asCALL_CDECL);
}

void RegisterAudioAPI(asIScriptEngine* engine)
{
    RegisterSound(engine);
    RegisterSoundListener(engine);
    RegisterSoundSources(engine);
    RegisterAudio(engine);
}

}
