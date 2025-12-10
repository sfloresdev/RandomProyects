#include <SDL2/SDL.h>
#include <stdio.h>

int	main(void)
{
	const char *FILE_NAME = "lostmedia2.wav";
	SDL_AudioSpec spec;
	Uint8 *audio_buf;
	Uint32 audio_len;

	SDL_InitSubSystem(SDL_INIT_AUDIO);
    SDL_InitSubSystem(SDL_INIT_VIDEO);

	SDL_AudioSpec *return_spec = SDL_LoadWAV(FILE_NAME, &spec, &audio_buf,
			&audio_len);

	if (!return_spec)
	{
		printf("Error trying to open the file\n");
		return (1);
	}
	printf("Audio file loaded\n");

	SDL_AudioDeviceID device_id = SDL_OpenAudioDevice(NULL, 0, return_spec,
			return_spec, 0);

	printf("Device ID is: %d\n", device_id);
	if (!device_id)
	{
		printf("Audio device is not loaded\n");
		SDL_FreeWAV(audio_buf);
		return (1);
	}
	printf("Audio device loaded succesfully\n");

	int queue_audio_result = SDL_QueueAudio(device_id, audio_buf, audio_len);

	if (queue_audio_result == 0)
		printf("Succes queueing the audio\n");
	else
	{
		printf("Couldn't queue the audio\n");
		SDL_CloseAudioDevice(device_id);
		SDL_FreeWAV(audio_buf);
	}

	SDL_PauseAudioDevice(device_id, 0);
	printf("\nControles: \n");
    //printf("  ESPACIO: Pausar/Reanudar\n");
    printf("  Q o ESC: Salir\n\n");

    SDL_Event event;
    int running = 1;
    int paused = 0;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;
            else if (event.type == SDL_KEYDOWN)
            {
                if (SDLK_q || SDLK_ESCAPE)
                {
                    running = 0;
                    break;
                }
            }
        }
        // Checks if audio has finished
        if (SDL_GetQueuedAudioSize(device_id) == 0)
        {
            printf("Audio finished\n");
            running = 0;
        }
        SDL_Delay(100);
    }

	SDL_CloseAudioDevice(device_id);
	SDL_FreeWAV(audio_buf);
    SDL_Quit();

    return 0;
}