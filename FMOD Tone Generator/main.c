
#include <stdio.h>
#include <stdlib.h>
#include "fmod.h"
#include "fmod_errors.h"
#include <math.h>
#include <string.h>
//#include <Windows.h>

#define M_PIE 3.1415926
#define MAX 50


//Creating and Initializing the FMOD API

FMOD_CREATESOUNDEXINFO tones[10];
FMOD_SYSTEM *fSystem;

FMOD_SOUND * sound;

FMOD_CHANNEL * channel;



void fadeIn();
void fadeOut();

void storeTones();

const char* Tones[] = { "256", "271", "287", "304", "323", "342", "362", "384", "406", "431" };

void mergeSort(int arr[], int low, int mid, int high);
void partition(int arr[], int low, int high);

void FMODErrorCheck(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! ( %d ) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

FMOD_RESULT Init_FMOD();

FMOD_CREATESOUNDEXINFO structNote0();
FMOD_CREATESOUNDEXINFO structNote1();
FMOD_CREATESOUNDEXINFO structNote2();
FMOD_CREATESOUNDEXINFO structNote3();
FMOD_CREATESOUNDEXINFO structNote4();
FMOD_CREATESOUNDEXINFO structNote5();
FMOD_CREATESOUNDEXINFO structNote6();
FMOD_CREATESOUNDEXINFO structNote7();
FMOD_CREATESOUNDEXINFO structNote8();
FMOD_CREATESOUNDEXINFO structNote9();


int main(void)
{
    
    int unSorted[10] = { 9, 7, 5, 3, 1, 0, 2, 4, 6, 8 };
    

    
    int i;
    
    FMOD_RESULT result;
    //MOD_BOOL Paused;
    
    result = FMOD_System_Create(&fSystem);
    Init_FMOD();
    
    storeTones();
    
    printf("*****************************\n*****Merge Sort My Tones*****\n*****************************\n");
    printf("\nPrint Tones During Merge Sort:\n");
    
    //call Merger Sort and Play tones while sorting
    partition(unSorted, 0, 10 - 1);
    
    //	Paused = 0;
    
    printf("Print Tone Post Merge Sort:\n");
    for (i = 0; i < 10; i++)
    {
        FMOD_System_CreateStream(fSystem, 0, FMOD_OPENUSER, &tones[i], &sound);
        printf("Frequency: %s\n", Tones[i]);
        FMOD_System_PlaySound(fSystem, FMOD_CHANNEL_FREE, sound, 0, &channel);
        usleep(1000000);
        
    }
    
    return 0;
}

FMOD_RESULT Init_FMOD()
{
    FMOD_RESULT result;
    unsigned int version;
    int numDrivers;
    FMOD_SPEAKERMODE speakerMode;
    FMOD_CAPS caps;
    
    result = FMOD_System_GetVersion(fSystem, &version);
    FMODErrorCheck(result);
    if (version < FMOD_VERSION)
        printf("You are using an old version of FMOD.  Version is %d.", version);
    
    result = FMOD_System_GetNumDrivers(fSystem, &numDrivers);
    FMODErrorCheck(result);
    if (numDrivers == 0){
        result = FMOD_System_SetOutput(fSystem, FMOD_OUTPUTTYPE_NOSOUND);
        FMODErrorCheck(result);
    }
    else {
        result = FMOD_System_GetDriverCaps(fSystem, 0, &caps, 0, &speakerMode);
        FMODErrorCheck(result);
        
        result = FMOD_System_SetSpeakerMode(fSystem, speakerMode);
        FMODErrorCheck(result);
    }
    
    if (caps & FMOD_CAPS_HARDWARE_EMULATED)
    {
        result = FMOD_System_SetDSPBufferSize(fSystem, 1024, 10);
        FMODErrorCheck(result);
    }
    
    result = FMOD_System_Init(fSystem, 100, FMOD_INIT_NORMAL, 0);
    
    if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
    {
        result = FMOD_System_SetSpeakerMode(fSystem, FMOD_SPEAKERMODE_STEREO);
        FMODErrorCheck(result);
        
        result = FMOD_System_Init(fSystem, 100, FMOD_INIT_NORMAL, 0);
    }
    FMODErrorCheck(result);
    
    
    return(FMOD_OK);
}


void storeTones()
{
    //scaleInitialization(256);
    
    tones[0] = structNote0();
    tones[1] = structNote1();
    tones[2] = structNote2();
    tones[3] = structNote3();
    tones[4] = structNote4();
    tones[5] = structNote5();
    tones[6] = structNote6();
    tones[7] = structNote7();
    tones[8] = structNote8();
    tones[9] = structNote9();
}

FMOD_RESULT F_CALLBACK createNote0(FMOD_SOUND *sound, void *data, unsigned int length)
{
   // static int const sampleRate = 44100;
    static int const frequency = 256;
    static float const volume = 0.3f;
    static int samplesElapsed = 0;
    signed short *buffer = (signed short *)data;
    
    for (unsigned int samples = 0; samples < length / 4; samples++){
        
        //double thisSample = (sin(2.0 * M_PIE * (float)samples * ((float)frequency / 44100.0)));
        //*buffer++ = (signed short)(thisSample* 32767.0f * volume);
        //*buffer++ = (signed short)(thisSample * 32767.0f * volume);
        double pos = frequency * ((float)(samplesElapsed) / 44100.0);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        samplesElapsed++;
    }
    return 0;
}
FMOD_CREATESOUNDEXINFO structNote0()
{
    FMOD_CREATESOUNDEXINFO soundInfo;
    
    memset(&soundInfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    soundInfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    
    soundInfo.decodebuffersize = 44100;
    
    soundInfo.length = 44100 * 2 * sizeof(signed short);
    
    soundInfo.numchannels = 2;
    soundInfo.defaultfrequency = 44100;
    soundInfo.format = FMOD_SOUND_FORMAT_PCM16;
    
    soundInfo.pcmreadcallback = createNote0;
    
    return soundInfo;
}

FMOD_RESULT F_CALLBACK createNote1(FMOD_SOUND *sound, void *data, unsigned int length)
{
   // static int const sampleRate = 44100;
    static int const frequency = 271;
    static float const volume = 0.3f;
    static int samplesElapsed = 0;
    signed short *buffer = (signed short *)data;
    
    for (unsigned int samples = 0; samples < length / 4; samples++){
        
        double pos = frequency * ((float)(samplesElapsed) / 44100.0);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        samplesElapsed++;
    }
    return 0;
}
FMOD_CREATESOUNDEXINFO structNote1()
{
    FMOD_CREATESOUNDEXINFO soundInfo;
    
    memset(&soundInfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    soundInfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    
    soundInfo.decodebuffersize = 44100;
    
    soundInfo.length = 44100 * 2 * sizeof(signed short);
    
    soundInfo.numchannels = 2;
    soundInfo.defaultfrequency = 44100;
    soundInfo.format = FMOD_SOUND_FORMAT_PCM16;
    
    soundInfo.pcmreadcallback = createNote1;
    
    return soundInfo;
}

FMOD_RESULT F_CALLBACK createNote2(FMOD_SOUND *sound, void *data, unsigned int length)
{
   // static int const sampleRate = 44100;
    static int const frequency = 287;
    static float const volume = 0.3f;
    static int samplesElapsed = 0;
    signed short *buffer = (signed short *)data;
    
    for (unsigned int samples = 0; samples < length / 4; samples++){
        
        double pos = frequency * ((float)(samplesElapsed) / 44100.0);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        samplesElapsed++;
    }
    return 0;
}
FMOD_CREATESOUNDEXINFO structNote2()
{
    FMOD_CREATESOUNDEXINFO soundInfo;
    
    memset(&soundInfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    soundInfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    
    soundInfo.decodebuffersize = 44100;
    
    soundInfo.length = 44100 * 2 * sizeof(signed short);
    
    soundInfo.numchannels = 2;
    soundInfo.defaultfrequency = 44100;
    soundInfo.format = FMOD_SOUND_FORMAT_PCM16;
    
    soundInfo.pcmreadcallback = createNote2;
    
    return soundInfo;
}

FMOD_RESULT F_CALLBACK createNote3(FMOD_SOUND *sound, void *data, unsigned int length)
{
    //static int const sampleRate = 44100;
    static int const frequency = 304;
    static float const volume = 0.3f;
    static int samplesElapsed = 0;
    signed short *buffer = (signed short *)data;
    
    for (unsigned int samples = 0; samples < length / 4; samples++){
        
        double pos = frequency * ((float)(samplesElapsed) / 44100.0);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        samplesElapsed++;
    }
    return 0;
}
FMOD_CREATESOUNDEXINFO structNote3()
{
    FMOD_CREATESOUNDEXINFO soundInfo;
    
    memset(&soundInfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    soundInfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    
    soundInfo.decodebuffersize = 44100;
    
    soundInfo.length = 44100 * 2 * sizeof(signed short);
    
    soundInfo.numchannels = 2;
    soundInfo.defaultfrequency = 44100;
    soundInfo.format = FMOD_SOUND_FORMAT_PCM16;
    
    soundInfo.pcmreadcallback = createNote3;
    
    return soundInfo;
}

FMOD_RESULT F_CALLBACK createNote4(FMOD_SOUND *sound, void *data, unsigned int length)
{
    //static int const sampleRate = 44100;
    static int const frequency = 323;
    static float const volume = 0.3f;
    static int samplesElapsed = 0;
    signed short *buffer = (signed short *)data;
    
    for (unsigned int samples = 0; samples < length / 4; samples++){
        
        double pos = frequency * ((float)(samplesElapsed) / 44100.0);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        samplesElapsed++;
    }
    return 0;
}
FMOD_CREATESOUNDEXINFO structNote4()
{
    FMOD_CREATESOUNDEXINFO soundInfo;
    
    memset(&soundInfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    soundInfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    
    soundInfo.decodebuffersize = 44100;
    
    soundInfo.length = 44100 * 2 * sizeof(signed short);
    
    soundInfo.numchannels = 2;
    soundInfo.defaultfrequency = 44100;
    soundInfo.format = FMOD_SOUND_FORMAT_PCM16;
    
    soundInfo.pcmreadcallback = createNote4;
    
    return soundInfo;
}

FMOD_RESULT F_CALLBACK createNote5(FMOD_SOUND *sound, void *data, unsigned int length)
{
    //static int const sampleRate = 44100;
    static int const frequency = 342;
    static float const volume = 0.3f;
    static int samplesElapsed = 0;
    signed short *buffer = (signed short *)data;
    
    for (unsigned int samples = 0; samples < length / 4; samples++){
        
        double pos = frequency * ((float)(samplesElapsed) / 44100.0);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        samplesElapsed++;
    }
    return 0;
}
FMOD_CREATESOUNDEXINFO structNote5()
{
    FMOD_CREATESOUNDEXINFO soundInfo;
    
    memset(&soundInfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    soundInfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    
    soundInfo.decodebuffersize = 44100;
    
    soundInfo.length = 44100 * 2 * sizeof(signed short);
    
    soundInfo.numchannels = 2;
    soundInfo.defaultfrequency = 44100;
    soundInfo.format = FMOD_SOUND_FORMAT_PCM16;
    
    soundInfo.pcmreadcallback = createNote5;
    
    return soundInfo;
}

FMOD_RESULT F_CALLBACK createNote6(FMOD_SOUND *sound, void *data, unsigned int length)
{
    //static int const sampleRate = 44100;
    static int const frequency = 362;
    static float const volume = 0.3f;
    static int samplesElapsed = 0;
    signed short *buffer = (signed short *)data;
    
    for (unsigned int samples = 0; samples < length / 4; samples++){
        
        double pos = frequency * ((float)(samplesElapsed) / 44100.0);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        samplesElapsed++;
    }
    return 0;
}
FMOD_CREATESOUNDEXINFO structNote6()
{
    FMOD_CREATESOUNDEXINFO soundInfo;
    
    memset(&soundInfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    soundInfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    
    soundInfo.decodebuffersize = 44100;
    
    soundInfo.length = 44100 * 2 * sizeof(signed short);
    
    soundInfo.numchannels = 2;
    soundInfo.defaultfrequency = 44100;
    soundInfo.format = FMOD_SOUND_FORMAT_PCM16;
    
    soundInfo.pcmreadcallback = createNote6;
    
    return soundInfo;
}

FMOD_RESULT F_CALLBACK createNote7(FMOD_SOUND *sound, void *data, unsigned int length)
{
    //static int const sampleRate = 44100;
    static int const frequency = 384;
    static float const volume = 0.3f;
    static int samplesElapsed = 0;
    signed short *buffer = (signed short *)data;
    
    for (unsigned int samples = 0; samples < length / 4; samples++){
        
        //double thisSample = (sin(2.0 * M_PIE * (float)samples * ((float)frequency / 44100.0)));
        //*buffer++ = (signed short)(thisSample* 32767.0f * volume);
        //*buffer++ = (signed short)(thisSample * 32767.0f * volume);
        double pos = frequency * ((float)(samplesElapsed) / 44100.0);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        samplesElapsed++;
    }
    return 0;
}
FMOD_CREATESOUNDEXINFO structNote7()
{
    FMOD_CREATESOUNDEXINFO soundInfo;
    
    memset(&soundInfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    soundInfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    
    soundInfo.decodebuffersize = 44100;
    
    soundInfo.length = 44100 * 2 * sizeof(signed short);
    
    soundInfo.numchannels = 2;
    soundInfo.defaultfrequency = 44100;
    soundInfo.format = FMOD_SOUND_FORMAT_PCM16;
    
    soundInfo.pcmreadcallback = createNote7;
    
    return soundInfo;
}

FMOD_RESULT F_CALLBACK createNote8(FMOD_SOUND *sound, void *data, unsigned int length)
{
    //static int const sampleRate = 44100;
    static int const frequency = 406;
    static float const volume = 0.3f;
    static int samplesElapsed = 0;
    signed short *buffer = (signed short *)data;
    
    for (unsigned int samples = 0; samples < length / 4; samples++){
        
        //double thisSample = (sin(2.0 * M_PIE * (float)samples * ((float)frequency / 44100.0)));
        //*buffer++ = (signed short)(thisSample* 32767.0f * volume);
        //*buffer++ = (signed short)(thisSample * 32767.0f * volume);
        double pos = frequency * ((float)(samplesElapsed) / 44100.0);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        samplesElapsed++;
    }
    return 0;
}
FMOD_CREATESOUNDEXINFO structNote8()
{
    FMOD_CREATESOUNDEXINFO soundInfo;
    
    memset(&soundInfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    soundInfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    
    soundInfo.decodebuffersize = 44100;
    
    soundInfo.length = 44100 * 2 * sizeof(signed short);
    
    soundInfo.numchannels = 2;
    soundInfo.defaultfrequency = 44100;
    soundInfo.format = FMOD_SOUND_FORMAT_PCM16;
    
    soundInfo.pcmreadcallback = createNote8;
    
    return soundInfo;
}

FMOD_RESULT F_CALLBACK createNote9(FMOD_SOUND *sound, void *data, unsigned int length)
{
    //static int const sampleRate = 44100;
    static int const frequency = 431;
    static float const volume = 0.3f;
    static int samplesElapsed = 0;
    signed short *buffer = (signed short *)data;
    
    for (unsigned int samples = 0; samples < length / 4; samples++){
        
        //double thisSample = (sin(2.0 * M_PIE * (float)samples * ((float)frequency / 44100.0)));
        //*buffer++ = (signed short)(thisSample* 32767.0f * volume);
        //*buffer++ = (signed short)(thisSample * 32767.0f * volume);
        double pos = frequency * ((float)(samplesElapsed) / 44100.0);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        *buffer++ = (signed short)(sin(pos * M_PIE * 2) * 32767.0f * volume);
        samplesElapsed++;
    }
    return 0;
}
FMOD_CREATESOUNDEXINFO structNote9()
{
    FMOD_CREATESOUNDEXINFO soundInfo;
    
    memset(&soundInfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    soundInfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    
    soundInfo.decodebuffersize = 44100;
    
    soundInfo.length = 44100 * 2 * sizeof(signed short);
    
    soundInfo.numchannels = 2;
    soundInfo.defaultfrequency = 44100;
    soundInfo.format = FMOD_SOUND_FORMAT_PCM16;
    
    soundInfo.pcmreadcallback = createNote9;
    
    return soundInfo;
}



void fadeOut()
{
    float vol = 0.0;
    float *currentVolume;
    currentVolume = &vol;
    
    float fadeAmount = .00001;
    FMOD_Channel_GetVolume(channel, currentVolume);
    
    while (vol > 0)
    {
        vol -= fadeAmount;
        FMOD_Channel_SetVolume(channel, *currentVolume);
    }
}

void fadeIn()
{
    float vol = 0.0;
    float *currentVolume;
    currentVolume = &vol;
    
    float fadeAmount = .00001;
    FMOD_Channel_GetVolume(channel, currentVolume);
    
    while (vol < 1)
    {
        vol += fadeAmount;
        FMOD_Channel_SetVolume(channel, *currentVolume);
    }
}

void play(int i)
{
    fadeIn();
    
    FMOD_System_CreateStream(fSystem, 0, FMOD_OPENUSER, &tones[i], &sound);
    
    FMOD_System_PlaySound(fSystem, FMOD_CHANNEL_REUSE, sound, 0, &channel);
    fadeIn();
    
    usleep(200000);
    
    fadeOut();
    
    FMOD_Channel_SetPaused(channel, 1);
}

void partition(int arr[], int low, int high){
    int mid;
    
    if (low < high){
        mid = (low + high) / 2;
        partition(arr, low, mid);
        partition(arr, mid + 1, high);
        mergeSort(arr, low, mid, high);
    }
}

void mergeSort(int arr[], int low, int mid, int high){
    
    int i, m, k, l, temp[50];
    
    l = low;
    i = low;
    m = mid + 1;
    
    while ((l <= mid) && (m <= high)){
        play(arr[l]);
        printf("Frequency: %s\n", Tones[l]);
        play(arr[m]);
        
        printf("Frequency: %s\n", Tones[m]);
        
        if (arr[l] <= arr[m]){
            temp[i] = arr[l];
            l++;
        }
        else{
            temp[i] = arr[m];
            m++;
        }
        i++;
    }
    
    if (l > mid){
        for (k = m; k <= high; k++){
            temp[i] = arr[k];
            i++;
        }
    }
    
    else{
        for (k = l; k <= mid; k++){
            temp[i] = arr[k];
            i++;
        }
    }
    
    for (k = low; k <= high; k++){
        arr[k] = temp[k];
    }
}


