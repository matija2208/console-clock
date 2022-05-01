#include <iostream>

int get_time(int& days, int& month, int& year, int& hours, int& minutes, int& seconds, int tHours)
{
	static unsigned long long t1;
	unsigned long long t = time(NULL);
	t += tHours * 3600;
	if (t1 == t)
	{
		return 1;
	}
	t1 = t;
	days = t / 86400 + 1;
	t %= 86400;
	hours = t / 3600;
	t %= 3600;
	minutes = t / 60;
	t %= 60;
	seconds = t;

	year = 1970;
	int n_of_days_in_a_year;
	while (days >= (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? n_of_days_in_a_year = 366, 366 : n_of_days_in_a_year = 365, 365))
	{
		days -= n_of_days_in_a_year;
		year++;
	}
	int n_of_days_in_a_month[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	month = 0;
	int temporary;
	while (days >= ((n_of_days_in_a_year == 366 && month == 1) ? temporary = 29, 29 : temporary = n_of_days_in_a_month[month], temporary))
	{
		days -= temporary;
		month++;
	}
	return 0;
}

int toInt(double x)
{
	if (x - int(x) > 0.5)
	{
		return int(x) + 1;
	}
	else
	{
		return int(x);
	}
}

void get_point_for_seconds(int seconds, int& x, int& y)
{
	double angle = (3.14 / 30.0) * (seconds * 1.0);
	double radius = 15.0;
	y = abs(toInt(radius * cos(angle)) - 19);
	x = toInt(radius * sin(angle)) + 19;
}
void get_point_for_minutes(int minutes, int& x, int& y)
{
	double angle = (3.14 / 30.0) * (minutes * 1.0);
	double radius = 13.0;
	y = abs(toInt(radius * cos(angle)) - 19);
	x = toInt(radius * sin(angle)) + 19;
}
void get_point_for_hours(int hours, int& x, int& y)
{
	if (hours > 12)
	{
		hours -= 12;
	}
	double angle = (3.14 / 6.0) * (hours * 1.0);
	double radius = 11.0;
	y = abs(toInt(radius * cos(angle)) - 19);
	x = toInt(radius * sin(angle)) + 19;
}

void draw_line(char canvas[39][79], int n, int m, int x, int y, char brush)
{
	float Y = n / 2;
	float X = m / 2 - 1;
	float yi;
	float xi;
	int steps;
	int dx = 2 * x - X;
	int dy = y - Y;

	canvas[toInt(Y)][toInt(X)] = brush;
	canvas[toInt(Y)][toInt(X) + 1] = brush;

	steps = abs((abs(dx) > abs(dy)) ? dx : dy);

	yi = (dy * 1.0) / (steps * 1.0);
	xi = (dx * 1.0) / (steps * 1.0);

	for (int i = 0; i < steps; i++)
	{
		X += xi;
		Y += yi;
		//std::cout <<i<<" "<< Y << " " << X << std::endl;
		canvas[toInt(Y)][toInt(X)] = brush;
		canvas[toInt(Y)][toInt(X) + 1] = brush;
	}
}

void put_date(char clock[39][79], int day, int month, int year)
{
	char months[12][4] = { "jan","feb","mar","apr","may","jun","jul","avg","sep","oct","nov","dec" };

	char date[15];

	sprintf_s(date, "%02d. %s, %d.", day, months[month], year);

	for (int i = 0; i < 14; i++)
	{
		clock[9][i + 32] = date[i];
	}
}

void fill_callendar(char calendar[13][35], int day, int month, int year)
{
	int day_of_the_week;
	int n_of_days_in_a_month[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		n_of_days_in_a_month[1]++;
	year -= month < 2;
	day_of_the_week = (year + year / 4 - year / 100 + year / 400 + "-bed=pen+mad."[month+1] + day - 1) % 7;
	int dayt = day;
	
	while (dayt > 1)
	{
		dayt --;
		day_of_the_week--;
		if (day_of_the_week < 0)
		{
			day_of_the_week += 7;
		}
	}
	
	if (day_of_the_week > 0)
	{
		dayt -= day_of_the_week;
		month--;
		dayt += n_of_days_in_a_month[month];
	}
	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			char x[3];
			sprintf_s(x, "%02d", dayt);
			if (dayt == day)
			{
				calendar[i * 2 + 2][j * 5 + 1] = 'x';
				calendar[i * 2 + 2][j * 5 + 2] = 'x';
			}
			else
			{
				calendar[i * 2 + 2][j * 5 + 1] = x[0];
				calendar[i * 2 + 2][j * 5 + 2] = x[1];
			}
			
			dayt++;
			if (dayt > n_of_days_in_a_month[month])
			{
				month++;
				dayt = 1;
			}
		}
	}
}

