#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

#define DEBUG 0

#define MAX_DIFF_TYPES_INGREDIENTS 10
#define MAX_INGREDIENTS_OF_TYPE 10
#define MAX_VERTEX 7
#define MAX_LEN_INGREDIENT_NAME 32

typedef double distance_t;
typedef double angle_t;

typedef struct
{
  distance_t x;
  distance_t y;
} point_t;

typedef struct
{
  distance_t x;
  distance_t y;
} vector_t;

typedef struct
{
  angle_t start;
  angle_t offset;
} angleInterval_t;

typedef struct
{
  point_t center;
  distance_t radius;
} circle_t;

typedef struct
{
  int edges;
  point_t center;
  point_t firstVertex;
  point_t vertex[MAX_VERTEX];
  angleInterval_t shadowInterval1;
  angleInterval_t shadowInterval2;
} polygon_t;

typedef struct
{
  char name[MAX_LEN_INGREDIENT_NAME];
  int edges;
  int n_items;
  polygon_t items[MAX_INGREDIENTS_OF_TYPE];
} ingredient_t;

#if DEBUG
static inline void printPoint (point_t p)
{
  fprintf(stderr, "(%f, %f)", p.x, p.y);
}

static inline void printVector (vector_t v)
{
  fprintf(stderr, "<%f, %f>", v.x, v.y);
}

static inline void printCircle (circle_t c)
{
  fprintf(stderr, "Center: ");
  printPoint(c.center);
  fprintf(stderr, " radius: %f\n", c.radius);
}

static inline void printPolygon (polygon_t p)
{
  int i;
  fprintf(stderr, "Center: ");
  printPoint(p.center);
  fprintf(stderr, " %d vertex:\n", p.edges);
  for (i = 0; i < p.edges; i++)
  {
    fprintf(stderr, "\t");
    printPoint(p.vertex[i]);
    fprintf(stderr, "\n");
  }
}

static inline void printIngredient (ingredient_t ingr)
{
  int i;
  fprintf(stderr, "%s: %d edges %d items\n", ingr.name, ingr.edges, ingr.n_items);
  for (i = 0; i < ingr.n_items; i++)
  {
    fprintf(stderr, "* ");
    printPolygon(ingr.items[i]);
  }
}
#endif

static inline angle_t normalizeAngle (angle_t a)
{
  angle_t n = a;
  while (n <= -M_PI)
  {
    n += 2 * M_PI;
  }
  while (n > M_PI)
  {
    n -= 2 * M_PI;
  }
  return n;
}

static inline angle_t calculateAngleOffset (angle_t from, angle_t to)
{
  angle_t f = normalizeAngle(from);
  angle_t t = normalizeAngle(to);
  angle_t o = t - f;
  if (o < 0)
  {
    o += 2 * M_PI;
  }
  return o;
}

static inline int angleInsideInverval (angle_t a, angleInterval_t i)
{
  angle_t ang = normalizeAngle(a);
  angle_t min = normalizeAngle(i.start);
  angle_t max = min + i.offset;
  angle_t max_n = normalizeAngle(max);
  int ret;

#if DEBUG
  fprintf(stderr, "angleInsideInverval(%f, [%f;;%f])\n", a, i.start, i.offset);
  fprintf(stderr, "\tang %f\tmin %f\tmax %f\tmax_n %f\t(max == max_n) %d\n", ang, min, max, max_n, (max == max_n));
#endif

  if (max == max_n)
  {
    ret = ((ang > min) && (ang < max));
  }
  else
  {
    ret = ((ang > min) || (ang < max_n));
  }

#if DEBUG
  fprintf(stderr, "\tret = %d\n", ret);
#endif
  return ret;
}

static inline int angleInsideAnyInterval (angle_t a, ingredient_t * ingredients, int diff_types_ingredients)
{
  int ret;
  int ingr;
  int item;

  ret = 0;
  for (ingr = 0; ingr < diff_types_ingredients; ingr++)
  {
    for (item = 0; item < ingredients[ingr].n_items; item++)
    {
      if (angleInsideInverval(a, ingredients[ingr].items[item].shadowInterval1))
      {
        ret = 1;
        break;
      }
      if (angleInsideInverval(a, ingredients[ingr].items[item].shadowInterval2))
      {
        ret = 1;
        break;
      }
    }
    if (ret)
    {
      break;
    }
  }

  return ret;
}

