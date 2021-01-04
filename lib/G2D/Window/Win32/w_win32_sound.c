#include "../w_win32.h"
#include <Mmsystem.h>
#include <stdlib.h>
#include <process.h>

struct G2D_Win32_Sound
{
	LPSTR lpName;
	HANDLE hRes;
};


enum ENUM_HANDLE_SIGNALS
{
	SIGNAL_END,
	SIGNAL_PROCESS,

	SIGNAL_COUNT
};

static HANDLE h_signals[SIGNAL_COUNT];

static HANDLE h_thread_sound_manager;
static uint id_thread_sound_manager;


#define MAX_SOUNDS 32
static struct G2D_Win32_Sound sounds[MAX_SOUNDS];  /* SHARED */
static bool sounds_ready[MAX_SOUNDS];  /* SHARED */
static CRITICAL_SECTION sounds_critical_section;


static bool
sound_play(int id)
{
	bool res;
	//LPSTR lpRes;

	if (id < 0 || id >= MAX_SOUNDS)
	{
		LOG_ERROR("Error playing sound: id < 0 || id >= MAX_SOUND\n");
		return false;
	}

	res = PlaySound(sounds[id].lpName, NULL, SND_ASYNC | SND_RESOURCE | SND_NODEFAULT);

	//lpRes = LockResource(sounds[id].hRes);
	//if (lpRes != NULL)
	//{
	//	res = sndPlaySound(lpRes, SND_MEMORY | SND_SYNC | SND_NODEFAULT);
	//	UnlockResource(sounds[id].hRes);
	//}
	//else
	//{
	//	LOG_ERROR("Error playing sound: LockResource() failed TODO\n");  /* TODO */
	//	res = false;
	//}

	return res;
}


/**
 * Main loop for sound manager thread.
 */
static DWORD WINAPI
thread_sound_manager(void* args)
{
	/* IDEA: spin off thread for each sound? */
	LOG_DEBUG("thread_sound_manager started\n");
	for (;;)
	{
		DWORD dw = WaitForMultipleObjects(SIGNAL_COUNT, h_signals, FALSE, INFINITE);

		switch (dw)
		{
		case (WAIT_OBJECT_0 + SIGNAL_END):
		{
			(void)ResetEvent(h_signals[SIGNAL_END]);

			_endthreadex(0);
		} break;
		case (WAIT_OBJECT_0 + SIGNAL_PROCESS):
		{
			EnterCriticalSection(&sounds_critical_section);  /* CRITICAL START */

			(void)ResetEvent(h_signals[SIGNAL_PROCESS]);

			int id;
			for (id = 0; id < MAX_SOUNDS; id++)
			{
				if (sounds[id].hRes && sounds[id].lpName
					&& sounds_ready[id] == true)
				{
					sounds_ready[id] = false;
					break;
				}
			}

			LeaveCriticalSection(&sounds_critical_section);  /* CRITICAL END */

			if (id < MAX_SOUNDS)
			{
				(void)sound_play(id);
			}
		} break;
		default:
		{
			/* error */
			//LOG_ERROR("Error at sound manager: WaitForMultipleObjects()\n");
			//_endthreadex(1);
		} break;
		}


		/* https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitformultipleobjectsex

		use waitformutlipleobjects ... ?

		OR message shit? message = name of sound

		*/
	}

	_endthreadex(0);
}



bool
w_win32_sound_manager_init()
{
	//return false;  /* TEMP */

	if (InitializeCriticalSectionAndSpinCount(&sounds_critical_section, 
		0x00000400) == 0)
	{
		LOG_ERROR("Error initialising critical section\n");
		return false;
	}

	for (int i = 0; i < SIGNAL_COUNT; i++)
	{
		h_signals[i] = CreateEvent(NULL, TRUE, FALSE, NULL);

		if (!h_signals[i])
		{
			/* ERROR close previous */
			for (int j = i - 1; j >= 0; j--)
				(void)CloseHandle(h_signals[j]);

			LOG_ERROR("Error creating h_signals\n");
			return false;
		}
	}

	(void)memset(sounds, 0, (sizeof *sounds) * MAX_SOUNDS);
	(void)memset(sounds_ready, 0, (sizeof *sounds_ready) * MAX_SOUNDS);

	/* Create new thread (max ever 1!) */
	h_thread_sound_manager = (HANDLE)_beginthreadex(NULL, 0, 
		(void*)thread_sound_manager, NULL, 0, &id_thread_sound_manager);
	if (h_thread_sound_manager == 0)
	{
		LOG_ERROR("Error creating thread: _beginthreadex()\n");
		return false;
	}

	return true;
}

bool
w_win32_sound_manager_destroy()
{
	//return false;  /* TEMP */

	/* Destroy thread */
	(void)SetEvent(h_signals[SIGNAL_END]);
	(void)WaitForSingleObject(h_thread_sound_manager, INFINITE);

	for (int i = 0; i < SIGNAL_COUNT; i++)
		(void)CloseHandle(h_signals[i]);

	(void)CloseHandle(h_thread_sound_manager);

	DeleteCriticalSection(&sounds_critical_section);

}