int main()
{
	int year, month, day, hours, minutes, seconds;
	char clock[39][79] =
	{
		"                              ##################                              ",
		"                        ######       XII        ######                        ",
		"                    ####                              ####                    ",
		"                ####                                      ####                ",
		"              ##    XI                                  I     ##              ",
		"            ##                                                  ##            ",
		"          ##                                                      ##          ",
		"        ##                                                          ##        ",
		"      ##                                                              ##      ",
		"      ##                                                              ##      ",
		"    ##  X                                                           II  ##    ",
		"    ##                                                                  ##    ",
		"  ##                                                                      ##  ",
		"  ##                                                                      ##  ",
		"  ##                                                                      ##  ",
		"##                                                                          ##",
		"##                                                                          ##",
		"##                                                                          ##",
		"##                                                                          ##",
		"##IX                                  ##                                 III##",
		"##                                                                          ##",
		"##                                                                          ##",
		"##                                                                          ##",
		"##                                                                          ##",
		"  ##                                                                      ##  ",
		"  ##                                                                      ##  ",
		"  ##                                                                      ##  ",
		"    ##                                                                  ##    ",
		"    ##VIII                                                          IV  ##    ",
		"      ##                                                              ##      ",
		"      ##                                                              ##      ",
		"        ##                                                          ##        ",
		"          ##                                                      ##          ",
		"            ##                                                  ##            ",
		"              ##   VII                                   V    ##              ",
		"                ####                                      ####                ",
		"                    ####                              ####                    ",
		"                        ######        VI        ######                        ",
		"                              ##################                              "
	};
	char calendar[13][35] = {
		" MO | TU | WE | TH | FR | ST | SU ",
		"----+----+----+----+----+----+----",
		"    |    |    |    |    |    |    ",
		"----+----+----+----+----+----+----",
		"    |    |    |    |    |    |    ",
		"----+----+----+----+----+----+----",
		"    |    |    |    |    |    |    ",
		"----+----+----+----+----+----+----",
		"    |    |    |    |    |    |    ",
		"----+----+----+----+----+----+----",
		"    |    |    |    |    |    |    ",
		"----+----+----+----+----+----+----",
		"    |    |    |    |    |    |    "
	};
	int x[3], y[3];

	int tHours;
	std::cout << "Enter your timezone : UTC";
	std::cin >> tHours;
	std::cout << "\033[?25l";
begin:
	if (!get_time(day, month, year, hours, minutes, seconds, tHours))
	{
		//system("cls");
		std::cout << "\033[0;0H";
		fill_callendar(calendar, day, month, year);
		put_date(clock, day, month, year);
		get_point_for_seconds(seconds, x[0], y[0]);
		draw_line(clock, 39, 78, x[0], y[0], '*');
		get_point_for_minutes(minutes, x[1], y[1]);
		draw_line(clock, 39, 78, x[1], y[1], '+');
		get_point_for_hours(hours, x[2], y[2]);
		draw_line(clock, 39, 78, x[2], y[2], '@');

		int t = 0;
		char z[3];
		sprintf_s(z, "%02d", day);
		for (int i = 0; i < 39; i++)
		{
			for (int j = 0; j < 79; j++)
			{
				if (clock[i][j] == '#')
					std::cout << '\333';
				else if (clock[i][j] == '*')
					std::cout << '\260';
				else if (clock[i][j] == '+')
					std::cout << '\261';
				else if (clock[i][j] == '@')
					std::cout << '\262';
				else
					std::cout << clock[i][j];
					
			}
			std::cout << "  ";
			if (i == 0)
			{
				char MONTH[12][10] = {
					"JANUARY  ",
					"FEBRUARY ",
					"MARCH    ",
					"APRIL    ",
					"MAY      ",
					"JUNE     ",
					"JULY     ",
					"AUGUST   ",
					"SEPTEMBER",
					"OCTOBER  ",
					"NOVEMBER ",
					"DECEMBER "
				};
				char t[36];
				sprintf_s(t, " %s                  %04d. ", MONTH[month], year);
				std::cout << t;
			}
			else if (i > 0 && i < 14)
			{
				for (int j = 0; j < 35; j++)
				{
					if (calendar[i-1][j] == 'x')
					{
						if (t == 0)
						{
							std::cout << "\033[32m" << z[0];
							t++;
						}
						else if (t == 1)
						{
							std::cout << z[1] << "\033[0m";
							t++;
						}
						else if (t == 2)
						{
							std::cout << z[0];
							t++;
						}
						else
						{
							std::cout << z[1];
							t++;
						}
						
					}
					else if (i == 1 && calendar[i-1][j] != ' ' && calendar[i-1][j] != '|')
					{
						std::cout << "\033[38;2;160;160;160m" << calendar[i - 1][j] << "\033[0m";
					}
					else if (calendar[i-1][j] == '|' || calendar[i-1][j] == '-' || calendar[i-1][j] == '+')
					{
						std::cout << "\033[38;2;128;128;128m" << calendar[i-1][j] << "\033[0m";
					}
					else
					{
						std::cout << calendar[i-1][j];
					}
				}
			}

			std::cout << std::endl;
		}
		draw_line(clock, 39, 78, x[0], y[0], ' ');
		draw_line(clock, 39, 78, x[1], y[1], ' ');
		draw_line(clock, 39, 78, x[2], y[2], ' ');
	}

	goto begin;

	return 0;
}