static inline vector_t getVector (point_t from, point_t to)
{
  vector_t v;
  v.x = to.x - from.x;
  v.y = to.y - from.y;
  return v;
}

static inline point_t addVector (point_t from, vector_t v)
{
  point_t to;
  to.x = from.x + v.x;
  to.y = from.y + v.y;
  return to;
}

static inline vector_t rotateVector (vector_t v, angle_t a)
{
  vector_t w;
  distance_t x;
  distance_t y;
  x = cos(a);
  y = sin(a);
  w.x = v.x * x - v.y * y;
  w.y = v.x * y + v.y * x;
  return w;
}

static inline angle_t getAngle (vector_t v)
{
  return normalizeAngle(atan2(v.y, v.x));
}

static inline int equalPoints (point_t a, point_t b)
{
  return (a.x == b.x) && (a.y == b.y);
}

// says if the point pt is at one side or the other of the rect that passes
// by cc and has angle ang
static inline int getPointPlacement (point_t pt, point_t cc, angle_t ang)
{
  angle_t angle_pt = getAngle(getVector(cc, pt));
  angle_t angle_diff = ang - angle_pt;
  int ret;

  if (angle_diff > M_PI)
  {
    ret = 1;
  }
  else if ((angle_diff >= 0) && (angle_diff < M_PI))
  {
    ret = 0;
  }
  else if ((angle_diff > -M_PI) && (angle_diff < 0))
  {
    ret = 1;
  }
  else if (angle_diff < -M_PI)
  {
    ret = 0;
  }
  else // ((angle_diff == -M_PI) || (angle_diff == M_PI))
  {
    // should never happen
#if DEBUG
    fprintf(stderr, "!!! We have a problem at line %d\n", __LINE__);
#endif
  }

  return ret;
}

static inline int checkAngle (angle_t a, ingredient_t * ingredients, int diff_types_ingredients, point_t cc)
{
  int ret;
  int ingr;
  int item;
  int forDaniel;
  int forSara;

  ret = 1;
  for (ingr = 0; ingr < diff_types_ingredients; ingr++)
  {
    forDaniel = 0;
    forSara = 0;
    for (item = 0; item < ingredients[ingr].n_items; item++)
    {
      if (getPointPlacement(ingredients[ingr].items[item].center, cc, a))
      {
        forDaniel++;
      }
      else
      {
        forSara++;
      }
    }
    if (forDaniel != forSara)
    {
      ret = 0;
      break;
    }
  }

  return ret;
}

static inline void buildPolygon (polygon_t * pol)
{
  int i;
  angle_t angle;
  vector_t v;
  vector_t v2;

  v = getVector(pol->center, pol->firstVertex);

  pol->vertex[0] = pol->firstVertex;

  for (i = 1; i < pol->edges; i++)
  {
    angle = 2 * i * M_PI / pol->edges;
    v2 = rotateVector(v, angle);
    pol->vertex[i] = addVector(pol->center, v2);
  }
}

static inline int calculateShadowIntervals (point_t cc, polygon_t * pol)
{
  int ret;
  angle_t angle_center_pol;
  angle_t angle_vertex;
  angle_t angle_diff;
  angle_t max_ang_back;
  angle_t max_ang_forw;
  int i;
  int center_inside_poligon;

  if (equalPoints(cc, pol->center))
  {
    ret = 0;
  }
  else
  {
    angle_center_pol = getAngle(getVector(cc, pol->center));

    max_ang_back = 0;
    max_ang_forw = 0;

    center_inside_poligon = 0;

    for (i = 0; i < pol->edges; i++)
    {
      if (!equalPoints(cc, pol->vertex[i]))
      {
        angle_vertex = getAngle(getVector(cc, pol->vertex[i]));
        angle_diff = angle_center_pol - angle_vertex;

        if (angle_diff > M_PI)
        {
          angle_diff = 2 * M_PI - angle_diff;
          if (angle_diff > max_ang_forw)
          {
            max_ang_forw = angle_diff;
          }
        }
        else if ((angle_diff >= 0) && (angle_diff < M_PI))
        {
          if (angle_diff > max_ang_back)
          {
            max_ang_back = angle_diff;
          }
        }
        else if ((angle_diff > -M_PI) && (angle_diff < 0))
        {
          angle_diff = -angle_diff;
          if (angle_diff > max_ang_forw)
          {
            max_ang_forw = angle_diff;
          }
        }
        else if (angle_diff < -M_PI)
        {
          angle_diff += 2 * M_PI;
          if (angle_diff > max_ang_back)
          {
            max_ang_back = angle_diff;
          }
        }
        else // ((angle_diff == -M_PI) || (angle_diff == M_PI))
        {
          center_inside_poligon = 1;
          break;
        }
      }
    }

    if (center_inside_poligon)
    {
      ret = 0;
    }
    else if (max_ang_back + max_ang_forw > M_PI)
    {
      ret = 0;
    }
    else
    {
      pol->shadowInterval1.start = normalizeAngle(angle_center_pol - max_ang_back);
      pol->shadowInterval1.offset = max_ang_back + max_ang_forw;
      pol->shadowInterval2.start = normalizeAngle(M_PI + angle_center_pol - max_ang_back);
      pol->shadowInterval2.offset = max_ang_back + max_ang_forw;

      ret = 1;
    }
  }

  return ret;
}