/**
 * Creates sound object and returns id.
 * 
 * \return return < 0: failure, 0-MAX_SOUNDS is id
 */
int 
w_win32_sound_create(LPSTR lpName)
{
	/* Check if free sound "slot" (max: MAX_SOUNDS) */

	EnterCriticalSection(&sounds_critical_section);  /* CRITICAL START */

	int id;
	for (id = 0; id < MAX_SOUNDS; id++)  /* TODO: POSSIBLE BUG (CHECK CORNER CASE WHERE FULL */
	{
		if (sounds[id].hRes == NULL || sounds[id].lpName == NULL)
			break;
	}

	if (id == MAX_SOUNDS)
	{
		LeaveCriticalSection(&sounds_critical_section);  /* CRITICAL END */
		LOG_ERROR("Error creating sound: MAX_SOUNDS\n");
		return -1;
	}

	/* if free: create sound and return index of it */
	HANDLE hResInfo;
	sounds[id].lpName = lpName;
	hResInfo = FindResource(NULL, lpName, "WAVE");
	if (hResInfo == NULL)
	{
		LeaveCriticalSection(&sounds_critical_section);  /* CRITICAL END */

		LOG_ERROR("Error creating sound: Could not find resource\n");
		(void)w_win32_sound_destroy(id);  /* also goes into CRITICAL SECTION */
		return -2;
	}

	// Load the WAVE resource. 

	sounds[id].hRes = LoadResource(NULL, hResInfo);
	if (sounds[id].hRes == NULL)
	{
		LeaveCriticalSection(&sounds_critical_section);  /* CRITICAL END */

		LOG_ERROR("Error creating sound: Could not load resource\n");
		(void)w_win32_sound_destroy(id);  /* also goes into CRITICAL SECTION */
		return -3;
	}

	LeaveCriticalSection(&sounds_critical_section);  /* CRITICAL END */

	return id;
}

bool 
w_win32_sound_destroy(int id)
{
	bool res = true;

	if (id > 0 && id < MAX_SOUNDS)
	{
		EnterCriticalSection(&sounds_critical_section);  /* CRITICAL START */

		if (sounds[id].hRes && !FreeResource(sounds[id].hRes))
		{
			LOG_ERROR("Error destroying sound: FreeResource() failed\n");
			res = false;
		}
		memset(&sounds[id], 0, (sizeof sounds[id]));

		LeaveCriticalSection(&sounds_critical_section);  /* CRITICAL END */
	}

	return res;
}

bool
w_win32_sound_play(int id)
{
	bool res = true;

	if (id < 0 || id >= MAX_SOUNDS)
	{
		LOG_ERROR("Error playing sound: id < 0 || id >= MAX_SOUND\n");
		return false;
	}

	EnterCriticalSection(&sounds_critical_section);  /* CRITICAL START */

	sounds_ready[id] = true;

	if (SetEvent(h_signals[SIGNAL_PROCESS]) == 0)
	{
		LOG_ERROR("Error playing sound (win32): SetEvent() failed\n");
		res = false;
	}

	LeaveCriticalSection(&sounds_critical_section);  /* CRITICAL END */

	return res;
}


//
//
//struct G2D_Win32_Sound* 
//w_win32_sound_create(LPSTR lpName)
//{
//	HANDLE hResInfo;
//	struct G2D_Win32_Sound* sound;
//
//	sound = malloc((sizeof *sound));
//	if (!sound)
//	{
//		/* ERROR */
//		return NULL;
//	}
//	(void)memset(sound, 0, (sizeof *sound));
//
//	sound->lpName = lpName;
//	hResInfo = FindResource(NULL, lpName, "WAVE");
//	if (hResInfo == NULL)
//	{
//		(void)free(sound);
//		return NULL;
//	}
//
//	// Load the WAVE resource. 
//
//	sound->hRes = LoadResource(NULL, hResInfo);
//	if (sound->hRes == NULL)
//	{
//		(void)free(sound);
//		return NULL;
//	}
//
//	return sound;
//}
//
//bool 
//w_win32_sound_destroy(struct G2D_Win32_Sound* sound)
//{
//	bool res = true;
//
//	if (!FreeResource(sound->hRes))
//		res = false;
//
//	free(sound);
//
//	return res;
//}
//
///**
// * .
// */
//bool 
//w_win32_sound_play(struct G2D_Win32_Sound* sound)
//{
//	bool res;
//	LPSTR lpRes;
//
//	lpRes = LockResource(sound->hRes);
//	if (lpRes != NULL)
//	{
//		res = sndPlaySound(lpRes, SND_MEMORY | SND_SYNC | SND_NODEFAULT);
//		UnlockResource(sound->hRes);
//	}
//	else
//	{
//		res = false;
//	}
//
//	return res;
//}