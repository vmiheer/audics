/*
copyright	: 	VIT,pune.
Authors		: 	Miheer Vaidya		Aakash Agrawal		Sandeep Tagadpallewar
			Tejas Bubane		Jaydev Kshirsagar
Liscence	:	GPL V3+

This program is for education and evaluation purpose only(currently)
authors don't provide warranty of any quality even warranty of fitness
and merchantability.
*/

/*
((short *)temp)
((short *)buffer)
((short *)buffer)[0]*4
loops
*/
/* Use the newer ALSA API */
#include"testn.h"
short *byte_generate(int byte_per_period,int time_period,int frequency)
{
 
  int n,count=1;
  float f=0,inc;
  short *samples;
  n = ( byte_per_period*1000000) / (frequency *time_period*4);
  inc = 2*3.14/n;
  samples = (short *)malloc((2*n + 1)*sizeof(short));
  samples[0] = n;
  for(;count<=2*n;count+=2,f=f+inc)
  {
    samples[count] = 0x7fff*sin(f);
    samples[count+1] = samples[count];
  }
  return(samples);
}	

void init_buffers()
{
	buffer_array[0] = byte_generate(128,725,16);
	buffer_array[1] = byte_generate(128,725,18);
	buffer_array[2] = byte_generate(128,725,21);
	buffer_array[3] = byte_generate(128,725,22);
	buffer_array[4] = byte_generate(128,725,25);
	buffer_array[5] = byte_generate(128,725,28);
	buffer_array[6] = byte_generate(128,725,31);
}

void compose_and_play(int inc_factor,int buff_id)
{
	int count = 138,cf;
	short *reader;
	for(int i=0;i<count;i++)
	{
		cf=0;
		reader = buffer_array[buff_id];
		reader++;
		if(!(i%9))
			cnt++;	
		for(writer=buff8;writer<&(buff8[512])&&cf<50;)
		{
			
			
			if((*writer = (*reader)>>cnt)==0)
				cf++;
//			write(STDOUT_FILENO,writer,2);
			writer++;
			
			*writer=(*reader)>>cnt;
//			write(STDOUT_FILENO,writer,2);
			writer++;
			reader = (short *)(((int *)reader) + inc_factor);
			if(reader > (short *)(buffer_array[buff_id][0]+(int *)buffer_array[buff_id]))
			{
				reader = buffer_array[buff_id];
				reader++;	
			}
		}
		snd_pcm_writei(handlec,buff8,256);
	}
}

void init_alsa() {
//  long loops; //number of periods
  int rc;	//for error check
  int size;	//size of 1 period in
  snd_pcm_t *handle;
  snd_pcm_hw_params_t *params;
  unsigned int val;
  int dir;
  snd_pcm_uframes_t frames;
//  char *buffer;

  /* Open PCM device for playback. */
  rc = snd_pcm_open(&handle, "default",
                    SND_PCM_STREAM_PLAYBACK, SND_PCM_ASYNC |SND_PCM_NONBLOCK);
  if (rc < 0) {
    fprintf(stderr,
            "unable to open pcm device: %s\n",
            snd_strerror(rc));
    exit(1);
  }
  handlec=handle;
  /* Allocate a hardware parameters object. */
  snd_pcm_hw_params_alloca(&params);

  /* Fill it in with default values. */
  snd_pcm_hw_params_any(handle, params);

  /* Set the desired hardware parameters. */

  /* Interleaved mode */
  snd_pcm_hw_params_set_access(handle, params,
                      SND_PCM_ACCESS_RW_INTERLEAVED);

  /* Signed 16-bit little-endian format */
  assert((snd_pcm_hw_params_set_format(handle, params,
                              SND_PCM_FORMAT_S16_LE))==0);

  /* Two channels (stereo) */
  snd_pcm_hw_params_set_channels(handle, params, 2);

  /* 44100 bits/second sampling rate (CD quality) */
  val = 44100;
  snd_pcm_hw_params_set_rate_near(handle, params,
                                  &val, &dir);

  /* Set period size to 32 frames. */
  frames = 32;
  snd_pcm_hw_params_set_period_size_near(handle,
                              params, &frames, &dir);

  /* Write the parameters to the driver */
  rc = snd_pcm_hw_params(handle, params);
  if (rc < 0) {
    fprintf(stderr,
            "unable to set hw parameters: %s\n",
            snd_strerror(rc));
    exit(1);
  }

  /* Use a buffer large enough to hold one period */
  snd_pcm_hw_params_get_period_size(params, &frames,
                                    &dir);
  fprintf(stderr,"Period framesize:%ld\n",(long)frames);
  //printf("Period dir:%ld\n",(long)dir);
  size = frames * 4; /* 2 bytes/sample, 2 channels */

  /* We want to loop for 5 seconds */
  snd_pcm_hw_params_get_period_time(params,
                                    &val, &dir);
  /* 5 seconds in microseconds divided by
   * period time */
   
//==================================================================================
	init_buffers();
//	char c1, c2;
//	int range, freq;
//	initscr();
//	noecho();
//	raw();
//		do {
/*			c1 = getch();
			clear();
			if(c1=='q'||c1=='w'||c1=='e'||c1=='r'||c1=='t'||c1=='y'||c1=='u'||c1=='i') 
			{
				switch(c1) {
					case 'q': range = 1;
							break;
					case 'w': range = 2;
							break;
					case 'e': range = 4;
							break;
					case 'r': range = 8;
							break;
					case 't': range = 16;
							break;
					case 'y': range = 32;
							break;
					case 'u': range = 64;
							break;
					case 'i': range = 128;
				}
			}
			else if(c1=='1'||c1=='2'||c1=='3'||c1=='4'||c1=='5'||c1=='6'||c1=='7') 
			{
				freq = ((int)(c1-'1'));
				compose_and_play(range,freq);
				compose_and_play(range,freq);
//				printw("function called\n");
			}
			else{
				break;
			}
		}while(1);*/
//==================================================================================
/*  snd_pcm_drain(handle);
  snd_pcm_close(handle);
//  free(buffer);
	free(buffer_array[0]);
	free(buffer_array[1]);
	free(buffer_array[2]);
	free(buffer_array[3]);
	free(buffer_array[4]);
	free(buffer_array[5]);
	free(buffer_array[6]);
  return 0; */
}
