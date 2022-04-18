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
	int n_of_days_in_a_month[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	month = 1;
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
	int dx = 2*x - X;
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

int main()
{
	int year,month,day,hours,minutes,seconds;
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
		"              ##   VII                                  V    ##              ",
		"                ####                                      ####                ",
		"                    ####                              ####                    ",
		"                        ######        VI        ######                        ",
		"                              ##################                              "
	};

	int x[3], y[3];
	
	int tHours;
	std::cout << "Enter your timezone : UTC";
	std::cin >> tHours;
	
	begin:
	if (!get_time(day, month, year, hours, minutes, seconds, tHours))
	{
		//system("cls");
		std::cout << "\033[0;0H";
		get_point_for_seconds(seconds, x[0], y[0]);
		draw_line(clock, 39, 78, x[0], y[0], '*');
		get_point_for_minutes(minutes, x[1], y[1]);
		draw_line(clock, 39, 78, x[1], y[1], '+');
		get_point_for_hours(hours, x[2], y[2]);
		draw_line(clock, 39, 78, x[2], y[2], '@');
		for (int i = 0; i < 39; i++)
		{
			for (int j = 0; j < 79; j++)
			{
				if (clock[i][j] != '#')
					std::cout << clock[i][j];
				else
					std::cout << '\333';
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