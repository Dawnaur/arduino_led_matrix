/******************************************************************************/
/*        ________                                                            */
/*        \______ \  _____  __  _  __ ____  _____    __ __ _______            */
/*         |    |  \ \__  \ \ \/ \/ //    \ \__  \  |  |  \\_  __ \           */
/*         |    `   \ / __ \_\     /|   |  \ / __ \_|  |  / |  | \/           */
/*        /_______  /(____  / \/\_/ |___|  /(____  /|____/  |__|              */
/*                \/      \/             \/      \/                           */
/*                                                                            */
/* Project:        LED_Matrix                                                 */
/* File:           matrix_led.ino                                             */
/* Started:        apr. 2020                                                  */
/* Last updated:   26 apr.. 2020                                              */
/* License:        MIT (https://opensource.org/licenses/MIT)                  */
/*                                                                            */
/******************************************************************************/

// #include "mapping_std.h"
// #include "mapping_alt.h"
// #include "mapping_alt2.h"
// #include "mapping_alt3.h"
// #include "mapping_alt4.h"
// #include "mapping_alt5.h"
// #include "mapping_alt6.h"
// #include "mapping_alt7.h"
 #include "mapping_alt8.h"

int				g_pin_line[8] = {A0, A1, A2, A3, A4, A5, 10, 11};
int				g_pin_column[8] = {2, 3, 4, 5, 6, 7, 8, 9};
bool			g_matrix[64];
unsigned long	g_echeance;
unsigned long	g_number_h;
unsigned long	g_number_l;

void	setup()
{
	for(int i = 0; i < 8; ++i)
	{
		pinMode(g_pin_line[i], OUTPUT);
		pinMode(g_pin_column[i], OUTPUT);
		digitalWrite(g_pin_line[i], LOW);
		digitalWrite(g_pin_column[i], HIGH);
	}
	g_echeance = millis() + 10;
	g_number_l = 0;
	g_number_h = 0;
	set_dot(0, 0);
}

void	set_dot(int x, int y)
{
	g_matrix[8 * y + x] = 1;
}

void	clear_dot(int x, int y)
{
	g_matrix[8 * y + x] = 0;
}

void	display(void)
{
	for(int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
			digitalWrite(g_pin_line[j], g_matrix[8 * j + i]);
		digitalWrite(g_pin_column[i], LOW);
		delayMicroseconds(10);
		digitalWrite(g_pin_column[i], HIGH);
	}
}


void	loop()
{
	if (millis() > g_echeance)
	{
		g_echeance += 42;
		g_number_l = (g_number_l + 1) % 0xFFFFFFFF;
		if (g_number_l == 0)
			++g_number_h;
		for (int i = 0; i < 64; ++i)
		{
			if (g_mapping[i] < 32)
				g_matrix[i] = (g_number_l >> g_mapping[i]) & 1;
			else
				g_matrix[i] = (g_number_h >> (g_mapping[i] - 32)) & 1;
		}
	}
	display();
}