/*
 * MinGW does not provide getline.
 * This is my own implementation, behaving like the standard says, except with the following:
 * - When a newline is found, only '\n' is written at the end of the returned string, even if
 *   a Windows-like newline ("\r\n") is found.
 * - Carriage return characters ('\r') are only supported if they come just before line feed ones ('\n'),
 *   ie: only in Windows-like newlines. Otherwise, they are silenty omitted.
 */
#define GETLINE_INITIAL_SIZE 32
static inline ssize_t getline (char ** lineptr, size_t * n, FILE * stream)
{
  ssize_t ret;
  int c;
  int finish_loop;

  if ((lineptr == NULL) || (n == NULL) || (stream == NULL))
  {
    ret = -1;
    errno = EINVAL;
  }
  else
  {
    if (*lineptr == NULL)
    {
      *n = GETLINE_INITIAL_SIZE;
      *lineptr = (char *)malloc(GETLINE_INITIAL_SIZE);
    }
    else if (*n == 0)
    {
      *n = GETLINE_INITIAL_SIZE;
      *lineptr = (char *)realloc(*lineptr, GETLINE_INITIAL_SIZE);
    }

    ret = 0;

    finish_loop = 0;
    while (!finish_loop && (c = fgetc(stream)) != EOF)
    {
      if (c == '\n')
      {
        finish_loop = 1;
      }

      if (c != '\r')
      {
        /* write char */
        
        if (ret == (ssize_t)*n)
        {
          *n *= 2;
          *lineptr = (char *)realloc(*lineptr, *n);
        }

        (*lineptr)[ret] = (char)c;
        ret++;
      }
    }

    if (ret == 0)
    {
      /* EOF at the start of the reading */
      ret = -1;
    }
    else
    {
      if (ret == (ssize_t)*n)
      {
        (*n)++;
        *lineptr = (char *)realloc(*lineptr, *n);
      }
      (*lineptr)[ret] = '\0';
    }
  }

  return ret;
}

