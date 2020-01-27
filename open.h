#ifndef __STAR_WARS_H_
#define __STAR_WARS_H_
#define _CRT_SECURE_NO_WARNINGS
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "yspng.h"
#include "ysglfontdata.h"
#include <stdio.h>



static void (*show_funcs[])(const char *) = {
	&YsGlDrawFontBitmap6x7,
	&YsGlDrawFontBitmap6x8,
	&YsGlDrawFontBitmap6x10,
	&YsGlDrawFontBitmap7x10,
	&YsGlDrawFontBitmap8x8,
	&YsGlDrawFontBitmap8x12,
	&YsGlDrawFontBitmap10x14,
	&YsGlDrawFontBitmap12x16,
	&YsGlDrawFontBitmap16x20,
	&YsGlDrawFontBitmap16x24,
	&YsGlDrawFontBitmap20x28,
	&YsGlDrawFontBitmap20x32,
	&YsGlDrawFontBitmap24x40,
	&YsGlDrawFontBitmap28x44,
	&YsGlDrawFontBitmap32x48

};

static int widths[] = {
	6,
	6,
	6,
	7,
	8,
	8,
	10,
	12,
	16,
	16,
	20,
	20,
	24,
	28,
	32};

static int heights[] = {
	7,
	8,
	10,
	10,
	8,
	12,
	14,
	16,
	20,
	24,
	28,
	32,
	40,
	44,
	48};

static int show_funcs_count = sizeof(show_funcs) / sizeof(show_funcs[0]);

static int run(void)
{
	YsSoundPlayer player;
	YsSoundPlayer::SoundData starwars;
	if (YSOK != starwars.LoadWav("opening_and_ending/StarWars.wav"))
	{
		printf("Failed to read %s\n", "StarWars.wav");
		return 1;
	}
	player.Start();
	player.PlayBackground(starwars);

	const char *file_name = "opening_and_ending/openingbg.png";

	YsRawPngDecoder png;
	if (YSOK == png.Decode(file_name))
	{
		png.Flip();
	}
	else
	{
		return 1;
	}

	FsOpenWindow(16, 16, png.wid, png.hei + 1, 1);
	double current_time = 0;
	double show_first = 1.0;
	double show_second_1 = 1.0;
	double show_second_2 = 5.0;
	double show_third_1 = 3.0;
	double show_third_2 = 15.0;
	bool move_begin = false;
	double move_begin_time = 0.0;
	while (FSKEY_ESC != FsInkey())
	{
		FsPollDevice();
		glClear(GL_DEPTH_BUFFER_BIT);

		glRasterPos2d(0.0, (double)(png.hei));
		glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
		if (current_time <= show_first)
		{
			glColor3ub(0, 255, 0);
			const char *show_str = "A long time ago in CMU...";
			int show_length = strlen(show_str);
			int idx = 12;
			glRasterPos2d(
				400 - widths[idx] * show_length / 2,
				300 + heights[idx] / 2);
			(*show_funcs[idx])(show_str);
		}

		if (show_second_1 <= current_time && current_time <= show_second_2)
		{
			glColor3ub(255, 0, 0);
			const char *show_str = "Training at 4 A.M";
			int show_length = strlen(show_str);

			int max_kind = show_second_2;
			int idx = show_funcs_count - 4 - (int)((current_time - show_second_1) * 2);
			if (idx < 0)
				idx = 0;
			glRasterPos2d(
				400 - widths[idx] * show_length / 2,
				300 + heights[idx] / 2);
			(*show_funcs[idx])(show_str);
		}
		if (show_third_1 <= current_time && current_time <= show_third_2)
		{
			glColor3ub(255, 255, 0);
			const char *strs[] =
				{
					"There once was a student in ",
					"CMU who wants to be the Best ",
					"Coder of All Time, He always ",
					"stayed up late even at 4 a.m ",
					"to train himself, he got stronger ",
					"and stronger day by day. He decided ",
					"to take the challenge, After he defeated ",
					"mid-term exam, individual project and ",
					"group project, he met the final exam..."};

			int strs_length = sizeof(strs) / sizeof(strs[0]);

			int show_totals = current_time - show_third_1;
			if (show_totals < 1)
			{
				show_totals = 1;
			}
			double diff_show_idx = 0;
			if (show_totals >= strs_length)
			{
				show_totals = strs_length;
				if (!move_begin)
				{
					move_begin_time = current_time;
				}
				move_begin = true;
			}

			const int diff_length = 20;
			int base_height = (current_time - move_begin_time) * 20;
			if (!move_begin)
			{
				base_height = 0;
			}
			else
			{
				diff_show_idx = current_time - move_begin_time;
			}
			for (int i_line = show_totals - 1; i_line >= 0; i_line--)
			{
				int real_i = show_totals - 1 - i_line;
				const char *show_str = strs[i_line];
				int show_length = strlen(show_str);
				int show_function_idx = show_funcs_count - 6 - real_i - diff_show_idx;
				if (show_function_idx < 0)
					show_function_idx = 0;
				glRasterPos2d(
					400 - widths[show_function_idx] * show_length / 2,
					500 - heights[show_function_idx] / 2 - diff_length * real_i - base_height);
				base_height += heights[show_function_idx];
				(*show_funcs[show_function_idx])(show_str);
			}
		}

		if (current_time > show_third_2)
			break;

		FsSwapBuffers();
		FsSleep(10);
		current_time += 0.01;
	}
	player.End();
	return 0;
}
#endif//__STAR_WARS_H_
