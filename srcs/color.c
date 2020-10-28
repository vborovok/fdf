#include "../fdf.h"

void		change_color_pair(void)
{
    static int i = 0;
    t_colorpair color_array[NUMBER_OF_COLOR_PAIRS];

    color_array[0] = (t_colorpair){BLUE_COLOR, RED_COLOR};
	color_array[1] = (t_colorpair){PINK_COLOR, YELLOW_COLOR};
	color_array[2] = (t_colorpair){PURPLE_COLOR, PINK_COLOR};
	color_array[3] = (t_colorpair){BLUE_COLOR, GREEN_COLOR};

    g_color_pair = color_array[i];
    i = (i + 1) % NUMBER_OF_COLOR_PAIRS;
}

static double percent(int start, int end, int current)
{
    double placement;
    double distance;

    placement = current - start;
    distance = end - start;
    return ((distance == 0) ? 1.0 : (placement / distance));
}

static int get_light(int start, int end, double percentage)
{
    return ((int)((1 - percentage) * start + percentage * end));
}

static int gradient(t_coord start, t_coord end, t_coord delta, t_coord current)
{
    int     red;
    int     green;
    int     blue;
    double  percentage;

    if (delta.x > delta.y)
        percentage = percent(start.x, end.x, current.x);
    else
        percentage = percent(start.y, end.y, current.y);
    red = get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percentage);
    green = get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percentage);
    blue = get_light(start.color & 0xFF, end.color & 0xFF, percentage);
    return ((red << 16) | (green << 8) | blue);
}

int     get_color(t_coord start, t_coord end, t_coord delta, t_coord current)
{
    if (start.bump && end.bump)
        return g_color_pair.bump;
    if (start.bump || end.bump) {

// temporary solution
/**/    start.color = g_color_pair.base;
/**/    end.color = g_color_pair.bump;
/**/    if (start.bump) {
/**/        end.color = g_color_pair.base;
/**/        start.color = g_color_pair.bump;
/**/    }
/**/
        return gradient(start, end, delta, current);
    }
    return g_color_pair.base;
}