int main (void)
{
  char * line;
  char * line_ptr;
  size_t size;
  FILE * input_data_file;
  int n_test_cases;
  int test_case;
  circle_t pizza;
  int diff_types_ingredients;
  int ingr;
  ingredient_t ingredients[MAX_DIFF_TYPES_INGREDIENTS];
  int i;
  int item;
  int impossible;
  const char * test_case_result;

  // save input data, just for review
  input_data_file = fopen("input_data.txt", "w");

  line = NULL;
  size = 0;

  getline(&line, &size, stdin);
  fprintf(input_data_file, "%s", line);

  sscanf(line, "%d", &n_test_cases);

#if DEBUG
  fprintf(stderr, "We are going to do %d test cases. Are you ready?\n\n", n_test_cases);
#endif

  for (test_case = 1; test_case <= n_test_cases; test_case++)
  {
    getline(&line, &size, stdin);
    fprintf(input_data_file, "%s", line);

    sscanf(line, "%lf %lf %lf", &pizza.center.x, &pizza.center.y, &pizza.radius);

    getline(&line, &size, stdin);
    fprintf(input_data_file, "%s", line);

    sscanf(line, "%d", &diff_types_ingredients);

    for (ingr = 0; ingr < diff_types_ingredients; ingr++)
    {
      getline(&line, &size, stdin);
      fprintf(input_data_file, "%s", line);

      // copy the name (just for having it), but no more than MAX_LEN_INGREDIENT_NAME chars
      // and yes, I'm to lazy to use strncpy together with sscanf below :/
      for (i = 0; (i < MAX_LEN_INGREDIENT_NAME) && !isspace(line[i]); i++)
      {
        ingredients[ingr].name[i] = line[i];
      }
      if (i == MAX_LEN_INGREDIENT_NAME)
      {
        ingredients[ingr].name[MAX_LEN_INGREDIENT_NAME - 1] = '\0';
      }
      else
      {
        ingredients[ingr].name[i] = '\0';
      }

      // jump the rest of the name and the following space
      while (!isspace(line[i]))
      {
        i++;
      }
      while (isspace(line[i]))
      {
        i++;
      }

      line_ptr = line + i;

      sscanf(line_ptr, "%d %d", &ingredients[ingr].edges, &ingredients[ingr].n_items);

      // read the items (ingredients of the same type)
      for (item = 0; item < ingredients[ingr].n_items; item++)
      {
        getline(&line, &size, stdin);
        fprintf(input_data_file, "%s", line);

        sscanf(line, "%lf %lf %lf %lf",
            &ingredients[ingr].items[item].center.x,
            &ingredients[ingr].items[item].center.y,
            &ingredients[ingr].items[item].firstVertex.x,
            &ingredients[ingr].items[item].firstVertex.y);

        ingredients[ingr].items[item].edges = ingredients[ingr].edges;
        buildPolygon(&ingredients[ingr].items[item]);
      }
    }

#if DEBUG
    fprintf(stderr, "#### * Test case %d:\n", test_case);

    fprintf(stderr, "Pizza: ");
    printCircle(pizza);

    fprintf(stderr, "%d diff ingredients:\n", diff_types_ingredients);
    for (i = 0; i < diff_types_ingredients; i++)
    {
      fprintf(stderr, "Ingredient %d: ", i);
      printIngredient(ingredients[i]);
    }

    fprintf(stderr, "\n");    
#endif

    // we already have all the data we need to solve this test case. Go!
#if DEBUG
    fprintf(stderr, "Data collected. Go!...\n");
#endif

    impossible = 0;

    for (ingr = 0; ingr < diff_types_ingredients; ingr++)
    {
      if (ingredients[ingr].n_items % 2 == 0)
      {
        for (item = 0; item < ingredients[ingr].n_items; item++)
        {
          if (!calculateShadowIntervals(pizza.center, &ingredients[ingr].items[item]))
          {
            impossible = 1;
#if DEBUG
            fprintf(stderr, "!! Impossible shadow intervals ingr %d item %d\n", ingr, item);
#endif
            break;
          }
        }
      }
      else
      {
        impossible = 1;
#if DEBUG
        fprintf(stderr, "!! There are an odd number of items of ingredient %d\n", ingr);
#endif
      }

      if (impossible)
      {
        break;
      }
    }

    if (!impossible)
    {
      // assume it is not possible. if it is, just break all the loops and exit
      impossible = 1;

      // the angle of the cut, if any, is (or can be) the start of an interval.
      // go through all intervals and see if we can use that angle
      for (ingr = 0; ingr < diff_types_ingredients; ingr++)
      {
        for (item = 0; item < ingredients[ingr].n_items; item++)
        {
          if (!angleInsideAnyInterval(ingredients[ingr].items[item].shadowInterval1.start, ingredients, diff_types_ingredients))
          {
            if (checkAngle(ingredients[ingr].items[item].shadowInterval1.start, ingredients, diff_types_ingredients, pizza.center))
            {
              // found!
              impossible = 0;
#if DEBUG
              fprintf(stderr, "Found good angle ingr %d item %d\n", ingr, item);
#endif
              break;
            }
          }
        }
        if (!impossible)
        {
          break;
        }
      }
    }

    if (impossible)
    {
      test_case_result = "FALSE";
    }
    else
    {
      test_case_result = "TRUE";
    }

#if DEBUG
    fprintf(stderr, "Result: %s (%d)\n", test_case_result, impossible);
#endif

    printf("Case #%d: %s\n", test_case, test_case_result);
  }

  free(line);

  fclose(input_data_file);

  return 0;
}
